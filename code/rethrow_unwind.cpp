try{
    // ... body of fiber logic ...
}catch(const std::unwind_exception&){
    // do not swallow unwind_exception
    throw;
}catch(...){
    // ... log, or whatever ...
}
