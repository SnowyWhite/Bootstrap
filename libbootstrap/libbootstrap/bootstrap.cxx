#include <iostream>
#include <libbootstrap/bootstrap.hxx>
#include <print>
#include <bits/ostream.tcc>

using namespace std;

namespace
{
  // std::filesystem::path
  // get_module_path (const HMODULE module_handle)
  // {
  //   constexpr int buffer_size = 4096;
  //   const auto module_path    = std::make_unique<WCHAR[]> (buffer_size);
  //
  //   if (::GetModuleFileNameW (module_handle, module_path.get (), buffer_size) == ERROR_INSUFFICIENT_BUFFER)
  //   [[unlikely]]
  //   {
  //     std::cerr << "Failed to get module path: Insufficient buffer size\n";
  //     return { };
  //   }
  //
  //   return module_path.get ();
  // }
}

namespace bootstrap
{
  DWORD
  initialize (LPVOID lpParam)
  {
    const auto params = static_cast<config*> (lpParam);
    const std::basic_string path (params->hostfxr_path, params->path_len);
    std::wcout << path << std::endl;

    /*
    const auto hostfxr = ::LoadLibraryW (hostfxr_path.get ());
    if (!hostfxr)
    {
    throw runtime_error ("failed to load hostfxr");
    }
    */

    return 0;
  }
}
