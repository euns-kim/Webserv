#include "Nothing.hpp"

Nothing::Nothing() {}

Nothing::Nothing(const Nothing& other) { (void) other; }

Nothing::~Nothing() {}

Nothing& Nothing::operator=(const Nothing&)
{
  return *this;
}

bool  Nothing::operator==(const Nothing&) const
{
  return true;
}
