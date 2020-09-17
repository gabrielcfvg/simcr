simcr: build /build/main.o /build/entidade.o /build/raposa.o /build/coelho.o 
	g++ -o simcr build/main.o build/entidade.o build/raposa.o build/coelho.o -static -Wall -Wextra


build:
	mkdir build

/build/main.o: main.cpp
	g++ -c -o main.o main.cpp -Wall -Wextra; \
	mv main.o build/

/build/entidade.o: entidades/entidade.cpp headers/entidade.hpp
	g++ -c -o entidade.o entidades/entidade.cpp -Wall -Wextra; \
	mv entidade.o build/

/build/raposa.o: entidades/raposa.cpp headers/raposa.hpp
	g++ -c -o raposa.o entidades/raposa.cpp -Wall -Wextra; \
	mv raposa.o build/

/build/coelho.o: entidades/coelho.cpp headers/coelho.hpp
	g++ -c -o coelho.o entidades/coelho.cpp -Wall -Wextra; \
	mv coelho.o build/
