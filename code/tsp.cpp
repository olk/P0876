namespace std {

template <class T, class Deleter=default_delete<T>>
class thread_specific_ptr {
public:
    // [thread.ptr.cons], constructors, move and assignment
    thread_specific_ptr();

    explicit thread_specific_ptr(const Deleter& deleter);
    thread_specific_ptr(thread_specific_ptr&& other);

    ~thread_specific_ptr();

    thread_specific_ptr& operator=(thread_specific_ptr&& other);

    // [thread.ptr.mem], members
    T* get() const noexcept;
    T* operator->() const noexcept;
    T& operator*() const noexcept;

    [[nodiscard]] unique_ptr<T, Deleter> release() noexcept;
    void reset() noexcept;
    void reset(T* new_value);

    explicit operator bool() const noexcept;

    void swap(thread_specific_ptr& other) noexcept;

    // [thread.ptr.special], specialized algorithms
    friend void swap(thread_specific_ptr& lhs, thread_specific_ptr& rhs) noexcept;

    // disable copy from lvalue
    thread_specific_ptr(const thread_specific_ptr&) = delete;
    thread_specific_ptr& operator=(const thread_specific_ptr&) = delete;

private:
    unique_ptr<T, Deleter> p;       // exposition only
};

} // namespace std
