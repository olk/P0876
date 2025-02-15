fiber_context other_fiber;

void yield()
{
    assert(other_fiber);
    // We switch back and forth between two fibers, A and B. One is running,
    // the other is suspended. When fiber A calls yield():
    //  1. other_fiber is emptied
    //  2. the lambda is called on fiber B
    //  3. other_fiber is set to fiber A
    //  4. fiber B receives empty fiber_context, which is ignored
    //  5. fiber B runs for a while
    //  6. fiber B calls yield()
    //  7. other_fiber is emptied
    //  8. the lambda is called on fiber A
    //  9. other_fiber is set to fiber B
    // 10. fiber A receives empty fiber_context, which is ignored
    // 11. fiber A runs for a while...
    std::move(other_fiber).resume_with(
        [](fiber_context&& prev)
        {
            other_fiber = std::move(prev);
            return fiber_context{};
        });
}

void uncaughts(std::string name)
{
    std::cout << "  " << name << ": std::uncaught_exceptions() = "
              << std::uncaught_exceptions() << std::endl;
}

void current(std::string name)
{
    auto exc = std::current_exception();
    if (! exc)
    {
        std::cout << "  " << name << ": std::current_exception() = nullptr" << std::endl;
    }
    else
    {
        try
        {
            std::rethrow_exception(exc);
        }
        catch (const std::exception& err)
        {
            std::cout << "  " << name << ": std::current_exception() = " << err.what() << std::endl;
        }
    }
}

void hop(std::string name)
{
    std::cout << name << " suspending:" << std::endl;
    std::string before{ name + " before" };
    uncaughts(before);
    current(before);
    yield();
    std::cout << name << " resuming:" << std::endl;
    std::string after{ name + " after" };
    uncaughts(after);
    current(after);
}

struct destruct
{
    destruct(std::string name): mName(name + ": ~destruct()") {}
    ~destruct()
    {
        hop(mName);
    }
    std::string mName;
};        

void testcode(std::string name)
{
    try
    {
        destruct d(name);
        std::string exname = name + " exception";
        std::cout << "throw " << exname << std::endl;
        throw std::runtime_error(exname);
    }
    catch (const std::exception& err)
    {
        std::cout << name << " caught " << err.what() << std::endl;
        hop(name + " catch block");
    }
}

fiber_context fiber(fiber_context&&)
{
    std::cout << "fiber() starting" << std::endl;
    testcode("fiber()");
    std::cout << "fiber() ending" << std::endl;
    assert(other_fiber);
    return std::move(other_fiber);
}

int main(int argc, char *argv[])
{
    std::cout << "main() starting" << std::endl;
    other_fiber = fiber_context(fiber);
    hop("main()");
    testcode("main()");
    std::cout << "main() ending" << std::endl;
    assert(! other_fiber);
    return 0;
}
