int a;
autocancel consumer, generator;
generator = launch([&a,&consumer,&generator](std::fiber_context&& m){
    a=0;
    int b=1;
    for(;;){
        generator.resume(consumer);
        int next=a+b;
        a=b;
        b=next;
    }
    return std::move(m);
});
consumer = launch([&a,&consumer,&generator](std::fiber_context&& m){
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), [&a,&generator]() mutable {
        consumer.resume(generator);
        return a;
    });
    std::cout << "v: ";
    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return std::move(m);
});
consumer.resume();

output: v: 0 1 1 2 3 5 8 13 21 34
