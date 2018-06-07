int main(){
    fiber_handle f{[](fiber_handle&& m){
        return std::move(m); // resume `main()` by returning `m`
    }};
    std::move(f).resume(); // resume `f`
    return 0;
}
