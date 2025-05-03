// #include "../../libbootstrap/libbootstrap/bootstrap.hxx"

#include <iostream>
#include <windows.h>

int __cdecl
main (int argc, char* argv[])
{
  using namespace std;

  if (argc < 2)
  {
    cerr << "error: missing dll name" << endl;
    return 1;
  }

  cout << "Loading " << argv[1] << '!' << endl;

  ::LoadLibraryA (argv[1]);
}
