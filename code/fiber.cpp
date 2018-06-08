class fiber_handle {
public:
    fiber_handle() noexcept;

    template<typename Fn>
    explicit fiber_handle(Fn&& fn);

    ~fiber_handle();

    fiber_handle(fiber_handle&& other) noexcept;
    fiber_handle& operator=(fiber_handle&& other) noexcept;
    fiber_handle(const fiber_handle& other) noexcept = delete;
    fiber_handle& operator=(const fiber_handle& other) noexcept = delete;

    fiber_handle resume() &&;
    template<typename Fn>
    fiber_handle resume_with(Fn&& fn) &&;
    fiber_handle resume_other_thread() &&;
    template<typename Fn>
    fiber_handle resume_other_thread_with(Fn&& fn) &&;

    bool can_resume() noexcept;
    bool can_resume_other_thread() noexcept;

    explicit operator bool() const noexcept;
    bool operator<(const fiber_handle& other) const noexcept;
    void swap(fiber_handle& other) noexcept;
};
