void foo(){
    fiber_context f{[](fiber_context&& m){
        m=std::move(m).resume(); // switch to `foo()`
        m=std::move(m).resume(); // switch to `foo()`
        ...
    }, assert_on_cancel};
    f=std::move(f).resume(); // start `f`
    f=std::move(f).resume(); // resume `f`
    ...
}
