#include <arken/base>

extern "C" {
#include <uuid/uuid.h>
}

char * os::uuid()
{
  // typedef unsigned char uuid_t[16];
  uuid_t uuid;

  // generate
  // uuid_generate_time_safe(uuid);
  uuid_generate_random(uuid);
  // uuid_generate(uuid);
  // uuid_generate_time(uuid);

  // unparse (to string)
  char * result = new char[37];// ex. "1b4e28ba-2fa1-11d2-883f-0016d3cca427" + "\0"
  uuid_unparse_lower(uuid, result);
  return result;
}
