#--------------------------------------------------------------------
# @file    require.rb
# @author  Martin Corino
#
# @brief   BRIX11 CIAOX11 brix collection loader
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module BRIX11

  module CIAOX11

    ROOT = File.dirname(__FILE__)
    TITLE = 'CIAOX11'.freeze
    DESC = 'BRIX11 CIAOX11 brix collection'.freeze
    COPYRIGHT = "Copyright (c) 2014-#{Time.now.year} Remedy IT Expertise BV, The Netherlands".freeze
    VERSION = {major: 0, minor: 1, release: 0}

    Collection.configure(:ciaox11, ROOT, TITLE, DESC, COPYRIGHT, VERSION) do |cfg|

      # declare dependency on :taox11 collection (forces it to load first)
      cfg.add_collection(:taox11)

      cfg.on_setup do |optparser, options|
        if Exec.mswin?
          search_path_env = 'PATH'
        else
          search_path_env = 'LD_LIBRARY_PATH'
        end
        # define common environment for spawning BRIX11 subprocesses
        base_root = Exec.get_run_environment('TAOX11_BASE_ROOT') || ''
        ciaox11_root = Exec.get_run_environment('CIAOX11_ROOT')
        ciaox11_root ||= Exec.update_run_environment('CIAOX11_ROOT', File.dirname(File.dirname(CIAOX11::ROOT)))
        unless dancex11_root = Exec.get_run_environment('DANCEX11_ROOT')
          if File.directory?(File.expand_path(File.join(ciaox11_root, '..', 'dancex11')))
            dancex11_root = Exec.update_run_environment('DANCEX11_ROOT', File.expand_path(File.join(ciaox11_root, '..', 'dancex11')))
          elsif File.directory?(File.expand_path(File.join(ciaox11_root, '..', 'DANCEX11')))
            dancex11_root = Exec.update_run_environment('DANCEX11_ROOT', File.expand_path(File.join(ciaox11_root, '..', 'DANCEX11')))
          end
        end

        # should we prepare for crossbuilds?
        if BRIX11.options.config.crossbuild
          x11_host_root = (Exec.get_run_environment('X11_HOST_ROOT') || '')
          # update library search paths for host (tool) libs
          Exec.update_run_environment(search_path_env, [File.join(x11_host_root, 'ciaox11', 'lib'), File.join(x11_host_root, 'dancex11', 'lib')], :append)
          # update executable search path for host deployment tools
          Exec.update_run_environment('PATH', [File.join(x11_host_root, 'ciaox11', 'bin'), File.join(x11_host_root, 'dancex11', 'bin')], :prepend)
        else # or regular build environment
          # update library search paths for (tool) libs
          Exec.update_run_environment(search_path_env, [File.join(ciaox11_root, 'lib'), File.join(dancex11_root, 'lib')], :append)
          # update executable search path for deployment tools
          Exec.update_run_environment('PATH', [File.join(ciaox11_root, 'bin'), File.join(dancex11_root, 'bin')], :prepend)
        end

        Exec.update_run_environment('RIDL_BE_SELECT', 'ccmx11') unless ENV['RIDL_BE_SELECT'] && BRIX11.use_environment?
        unless ENV['RIDL_BE_PATH'] && BRIX11.use_environment?
          # update ridl backend search path taking crossbuild config into account
          ciaox11_be_path = if BRIX11.options.config.crossbuild
                              File.join(x11_host_root, 'ciaox11')
                            else
                              ciaox11_root
                            end
          ridl_be_path = Exec.update_run_environment(
                              'RIDL_BE_PATH',
                              ciaox11_be_path,
                              :append)
          ridl_be_path.split(/:|;/).each { |p| $: << p unless $:.include?(p) }
        end

        # update documentation config
        Common::GenerateDocumentation::OPTIONS[:docsources].merge!({
            'ciaox11' => ['${CIAOX11_ROOT}/docs'],
            'ddsx11'    => ['${CIAOX11_ROOT}/ddsx11/docs'],
            'tt4ccm'    => ['${CIAOX11_ROOT}/connectors/tt4ccm/docs'],
            'corba4ccm' => ['${CIAOX11_ROOT}/connectors/corba4ccm/docs'],
            'ami4ccm'   => ['${CIAOX11_ROOT}/connectors/ami4ccm/docs',
                            '${CIAOX11_ROOT}/connectors/ami4ccm/tutorials/hello/tutorial'],
            'dds4ccm'   => ['${CIAOX11_ROOT}/connectors/dds4ccm/docs'],
            'dancex11'  => ['${DANCEX11_ROOT}/docs']
          })
        Common::GenerateDocumentation::OPTIONS[:adoc_attribs]['ciaox11_src_root'] = Exec.get_run_environment('CIAOX11_ROOT')
        Common::GenerateDocumentation::OPTIONS[:adoc_attribs]['dancex11_src_root'] = Exec.get_run_environment('DANCEX11_ROOT')
      end

    end

    Dir.glob(File.join(ROOT, 'cmds', '*.rb')).each { |p| require "brix/ciaox11/cmds/#{File.basename(p)}"}
  end

end
