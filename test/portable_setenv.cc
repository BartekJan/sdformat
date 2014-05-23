#if (_MSC_VER >= 1400) // Visual Studio 2005
#include <sstream>

int setenv(const char name, const char *value, int /*rewrite*/)
{
  std::stringstream sstr;
  sstr<<name<<'='<<value;
  return _putenv(sstr.str().c_str());
}

void setenv(const char name)
{
  std::stringstream sstr;
  sstr << name << '=';
  return _putenv(sstr.str().c_str());
}

#endif
