#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  SEV interaction pattern recipe specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
# Chamber of commerce Rotterdam nr.276339, The Netherlands
#--------------------------------------------------------------------

module AxciomaPC

  module SEV

    # register NDDS IDL generation project
    DataIDLExtension.dds_idl_gen_prj << :ddsx11_ndds_idl_gen

  end # SEV

end
