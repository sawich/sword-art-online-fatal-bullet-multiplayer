#pragma once

#include "../framework.hpp"

namespace uef::f_name_defs
{
  /** 
   * Use a modest bucket count on consoles
   *
   * On PC platform we use a large number of name hash buckets to accommodate the editor's
   * use of FNames to store asset path and content tags
   **/
  static const constexpr uint32_t name_hash_bucket_count{ 65536 };
}