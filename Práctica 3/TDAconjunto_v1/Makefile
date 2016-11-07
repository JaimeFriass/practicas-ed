CPPFLAGS = g++ -c

#Creación de ejecutables

principal : principal.o 
	$(CPPFLAGS) principal.o -o principal

#Creación de archivos objeto

principal.o: principal.cpp conjunto.o
	$(CPPFLAGS) principal.cpp -o principal.o -I.

enfermedad.o: enfermedad.cpp
	$(CPPFLAGS) enfermedad.cpp -o enfermedad.o -I.

mutacion.o: mutacion.cpp enfermedad.o
	$(CPPFLAGS) mutacion.cpp -o mutacion.o -I.

conjunto.o: conjunto.cpp mutacion.o
	$(CPPFLAGS) conjunto.cpp -o conjunto.o -I.

#Limpieza de archivos objeto, ejecutables y bibliotecas

clean:
	echo "Limpiando..."
	rm *.o