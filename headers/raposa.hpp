#ifndef RAPOSA
#define RAPOSA

#include <tuple>
#include <vector>
#include "entidade.hpp"

class Raposa: public Entidade {

    public:
        bool filho = false;

    public:
        Raposa(int x, int y);

        void process(MAPA* mapa);

        std::tuple<bool, int, int> escolher_lado(MAPA* mapa);

        std::tuple<bool, TileObject> validacao_pos(int x, int y, MAPA* mapa);

};

#endif