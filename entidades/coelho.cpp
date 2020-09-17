#include "../headers/coelho.hpp"
#include "../headers/main.hpp"

Coelho::Coelho(int x, int y): Entidade(x, y) {
    this->tipo = TileObject::Coelho;
    this->age = get_GER_PROC_COELHOS();
}

void Coelho::process(MAPA* mapa) {
    auto tmp = this->escolher_lado(mapa);

    if (this->filho == false && this->age == 0) {
        this->filho = true;
    }

    if (std::get<0>(tmp)) {

        delete (*mapa)[std::get<1>(tmp)][std::get<2>(tmp)];
        (*mapa)[std::get<1>(tmp)][std::get<2>(tmp)] = (*mapa)[this->x][this->y];

        if (this->filho == true) {
            (*mapa)[this->x][this->y] = new Coelho{this->x, this->y};
            this->filho = false;
            this->age = get_GER_PROC_COELHOS();
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
}

std::tuple<bool, int, int> Coelho::escolher_lado(MAPA* mapa) {
    
    //printf("pos x: %d, y: %d\n", this->x, this->y);

    std::tuple<bool, int, int> poss[] = {std::make_tuple(false, 0, 0), std::make_tuple(false, 0, 0), std::make_tuple(false, 0, 0), std::make_tuple(false, 0, 0)};
    
    if (this->y >= 1) {
        if (this->validacao_pos(this->x, this->y-1, mapa)) {
            poss[0] = std::make_tuple(true, this->x, this->y-1);
        }
    }
    if (this->x < get_SIZE_X() - 1)  {
        if (this->validacao_pos(this->x+1, this->y, mapa)) {
            poss[1] = std::make_tuple(true, this->x+1, this->y);
        }
    }
    if (this->y < get_SIZE_Y() - 1) {
        if (this->validacao_pos(this->x, this->y+1, mapa)) {
            poss[2] = std::make_tuple(true, this->x, this->y+1);
        }
    }
    if (this->x >= 1) {
        if (this->validacao_pos(this->x-1, this->y, mapa)) {
            poss[3] = std::make_tuple(true, this->x-1, this->y);
        }
    }

    int P = 0;

    for (int i = 0; i < 4; i++) {
        if (std::get<0>(poss[i])) {
            P++;
        }
        //printf("bool: %d, x: %d, y: %d\n", std::get<0>(poss[i]), std::get<1>(poss[i]), std::get<2>(poss[i]));
    }

    if (P == 0) {
        return std::tuple<bool, int, int> (false, this->x, this->y);
    }

    int ch = (get_ATUAL_GER() + this->x + this->y) % P;
    P = -1;
    //printf("==========================> %d", ch);
    for (int i = 0; i < 4; i++) {
        if (std::get<0>(poss[i])) {
            P++;
        }
        if (P == ch) {
            return poss[i];
        }
    }
    
    return std::tuple<bool, int, int> (false, this->x, this->y);
}


bool Coelho::validacao_pos(int x, int y, MAPA* mapa) {
            
    if ((*mapa)[x][y]->tipo == TileObject::Vazio) {
        return true;
    }

    if ((*mapa)[x][y]->tipo == TileObject::Coelho) {
        if (!((*mapa)[x][y]->estabelecido)) {
            if ((*mapa)[x][y]->age < this->age) {
                return true;
            }
        }
    }

    return false;
}