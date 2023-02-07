int main(){
    fiber_context f{make_fiber_context([](fiber_context&& m){
        return std::move(m); // resume `main()` by returning `m`
    }).first};
    f = std::move(f).resume(); // resume `f`
    assert(f.empty());
    return 0;
}
