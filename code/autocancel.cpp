// notify_done is an RAII class that binds a bool& reference and, when
// destroyed, sets the referenced bool true.
class notify_done
{
public:
    notify_done(bool& done):
        done_(done)
    {
        done_ = false;
    }

    notify_done(const notify_done&) = delete;
    notify_done& operator=(const notify_done&) = delete;

    ~notify_done()
    {
        done_ = true;
    }

private:
    bool& done_;
};

// autocancel is a wrapper class that launches a fiber and, when destroyed,
// implicitly requests stop on that fiber. It uses the tactic seen in the
// example 'filament' class to continually update the fiber_context
// representing the fiber of interest. (See "returning synthesized
// std::fiber_context object from resume()")
class autocancel{
private:
    std::fiber_context f_;
    bool               stop_flag_{false};
    bool               done_{false};

public:
    autocancel() = default;
    template <typename Fn>
    autocancel(Fn&& entry_function)
    {
        f_ = std::fiber_context(
            [this, entry=std::forward<Fn>(entry_function)]
            (std::fiber_context&& prev)
            {
                notify_done term(done_);
                return entry(std::move(prev));
            });
    }
                
    autocancel(const autocancel&) = delete;
    autocancel& operator=(const autocancel&) = delete;
    autocancel(autocancel&&) = delete;
    autocancel& operator=(autocancel&&) = delete;

    ~autocancel() {
        stop_flag_ = true;
        while (f_ && ! done_) {
            resume(*this);
        }
        assert(done_);
    }

    bool stop_requested() const noexcept {
        return stop_flag_;
    }

    // for initial entry from a plain fiber rather than an autocancel object
    std::fiber_context resume(){
        return std::move(f_).resume();
    }
    
    void resume( autocancel& ac){
        std::move(ac.f_).resume_with(
            [this](std::fiber_context&& f)->std::fiber_context
            {
                f_ = std::move(f);
                return {};
            });
    }
};
