int a;
autocancel consumer, generator;
generator = autocancel{[&a,&consumer,&generator](std::fiber_context&& m){
    a=0;
    int b=1;
    while (! generator.stop_requested()){
        generator.resume(consumer);
        int next=a+b;
        a=b;
        b=next;
    }
    return std::move(m);
}};
consumer = autocancel{[&a,&consumer,&generator](std::fiber_context&& m){
    std::vector<int> v(10);
    std::generate(v.begin(), v.end(), [&a,&consumer,&generator]() mutable {
        consumer.resume(generator);
        return a;
    });
    std::cout << "v: ";
    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return std::move(m);
}};
consumer.resume();

output: v: 0 1 1 2 3 5 8 13 21 34
