OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CPPFLAGS = g++ -std=c++11 -g -Wall

#Creación de ejecutables

principal : principal.o 
	$(CPPFLAGS) principal.o -o principal

#Creación de archivos objeto

principal.o: principal.cpp conjunto.o
	$(CPPFLAGS) -c principal.cpp -o principal.o -I.

enfermedad.o: enfermedad.cpp
	$(CPPFLAGS) -c enfermedad.cpp -o enfermedad.o -I.

mutacion.o: mutacion.cpp enfermedad.o
	$(CPPFLAGS) -c mutacion.cpp -o mutacion.o -I.

conjunto.o: conjunto.cpp mutacion.o
	$(CPPFLAGS) -c conjunto.cpp -o conjunto.o -I.

#Limpieza de archivos objeto, ejecutables y bibliotecas

clean:
	echo "Limpiando..."
	rm *.o

mrproper: clean
	rm $(LIB)/*.a
