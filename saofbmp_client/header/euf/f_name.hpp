#pragma once

#include "../framework.hpp"
#include "f_name_defs.hpp"

namespace uef
{
  /** 
   *
   **/
  struct f_name
  {
    union
    {
      struct
      {
        /** Index into the Names array (used to find String portion of the string/number pair used for comparison) **/
        int32_t comparison_index;

        /** Index into the Names array (used to find String portion of the string/number pair used for display) **/
        //int32_t display_index;

        /** Number portion of the string/number pair (stored internally as 1 more than actual, so zero'd memory will be the default, no-instance case) **/
        uint32_t number;
      };

      /** **/
      uint64_t composite_comparison_value;
    };
  };
}