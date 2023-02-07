namespace std {
namespace experimental {
inline namespace concurrency_v2 {

class fiber_context {
public:
    fiber_context() noexcept;
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
};

template <typename Fn>
std::pair<fiber_context, stop_source> make_fiber_context(Fn&& f);

} // namespace concurrency_v2
} // namespace experimental
} // namespace std
