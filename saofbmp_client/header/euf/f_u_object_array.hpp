#pragma once

#include "f_u_object_item.hpp"
#include "f_critical_section.hpp"
#include "f_fixed_u_object_array.hpp"

namespace uef
{
  /** 
   * FUObjectArray replaces the functionality of GObjObjects and UObject::index
   *
   * Note the layout of this data structure is mostly to emulate the old behavior and minimize code rework during code restructure.
   * Better data structures could be used in the future, for example maybe all that is needed is a TSet<UObject *>
   * One has to be a little careful with this, especially with the GC optimization. I have seen spots that assume
   * that non-GC objects come before GC ones during iteration.
   **/
  class f_u_object_array
  {
  public:
    /** 
     * Returns the UObject corresponding to index. Be advised this is only for very low level use.
     *
     * @param index index of object to return
     * @return Object at this index
     **/
    f_u_object_item* index_to_object(const int32_t index) const noexcept
    {
      if (index < m_objects.num()) { return const_cast<f_u_object_item*>(&m_objects[index]); }
      return nullptr;
    }

    /** **/
    f_u_object_item* index_to_object_unsafe_for_gc(const int32_t index) const noexcept
    {
      return const_cast<f_u_object_item*>(&m_objects[index]);
    }

    //f_u_object_item* index_to_object(const int32_t index, bool bEvenIfPendingKill)
    //{
    //  f_u_object_item* item = index_to_object(index);
    //  if (item && item->object)
    //  {
    //    if (!bEvenIfPendingKill && item->is_pending_kill())
    //    {
    //      item = nullptr;
    //      ;
    //    }
    //  }
    //  return item;
    //}

    //f_u_object_item* ObjectToObjectItem(UObjectBase* Object)
    //{
    //  f_u_object_item* item = index_to_object(Object->InternalIndex);
    //  return item;
    //}

    /** **/
    bool is_valid(f_u_object_item* item, const bool bEvenIfPendingKill) const noexcept
    {
      if (item) {
        return bEvenIfPendingKill ? !item->is_unreachable() : !(item->is_unreachable() || item->is_pending_kill());
      }
      return false;
    }

    /** **/
    f_u_object_item* index_to_valid_object(const int32_t index, const bool bEvenIfPendingKill) const noexcept
    {
      f_u_object_item* item{ index_to_object(index) };
      return is_valid(item, bEvenIfPendingKill) ? item : nullptr;
    }

    /** **/
    bool is_valid(const int32_t index, const bool bEvenIfPendingKill) const noexcept
    {
      /** This method assumes index points to a valid object. **/
      return is_valid(index_to_object(index), bEvenIfPendingKill);
    }

    /** **/
    bool is_stale(f_u_object_item* item, const bool bEvenIfPendingKill) const noexcept
    {
      /** This method assumes item is valid. **/
      return bEvenIfPendingKill ? (item->is_pending_kill() || item->is_unreachable()) : (item->is_unreachable());
    }

    /** **/
    bool is_stale(const int32_t index, const bool bEvenIfPendingKill) const noexcept
    {
      /** This method assumes index points to a valid object. **/
      if (auto item{ index_to_object(index) }; item) {
        return is_stale(item, bEvenIfPendingKill);
      }
      return true;
    }

  public:
    using t_u_object_array = f_fixed_u_object_array;

    /** First index into objects array taken into account for GC. **/
    int32_t m_first_gc_index;

    /** index pointing to last object created in range disregarded for GC. **/
    int32_t m_last_non_gc_index;

    /** Maximum number of objects in the disregard for GC Pool **/
    int32_t m_max_objects_not_considered_by_gc;

    /** If true this is the intial load and we should load objects int the disregarded for GC range. **/
    bool m_open_for_disregard_for_gc;

    /** Array of all live objects. **/
    t_u_object_array m_objects;

    /** Synchronization object for all live objects. **/
    //f_critical_section ObjObjectsCritical;

    /** Available object indices. **/
    //TLockFreePointerListUnordered<int32_t, PLATFORM_CACHE_LINE_SIZE> ObjAvailableList;
  //
  //#if UE_GC_TRACK_OBJ_AVAILABLE
  //  /** Available object index count. **/
  //  FThreadSafeCounter ObjAvailableCount;
  //#endif
  //  /** 
  //   * Array of things to notify when a UObjectBase is created
  //   **/
  //  TArray<FUObjectCreateListener* > UObjectCreateListeners;
  //  /** 
  //   * Array of things to notify when a UObjectBase is destroyed
  //   **/
  //  TArray<FUObjectDeleteListener* > UObjectDeleteListeners;
  //#if THREADSAFE_UOBJECTS
  //  FCriticalSection UObjectDeleteListenersCritical;
  //#endif
  //
  //  /** Current master serial number **/
  //  FThreadSafeCounter MasterSerialNumber;
  };
}