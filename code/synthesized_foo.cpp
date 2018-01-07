void foo(){
    fiber f{[](fiber&& m){
        m.resume(); // switch to `foo()`
        m.resume(); // switch to `foo()`
    }};
    f.resume(); // start `f`
    f.resume(); // resume `f`
}
