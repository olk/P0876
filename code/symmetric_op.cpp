fiber* pf1;
fiber f4{[&pf1]{
    pf1->resume();
};
fiber f3{[&f4]{
    f4.resume();
}};
fiber f2{[&f3]{
    f3.resume();
}};
fiber f1{[&f2]{
    f2.resume();
}};
pf1=&f1;
f1.resume();
