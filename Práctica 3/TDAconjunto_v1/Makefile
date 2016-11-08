CPPFLAGS = g++ -c

#Creación de ejecutables

principal : principal.o conjunto.o enfermedad.o mutacion.o 
	g++ -o principal principal.o conjunto.o enfermedad.o mutacion.o  

#Creación de archivos objeto

principal.o: principal.cpp 
	$(CPPFLAGS) principal.cpp -o principal.o -I.

enfermedad.o: enfermedad.cpp
	$(CPPFLAGS) enfermedad.cpp -o enfermedad.o -I.

mutacion.o: mutacion.cpp
	$(CPPFLAGS) mutacion.cpp -o mutacion.o -I.

conjunto.o: conjunto.cpp
	$(CPPFLAGS) conjunto.cpp -o conjunto.o -I.

#Limpieza de archivos objeto, ejecutables y bibliotecas

clean:
	echo "Limpiando..."
	rm *.o