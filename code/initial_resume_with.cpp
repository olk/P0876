fiber_context topfunc(fiber_context&& prev);
fiber_context injected(fiber_context&& prev);

fiber_context f{ make_fiber_context(topfunc).first };
// topfunc() has not yet been entered
std::move(f).resume_with(injected);
