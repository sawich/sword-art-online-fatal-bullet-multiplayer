#pragma once

#include "f_name.hpp"
#include "e_lifetime_condition.hpp"

namespace uef
{
	/** 
	 * An UnrealScript variable.
	 **/
	class u_property
	{
		// Persistent variables.
		int32_t ArrayDim;
		int32_t ElementSize;
		uint64_t PropertyFlags;
		uint16_t RepIndex;

		f_name RepNotifyFunc;

	private:
		// In memory variables (generated during Link()).
		int32_t Offset_Internal;

		e_lifetime_condition BlueprintReplicationCondition;

	public:
		/** In memory only: Linked list of properties from most-derived to base **/
		u_property* PropertyLinkNext;

		/** In memory only: Linked list of object reference properties from most-derived to base **/
		u_property* NextRef;

		/** In memory only: Linked list of properties requiring destruction. Note this does not include things that will be destroyed byt he native destructor **/
		u_property* DestructorLinkNext;

		/** In memory only: Linked list of properties requiring post constructor initialization.**/
		u_property* PostConstructLinkNext;
	};
}