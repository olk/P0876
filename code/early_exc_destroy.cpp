struct Excp {
    Excp(const char *x) : x(x) {}
    ~Excp() { fprintf(stderr, "Destroying Excp(\"%s\").\n", x); }
    const char *const x;
};

int main(void) {
    // 0. fiberB is prepared but not yet resumed
    fiber_context fiberB{[](fiber_context &&fiberA) {
        try {
            // 3. fiberB throws Excp("lambda")
            throw Excp("lambda");
        } catch (const Excp& exc) {
            // 4. fiberB catches Excp("lambda"), resumes default fiber
            fiberA = std::move(fiberA).resume();
            // 8. *** ANY ACCESS TO exc HERE ACCESSES A DESTROYED OBJECT ***
            fprintf(stderr, "9. Should destroy Excp(\"lambda\").\n");
            // 9. Excp("main") is destroyed instead
        }
        // 10. fiberB terminates by resuming default fiber
        return std::move(fiberA);
    }};
    try {
        // 1. default fiber throws Excp("main")
        throw Excp("main");
    } catch (const Excp&) {
        // 2. default fiber catches Excp("main"), enters fiberB
        fiberB = std::move(fiberB).resume();
        // 5. current_exception() reports Excp("lambda")
        fprintf(stderr, "6. Should destroy Excp(\"main\").\n");
        // 6. the current_exception() is destroyed
    }
    // 7. default fiber resumes fiberB to let it terminate
    fiberB = std::move(fiberB).resume();
}

Output:
6. Should destroy Excp("main").
Destroying Excp("lambda").
9. Should destroy Excp("lambda").
Destroying Excp("main").
