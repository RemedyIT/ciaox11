#!/usr/bin/env ruby
#--------------------------------------------------------------------
# @file    convert_plan.rb
# @author  Marijke Hengstmengel
#
# @brief   Script to convert a CIAO cdp to an AXCIOMA cdp plan. This script
#          only replaces the names of the execParameters and removes the
#          not needed local deploy requirements. It doesn't add CORBA
#          connectors when synchronous request/reply is being used
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
$: << File.dirname(__FILE__)

require 'optparse'
require 'fileutils'
require 'tempfile'

$NlRemedyIt = "nl.remedy.it"
$DnCx11_pre  = $NlRemedyIt +".DnCX11"
$EduVdrBilt = "edu.vanderbilt.dre"
$EdudrVBilt = "edu.dre.vanderbilt"
$CIAO_pre = $EduVdrBilt + ".CIAO"
$DAnCE_pre = $EduVdrBilt + ".DAnCE"
$DAnCE_pre2 = $EdudrVBilt + ".DAnCE"


#The last 3 lines should always stay at the end of this hash.
$conversion_hash = {"#{$DAnCE_pre}.LocalityUUID" => "#{$DnCx11_pre}.DnCX11.Locality. " ,
                    "#{$DAnCE_pre}.LocalityTimeout" => "#{$DnCx11_pre}.Locality.Timeout",
                    "#{$DAnCE_pre}.LocalityArguments" => "#{$DnCx11_pre}.Locality.Arguments",
                    "#{$DAnCE_pre}.LocalityExec" => "#{$DnCx11_pre}.Locality.Exec",
                    "#{$DAnCE_pre}.LocalityMultithread" => "#{$DnCx11_pre}.Locality.Multithread",
                    "#{$EduVdrBilt}.CCM." => "#{$NlRemedyIt}.CCM.",
                    "home factory" => "#{$DnCx11_pre}.Home.Factory",
                    "component factory" => "#{$DnCx11_pre}.Executor.Factory",
                    "#{$CIAO_pre}.ExecutorArtifact" => "#{$DnCx11_pre}.Executor.Artifact",
                    "#{$CIAO_pre}.ServantEntrypoint" => "#{$DnCx11_pre}.Servant.Factory",
                    "#{$CIAO_pre}.ServantArtifact" => "#{$DnCx11_pre}.Servant.Artifact",
                    "#{$DAnCE_pre2}"=>"#{$DnCx11_pre}",
                    "#{$DAnCE_pre}"=>"#{$DnCx11_pre}",
                    "#{$CIAO_pre}"=>"#{$DnCx11_pre}",
                    $EduVdrBilt => $NlRemedyIt
                   }

$local_interface_array = ["<deployRequirement>",
                          "<name>#{$DnCx11_pre}.ConnectionType</name>",
                          "<resourceType>Local_Interface</resourceType>",
                          "</deployRequirement>"
                         ]


module CIAOX11_Plan_Converter

  def self.convert_plan(options)
    file_tmp = Tempfile.new("cdp_out")
    @line_nr = 0
    File.open(options[:cdp_plan_in], "r").each_line do |line|
      @line_nr +=1
      $conversion_hash.each_pair do |key, value|
        if line.include?(key)
          line.sub!(key, value)
          if options[:logging]
            puts "#{@line_nr} Line Changing <#{key}>  to <#{value}> "
          end
          break
        end
      end #  until found
      file_tmp.write(line)
    end
    # We now have a temp file, where changes defined in conversion_hash has taken place
    # now we loop again to delete obsolete lines
    output_file = File.open(options[:cdp_plan_out], "w")

    # Remove_local_interface
    file_tmp.rewind
    start_line = 0
    line1, line2, line3 = ""
    @line_nr =0
    file_tmp.each_line do |line|
      @line_nr +=1
      case start_line
      when 0
        if line.include?($local_interface_array[0])
          start_line = 1
          line1 = line
        else
          output_file.write(line)
        end
      when 1
        if line.include?($local_interface_array[1])
          start_line = 2
          line2 = line
        else
          # Although found local_interface_array[0] in line 1,
          # not found local_interface_array[1] in next line,
          # so write both line1 and current line to output file
          start_line = 0
          output_file.write(line1)
          output_file.write(line)
          line1 = ""
        end
      when 2
        if line.include?($local_interface_array[2])
          start_line = 3
          line3 = line
        else
          start_line = 0
          output_file.write(line1)
          output_file.write(line2)
          output_file.write(line)
          line1, line2 = ""
        end
      when 3
        if line.include?($local_interface_array[3])
          # All 4 lines are there , so skip these and start again with start_line 0
          if options[:logging]
            begin_line = @line_nr - 3
            puts "Lines #{begin_line} to #{@line_nr} from the original plan are deleted."
          end
          start_line = 0
        else
          start_line = 0
          output_file.write(line1)
          output_file.write(line2)
          output_file.write(line3)
          line1, line2, line3 = ""
          output_file.write(line)
        end
      else
        #nothing shouldn't happen
      end
    end
    file_tmp.close!()
  end

  def self.check_input_file_name (filename)
    ret = false
    if !File.file?(filename)
      puts "Error, input plan <#{filename}> doesn't exist"
    else
      if File.extname(filename).casecmp(".cdp") != 0
        puts "Error, extension of input plan file <#{filename}> must be '.cdp'"
      else
        ret = true
      end
    end
    ret
  end

  def self.check_output_file_name (filename)
    ret = false
    dirname = File.dirname (filename)
    if !File.directory?(dirname)
      puts "Error, directory <#{dirname}> for output plan <#{filename}> doesn't exist"
    else
      if !File.extname(filename).eql?(".cdp")
        puts "Error, extension of output plan file <#{filename}> must be '.cdp'"
      else
        ret = true
      end
    end
    ret
  end

  def self.run(options)
    if (check_input_file_name(options[:cdp_plan_in]) && check_output_file_name(options[:cdp_plan_out]))
      puts "Starting conversion deploymentplan in #{options[:cdp_plan_in]}"
      self.convert_plan(options)
    end
  end
end

options = {:cdp_plan_in => nil, :cdp_plan_out => nil, :logging =>false}

script_name = File.basename($0, '.*')
if not script_name =~ /convert_plan/
  script_name = 'ruby '+$0
end
parser = OptionParser.new do|opts|
  opts.banner = "Usage: #{script_name} [options]"
  opts.on('-i', '--input plan', 'Filename for input plan (*.cdp)') do |in_plan|
    options[:cdp_plan_in] = in_plan;
  end

  opts.on('-o', '--output plan', 'Filename for output plan (*.cdp)') do |out_plan|
    options[:cdp_plan_out] = out_plan;
  end

  opts.on('-l', '--log', 'Logging the line numbers of changed lines') do |log|
    options[:logging] = true
  end

  opts.on('-h', '--help', 'Displays Help') do
    puts opts
    exit
  end
end

parser.parse!

if options[:cdp_plan_in] == nil
  begin
    print 'Enter filename of input cdp plan: '
    input_file = gets.chomp
    if (CIAOX11_Plan_Converter::check_input_file_name(input_file))
      options[:cdp_plan_in] = input_file
    end
  end until  options[:cdp_plan_in] != nil
end

if options[:cdp_plan_out] == nil
  begin
    print 'Enter filename of output cdp plan: '
    output_file = gets.chomp
    if (CIAOX11_Plan_Converter::check_output_file_name(output_file))
      options[:cdp_plan_out] = output_file
    end
  end until  options[:cdp_plan_out] != nil
end


CIAOX11_Plan_Converter.run(options)
