#ifndef ENTIDADE
#define ENTIDADE

#include <tuple>
#include <vector>
#include <memory>
#include <cstdio>

#define MAPA std::vector<std::vector<std::unique_ptr<Entidade>>>

enum class TileObject {
    Raposa,
    Coelho,
    Rocha,
    Vazio
};


class Entidade {

    protected:
        int x;
        int y;

    public:
        TileObject tipo;
        bool sobre_coelho = false;
        bool estabelecido = true;
        int fome;
        int age;


    public:
        Entidade(int x, int y);
        
        virtual void process(MAPA* mapa);
        
        void set_pos(int x, int y);

};

class Rocha: public Entidade {

    public:
        Rocha(int x, int y);

        void process(MAPA* mapa);
};

#endif
