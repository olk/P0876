folly::EventBase ev_base;
auto& fiber_manager=folly::fibers::getFiberManager(ev_base);
folly::fibers::Baton baton;
fiber_manager.addTask([&]{
	std::cout << "task 1: start" << std::endl;
	baton.wait();
	std::cout << "task 1: after baton.wait()" << std::endl;
});
fiber_manager.addTask([&]{
	std::cout << "task 2: start" << std::endl;
	baton.post();
	std::cout << "task 2: after baton.post()" << std::endl;
});
ev_base.loop();
