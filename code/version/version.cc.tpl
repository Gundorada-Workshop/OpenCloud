#include "version/version.h"

namespace version
{
  std::string_view branch()
  {
    return "<%= git.current_branch %>";
  }

  std::string_view revision()
  {
    return "<%= git.revparse("HEAD") %>";
  }
}