#--------------------------------------------------------------------
# @file    util.rb
# @author  Marijke Hengstmengel
#
# @brief   General utils
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------
require 'pathname'

module AxciomaPC

  module Util

    def self.path_rel_to_path (path, path_rel_to)
      p = Pathname.new(path)
      p.relative_path_from(Pathname.new(path_rel_to))
    end

    def self.path_without_env (path)
      #Find each $(...) in path with gsub and substitute with the solved environment variable
      #use match.match()[1] to get the value between $( and ) , for using in ENV .
   #   new_path = path.gsub(/\$\((.*?)\)/) {|match| ENV[match.match(/\$\((.*?)\)/)[1]]}
      #Use the brix11 environment variable if set, else use the user set environment variable
      new_path = path.gsub(/\$\((.*?)\)/) { |match| BRIX11::Exec.get_run_environment(match.match(/\$\((.*?)\)/)[1], true) }
    end

  end

end # AxciomaPC
