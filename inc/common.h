#ifndef H_COMMON
#define H_COMMON

#include <stdexcept>

namespace curran {

class IndexError : public std::out_of_range {};

} // namespace curran
#endif // H_COMMON
