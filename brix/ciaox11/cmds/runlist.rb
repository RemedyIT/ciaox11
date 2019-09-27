#--------------------------------------------------------------------
# @file    runlist.rb
# @author  Martin Corino
#
# @brief   Run an ACE auto_run_test regression test list.
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------
require 'brix11/command'

module BRIX11
  module CIAOX11

    class RunList < TAOX11::RunList

      # setup
      def self.setup(optparser, options)
        # base setup
        TAOX11::RunList.setup(optparser, options)
        # add debug/release options for windows environment
        if Sys.mswin?
          optparser.on('--debug',
                       'Run tests using Debug deployment environment (only applicable for msvc/icc builds).' ) { options[:runlist][:debug] = true }
          optparser.on('--release',
                       'Run tests using Release deployment environment (only applicable for msvc/icc builds).' ) { options[:runlist][:debug] = false }
        end
      end

      # override
      def run(argv)
        # do we need debug runtimes?
        if Sys.mswin? && options[:runlist][:debug]
          # set debug runtime env
          options[:runlist][:runopts][:env] = { 'DANCEX11_BIN_FOLDER' => 'bin\Debug' }
        end
        # call super
        super
      end

      Command.register('run:list', TAOX11::RunList::DESC, CIAOX11::RunList, true)
    end # RunList

  end # CIAOX11
end # BRIX11
