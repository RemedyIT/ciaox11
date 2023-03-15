#--------------------------------------------------------------------
# @file    mpc_idl.rb
# @author  Marijke Hengstmengel
#
# @brief   mpc registry for idl projects
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'pathname'
require 'ostruct'

module AxciomaPC
  module MPC
    # class to efficiently keep track of IDL compiler flags
    # that need to be added (+=) or removed (-=) in MPC
    # uses Util::Flags to prevent duplicates
    class IDLFlags
      def initialize(add_f = nil, del_f = nil)
        if Util::Flags === add_f
          @idl_add_flags = add_f
        else
          @idl_add_flags = Util::Flags.new
          @idl_add_flags << add_f if add_f
        end
        if Util::Flags === del_f
          @idl_del_flags = del_f
        else
          @idl_del_flags = Util::Flags.new

          self.delete(del_f)
        end
      end

      def add_flags
        @idl_add_flags
      end

      def del_flags
        @idl_del_flags
      end

      def add(val)
        add_f = (Util::Flags === val ? val : Util::Flags.new(val))
        del_f = @idl_del_flags & add_f
        @idl_del_flags.delete(del_f)
        @idl_add_flags << (add_f - del_f)
        self
      end
      alias :<< :add

      def delete(val)
        del_f = (Util::Flags === val ? val : Util::Flags.new(val))
        exist_f = @idl_add_flags & del_f
        @idl_add_flags.delete(exist_f)
        @idl_del_flags << (del_f - exist_f)
        self
      end

      def +(val)
        self.dup << val
      end

      def -(val)
        self.dup.delete(val)
      end

      def dup
        IDLFlags.new(@idl_add_flags, @idl_del_flags)
      end

      def to_s
        "APC::IDLFlags[ += #{@idl_add_flags.join}; -= #{@idl_del_flags.join}]"
      end
    end # IDLFlags

    class IDLProject < MPC::Project

      # registry with default IDLProject settings for the various
      # IDLProject types; derived classes will add to this
      DEFAULTS = {
          comp_gen: {
              add_idl_flags: '-Gcomp -Gxhex -Gxhsv -Scc -Scp -Gex -oI\\ .',
              export: true,
              base_projects: %w{ciaox11_idldefaults},
              idl_extras: 'precious_files += _exec.h\Z _exec.cpp\Z',
              auto_dependencies: %w{}
          },
          idl_gen: {
              add_idl_flags: '-Scc -Scp',
              export: true,
              base_projects: %w{ciaox11_idldefaults},
              auto_dependencies: %w{}
          },
      }

      def initialize(type, recipe)
        super(type, recipe)
        @idl_flags = IDLFlags.new
        @extras = Util::UniqueStringList.new
        DEFAULTS[type].each do |k, v|
          case k
          when :auto_dependencies
            v.each { |adp| project_dependencies << "#{mpc_id}_#{adp}" }
          else
            self.send(k, v)
          end
        end
        @idl_files = Util::UniqueStringList.new
      end

      def idl_flags(val = nil)
        @idl_flags = (IDLFlags === val ? val : IDLFlags.new(val)) if val
        @idl_flags
      end
      alias :idl_flags= :idl_flags

      def add_idl_flags(flags = nil)
        idl_flags.add flags if flags
        idl_flags.add_flags
      end

      def del_idl_flags(flags = nil)
        idl_flags.delete flags if flags
        idl_flags.del_flags
      end

      def export_name
        recipe.export_name
      end

      def gen_dir
        recipe.gen_dir
      end

      def include_dependencies
        includes.to_a + [recipe.full_gen_path]
      end

      def template_path(path = nil)
        @template_path = path if path
        @template_path ||= 'idl'
      end

      # we assume that the idl_flags_min are always processed after the idl_flags_plus!
      def set_stub_flags
        # suppress the disabling of stub generation
        idl_flags.delete '-Scc -Scp'
        idl_flags.add '-Gxhst'
      end

      def export(export_b = false)
         @export = export_b if export_b
         @export
      end

      # return IDL input sources as relative paths wrt current recipe/project
      def sources
        recipe.get_relative_paths(@project_files)
      end

      def includes_flags
        recipe.get_relative_paths(includes).collect { |idir| "-I#{idir}" }.join(' ')
      end

      def idl_extras(extras = nil)
        @extras.assign(extras) if extras
        @extras
      end

      # Methods for MPC project file generation
      def mpc_genobj
        unless @mpc_genobj
          idlflags = idl_flags.add_flags.dup
          if export
            idlflags << "-Wb,base_export_macro=#{export_name.upcase} -Wb,base_export_include=#{export_name.downcase}"
          end
          idlflags << includes_flags
          idlflags << ["-I#{recipe.gen_dir}"]
          # todo, added temporarily, see issue #4337
          idlflags << '-Gos'
          # use StringList#add to skip string splitting
          idlflags.add "-o #{recipe.gen_dir}"
          idl_sections = []
          idl_sources = sources
          other_idl_flags = Util::Flags.new
          # Optimize by making sure export headers are only generated once per project
          if idl_sources.size > 1 && idlflags.include?(/-Gxh/)
            # create first IDL section with only 1 IDL source and
            # add all '-GxhXXX' flags for this section only
            idl_sections << OpenStruct.new(idl_flags_plus: Util::Flags.new,
                                           sources: [idl_sources.shift])
            # add all '-GxhXXX' flags
            idlflags.each { |flag| idl_sections.last.idl_flags_plus.add(flag) if /-Gxh/ =~ flag }
            # add '-Xxxx' flags for all '-GxhXXX' flags to other idl section (except for '-Gxh')
            idl_sections.last.idl_flags_plus.each { |flag| other_idl_flags.add(flag.sub(/-Gxh/, '-X')) if flag != '-Gxh' }
            # Remove all '-GxhXXX' flags from main flags list
            idl_sections.last.idl_flags_plus.each { |flag| idlflags.delete(flag) }
          end
          # add idl section with remaining IDL source files without any flags
          idl_sections << OpenStruct.new(idl_flags_plus: other_idl_flags,
                                         sources: idl_sources)
          # create generator object with main flags lists and section list
          @mpc_genobj = OpenStruct.new(idl_flags_plus: idlflags,
                                       idl_flags_minus: idl_flags.del_flags.dup,
                                       idl_sections: idl_sections)
        end
        @mpc_genobj
      end
      private :mpc_genobj

      # TODO is this true?
      # At the moment there are always plus flags for export ?
      def idl_flags_plus
        mpc_genobj.idl_flags_plus
      end

      def idl_flags_minus
        mpc_genobj.idl_flags_minus
      end

      def idl_sections
        mpc_genobj.idl_sections
      end

    end # IDLProject
  end # MPC
end # AxciomaPC
