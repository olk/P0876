int main(){
    fiber_context f{launch([](fiber_context&& m){
        m=std::move(m).resume(); // switch to `main()`
        ...
    })};
    f=std::move(f).resume(); // resume `f`
    return 0;
}
