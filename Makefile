ALL: gramaticas
PHONY= clean

gramaticas: main.cpp
	g++ --std=c++11 main.cpp -o gramaticas

clean:
	\rm -f gramaticas
