// autocancel is a wrapper class that, when destroyed, implicitly cancels its
// stored fiber_context. It uses the tactic seen earlier in the example
// 'filament' class to continually update the fiber_context representing the
// fiber of interest.
class autocancel{
private:
    std::fiber_context       f_;

public:
    autocancel(std::fiber_context&& f):
        f_{std::move(f)}
    {}

    ~autocancel() {
        // For purposes of code examples, assume that cancel() always
        // returns an empty fiber_context instance, which is safe to
        // discard.
        std::move(f_).cancel();
    }

    void resume( autocancel& ac){
        std::move(ac.f_).resume_with([this](std::fiber_context&& f)->std::fiber_context{
            f_=std::move(f);
            return {};
        });
    }
};
