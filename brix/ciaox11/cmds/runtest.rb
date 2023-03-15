#--------------------------------------------------------------------
# @file    runtest.rb
# @author  Martin Corino
#
# @brief   Run (regression) test script.
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'brix11/command'

module BRIX11
  module CIAOX11
    class RunTest < TAOX11::RunTest
      # setup
      def self.setup(optparser, options)
        # base setup
        TAOX11::RunTest.setup(optparser, options)
        # add debug/release options for windows environment
        if Sys.mswin?
          optparser.on('--debug',
                       'Run test using Debug deployment environment (only applicable for msvc/icc builds).') { options[:runtest][:debug] = true }
          optparser.on('--release',
                       'Run test using Release deployment environment (only applicable for msvc/icc builds).') { options[:runtest][:debug] = false }
        end
      end

      public

      # override
      def run(argv)
        # do we need debug runtimes?
        if Sys.mswin? && options[:runtest][:debug]
          # set debug runtime env
          options[:runtest][:runopts][:env] = { 'DANCEX11_BIN_FOLDER' => 'bin\Debug' }
        end
        # call super
        super
      end

      Command.register('run:test|script', TAOX11::RunTest::DESC, CIAOX11::RunTest, true)
    end # RunTest
  end # CIAOX11
end # BRIX11
