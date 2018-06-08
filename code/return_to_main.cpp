int main() {
    fiber_handle f{[]{
        ...
        // switch to `main()` only by returning
    }};
    f.resume(); // resume `f`
    return 0;
}
