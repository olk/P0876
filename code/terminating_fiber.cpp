int main(){
    fiber f{[](fiber&& m){
        return std::move(m); // resume `main()` by returning `m`
    }};
    std::move(f).resume(); // resume `f`
    return 0;
}
