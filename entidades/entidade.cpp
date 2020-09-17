#include "../headers/entidade.hpp"
#include "../headers/main.hpp"

Entidade::Entidade(int x, int y) {
    this->x = x;
    this->y = y;
    this->age = 666;
    this->fome = get_GER_ALIM_RAPOSAS();
    this->tipo = TileObject::Vazio;
};

void Entidade::process(MAPA* mapa) {};

void Entidade::set_pos(int x, int y) {
    this->x = x;
    this->y = y;
}


Rocha::Rocha(int x, int y): Entidade(x, y) {
    this->tipo = TileObject::Rocha;
};

void Rocha::process(MAPA* mapa) {};

