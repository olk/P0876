class fiber_context {
public:
    fiber_context() noexcept;

    template<typename Fn>
    explicit fiber_context(Fn&& fn);

    template<typename StackAlloc, typename Fn>
    fiber_context(std::allocator_arg_t, StackAlloc&& salloc, Fn&& fn);

    ~fiber_context();

    fiber_context(fiber_context&& other) noexcept;
    fiber_context& operator=(fiber_context&& other) noexcept;
    fiber_context(const fiber_context& other) noexcept = delete;
    fiber_context& operator=(const fiber_context& other) noexcept = delete;

    fiber_context resume() &&;
    template<typename Fn>
    fiber_context resume_with(Fn&& fn) &&;
    fiber_context resume_other_thread() &&;
    template<typename Fn>
    fiber_context resume_other_thread_with(Fn&& fn) &&;

    bool uses_system_stack() noexcept;
    std::thread::id previous_thread() noexcept;

    explicit operator bool() const noexcept;
    bool operator<(const fiber_context& other) const noexcept;
    void swap(fiber_context& other) noexcept;
};
