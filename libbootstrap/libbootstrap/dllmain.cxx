#include <algorithm>
#include <windows.h>
#include <filesystem>
#include <iostream>

HMODULE module_handle = nullptr;
std::filesystem::path module_path{ };
std::filesystem::path target_path{ };

std::filesystem::path
get_module_path (const HMODULE module_handle)
{
  constexpr auto buffer_size = 4096;
  const auto module_path     = std::make_unique<WCHAR[]> (buffer_size);

  if (::GetModuleFileNameW (module_handle, module_path.get (), buffer_size) == ERROR_INSUFFICIENT_BUFFER)
  [[unlikely]]
  {
    std::cerr << "Failed to get module path: Insufficient buffer size\n";
    return { };
  }

  return module_path.get ();
}

// void
// install_exception_handler ()
// {
//   ::CreateThread (nullptr, 0,
//                   reinterpret_cast<LPTHREAD_START_ROUTINE> (&::LoadLibraryW),
//                   const_cast<LPVOID> (static_cast<LPCVOID> (L"dbghelp.dll")),
//                   0, nullptr);
//
//   handle_exception_handler = ::AddVectoredExceptionHandler (1, [] (PEXCEPTION_POINTERS ex) -> LONG {
//     // Ignore debugging and some common language exceptions
//     if (const DWORD code = ex->ExceptionRecord->ExceptionCode;
//       code == CONTROL_C_EXIT || code == 0x406D1388 /* SetThreadName */ ||
//       code == DBG_PRINTEXCEPTION_C || code == DBG_PRINTEXCEPTION_WIDE_C || code == STATUS_BREAKPOINT ||
//       code == 0xE043452 /* CLR exception */ ||
//       code == 0xE06D7363 /* Visual C++ exception */ ||
//       (code ^ 0xE24C4A00) <= 0xFF /* LuaJIT exception */)
//       goto continue_search;
//
//     if (static unsigned int dump_index = 0; dump_index < 100)
//     {
//       const auto dbghelp_module = ::GetModuleHandleW (L"dbghelp.dll");
//       if (dbghelp_module == nullptr)
//         goto continue_search;
//
//       const auto dbghelp_write_dump = reinterpret_cast<BOOL(WINAPI*) (HANDLE, DWORD, HANDLE, MINIDUMP_TYPE,
//                                                                       PMINIDUMP_EXCEPTION_INFORMATION,
//                                                                       PMINIDUMP_USER_STREAM_INFORMATION,
//                                                                       PMINIDUMP_CALLBACK_INFORMATION)> (
//         ::GetProcAddress (dbghelp_module, "MiniDumpWriteDump"));
//       if (dbghelp_write_dump == nullptr)
//         goto continue_search;
//
//       char dump_name[] = "exception_00.dmp";
//       dump_name[10]    = '0' + static_cast<char> (dump_index / 10);
//       dump_name[11]    = '0' + static_cast<char> (dump_index % 10);
//
//       HANDLE file = ::CreateFileA (dump_name,
//                                    GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS,
//                                    FILE_ATTRIBUTE_NORMAL, nullptr);
//
//       if (file == INVALID_HANDLE_VALUE)
//         goto continue_search;
//
//       MINIDUMP_EXCEPTION_INFORMATION info;
//       info.ThreadId          = ::GetCurrentThreadId ();
//       info.ExceptionPointers = ex;
//       info.ClientPointers    = TRUE;
//
//       if (dbghelp_write_dump (::GetCurrentProcess (), ::GetCurrentProcessId (), file, MiniDumpNormal, &info, nullptr,
//                               nullptr))
//         dump_index++;
//       else
//         std::cerr << "MiniDumpWriteDump failed\n";
//
//       ::CloseHandle (file);
//     }
//
//   continue_search:
//     return EXCEPTION_CONTINUE_SEARCH;
//   });
// }

BOOL APIENTRY
DllMain (const HMODULE hModule, DWORD dwReason, LPVOID)
{
  if (dwReason == DLL_PROCESS_ATTACH)
  {
    module_handle = hModule;
    module_path   = get_module_path (module_handle);
    target_path   = get_module_path (nullptr);

    // if (HMODULE modules[1024]; ::K32EnumProcessModules (::GetCurrentProcess (), modules, sizeof(modules), &dwReason))
    // {
    //   for (DWORD i = 0; i < std::min<DWORD> (dwReason / sizeof (HMODULE), std::size (modules)); i++)
    //   {
    //     if (modules[i] != hModule && ::GetProcAddress (modules[i], "get_hostfxr_path") != nullptr)
    //     {
    //       // nethost.dll needs to be loaded before we can load bootstrap
    //       break;
    //     }
    //   }
    // }
    //
    // install_exception_handler ();
  }

  // if (dwReason == DLL_PROCESS_DETACH)
  // {
  //   if (handle_exception_handler != nullptr)
  //     ::RemoveVectoredExceptionHandler (handle_exception_handler);
  // }

  return TRUE;
}
