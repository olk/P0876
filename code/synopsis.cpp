#include <fiber_context>

namespace std {
namespace experimental {
inline namespace concurrency_v2 {

class fiber_context;

class unwind_exception;

void unwind_fiber(fiber_context&& other);

} // namespace concurrency_v2
} // namespace experimental
} // namespace std
