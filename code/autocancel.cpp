// autocancel is a wrapper class that, when destroyed, implicitly cancels its
// stored fiber_context. It uses the tactic seen in the example 'filament'
// class to continually update the fiber_context representing the fiber of
// interest. (See "returning synthesized std::fiber_context instance from
// resume()")
class autocancel{
private:
    std::fiber_context       f_;

public:
    autocancel() = default;
    autocancel(std::fiber_context&& f):
        f_{std::move(f)}
    {}

    ~autocancel() {
        // For purposes of code examples, assume that cancel() always
        // returns an empty fiber_context instance, which is safe to
        // discard.
        std::move(f_).cancel();
    }

    // for initial entry from a plain fiber rather than an autocancel instance
    void resume(){
        std::move(f_).resume();
    }
    
    void resume( autocancel& ac){
        std::move(ac.f_).resume_with([this](std::fiber_context&& f)->std::fiber_context{
            f_=std::move(f);
            return {};
        });
    }
};
