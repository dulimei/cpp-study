#include "util/name_of.hpp"

#include <cxxabi.h>
#include <string>
#include <stdlib.h>

std::string name_of(const std::type_info &ti)
{
  // this should be replaced with boost::typeindex

  const static std::string typename_notavailable = "N/A";

  const char* mangled = ti.name();

  if (!mangled)
    {
      return typename_notavailable;
    }

  int status;

  char* demangled = abi::__cxa_demangle(mangled, 0, 0, &status);

  std::string rv;

  if (status != 0)
    rv = mangled;
  else
    rv = demangled ? demangled : typename_notavailable;

  free(demangled);
  return rv;
}
