struct Bad: public std::runtime_error {
    Bad(): std::runtime_error("Bad") {}
};

struct Worse: public std::runtime_error {
    Worse(): std::runtime_error("Worse") {}
};

int main(void) {
    // 0. fiberB is prepared but not yet resumed
    fiber_context fiberB{[](fiber_context &&fiberA) {
        try {
            // 3. fiberB throws Worse
            throw Worse();
        } catch (const std::exception& caught) {
            // 4. fiberB catches Worse, resumes default fiber
            fiberA = std::move(fiberA).resume();
        }
        // 8. fiberB terminates by resuming default fiber
        return std::move(fiberA);
    }};
    std::string thrown{ "Nothing" };
    try {
        try {
            Bad myBad;
            thrown = myBad.what();
            // 1. default fiber throws Bad
            throw myBad;
        } catch (const std::exception& caught) {
            // 2. default fiber catches Bad, enters fiberB
            fiberB = std::move(fiberB).resume();
            // 5. the most recently activated handler within the thread that
            // is still active is in fiberB, and its exception is Worse
            throw;
        }
    } catch (const std::exception& caught) {
        // 6. caught is Worse
        std::cout << "Situation went from " << thrown << " to " << caught.what()
                  << std::endl;
    }
    // 7. default fiber resumes fiberB to let it terminate
    fiberB = std::move(fiberB).resume();
}
