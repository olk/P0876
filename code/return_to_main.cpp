int main() {
    fiber_context f{make_fiber_context([]{
        ...
        // switch to `main()` only by returning
    }).first};
    f.resume(); // resume `f`
    return 0;
}
