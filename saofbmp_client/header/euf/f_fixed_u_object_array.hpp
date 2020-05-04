#pragma once

#include "f_u_object_item.hpp"

namespace uef
{
  /** 
   * Fixed size UObject array.
   **/
  class f_fixed_u_object_array
  {
  public:
    /** **/
    f_u_object_item const* get_object_ptr(const int32_t index) const
    {
      return &m_objects[index];
    }

    /** **/
    f_u_object_item* get_object_ptr(const int32_t index)
    {
      return &m_objects[index];
    }

    /** 
     * Return the number of elements in the array
     * Thread safe, but you know, someone might have added more elements before this even returns
     * @return	the number of elements in the array
     **/
    int32_t num(void) const noexcept { return m_num_elements; }

    /** 
     * Return if this index is valid
     * Thread safe, if it is valid now, it is valid forever. Other threads might be adding during this call.
     * @param	index	index to test
     * @return	true, if this is a valid
     **/
    bool is_valid_index(const int32_t index) const noexcept { return index < num() && index >= 0; }

    /** 
     * Return a reference to an element
     * @param	index	index to return
     * @return	a reference to the pointer to the element
     * Thread safe, if it is valid now, it is valid forever. This might return nullptr, but by then, some other thread might have made it non-nullptr.
     **/
    f_u_object_item const& operator[](const int32_t index) const noexcept
    {
      f_u_object_item const* ItemPtr{ get_object_ptr(index) };
      return *ItemPtr;
    }

    /** **/
    template <typename Index>
    f_u_object_item& operator[](const Index index) noexcept
    {
      f_u_object_item* ItemPtr{ get_object_ptr(index) };
      return *ItemPtr;
    }

  private:
    /** Static master table to chunks of pointers **/
    f_u_object_item* m_objects;

    /** Number of elements we currently have **/
    int32_t m_max_elements;

    /** Current number of UObject slots **/
    int32_t m_num_elements;
  };
}