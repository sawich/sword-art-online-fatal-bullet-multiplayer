#pragma once

#include "u_object.hpp"

namespace uef
{
	/** 
	 * Base class of reflection data objects.
	 **/
	class u_field : public u_object
	{
		/** **/
		u_field* next;
	};
}