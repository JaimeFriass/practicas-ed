CPPFLAGS = g++ -std=c++11 -c

#Creación de ejecutables

principal : principal.o enfermedad.o mutacion.o 
	g++ -O3 -o principal principal.o enfermedad.o mutacion.o  

#Creación de archivos objeto

principal.o: principal.cpp conjunto.h
	$(CPPFLAGS) principal.cpp -o principal.o -I.

enfermedad.o: enfermedad.cpp
	$(CPPFLAGS) enfermedad.cpp -o enfermedad.o -I.

mutacion.o: mutacion.cpp
	$(CPPFLAGS) mutacion.cpp -o mutacion.o -I.

#Limpieza de archivos objeto, ejecutables y bibliotecas

clean:
	echo "Limpiando..."
	rm *.o
mrproper: clean
	rm principal