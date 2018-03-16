class cross_thread_fiber_context {
public:
    cross_thread_fiber_context() noexcept;

    template<typename Fn>
    explicit cross_thread_fiber_context(Fn&& fn);

    template<typename StackAlloc, typename Fn>
    cross_thread_fiber_context(std::allocator_arg_t, StackAlloc&& salloc, Fn&& fn);

    ~cross_thread_fiber_context();

    cross_thread_fiber_context(cross_thread_fiber_context&& other) noexcept;
    cross_thread_fiber_context& operator=(cross_thread_fiber_context&& other) noexcept;
    cross_thread_fiber_context(const cross_thread_fiber_context& other) noexcept = delete;
    cross_thread_fiber_context& operator=(const cross_thread_fiber_context& other) noexcept = delete;

    cross_thread_fiber_context resume() &&;
    template<typename Fn>
    cross_thread_fiber_context resume_with(Fn&& fn) &&;

    cross_thread_fiber_context resume_other_thread() &&;
    template<typename Fn>
    cross_thread_fiber_context resume_other_thread_with(Fn&& fn) &&;

    bool any_thread() const noexcept;

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;
    bool operator<(const cross_thread_fiber_context& other) const noexcept;
    void swap(cross_thread_fiber_context& other) noexcept;
};
