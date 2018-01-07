int main(){
    int a;
    fiber m=fiber::current(); // get active fiber
    fiber f{[&]{
        a=0;
        int b=1;
        for(;;){
            m.resume(); // switch to `main()`
            int next=a+b;
            a=b;
            b=next;
        }
    }};
    for(int j=0; j<10; ++j) {
        f.resume(); // resume `f`
        std::cout << a << " ";
    }
    return 0;
}
