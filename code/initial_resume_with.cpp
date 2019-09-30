fiber_context topfunc(fiber_context&& prev);
fiber_context injected(fiber_context&& prev);

fiber_context f(topfunc, assert_on_cancel);
// topfunc() has not yet been entered
std::move(f).resume_with(injected);
