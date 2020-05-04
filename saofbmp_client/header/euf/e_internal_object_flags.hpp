#pragma once

#include "../framework.hpp"

namespace uef
{
  /** 
   * Objects flags for internal use (GC, low level UObject code)
   **/
  enum class e_internal_object_flags : int32_t
  {
    none = 0,

    /** All the other bits are reserved, DO NOT ADD NEW FLAGS HERE! **/
    /** External reference to object in cluster exists **/
    reachable_in_cluster = 1 << 23, 
    
    /** Root of a cluster **/
    cluster_root = 1 << 24, 
    
    /** Native (UClass only). **/
    native = 1 << 25, 
    
    /** Object exists only on a different thread than the game thread. **/
    async = 1 << 26, 
    
    /** Object is being asynchronously loaded. **/
    async_loading = 1 << 27, 
    
    /** Object is not reachable on the object graph. **/
    unreachable = 1 << 28, 
    
    /** Objects that are pending destruction (invalid for gameplay but valid objects) **/
    pending_kill = 1 << 29, 
    
    /** Object will not be garbage collected, even if unreferenced. **/
    root_set = 1 << 30, 

    garbage_collection_keep_flags = native | async | async_loading,

    /** Make sure this is up to date! **/
    all_flags = reachable_in_cluster | cluster_root | native | async | async_loading | unreachable | pending_kill | root_set
  };
}