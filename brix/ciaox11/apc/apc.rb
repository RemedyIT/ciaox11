#--------------------------------------------------------------------
# @file    apc.rb
# @author  Marijke Hengstmengel
#
# @brief   Axcioma Project Creator
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------#

module AxciomaPC
  COPYRIGHT = 'Copyright (c) 2012 Remedy IT Expertise BV, The Netherlands'.freeze

  RECIPE_FILE_EXT = 'aprc'.freeze

  OPTIONS = {
  }

  def self.root_path
    f = File.expand_path(__FILE__)
    f = File.expand_path(File.readlink(f)) if File.symlink?(f)
    r = File.dirname(f)
    $: << r unless $:.include?(r)
    r
  end

  APC_ROOT = self.root_path

end # AxciomaPC

Dir.glob(File.join(AxciomaPC::APC_ROOT, '*.rb')).each do |fnm|
  require File.basename(fnm) unless File.basename(fnm) == 'apc.rb'
end
