#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <iostream>
#include <tuple>
#include <string>

#include "headers/main.hpp"
#include "headers/entidade.hpp"
#include "headers/coelho.hpp"
#include "headers/raposa.hpp"


const char *TileRepr[] = {
    "Raposa",
    "Coelho",
    "Rocha",
    "Vazio"
};

// ######################################################################################
// #                                                                                    #
// #                         VARIÁVEIS E CONSTANTES GLOBAIS                             #
// #                                                                                    #
// ######################################################################################

int SIZE_X;
int SIZE_Y;
int GER_PROC_COELHOS;
int GER_PROC_RAPOSAS;
int GER_ALIM_RAPOSAS;
int NUM_GER;
int ATUAL_GER = 0;

int get_SIZE_X() {return SIZE_X;}
int get_SIZE_Y() {return SIZE_Y;}
int get_GER_PROC_COELHOS() {return GER_PROC_COELHOS;}
int get_GER_PROC_RAPOSAS() {return GER_PROC_RAPOSAS;}
int get_GER_ALIM_RAPOSAS() {return GER_ALIM_RAPOSAS;}
int get_NUM_GER() {return NUM_GER;}
int get_ATUAL_GER() {return ATUAL_GER;}

// ######################################################################################
// #                                                                                    #
// #                                     MAIN                                           #
// #                                                                                    #
// ######################################################################################

MAPA *ptr_mapa;

int main() {
 
    // ############################
    // #          INPUT           #
    // ############################

    int NUM_OBJS;
    std::vector<std::tuple<TileObject, int, int>> OBJS {};

    std::cin >> GER_PROC_COELHOS >> GER_PROC_RAPOSAS >> GER_ALIM_RAPOSAS;
    std::cin >> NUM_GER >> SIZE_X >> SIZE_Y >> NUM_OBJS;

    for (int i = 0; i < NUM_OBJS; i++) {

        std::string obj_type;
        int x, y;
        TileObject saida;

        std::cin >> obj_type;
        std::cin >> x >> y;


        if (obj_type == "COELHO") {
            saida = TileObject::Coelho;
        }
        else if (obj_type == "RAPOSA") {
            saida = TileObject::Raposa;
        }
        else if (obj_type == "ROCHA") {
            saida = TileObject::Rocha;
        }
        else {
            printf("entrada inválida!!!\n");
            return 1;
        }

        OBJS.push_back(std::tuple<TileObject, int, int>(saida, x, y));
    }

    

    // ############################
    // #       PROCESSAMENTO      #
    // ############################

    srand(time(NULL));

    std::vector<std::vector<Entidade*>> mapa(SIZE_X, std::vector<Entidade*>(SIZE_Y, new Entidade(0, 0)));
    ptr_mapa = &mapa;

    for (int i = 0; i < SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            mapa[i][j] = new Entidade{i, j};
        }
    }

    for (auto i: OBJS) {
        int x = std::get<1>(i);
        int y = std::get<2>(i);

        switch (std::get<0>(i)) {
            case TileObject::Coelho: {
                mapa[x][y] = new Coelho{x, y};
                break;
            }
            case TileObject::Raposa: {
                mapa[x][y] = new Raposa{x, y};
                break;
            }
            case TileObject::Rocha: {
                mapa[x][y] = new Rocha{x, y};
                break;
            }
            case TileObject::Vazio: {
                break;
            }
        }
    }

    for (;ATUAL_GER < NUM_GER; ATUAL_GER++) {
        
        for (int i = 0; i < SIZE_Y+2; i++) {
            printf("-");
        }
        puts("");
        for (auto &i: *ptr_mapa) {
            printf("|");
            for (auto &j: i) {
                switch (j->tipo) {
                    case TileObject::Vazio: {
                        printf(" ");
                        break;
                    }
                    case TileObject::Rocha: {
                        printf("P");
                        break;
                    }
                    case TileObject::Coelho: {
                        printf("C");
                        break;
                    }
                    case TileObject::Raposa: {
                        printf("R");
                        break;
                    }
                }
            }
            printf("|\n");
        }
        for (int i = 0; i < SIZE_Y+2; i++) {
            printf("-");
        }
        puts("");
 
        
        for(int row = 0; row < SIZE_X; row++) {
            for (int ent = 0; ent < SIZE_Y; ent++) {  
                if (mapa[row][ent]->estabelecido) {
                    mapa[row][ent]->process(ptr_mapa);   
                }
            }
        }
    
        for(int row = 0; row < SIZE_X; row++) {
            for (int ent = 0; ent < SIZE_Y; ent++) {
                mapa[row][ent]->estabelecido = true;
            }
        }
    
    }

    
    // ############################
    // #          OUTPUT          #
    // ############################
    
    for (int i = 0; i < SIZE_Y+2; i++) {
        printf("-");
    }
    puts("");
    for (auto &i: *ptr_mapa) {
        printf("|");
        for (auto &j: i) {
            switch (j->tipo) {
                case TileObject::Vazio: {
                    printf(" ");
                    break;
                }
                case TileObject::Rocha: {
                    printf("P");
                    break;
                }
                case TileObject::Coelho: {
                    printf("C");
                    break;
                }
                case TileObject::Raposa: {
                    printf("R");
                    break;
                }
            }
        }
        printf("|\n");
    }
    for (int i = 0; i < SIZE_Y+2; i++) {
        printf("-");
    }
    puts("");

    

}

