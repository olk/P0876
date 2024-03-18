struct Excp {
    Excp(const char *x) : x(x) {}
    ~Excp() { fprintf(stderr, "Destroying Excp(\"%s\").\n", x); }
    const char *const x;
};

int main(void) {
    fiber_context fiberB{[](fiber_context &&fiberA) {
        try {
            throw Excp(__PRETTY_FUNCTION__);
        } catch (...) {
            fiberA = std::move(fiberA).resume();
            fprintf(stderr, "Should destroy Excp(\"%s\").\n", __PRETTY_FUNCTION__);
        }
        return std::move(fiberA);
    }};
    try {
        throw Excp(__PRETTY_FUNCTION__);
    } catch (...) {
        fiberB = std::move(fiberB).resume();
        fprintf(stderr, "Should destroy Excp(\"%s\").\n", __PRETTY_FUNCTION__);
    }
    fiberB = std::move(fiberB).resume();
}

Output:
Should destroy Excp("int main()").
Destroying Excp("main()::<lambda(fiber_context&&)>").
Should destroy Excp("main()::<lambda(fiber_context&&)>").
Destroying Excp("int main()").
