OBJ = obj
BIN = bin
INC = include
LIB = lib
SRC = src
CPPFLAGS = g++ -std=c++11 -g -Wall

#Creación de ejecutables

principal : enfermedad.o mutacion.o principal.o
	$(CPPFLAGS) -o principal principal.o mutacion.o enfermedad.o

#Creación de archivos objeto

principal.o: principal.cpp enfermedad.h mutacion.h
	$(CPPFLAGS) -c principal.cpp -o principal.o -Iinclude/

enfermedad.o: enfermedad.hxx enfermedad.h
	$(CPPFLAGS) -c enfermedad.hxx -o enfermedad.o -Iinclude/

mutacion.o: mutacion.hxx mutacion.h enfermedad.h
	$(CPPFLAGS) -c mutacion.hxx -o mutacion.o -Iinclude/

#Limpieza de archivos objeto, ejecutables y bibliotecas

clean:
	echo "Limpiando..."
	rm $(OBJ)/*.o

mrproper: clean
	rm $(LIB)/*.a
