void foo(){
    fiber f{[](fiber&& m){
        m=std::move(m).resume(); // switch to `foo()`
        m=std::move(m).resume(); // switch to `foo()`
        ...
    }};
    f=std::move(f).resume(); // start `f`
    f=std::move(f).resume(); // resume `f`
}
