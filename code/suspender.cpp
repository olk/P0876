fiber_context f(make_fiber_context([](fiber_context&& caller){
    // ...
    std::move(caller).resume();
    // ...
}).first);

fiber_context fn(fiber_context&&);

f = std::move(f).resume();
// ...
std::move(f).resume_with(fn);
