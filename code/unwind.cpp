constexpr _Unwind_Exception_Class __gxx_fiber_exception_class
= ((((((((_Unwind_Exception_Class) 'G'
     << 8 | (_Unwind_Exception_Class) 'N')
    << 8 | (_Unwind_Exception_Class) 'U')
       << 8 | (_Unwind_Exception_Class) 'F')
      << 8 | (_Unwind_Exception_Class) 'I')
     << 8 | (_Unwind_Exception_Class) 'B')
    << 8 | (_Unwind_Exception_Class) 'E')
   << 8 | (_Unwind_Exception_Class) 'R');

#define __GXX_INIT_FIBER_EXCEPTION_CLASS(c) c = __gxx_fiber_exception_class

class foreign_unwind_ex : public _Unwind_Exception {
private:
    static void fiber_unwind_cleanup(_Unwind_Reason_Code code, _Unwind_Exception *exc) {
        // We only want to be called through _Unwind_DeleteException.
        if ( _URC_FOREIGN_EXCEPTION_CAUGHT != code) {
            std::terminate();
        }
        delete exc;
    }

public:
    foreign_unwind_ex() noexcept {
        __GXX_INIT_FIBER_EXCEPTION_CLASS( exception_class);
        exception_cleanup = fiber_unwind_cleanup;
    }
};

template< typename Ctx >
_Unwind_Reason_Code fiber_unwind_stop(
		int version,
        _Unwind_Action actions,
        _Unwind_Exception_Class exc_class,
        _Unwind_Exception * exc,
        _Unwind_Context * context,
        void * param) {
    if ( actions & _UA_END_OF_STACK) {
        _Unwind_DeleteException( exc);
        // end of stack: switch back to calling fiber
        Ctx{ param }.resume();
        __builtin_unreachable();
    }
    return _URC_NO_REASON;
}

template< typename Ctx >
transfer_t fiber_unwind( transfer_t t) {
    _Unwind_ForcedUnwind( new foreign_unwind_ex{}, fiber_unwind_stop< Ctx >, t.fctx);
    __builtin_unreachable();
}
