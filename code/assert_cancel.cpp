// assert_on_cancel() is a cancellation function for use when you're quite sure
// that the invoker will preserve every fiber_context representing this fiber
// until it has voluntarily returned from its top-level function. Accidentally
// destroying any fiber_context representing this fiber is a programming error.
std::fiber_context assert_on_cancel(std::fiber_context&&) {
    assert(false);
}
