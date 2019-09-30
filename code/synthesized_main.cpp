int main(){
    fiber_context f{[](fiber_context&& m){
        m=std::move(m).resume(); // switch to `main()`
        ...
    }, assert_on_cancel};
    f=std::move(f).resume(); // resume `f`
    ...
    return 0;
}
