int main(){
    fiber f{[](fiber&& m){
        m.resume(); // switch to `main()`
    }};
    f.resume(); // resume `f`
    return 0;
}
