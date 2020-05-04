#pragma once

#include "u_object.hpp"
#include "u_property.hpp"
#include "u_field.hpp"
#include "t_array.hpp"

namespace uef
{
	/** 
	 * Base class for all UObject types that contain fields.
	 **/
	class u_struct
	{
	private:
		/** Struct this inherits from, may be null **/
		u_struct* super_struct;

	public:
		/** Pointer to start of linked list of child fields **/
		u_field* children;

		/** Total size of all UProperties, the allocated structure may be larger due to alignment **/
		int32_t PropertiesSize;

		/** Alignment of structure in memory, structure will be at least this large **/
		int32_t MinAlignment;

		/** Script bytecode associated with this object **/
		t_array<uint8_t> Script;
		
		/** In memory only: Linked list of properties from most-derived to base **/
		u_property* PropertyLink;

		/** In memory only: Linked list of object reference properties from most-derived to base **/
		u_property* RefLink;

		/** In memory only: Linked list of properties requiring destruction. Note this does not include things that will be destroyed byt he native destructor **/
		u_property* DestructorLink;

		/** In memory only: Linked list of properties requiring post constructor initialization **/
		u_property* PostConstructLink;

		/** Array of object references embedded in script code. Mirrored for easy access by realtime garbage collection code **/
		t_array<u_object*> ScriptObjectReferences;
	};
}