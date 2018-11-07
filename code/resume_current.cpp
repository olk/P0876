fiber_context m=fiber_context::current();
m.resume(); // tries to resume active fiber == UB
