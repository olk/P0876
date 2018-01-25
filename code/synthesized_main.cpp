int main(){
    fiber f{[](fiber&& m){
        m=m.resume(); // switch to `main()`
        ...
    }};
    f=f.resume(); // resume `f`
    return 0;
}
