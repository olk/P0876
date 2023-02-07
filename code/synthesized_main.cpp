int main(){
    fiber_context f{make_fiber_context([](fiber_context&& m){
        m=std::move(m).resume(); // switch to `main()`
        ...
    }).first};
    f=std::move(f).resume(); // resume `f`
    ...
    return 0;
}
