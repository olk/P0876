int main(){
    fiber_context f{[](fiber_context&& m){
        return std::move(m); // resume `main()` by returning `m`
    }, assert_on_cancel};
    f = std::move(f).resume(); // resume `f`
    assert(f.empty());
    return 0;
}
