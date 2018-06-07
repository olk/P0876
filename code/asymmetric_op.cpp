fiber_handle f4{[]{
    self::suspend();
};
fiber_handle f3{[&f4]{
    f4.resume();
    self::suspend();
}};
fiber_handle f2{[&f3]{
    f3.resume();
    self::suspend();
}};
fiber_handle f1{[&f2]{
    f2.resume();
    self::suspend();
}};
f1.resume();
