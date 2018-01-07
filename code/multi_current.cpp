fiber f1=fiber::current();
fiber f2=fiber::current();
assert(f1==f2); // f1 and f2 point to the same (active) fiber
