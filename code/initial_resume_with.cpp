fiber_context topfunc(fiber_context&& prev);
fiber_context injected(fiber_context&& prev);

fiber_context f(topfunc);
// topfunc() has not yet been entered
f.resume_with(injected);
