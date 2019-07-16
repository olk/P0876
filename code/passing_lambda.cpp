int i=1;
std::fiber_context lambda{[&i](fiber_context&& caller){
    std::cout << "inside lambda,i==" << i << std::endl;
    i+=1;
    caller=std::move(caller).resume();
    return std::move(caller);
}, assert_cancel};
lambda=std::move(lambda).resume();
std::cout << "i==" << i << std::endl;
lambda=std::move(lambda).resume();

output:
    inside lambda,i==1
    i==2
