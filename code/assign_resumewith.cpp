class filament{
private:
    fiber       f_;

public:
    ...
    void resume_next( filament& fila){
        fila.f_.resume_with([this](fiber&& f)->fiber{
            f_=std::move(f);
            return {};
        }
    }
};
