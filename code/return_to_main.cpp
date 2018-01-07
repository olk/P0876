int main() {
    fiber f{[]{
        ...
        // switch to `main()` only by returning
    }};
    f.resume(); // resume `f`
    return 0;
}
