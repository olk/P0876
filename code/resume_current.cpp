fiber_handle m=fiber_handle::current();
m.resume(); // tries to resume active fiber == UB
