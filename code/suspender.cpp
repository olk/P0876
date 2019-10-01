fiber_context f([](fiber_context&& caller){
    // ...
    std::move(caller).resume();
    // ...
}, assert_on_cancel);

fiber_context fn(fiber_context&&);

f = std::move(f).resume();
// ...
std::move(f).resume_with(fn);
