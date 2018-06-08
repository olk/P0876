class filament{
private:
    fiber_handle       f_;

public:
    ...
    void resume_next( filament& fila){
        std::move(fila.f_).resume_with([this](fiber_handle&& f)->fiber_handle{
            f_=std::move(f);
            return {};
        }
    }
};
