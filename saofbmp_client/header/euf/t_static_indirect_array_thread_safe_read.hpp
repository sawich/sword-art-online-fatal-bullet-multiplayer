#pragma once

#include "../framework.hpp"

namespace uef
{
	/** 
	 * Simple array type that can be expanded without invalidating existing entries.
	 * This is critical to thread safe FNames.
	 * @param ElementType Type of the pointer we are storing in the array
	 * @param MaxTotalElements absolute maximum number of elements this array can ever hold
	 * @param ElementsPerChunk how many elements to allocate in a chunk
	 **/
	template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
	class t_static_indirect_array_thread_safe_read
	{
	public:
		/** **/
		size_t num(void) const noexcept { return m_num_elements; }
		
		/** **/
		bool is_valid_index(const int32_t index) const noexcept { return index < num() && index >= 0; }
		
		/** **/
		ElementType const* const& get_by_id(const int32_t index) const noexcept { return *get_item_ptr(index); }
		
		/** **/
		ElementType const* const* get_item_ptr(const int32_t index) const noexcept
		{
			const int32_t chunk_index = index / ElementsPerChunk;
			const int32_t within_chunk_index = index % ElementsPerChunk;
			ElementType** chunk = m_chunks[chunk_index];
			return chunk + within_chunk_index;
		}

	private:
		/** Figure out how many elements we need in the master table **/
		static const constexpr auto CHUNK_TABLE_SIZE{ (MaxTotalElements + ElementsPerChunk - 1) / ElementsPerChunk };

		/** Static master table to chunks of pointers **/
		ElementType** m_chunks[CHUNK_TABLE_SIZE];

		/** Number of elements we currently have **/
		int32_t m_num_elements;

		/** Number of chunks we currently have **/
		int32_t m_num_chunks;
	};
}