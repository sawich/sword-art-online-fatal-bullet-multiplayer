#pragma once

namespace uef::windows
{
  /** For structures which are opaque **/
  struct critical_section { void* Opaque1[1]; long Opaque2[2]; void* Opaque3[3]; };
}
