/*
 * enfermedad.h
 *
 * Copyright  (C) Juan F. Huete y Carlos Cano
 */
#ifndef __ENFERMEDAD_H
#define __ENFERMEDAD_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;


//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad,  .....
 * Descripción contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP (nombre de la enfermedad, id, BD que provee el id)
 
 @todo Implementa esta clase, junto con su documentación asociada
 
 */

class enfermedad {
private:
	string  name;       // nombre de la enfermedad. Almacenar completo en minúscula.
	string  ID;         // ID único para la enfermedad
	string  database;   // Base de datos que provee el ID
	
public:
/**
@brief Crea una enfermedad iniciando chr y pos a 1.
*/
 enfermedad (); //Constructor de enfermedad por defecto
/**
@brief Crea una enfermedad a partir de 3 cadenas de string.
@param name	string con el nombre
@param ID	string con el ID
@param database	string con la base de datos que provee el ID
*/
 enfermedad (const string & name, const string & ID, const string & database);

/**
@brief Cambia el valor de name
@param name	string con el nuevo nombre
	 
Cambia el valor del nombre de la enfermedad.
*/
 void setName(const string & name);
/**
@brief Cambia el valor de ID
@param ID	nuevo valor de ID
	 
Cambia el valor del ID de la enfermedad.
*/
 void setID(const string & ID);
/**
@brief Cambia el valor de database
@param database	nuevo valor de database
	 
Cambia el valor de la base de datos de la enfermedad.
*/
 void setDatabase(const string & database);

/**
@brief Devuelve el nombre
@returns name	nombre de la enfermedad
	 
Devuelve el nombre de la enfermedad.
*/
 string getName() const;
/**
@brief Devuelve el ID
@returns ID	ID de la enfermedad
	 
Devuelve el ID de la enfermedad.
*/
 string getID() const;
/**
@brief Devuelve database
@returns database	base de datos
	 
Devuelve la base de datos de la enfermedad.
*/
 string getDatabase() const;

/**
@brief Sobrecarga del operador =
@param e	enfermedad a igualar
	 
Sobrecarga el operador de asignación para ajustarlo a enfermedades.
*/
 enfermedad & operator=(const enfermedad & e);
/**
@brief Convierte una enfermedad a una cadena string.
@returns str	cadena a devolver con la enfermedad
	 
Se convierte una enfermedad a una cadena string.
*/
 string toString() const;
	
	// Operadores relacionales
/**
@brief Sobrecarga del operador ==
@param e	enfermedad a comparar
	 
Sobrecarga el operador de comparación para ajustarlo a una enfermedad.
*/
 bool operator==(const enfermedad & e) const;
/**
@brief Sobrecarga del operador !=
@param e	enfermedad a comparar
	 
Sobrecarga el operador de asignación para ajustarlo a enfermedades.
*/
 bool operator!=(const enfermedad & e) const;
/**
@brief Sobrecarga del operador <
@param e	enfermedad a comparar
	 
Sobrecarga el operador de asignación para comparar dos enfermedades en función del orden
alfabético de l campo name.
*/
 bool operator<(const enfermedad & e) const;

/**
@brief Devuelve si el nombre contiene el string argumentado.
@param str	string a buscar en el nombre
	 
Devuelve si está el string argumentado en el nombre de la enfermedad aunque no se trate del nombre completo. 
No es sensible a mayúsculas/minúsculas
*/
 bool nameContains(const string & str) const;

/**
@brief Guarda la enfermedad en un string
@returns string		Cadena de string con la enfermedad
	 
Convierte la enfermedad en un string.
*/
 string imprime_Enf() const;	//Guarda la enfermedad en un string
	
};

/**
@brief Sobrecarga el operador <<
@param os
@param e	Enfermedad a imprimir

Sobrecarga el operador << para imprimir una enfermedad con todos sus campos.
*/
ostream& operator<< ( ostream& os, const enfermedad & e);

#include "enfermedad.hxx" // Incluimos la implementacion.


#endif
