#include <fiber_context>

#define __cpp_lib_experimental_fiber_context 201907

namespace std {
namespace experimental {
inline namespace concurrency_v2 {

class fiber_context;

class unwind_exception;

void unwind_fiber(fiber_context&& other);

} // namespace concurrency_v2
} // namespace experimental
} // namespace std
