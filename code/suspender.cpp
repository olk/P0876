fiber_handle f([](fiber_handle&& caller){
    // ...
    std::move(caller).resume();
    // ...
});

fiber_handle fn(fiber_handle&&);

f = std::move(f).resume();
// ...
std::move(f).resume_with(fn);
