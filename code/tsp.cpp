namespace std {

template <class T, class Deleter=default_delete<T>>
class thread_specific_ptr {
public:
    // [thread.ptr.cons], constructors, move and assignment
    thread_specific_ptr();
    explicit thread_specific_ptr(const Deleter& deleter);
    explicit thread_specific_ptr(Deleter&& deleter);

    ~thread_specific_ptr();

    // [thread.ptr.mem], members
    T* get() const noexcept;
    T* operator->() const noexcept;
    T& operator*() const noexcept;

    [[nodiscard]] T* release() noexcept;
    void reset() noexcept;
    void reset(T* new_value);

    explicit operator bool() const noexcept;

    // disable copy from lvalue
    thread_specific_ptr(const thread_specific_ptr&) = delete;
    thread_specific_ptr& operator=(const thread_specific_ptr&) = delete;
    // disable move
    thread_specific_ptr(thread_specific_ptr&&) = delete;
    thread_specific_ptr& operator=(thread_specific_ptr&&) = delete;

private:
    Deleter del;                    // exposition only
};

} // namespace std
