fiber_context* pf1;
fiber_context f4{make_fiber_context([&pf1]{
    pf1->resume();
}).first};
fiber_context f3{make_fiber_context([&f4]{
    f4.resume();
}).first};
fiber_context f2{make_fiber_context([&f3]{
    f3.resume();
}).first};
fiber_context f1{make_fiber_context([&f2]{
    f2.resume();
}).first};
pf1=&f1;
f1.resume();
