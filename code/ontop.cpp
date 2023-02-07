int data = 0;
fiber_context f{make_fiber_context([&data](fiber_context&& m){
    std::cout << "f1: entered first time: " << data  << std::endl;
    data+=1;
    m=std::move(m).resume();
    std::cout << "f1: entered second time: " << data  << std::endl;
    data+=1;
    m=std::move(m).resume();
    std::cout << "f1: entered third time: " << data << std::endl;
    return std::move(m);
}).first};
f=std::move(f).resume();
std::cout << "f1: returned first time: " << data << std::endl;
data+=1;
f=std::move(f).resume();
std::cout << "f1: returned second time: " << data << std::endl;
data+=1;
f=std::move(f).resume_with([&data](fiber_context&& m){
    std::cout << "f2: entered: " << data << std::endl;
    data=-1;
    return std::move(m);
});
std::cout << "f1: returned third time" << std::endl;

output:
    f1: entered first time: 0
    f1: returned first time: 1
    f1: entered second time: 2
    f1: returned second time: 3
    f2: entered: 4
    f1: entered third time: -1
    f1: returned third time
