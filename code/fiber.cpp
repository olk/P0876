namespace std {
namespace experimental {
inline namespace concurrency_v2 {

class fiber_context {
public:
    fiber_context() noexcept;

    template<typename Fn0, typename Fn1>
    explicit fiber_context(Fn0&& entry, Fn1&& cancel);

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

    fiber_context cancel() &&;
    fiber_context cancel_from_any_thread() &&;

    bool can_resume() noexcept;
    bool can_resume_from_any_thread() noexcept;

    explicit operator bool() const noexcept;
    bool valid() const noexcept;
    void swap(fiber_context& other) noexcept;
};

} // namespace concurrency_v2
} // namespace experimental
} // namespace std
