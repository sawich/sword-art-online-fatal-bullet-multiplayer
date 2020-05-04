#pragma once

#include "../framework.hpp"
#include "e_internal_object_flags.hpp"

namespace uef
{
  class u_object;

  /** 
   * Single item in the UObject array.
   **/
  struct f_u_object_item
  {
  public:
    void set_owner_index(const int32_t owner_index) const noexcept
    {
      m_cluster_root_index = owner_index;
    }

    /** **/
    int32_t get_owner_index(void) const noexcept
    {
      return m_cluster_root_index;
    }

    /** Encodes the cluster index in the m_cluster_root_index variable **/
    void set_cluster_index(const int32_t cluster_index) const noexcept
    {
      m_cluster_root_index = -cluster_index - 1;
    }

    /** Decodes the cluster index from the m_cluster_root_index variable **/
    int32_t get_cluster_index(void) const noexcept
    {
      return -m_cluster_root_index - 1;
    }

    /** **/
    int32_t get_serial_number(void) const noexcept
    {
      return m_serial_number;
    }

    /** **/
    void set_flags(const e_internal_object_flags flags_to_set) const noexcept
    {
      m_flags |= int32_t(flags_to_set);
    }

    /** **/
    e_internal_object_flags get_flags(void) const noexcept
    {
      return e_internal_object_flags(m_flags);
    }

    /** **/
    void clear_flags(e_internal_object_flags flags_to_clear) const noexcept
    {
      m_flags &= ~int32_t(flags_to_clear);
    }

    /** 
     * Uses atomics to clear the specified flag(s).
     * @param flags_to_clear
     * @return True if this call cleared the flag, false if it has been cleared by another thread.
     **/
     //bool ThisThreadAtomicallyClearedFlag(e_internal_object_flags FlagToClear)
     //{
     //  static_assert(sizeof(int32_t) == sizeof(m_flags), "m_flags must be 32-bit for atomics.");
     //  bool bIChangedIt = false;
     //  while (1)
     //  {
     //    int32_t StartValue = int32_t(m_flags);
     //    if (!(StartValue & int32_t(FlagToClear)))
     //    {
     //      break;
     //    }
     //    int32_t NewValue = StartValue & ~int32_t(FlagToClear);
     //    if ((int32_t)FPlatformAtomics::InterlockedCompareExchange((int32_t*)&m_flags, NewValue, StartValue) == StartValue)
     //    {
     //      bIChangedIt = true;
     //      break;
     //    }
     //  }
     //  return bIChangedIt;
     //}

     //bool ThisThreadAtomicallySetFlag(e_internal_object_flags FlagToSet)
     //{
     //  static_assert(sizeof(int32_t) == sizeof(m_flags), "m_flags must be 32-bit for atomics.");
     //  bool bIChangedIt = false;
     //  while (1)
     //  {
     //    int32_t StartValue = int32_t(m_flags);
     //    if (StartValue & int32_t(FlagToSet))
     //    {
     //      break;
     //    }
     //    int32_t NewValue = StartValue | int32_t(FlagToSet);
     //    checkSlow(NewValue != StartValue);
     //    if ((int32_t)FPlatformAtomics::InterlockedCompareExchange((int32_t*)&m_flags, NewValue, StartValue) == StartValue)
     //    {
     //      bIChangedIt = true;
     //      break;
     //    }
     //  }
     //  return bIChangedIt;
     //}

     /** **/
    bool has_any_flags(e_internal_object_flags in_flags) const noexcept
    {
      return !!(m_flags & int32_t(in_flags));
    }

    /** **/
    void set_unreachable(void) const noexcept
    {
      m_flags |= int32_t(e_internal_object_flags::unreachable);
    }

    /** **/
    void clear_unreachable(void) const noexcept
    {
      m_flags &= ~int32_t(e_internal_object_flags::unreachable);
    }

    /** **/
    bool is_unreachable(void) const noexcept
    {
      return !!(m_flags & int32_t(e_internal_object_flags::unreachable));
    }

    //bool ThisThreadAtomicallyClearedRFUnreachable()
    //{
    //  return ThisThreadAtomicallyClearedFlag(e_internal_object_flags::Unreachable);
    //}

    /** **/
    void set_pending_kill(void) const noexcept
    {
      m_flags |= int32_t(e_internal_object_flags::pending_kill);
    }

    /** **/
    void clear_pending_kill(void) const noexcept
    {
      m_flags &= ~int32_t(e_internal_object_flags::pending_kill);
    }

    /** **/
    bool is_pending_kill(void) const noexcept
    {
      return !!(m_flags & int32_t(e_internal_object_flags::pending_kill));
    }

    /** **/
    void set_root_set(void) const noexcept
    {
      m_flags |= int32_t(e_internal_object_flags::root_set);
    }

    /** **/
    void clear_root_set(void) const noexcept
    {
      m_flags &= ~int32_t(e_internal_object_flags::root_set);
    }

    /** **/
    bool is_root_set(void) const noexcept
    {
      return !!(m_flags & int32_t(e_internal_object_flags::root_set));
    }

    /** **/
    void reset_serial_number_and_flags(void) const noexcept
    {
      m_flags = 0;
      m_cluster_root_index = 0;
      m_serial_number = 0;
    }

  public:
    /** Pointer to the allocated m_object **/
    u_object* m_object;

    /** Internal m_flags **/
    mutable int32_t m_flags;

    /** UObject Owner Cluster Index **/
    mutable int32_t m_cluster_root_index;

    /** Weak Object Pointer Serial number associated with the m_object **/
    mutable int32_t m_serial_number;
  };
}