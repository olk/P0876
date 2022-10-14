// autocancel is a wrapper class that, when destroyed, implicitly requests
// stop on its stored fiber_context. It uses the tactic seen in the example
// 'filament' class to continually update the fiber_context representing the
// fiber of interest. (See "returning synthesized std::fiber_context instance
// from resume()")
class autocancel{
private:
    std::fiber_context       f_;

public:
    autocancel() = default;
    template <typename Fn>
    autocancel(Fn&& entry_function):
        f_{std::forward<Fn>(entry_function)}
    {}
    autocancel& operator=(autocancel&& other) = default;

    ~autocancel() {
        f_.request_stop();
        while (f_) {
            resume(*this);
        }
    }

    bool stop_requested() const noexcept {
        return f_.get_stop_source().stop_requested();
    }

    // for initial entry from a plain fiber rather than an autocancel instance
    std::fiber_context resume(){
        return std::move(f_).resume();
    }
    
    void resume( autocancel& ac){
        std::move(ac.f_).resume_with([this](std::fiber_context&& f)->std::fiber_context{
            f_=std::move(f);
            return {};
        });
    }
};
