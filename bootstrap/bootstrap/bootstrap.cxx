#include <libbootstrap/bootstrap.hxx>
#include <../libnethost/include/nethost.h>
#include <iostream>
#include <memory>
#include <windows.h>

int __cdecl
main (const int argc, char* argv[])
{
  using namespace std;

  const auto hostfxr_path = make_unique<char_t[]> (bootstrap::MAX_PATH_LENGTH);
  size_t buffer_size      = bootstrap::MAX_PATH_LENGTH;

  if (get_hostfxr_path (hostfxr_path.get (), &buffer_size, nullptr) != 0)
  {
    throw runtime_error ("failed to get hostfxr_path");
  }

  bootstrap::config config{ .path_len = buffer_size };
  copy_n (hostfxr_path.get (), buffer_size, config.hostfxr_path);

  wcout << "Length: " << config.path_len << endl;
  wcout << "Path: " << config.hostfxr_path << endl;

  bootstrap::initialize (&config);

  return 0;
}
