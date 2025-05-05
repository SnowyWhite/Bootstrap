#pragma once

#include <bemapiset.h>
#include <libbootstrap/export.hxx>

namespace bootstrap
{
  constexpr size_t MAX_PATH_LENGTH = MAX_PATH; // TODO: Enable wide path support?

  #pragma pack(push, 1)
  struct config
  {
    wchar_t hostfxr_path[MAX_PATH_LENGTH];
    size_t  path_len; // Actual path length in characters, *not* bytes
  };
  #pragma pack(pop)

  LIBBOOTSTRAP_SYMEXPORT
  DWORD WINAPI
  initialize (LPVOID lpParam);
}
