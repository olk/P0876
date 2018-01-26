int main(){
    fiber f1,f2,f3;
    f3=fiber{[&](fiber&& f){
        f2=std::move(f);
        for(;;){
            std::cout << "f3 ";
            f2=f1.resume();
        }
        return fiber{};
    }};
    f2=fiber{[&](fiber&& f){
        f1=std::move(f);
        for(;;){
            std::cout << "f2 ";
            f1=f3.resume();
        }
        return fiber{};
    }};
    f1=fiber{[&](fiber&& /*main*/){
        for(;;){
            std::cout << "f1 ";
            f3=f2.resume();
        }
        return fiber{};
    }};
    f1.resume();
    return 0;
}

output:
1 2 3 1 2 3 1 2 3 ...
