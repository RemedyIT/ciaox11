#--------------------------------------------------------------------
# @file    connector.rb
# @author  Marijke Hengstmengel
#
# @brief   ExF Connector recipe extension
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  # reopen recipe class
  class ConnectorRecipe < Recipe
    # reopen recipe configurator class
    class ConnectorConfigurator < Recipe::Configurator
      # add use_exf property
      def use_exf(flag)
        @recipe.exf(flag)
      end
    end

    # add exf property
    def exf(flag = nil)
      @exf = (flag == true) unless flag.nil?
      @exf ? true : false # make sure to return true or false even is attribute is nil
    end
  end

end
