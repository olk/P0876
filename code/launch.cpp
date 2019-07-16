// unwind_exception is an exception used internally by launch() to unwind the
// stack of a suspended fiber when the referencing fiber_context instance is
// destroyed.
class unwind_exception: public std::runtime_error {
public:
    unwind_exception(std::fiber_context&& previous):
        std::runtime_error("unwinding std::fiber_context"),
        mPrevious(std::make_shared<std::fiber_context>(previous)) {}

    std::shared_ptr<std::fiber_context> get_previous() const { return mPrevious; }

private:
    // Directly storing fiber_context would make unwind_exception move-only.
    // Instead, store a shared_ptr so unwind_exception remains copyable.
    std::shared_ptr<std::fiber_context> mPrevious;
};

// launch() is a factory function that returns a fiber_context representing a
// new fiber that will run the passed entry_function. It implicitly provides a
// top-level wrapper and a cancellation-function. If some fiber_context
// representing this new fiber is eventually destroyed, ~fiber_context() will
// call this cancellation-function, which will throw unwind_exception. The
// top-level wrapper will catch it and return the bound fiber_context, thereby
// resuming the fiber that called ~fiber_context().
template <typename Fn>
std::fiber_context launch(Fn&& entry_function) {
    return std::fiber_context(
        // entry-function passed to std::fiber_context constructor binds
        // entry_function, calls it within try/catch, catches
        // unwind_exception, extracts its shared_ptr<fiber_context>,
        // dereferences it and returns that fiber_context.
        [entry=std::move(entry_function)]
        (std::fiber_context&& previous) {
            try {
                return entry(std::move(previous));
            }
            catch (const unwind_exception& unwind) {
                return *unwind.get_previous();
            }
        },
        // cancellation-function passed to std::fiber_context constructor
        // throws unwind_exception, binding passed fiber_context instance.
        [](std::fiber_context&& previous) {
            throw unwind_exception(std::move(previous));
        });
}
