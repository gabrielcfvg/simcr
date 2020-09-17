#ifndef COELHO
#define COELHO

#include <tuple>
#include <vector>
#include "entidade.hpp"

class Coelho: public Entidade {

    public:
        bool filho;

    public:
        Coelho(int x, int y);

        void process(MAPA* mapa);

        std::tuple<bool, int, int> escolher_lado(MAPA* mapa);

        bool validacao_pos(int x, int y, MAPA* mapa);

};


#endif