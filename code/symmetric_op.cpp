fiber_context* pf1;
fiber_context f4{[&pf1]{
    pf1->resume();
};
fiber_context f3{[&f4]{
    f4.resume();
}};
fiber_context f2{[&f3]{
    f3.resume();
}};
fiber_context f1{[&f2]{
    f2.resume();
}};
pf1=&f1;
f1.resume();
