#include <fiber_context>

#define __cpp_lib_experimental_fiber_context 202302

namespace std {
namespace experimental {
inline namespace concurrency_v2 {

class fiber_context;

template <typename F>
std::pair<fiber_context, stop_source> make_fiber_context(F&& entry);

} // namespace concurrency_v2
} // namespace experimental
} // namespace std
