class fiber {
public:
    fiber() noexcept;

    template<typename Fn>
    fiber(Fn&& fn);

    template<typename StackAlloc, typename Fn>
    fiber(std::allocator_arg_t, StackAlloc&& salloc, Fn&& fn);

    ~fiber();

    fiber( fiber&& other) noexcept;
    fiber & operator=( fiber&& other) noexcept;
    fiber( const fiber& other) noexcept = delete;
    fiber & operator=( const fiber& other) noexcept = delete;

    fiber resume();
    template<typename Fn>
    fiber resume_with( Fn&& fn);

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;
    bool operator==( const fiber& other) const noexcept;
    bool operator!=( const fibert& other) const noexcept;
    bool operator<( const fiber& other) const noexcept;
    bool operator>( const fiber& other) const noexcept;
    bool operator<=( const fiber& other) const noexcept;
    bool operator>=( const fiber& other) const noexcept;
    void swap( fiber& other) noexcept;
};
