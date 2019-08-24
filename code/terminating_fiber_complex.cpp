int main(){
    fiber_context m;
    fiber_context f1{[&](fiber_context&& f){
        std::cout << "f1: entered first time" << std::endl;
        assert(!f);
        return std::move(m); // resume (main-)fiber that has started `f2`
    }, assert_on_cancel};
    fiber_context f2{[&](fiber_context&& f){
        std::cout << "f2: entered first time" << std::endl;
        m=std::move(f); // preserve `f` (== suspended main())
        return std::move(f1);
    }, assert_on_cancel};
    std::move(f2).resume();
    std::cout << "main: done" << std::endl;
    return 0;
}

output:
f2: entered first time
f1: entered first time
main: done
