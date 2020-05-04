#pragma once

#include "euf/t_name_entry_array.hpp"
#include "euf/f_u_object_array.hpp"

class ue
{
public:
	uef::t_name_entry_array* get_names(void) const noexcept { return m_names; }
	uef::f_u_object_array* get_objects(void) const noexcept { return m_objects; }

	static const ue* get_instance(void) noexcept { return m_instance.get(); }

	static void attach(void) noexcept
	{
		assert(!m_instance);
		m_instance = std::make_unique<ue>();
	}

	static void detach(void) noexcept
	{
		assert(m_instance);
		m_instance.reset();
	}

	ue(void) noexcept
		: m_names{ reinterpret_cast<uef::t_name_entry_array*>(*(reinterpret_cast<uintptr_t*>(0x144B763F8))) }
		, m_objects{ reinterpret_cast<uef::f_u_object_array*>(reinterpret_cast<uintptr_t*>(0x144B7ED60)) }
	{}

private:
	using ue_t = std::unique_ptr<ue>;
	static std::unique_ptr<ue> m_instance;

	uef::t_name_entry_array* m_names;
	uef::f_u_object_array* m_objects;
};

ue::ue_t ue::m_instance{ nullptr };