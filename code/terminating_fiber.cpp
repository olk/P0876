int main(){
    fiber f{[](fiber&& m){
        return std::move(m); // resume `main()` by returning `m`
    }};
    f.resume(); // resume `f`
    return 0;
}
