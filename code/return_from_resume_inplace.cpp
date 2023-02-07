int main(){
    fiber_context m,f1,f2,f3;
    f3=make_fiber_context([&](fiber_context&& f)->fiber_context{
        f2=std::move(f);
        for(;;){
            std::cout << "f3 ";
            std::move(f1).resume();
        }
        return {};
    }).first;
    f2=make_fiber_context([&](fiber_context&& f)->fiber_context{
        f1=std::move(f);
        for(;;){
            std::cout << "f2 ";
            std::move(f3).resume();
        }
        return {};
    }).first;
    f1=make_fiber_context([&](fiber_context&& f)->fiber_context{
        m=std::move(f);
        for(;;){
            std::cout << "f1 ";
            std::move(f2).resume();
        }
        return {};
    }).first;
    std::move(f1).resume();
    return 0;
}

output:
f1 f2 f3 f1 f3 f1 f3 f1 f3 ...
