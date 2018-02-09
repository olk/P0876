class filament{
private:
    fiber       f_;

public:
    ...
    void resume_next( filament& fila){
        std::move(fila.f_).resume_with([this](fiber&& f)->fiber{
            f_=std::move(f);
            return {};
        }
    }
};
