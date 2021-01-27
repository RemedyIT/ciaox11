#--------------------------------------------------------------------
# @file    recipe_ext.rb
# @author  Martin Corino
#
# @brief  SEV interaction pattern recipe specializations
#
# @copyright Copyright (c) Remedy IT Expertise BV
#--------------------------------------------------------------------

module AxciomaPC

  module SEV

    # register OpenDDS IDL generation project
    DataIDLExtension.dds_idl_gen_prj << :ddsx11_opendds_idl_gen

  end # SEV

end
