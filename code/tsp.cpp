namespace std {

template <class T>
class thread_specific_ptr {
public:
    // [thread.ptr.cons], constructors, move and assignment
    thread_specific_ptr();

    explicit thread_specific_ptr(void (*cleanup_function)(T*));

    ~thread_specific_ptr();

    thread_specific_ptr(const thread_specific_ptr& other) = default;
    thread_specific_ptr& operator=(const thread_specific_ptr& other) = default;
    thread_specific_ptr(thread_specific_ptr&& other) = default;
    thread_specific_ptr& operator=(thread_specific_ptr&& other) = default;

    // [thread.ptr.mem], members
    T* get() const noexcept;
    T* operator->() const noexcept;
    T& operator*() const noexcept;

    T* release() noexcept;
    void reset(T* new_value=nullptr);

    explicit operator bool() const noexcept;

    void swap(thread_specific_ptr& other) noexcept;

    // [thread.ptr.special], specialized algorithms
    friend void swap(thread_specific_ptr& lhs, thread_specific_ptr& rhs) noexcept;
};

} // namespace std
