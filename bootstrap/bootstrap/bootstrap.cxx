#include <libbootstrap/bootstrap.hxx>
#include <iostream>
#include <windows.h>

int __cdecl
main (const int argc, char* argv[])
{
  using namespace std;

  if (argc < 2)
  {
    cerr << "error: missing dll name" << endl;
    return 1;
  }

  bootstrap::say_hello (cout, argv[1]);

  cout << "Loading " << argv[1] << '!' << endl;

  ::LoadLibraryA (argv[1]);
}
