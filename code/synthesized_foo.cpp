void foo(){
    fiber_context f{make_fiber_context([](fiber_context&& m){
        m=std::move(m).resume(); // switch to `foo()`
        m=std::move(m).resume(); // switch to `foo()`
        ...
    }).first};
    f=std::move(f).resume(); // start `f`
    f=std::move(f).resume(); // resume `f`
    ...
}
