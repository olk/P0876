fiber_handle f1=fiber_handle::current();
fiber_handle f2=fiber_handle::current();
assert(f1==f2); // f1 and f2 point to the same (active) fiber
