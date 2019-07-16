int main(){
    fiber_context f{[](fiber_context&& m){
        return std::move(m); // resume `main()` by returning `m`
    }, assert_cancel};
    std::move(f).resume(); // resume `f`
    return 0;
}
