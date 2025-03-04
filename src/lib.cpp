#ifdef ADRTXT_MODULE
module;
export module lib;
export {
#endif
#include "lib.hpp"
#ifdef ADRTXT_MODULE
}
#endif // ADRTXT_MODULE

namespace lib {
  auto return_true() -> bool {
    return true;
  }
}
