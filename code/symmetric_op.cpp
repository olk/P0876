fiber_context* pf1;
fiber_context f4{[&pf1]{
    pf1->resume();
}, assert_cancel};
fiber_context f3{[&f4]{
    f4.resume();
}, assert_cancel};
fiber_context f2{[&f3]{
    f3.resume();
}, assert_cancel};
fiber_context f1{[&f2]{
    f2.resume();
}, assert_cancel};
pf1=&f1;
f1.resume();
