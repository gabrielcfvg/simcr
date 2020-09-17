#include "../headers/raposa.hpp"
#include "../headers/main.hpp"

Raposa::Raposa(int x, int y): Entidade(x, y) {
    this->tipo = TileObject::Raposa;
    this->age = get_GER_PROC_RAPOSAS();
}



void Raposa::process(MAPA* mapa) {
    auto tmp = this->escolher_lado(mapa);

    if (this->filho == false && this->age == 0) {
        this->filho = true;
    }

    if (this->fome == 0) {
        (*mapa)[this->x][this->y] = new Entidade{this->x, this->y};
        printf("RAPOSA MORREU\n");
        delete this;
    };

    if (std::get<0>(tmp)) {

        delete (*mapa)[std::get<1>(tmp)][std::get<2>(tmp)];
        (*mapa)[std::get<1>(tmp)][std::get<2>(tmp)] = (*mapa)[this->x][this->y];

        if (this->filho == true) {
            (*mapa)[this->x][this->y] = new Raposa{this->x, this->y};
            this->filho = false;
            this->age = get_GER_PROC_RAPOSAS();
            //printf("FILHO\n");
        }
        else {
            (*mapa)[this->x][this->y] = new Entidade{this->x, this->y};
            this->age -= 1;
            //printf("NÂO FILHO\n");
        }

        this->estabelecido = false;
        this->x = std::get<1>(tmp);
        this->y = std::get<2>(tmp);
    }
    else {

        if (this->filho == false) {
            this->age -= 1;
        }
    }

    this->fome -= 1;
}

std::tuple<bool, int, int> Raposa::escolher_lado(MAPA* mapa) {

            
    std::tuple<bool, int, int> poss_coelho[] = {
        std::make_tuple(false, 0, 0),
        std::make_tuple(false, 0, 0),
        std::make_tuple(false, 0, 0), 
        std::make_tuple(false, 0, 0)
    };

    std::tuple<bool, int, int> poss_vazio[] = {
        std::make_tuple(false, 0, 0), 
        std::make_tuple(false, 0, 0), 
        std::make_tuple(false, 0, 0), 
        std::make_tuple(false, 0, 0)
    };

    auto validade_and_insert = [&](int idx, int x, int y) {

        auto res = this->validacao_pos(x, y, mapa);

        if (std::get<0>(res)) {

            switch (std::get<1>(res)) {
                case TileObject::Coelho: {
                    poss_coelho[idx] = std::make_tuple(true, x, y);
                    break;
                }
                case TileObject::Vazio: {
                    poss_vazio[idx] = std::make_tuple(true, x, y);
                }
            }
        }
    };

    if (this->y >= 1) {
        validade_and_insert(0, this->x, this->y - 1);
    }
    if (this->x < get_SIZE_X() - 1)  {
        validade_and_insert(1, this->x + 1, this->y);
    }
    if (this->y < get_SIZE_Y() - 1) {
        validade_and_insert(2, this->x, this->y + 1);
    }
    if (this->x >= 1) {
        validade_and_insert(3, this->x - 1, this->y);
    }

    int Pc = 0;
    int Pv = 0;
    int ch;

    for (int i = 0; i < 4; i++) {
        if (std::get<0>(poss_coelho[i])) {
            Pc++;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (std::get<0>(poss_vazio[i])) {
            Pv++;
        }
    }

    if (Pc > 0) {

        ch = (get_ATUAL_GER() + this->x + this->y) % Pc;
        Pc = -1;

        for (int i = 0; i < 4; i++) {
            if (std::get<0>(poss_coelho[i])) {
                Pc++;
            }
            if (Pc == ch) {
                this->fome = get_GER_ALIM_RAPOSAS();
                return poss_coelho[i];
            }
        }
    }
    else if (Pc == 0) {

        if (Pv == 0) {
            return std::tuple<bool, int, int> (false, this->x, this->y);
        }

        ch = (get_ATUAL_GER() + this->x + this->y) % Pv;
        Pv = -1;

        for (int i = 0; i < 4; i++) {
            if (std::get<0>(poss_vazio[i])) {
                Pv++;
            }
            if (Pv == ch) {
                return poss_vazio[i];
            }
        }
    }
    return std::tuple<bool, int, int> (false, this->x, this->y);
}

std::tuple<bool, TileObject> Raposa::validacao_pos(int x, int y, MAPA* mapa) {

    if ((*mapa)[x][y]->tipo == TileObject::Vazio) {
        return std::make_tuple(true, TileObject::Vazio);
    }

    else if ((*mapa)[x][y]->tipo == TileObject::Coelho) {
        return std::make_tuple(true, TileObject::Coelho);
    }

    else if ((*mapa)[x][y]->tipo == TileObject::Raposa) {

        // significa que a raposa na posição se moveu nesse
        // turno e no movimento comeu um coelho
        if ((*mapa)[x][y]->sobre_coelho) {
            if ((*mapa)[x][y]->age > this->age) {
                return std::make_tuple(true, TileObject::Coelho);
            }
        }

        // significa que a raposa na posição se moveu nesse
        // turno e foi para um espaço vazio
        else if ((*mapa)[x][y]->estabelecido) {
            if ((*mapa)[x][y]->fome < this->fome) {
                return std::make_tuple(true, TileObject::Coelho);
            }

            else if ((*mapa)[x][y]->fome == this->fome && (*mapa)[x][y]->age > this->age) {
                return std::make_tuple(true, TileObject::Coelho);
            }
        }
    }

    return std::make_tuple(false, TileObject::Vazio);
}
