#pragma once

#include "../framework.hpp"

namespace uef
{
  /** 
   * A global name, as stored in the global name table.
   **/
  struct f_name_entry
  {
  public:
    /** **/
    const char* get_ansi_name(void) const noexcept { return m_ansi_name; }

    /** **/
    const wchar_t* get_wide_name(void) const noexcept { return m_wide_name; }

  private:
    /** Index of name in hash. **/
    int32_t m_index;

  public:
    /** Pointer to the next entry in this hash bin's linked list. **/
    f_name_entry* m_hash_next;

  protected:
    /** Name, variable-sized - note that AllocateNameEntry only allocates memory as needed. **/
    union
    {
      char m_ansi_name[1024];
      wchar_t m_wide_name[1024];
    };
  };
}