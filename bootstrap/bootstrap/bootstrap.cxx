#include <libbootstrap/bootstrap.hxx>
#include <../libnethost/include/nethost.hxx>
#include <iostream>
#include <memory>
#include <windows.h>

int __cdecl
main (const int argc, char* argv[])
{
  using namespace std;

  constexpr auto max_path_length = MAX_PATH;
  const auto hostfxr_path        = make_unique<char_t> (max_path_length);
  size_t buffer_size             = max_path_length;

  if (get_hostfxr_path (hostfxr_path.get (), &buffer_size, nullptr) != 0x0)
  {
    throw runtime_error ("failed to get hostfxr_path");
  }

  wcout << L"hostfxr path: " << hostfxr_path.get () << endl;

  const auto hostfxr = ::LoadLibraryW (hostfxr_path.get ());
  if (!hostfxr)
  {
    throw runtime_error ("failed to load hostfxr");
  }

  return 0;
}
