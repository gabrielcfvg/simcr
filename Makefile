CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17

simcr: main.cpp entidades/entidade.cpp headers/entidade.hpp entidades/coelho.cpp headers/coelho.hpp entidades/raposa.cpp headers/raposa.hpp
	$(CXX) -o simcr main.cpp entidades/entidade.cpp entidades/coelho.cpp entidades/raposa.cpp -static $(CXXFLAGS)