fiber_handle topfunc(fiber_handle&& prev);
fiber_handle injected(fiber_handle&& prev);

fiber_handle f(topfunc);
// topfunc() has not yet been entered
std::move(f).resume_with(injected);
