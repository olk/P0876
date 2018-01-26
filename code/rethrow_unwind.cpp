try{
    // ... body of context logic ...
}catch(const std::unwind_exception&){
    // do not swallow unwind_exception
    throw;
}catch(...){
    // ... log, or whatever ...
}
