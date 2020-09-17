CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17

simcr: build /build/main.o /build/entidade.o /build/raposa.o /build/coelho.o 
	$(CXX) -o simcr build/main.o build/entidade.o build/raposa.o build/coelho.o -static $(CXXFLAGS)


build:
	mkdir build

/build/main.o: main.cpp
	$(CXX) -c -o main.o main.cpp $(CXXFLAGS); \
	mv main.o build/

/build/entidade.o: entidades/entidade.cpp headers/entidade.hpp
	$(CXX) -c -o entidade.o entidades/entidade.cpp $(CXXFLAGS); \
	mv entidade.o build/

/build/raposa.o: entidades/raposa.cpp headers/raposa.hpp
	$(CXX) -c -o raposa.o entidades/raposa.cpp $(CXXFLAGS); \
	mv raposa.o build/

/build/coelho.o: entidades/coelho.cpp headers/coelho.hpp
	$(CXX) -c -o coelho.o entidades/coelho.cpp $(CXXFLAGS); \
	mv coelho.o build/
