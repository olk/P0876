namespace std {

class fiber_context {
public:
    fiber_context() noexcept;

    template<typename F>
    explicit fiber_context(F&& entry);

    template<typename F, typename D>
    explicit fiber_context(F&& entry, span<byte> stack, D&& deleter);

    ~fiber_context();

    fiber_context(fiber_context&& other) noexcept;
    fiber_context& operator=(fiber_context&& other) noexcept;
    fiber_context(const fiber_context& other) noexcept = delete;
    fiber_context& operator=(const fiber_context& other) noexcept = delete;

    fiber_context resume() &&;
    template<typename Fn>
    fiber_context resume_with(Fn&& fn) &&;

    bool can_resume() noexcept;

    explicit operator bool() const noexcept;
    bool empty() const noexcept;
    void swap(fiber_context& other) noexcept;

private:
    unspecified-type state;         // exposition only
};

} // namespace std
