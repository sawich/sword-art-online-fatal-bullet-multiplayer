#pragma once

#include "../framework.hpp"

namespace uef
{
  /** 
   *
   **/
  template <typename T> struct t_array
  {
    /** **/
    T* m_data;

    /** **/
    int32_t m_array_num;

    /** **/
    int32_t m_array_max;
  };
}