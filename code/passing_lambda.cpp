int i=1;
std::fiber lambda{[&i](fiber&& caller){
    std::cout << "inside lambda,i==" << i << std::endl;
    i+=1;
    caller=caller.resume();
    return std::move(caller);
}};
lambda=lambda.resume();
std::cout << "i==" << i << std::endl;
lambda=lambda.resume();

output:
    inside lambda,i==1
    i==2
