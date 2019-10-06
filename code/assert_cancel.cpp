// assert_on_cancel() is a cancellation function for use when you're quite
// sure that no one will call cancel(). Therefore, code must preserve every
// fiber_context instance representing this fiber. The fiber in question must
// voluntarily return from its top-level function. Accidentally destroying any
// fiber_context representing this fiber is a programming error.
std::fiber_context assert_on_cancel(std::fiber_context&&) {
    assert(false);
    return {};
}
