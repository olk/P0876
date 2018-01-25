void foo(){
    fiber f{[](fiber&& m){
        m=m.resume(); // switch to `foo()`
        m=m.resume(); // switch to `foo()`
        ...
    }};
    f=f.resume(); // start `f`
    f=f.resume(); // resume `f`
}
