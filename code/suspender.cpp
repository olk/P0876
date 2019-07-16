fiber_context f(launch([](fiber_context&& caller){
    // ...
    std::move(caller).resume();
    // ...
}));

fiber_context fn{fiber_context&&};

f = std::move(f).resume();
// ...
std::move(f).resume_with(fn);
