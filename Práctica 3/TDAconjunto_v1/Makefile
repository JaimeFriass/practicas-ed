OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CPPFLAGS = g++ -std=c++11 -g -Wall

#Creación de ejecutables

principal : principal.o
	$(CPPFLAGS) -o principal principal.o

#Creación de archivos objeto

principal.o: principal.cpp enfermedad.h mutacion.h conjunto.h
	$(CPPFLAGS) -c principal.cpp -o principal.o -Iinclude/

enfermedad.o: enfermedad.hxx enfermedad.h
	$(CPPFLAGS) -c enfermedad.hxx -o enfermedad.o -Iinclude/

mutacion.o: mutacion.hxx mutacion.h enfermedad.h
	$(CPPFLAGS) -c mutacion.hxx -o mutacion.o -Iinclude/

conjunto.o: conjunto.hxx mutacion.h enfermedad.h conjunto.h
	$(CPPFLAGS) -c conjunto.hxx -o conjunto.o -Iinclude/

#Limpieza de archivos objeto, ejecutables y bibliotecas

clean:
	echo "Limpiando..."
	rm $(OBJ)/*.o

mrproper: clean
	rm $(LIB)/*.a
