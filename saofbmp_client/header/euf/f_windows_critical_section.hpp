#pragma once

#include "windows/critical_section.hpp"

namespace uef
{
  /** 
   * This is the Windows version of a critical section. It uses an aggregate
   * CRITICAL_SECTION to implement its locking.
   **/
  class f_windows_critical_section
  {
    /** The windows specific critical section **/
    windows::critical_section critical_section;
  };
}