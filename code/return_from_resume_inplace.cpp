int main(){
    fiber_context f1,f2,f3;
    f3=fiber_context{[&](fiber_context&& f)->fiber_context{
        f2=std::move(f);
        for(;;){
            std::cout << "f3 ";
            std::move(f1).resume();
        }
        return {};
    }};
    f2=fiber_context{[&](fiber_context&& f)->fiber_context{
        f1=std::move(f);
        for(;;){
            std::cout << "f2 ";
            std::move(f3).resume();
        }
        return {};
    }};
    f1=fiber_context{[&](fiber_context&& /*main*/)->fiber_context{
        for(;;){
            std::cout << "f1 ";
            std::move(f2).resume();
        }
        return {};
    }};
    std::move(f1).resume();
    return 0;
}

output:
f1 f2 f3 f1 f3 f1 f3 f1 f3 ...
