class fiber_context {
public:
    fiber_context() noexcept;

    template<typename Fn>
    explicit fiber_context(Fn&& fn);

    ~fiber_context();

    fiber_context(fiber_context&& other) noexcept;
    fiber_context& operator=(fiber_context&& other) noexcept;
    fiber_context(const fiber_context& other) noexcept = delete;
    fiber_context& operator=(const fiber_context& other) noexcept = delete;

    fiber_context resume() &&;
    template<typename Fn>
    fiber_context resume_with(Fn&& fn) &&;
    fiber_context resume_from_any_thread() &&;
    template<typename Fn>
    fiber_context resume_from_any_thread_with(Fn&& fn) &&;

    bool can_resume() noexcept;
    bool can_resume_from_any_thread() noexcept;

    explicit operator bool() const noexcept;
    bool valid() const noexcept;
    void swap(fiber_context& other) noexcept;
};
