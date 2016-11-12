/*
 * conjunto.h
 *
 * Copyright  (C) Juan F. Huete y Carlos Cano
 */

#ifndef __CONJUNTO_H
#define __CONJUNTO_H
#include <string>
#include <vector>
#include <iostream>

#include "mutacion.h"
#include "enfermedad.h"

using namespace std;


//! Clase conjunto
/*! conjunto<T,CMP>::conjunto, find, size,  insert, erase,

 * Tipos conjunto<T,CMP>::value_type, conjunto<T,CMP>::size_type, conjunto<T,CMP>::iterator, conjunto<T,CMP>::const_iterator

 * Descripción

 * Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  En nuestro caso el conjunto va a tener un subconjunto restringido de métodos (inserción de elementos, consulta de un elemento, etc). Este conjunto "simulará" un conjunto de la stl, con algunas claras diferencias pues, entre otros,  no estará dotado de la capacidad de iterar (recorrer) a través de sus elementos.

 * Asociado al conjunto, tendremos el tipo  \code conjunto::value_type \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto, en nuestro caso mutaciones (SNPs) o enfermedades. Es requisito que el tipo conjunto::value_type tenga definida una relación de orden, CMP, y el operador de asignación, operator= .

 * El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática.

 @todo Implementa esta clase siguiendo la especificación asociada
 */


template <typename T, typename CMP>

class conjunto{
public:
	typedef T value_type;
	typedef unsigned int size_type;
	typedef vector<value_type>::iterator iterator;
	typedef vector<value_type>::const_iterator const_iterator;

	//Nazaret
	/** @brief constructor primitivo.
	 */
	conjunto( );

	//Jaime
	/** @brief constructor de copia
	 @param[in] d conjunto a copiar
	 */
	conjunto (const conjunto<T,CMP> & d);

	//Jesús
	/** @brief busca una entrada en el conjunto
	 @param[in] s entrada  a buscar.
	 @return Si existe una entrada en el conjunto con ese valor devuelve el iterador a su posicion, en caso contrario devuelve iterador al final de conjunto
	 @post no modifica el conjunto.

	 */
	iterator  find (const value_type & s);
	const_iterator  find (const value_type & s) const;


	//Nazaret
	/** @brief cuenta cuantas entradas coinciden con los parámetros dados.
	 @param[in] e entrada.
	 @return Como el conjunto no puede tener entradas repetidas, devuelve 1 (si se encuentra la entrada) o 0 (si no se encuentra).
	 @post no modifica el conjunto.
	 */

	size_type count (const value_type & e) const;


	//Jaime
	/** @brief Inserta una entrada en el conjunto
	 @param val entrada a insertar
	 @return un par donde el segundo campo vale true si la entrada se ha podido insertar con éxito, esto es, no existe una mutación con igual valor en el conjunto. False en caso contrario.
	 El primer campo del par devuelve un iterador al elemento insertado, o end() si no fue posible la insercion
	 @post Si e no esta en el conjunto, el size() sera incrementado en 1.
	 */
	pair<iterator,bool> insert (const value_type& val);
	pair<iterator,bool> insert (value_type& val);

	//Jesús
	/** @brief Borra una entrada en el conjunto .
	 Busca la entrada y si la encuentra la borra.
	 @param[in] val entrada a borrar.
	 @param[in] position itarador que apunta a la  entrada que queremos borrar
	 @return devuelve la posicion siguiente al elemento borrado (para la version con iterador) o el numero de elementos borrados
	 @post Si esta en el conjunto su tamaño se decrementa en 1.
	 */
	iterator  erase (const iterator position);
	size_type erase (const value_type& val);

	//Nazaret
	/** @brief Borra todas las entradas del conjunto, dejandolo vacio.
	 @post El conjunto se modifica, quedando vacio.
	 */
	void clear();

	//Jaime
	/** @brief numero de entradas en el conjunto
	 @post  No se modifica el conjunto.
	 @return numero de entradas en el conjunto
	 */
	size_type size() const ;

	//Jesús
	/** @brief Chequea si el conjunto esta vacio (size()==0)
	 @post  No se modifica el conjunto.
	 */
	bool empty() const;

	//Nazaret
	/** @brief operador de asignación
	 @param[in] org conjunto a copiar.
	 @return Crea y devuelve un conjunto duplicado exacto de org.
	 */
	conjunto & operator=( const conjunto & org);

	//Jaime
	/** @brief begin del conjunto
	 @return Devuelve un iterador al primer elemento del conjunto. Si no existe devuelve end
	 @post no modifica el conjunto.
	 */
	conjunto::iterator begin ();

	//Jesús
	/** @brief end del conjunto
	 @return Devuelve un iterador al final del conjunto (posicion siguiente al ultimo).
	 @post no modifica el conjunto.
	 */
	conjunto::iterator end ();

	//Nazaret
	/** @brief begin del conjunto
	 @return Devuelve un iterador constante al primer elemento del conjunto. Si no existe devuelve cend
	 @post no modifica el conjunto.
	 */
	conjunto::const_iterator cbegin () const;

	//Jaime
	/** @brief end del conjunto
	 @return Devuelve un iterador constante al final del conjunto (posicion siguiente al ultimo.
	 @post no modifica el conjunto.
	 */
	conjunto::const_iterator cend () const;

	//Jesús
	/**
	 @brief busca primer elemento que no está por debajo ('antes', '<') de los parámetros dados.
	 @param[in] val entrada.
	 @return Devuelve un iterador al primer elemento que cumple que "elemento<e" es falso, esto es, el primer elemento que  es mayor o igual que val
	 Si no existe devuelve end
	 @post no modifica el conjunto.
	 */
	iterator lower_bound (const value_type& val);
	const_iterator lower_bound (const value_type& val) const;

	//Nazaret
	/** @brief busca primer elemento por encima ('después', '>') de los parámetros dados.
	 @param[in] val entrada. Devuelve un iterador al primer elemento que cumple que "elemento>e", esto es, el primer elemento ESTRICTAMENTE mayor que val
	 Si no existe devuelve end
	 @post no modifica el conjunto.
	 */
	iterator upper_bound (const value_type& val);
	const_iterator upper_bound (const value_type& val) const;



private:
	vector<value_type> vm; // vector que almacena los elementos del conjunto

	//Jaime
	CMP comp; // criterio para guiar la ordenacion



	/** @brief Chequea el Invariante de la representacion
	 @return true si el invariante es correcto, falso en caso contrario
	 */
	bool cheq_rep( ) const;




};

template <typename T, typename CMP>

//Jesús
/** @brief imprime todas las entradas del conjunto
 @post No se modifica el conjunto.
 Implementar tambien esta funcion
*/
ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C);



#endif
