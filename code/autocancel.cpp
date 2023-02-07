// autocancel is a wrapper class that, when destroyed, implicitly requests
// stop on its stored fiber_context. It uses the tactic seen in the example
// 'filament' class to continually update the fiber_context representing the
// fiber of interest. (See "returning synthesized std::fiber_context instance
// from resume()")
class autocancel{
private:
    std::pair<std::fiber_context, std::stop_source> fiber_;

public:
    autocancel() = default;
    template <typename Fn>
    autocancel(Fn&& entry_function):
        fiber_{std::make_fiber_context(std::forward<Fn>(entry_function))}
    {}
    autocancel& operator=(autocancel&& other) = default;

    ~autocancel() {
        fiber_.second.request_stop();
        while (fiber_.first) {
            resume(*this);
        }
    }

    bool stop_requested() const noexcept {
        return fiber_.second.stop_requested();
    }

    // for initial entry from a plain fiber rather than an autocancel instance
    std::fiber_context resume(){
        return std::move(fiber_.first).resume();
    }
    
    void resume( autocancel& ac){
        std::move(ac.fiber_.first).resume_with(
            [this](std::fiber_context&& f)->std::fiber_context
            {
                fiber_.first = std::move(f);
                return {};
            });
    }
};
