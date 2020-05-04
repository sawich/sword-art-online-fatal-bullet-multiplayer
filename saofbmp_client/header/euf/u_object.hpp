#pragma once

#include "f_name.hpp"

namespace uef
{
  /**
   *
   **/
  enum e_object_flag
  {
    /** Do not add new flags unless they truly belong here. There are alternatives. if you change any the bit of any of the RF_Load flags, then you will need legacy serialization. **/

    /** No flags, used to avoid a cast **/
    RF_NoFlags = 0x00000000,

    /** This first group of flags mostly has to do with what kind of object it is. Other than transient, these are the persistent object flags. The garbage collector also tends to look at these. **/

    /** Object is visible outside its package. **/
    RF_Public = 0x00000001,

    /** Keep object around for editing even if unreferenced. **/
    RF_Standalone = 0x00000002,

    /** Object (UField) will be marked as native on construction (DO NOT USE THIS FLAG in HasAnyFlags() etc). **/
    RF_MarkAsNative = 0x00000004,

    /** Object is transactional. **/
    RF_Transactional = 0x00000008,

    /** This object is its class's default object. **/
    RF_ClassDefaultObject = 0x00000010,

    /** This object is a template for another object - treat like a class default object. **/
    RF_ArchetypeObject = 0x00000020,

    /** Don't save object. **/
    RF_Transient = 0x00000040,

    /** This group of flags is primarily concerned with garbage collection. **/

    /** Object will be marked as root set on construction and not be garbage collected, even if unreferenced (DO NOT USE THIS FLAG in HasAnyFlags() etc). **/
    RF_MarkAsRootSet = 0x00000080,

    /** This is a temp user flag for various utilities that need to use the garbage collector. The garbage collector itself does not interpret it. **/
    RF_TagGarbageTemp = 0x00000100,

    /** The group of flags tracks the stages of the lifetime of a uobject **/

    /** This object has not completed its initialization process. Cleared when ~FObjectInitializer completes. **/
    RF_NeedInitialization = 0x00000200,

    /** During load, indicates object needs loading. **/
    RF_NeedLoad = 0x00000400,

    /** Keep this object during garbage collection because it's still being used by the cooker. **/
    RF_KeepForCooker = 0x00000800,

    /** Object needs to be postloaded. **/
    RF_NeedPostLoad = 0x00001000,

    /** During load, indicates that the object still needs to instance subobjects and fixup serialized component references. **/
    RF_NeedPostLoadSubobjects = 0x00002000,

    /** Object has been consigned to oblivion due to its owner package being reloaded, and a newer version currently exists. **/
    RF_NewerVersionExists = 0x00004000,

    /** BeginDestroy has been called on the object. **/
    RF_BeginDestroyed = 0x00008000,

    /** FinishDestroy has been called on the object. **/
    RF_FinishDestroyed = 0x00010000,

    /** Misc. Flags **/

    /** Flagged on UObjects that are used to create UClasses (e.g. Blueprints) while they are regenerating their UClass on load (See FLinkerLoad::CreateExport()). **/
    RF_BeingRegenerated = 0x00020000,

    /** Flagged on subobjects that are defaults. **/
    RF_DefaultSubObject = 0x00040000,

    /** Flagged on UObjects that were loaded. **/
    RF_WasLoaded = 0x00080000,

    /** Do not export object to text form (e.g. copy/paste). Generally used for sub-objects that can be regenerated from data in their parent object. **/
    RF_TextExportTransient = 0x00100000,

    /** Object has been completely serialized by linkerload at least once. DO NOT USE THIS FLAG, It should be replaced with RF_WasLoaded. **/
    RF_LoadCompleted = 0x00200000,

    /** Archetype of the object can be in its super class. **/
    RF_InheritableComponentTemplate = 0x00400000,

    /** Object should not be included in any type of duplication (copy/paste, binary duplication, etc.). **/
    RF_DuplicateTransient = 0x00800000,

    /** References to this object from persistent function frame are handled as strong ones. **/
    RF_StrongRefOnFrame = 0x01000000,

    /** Object should not be included for duplication unless it's being duplicated for a PIE session. **/
    RF_NonPIEDuplicateTransient = 0x02000000,

    /** Field Only. Dynamic field - doesn't get constructed during static initialization, can be constructed multiple times. **/
    RF_Dynamic = 0x04000000,

    /** This object was constructed during load and will be loaded shortly. **/
    RF_WillBeLoaded = 0x08000000,
  };

  class u_class;

	/** 
	 *
	 **/
	class u_object 
  {
  public:
    /** 
     * Returns the unique ID of the object...
     * these are reused so it is only unique while the object is alive. Useful as a tag.
     **/
    uint32_t get_unique_id(void) const noexcept
    {
      return static_cast<uint32_t>(m_internal_index);
    }

    /** **/
    u_class* get_class(void) const noexcept
    {
      return m_class_private;
    }

    /** **/
    u_object* get_outer(void) const noexcept
    {
      return m_outer_private;
    }

    /** **/
    f_name get_f_name(void) const noexcept { return m_name_private; }

  private:
    /** **/
    uintptr_t v_table;

    /** 
     * Flags used to track and report various object states.
     * This needs to be 8 byte aligned on 32-bit platforms to reduce memory waste
     **/
    e_object_flag m_object_flags;

    /** Index into GObjectArray...very private. **/
    int32_t m_internal_index;

    /** Class the object belongs to. **/
    u_class* m_class_private;

    /** Name of this object **/
    f_name m_name_private;

    /** Object this object resides in. **/
    u_object* m_outer_private;
  };
}