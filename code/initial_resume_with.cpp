fiber_context topfunc(fiber_context&& prev);
fiber_context injected(fiber_context&& prev);

fiber_context f(launch(topfunc));
// topfunc() has not yet been entered
std::move(f).resume_with(injected);
