#include <foo/abi2.hpp>
#include <stdio.h>

namespace foo {

  // exception to be thrown in case of detected incompatiblity
  struct incompatible_version : std::exception
  {
    unsigned compiled_version, running_version;
    incompatible_version(unsigned compiledwith, unsigned runningwith);
    virtual const char* what() const throw();
  };

}


namespace foo {
  incompatible_version::incompatible_version(unsigned c, unsigned r)
    : compiled_version(c), running_version(r)
  { }

  const char* incompatible_version::what() const throw()
  {
    return "Runtime version of foo is incompatible with the compiletime version of foo. "
      "Check the contents of your runtime link path.";
  }

  bool abi_version_is_okay(unsigned runtime)
  {
    printf("%s\n", __PRETTY_FUNCTION__);
    if (runtime != abi_version)
      throw incompatible_version(abi_version, runtime);
    return true;
  }
}
