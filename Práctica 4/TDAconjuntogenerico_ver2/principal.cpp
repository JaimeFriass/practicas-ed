#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>


using namespace std;
using namespace std::chrono;

/*functor :conjunto de mutacion decreciente por cromosoma/posicion*/
class DecrecienteChrPos{
public:
    bool operator()( const mutacion &a, const mutacion &b){
	/* también podría ser : return !(a < b)*/
 		return ( ( a.getChr() < b.getChr() ) && ( a.getPos() < b.getPos() ) );
	}
};

/*functor :conjunto de mutacion creciente por cromosoma/posicion*/
class CrecienteChrPos{
public:
    bool operator()(const mutacion &a, const mutacion &b){
	/* también podría ser : return !(a < b)*/
 		return !( ( a.getChr() < b.getChr() ) && ( a.getPos() < b.getPos() ) );
	}
};

class CrecienteID{
public:
	bool operator()(const mutacion &a, const mutacion &b){
		return (a.getID() < b.getID()); // devuelve verdadero si el ID de a precede al ID de b
	}
};

class DecrecienteID{
public:
	bool operator()(const mutacion &a, const mutacion &b){
		return !(a.getID() < b.getID()); // devuelve verdadero si el ID de a precede al ID de b
	}
};

class CrecienteEnf{
public:
	bool operator()(const enfermedad &a, const enfermedad &b){
		return (a < b);
	}
};

class DecrecienteEnf{
public:
	bool operator()(const enfermedad &a, const enfermedad &b){
		return !(a < b);
	}
};


/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
 @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

template <typename T, typename CMP>

bool load(conjunto<T, CMP> &  cm, const string & s) {
	ifstream fe;
	string cadena;
	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;

	cout << "Abrimos "<< s << endl;
	fe.open(s.c_str(), ifstream::in);
	if (fe.fail()){
		cerr << "Error al abrir el fichero " << s << endl;
	}
	else {
		//leo la cabecera del fichero (líneas que comienzan con #)
		do{
			getline(fe,cadena,'\n');
		}while (cadena.find("#")==0 && !fe.eof());

		//leo la tabla de mutaciones, una línea cada vez
		while ( !fe.eof() ){
		 //cout << "leo:: "<< cadena << endl;
		 // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
			mutacion mut = mutacion(cadena);
		 // Insertar mutación en el conjunto

			start =  high_resolution_clock::now();;

			cm.insert(mut);

			end =  high_resolution_clock::now();;

			tiempo_transcurrido  = duration_cast<duration<double> >(end-start);
			cout << "\nTiempo insert : "<< tiempo_transcurrido.count() << endl;

			getline(fe,cadena,'\n');
	 }
	 fe.close();
	 return true;
 } // else
	fe.close();
	return false;
}


int main(int argc, char *argv[]){

	conjunto<mutacion, CrecienteID> conjuntoMutaciones;
	string query_str;
	high_resolution_clock::time_point start,end;
	duration<double> tiempo_transcurrido;

	//Cargar las mutaciones en vectorSNPs
	load(conjuntoMutaciones, "clinvar_20160831.vcf");

	//Imprimir número de elementos almacenados en conjuntoMutaciones
	cout << "Lectura del fichero finalizada. Mutaciones cargadas: " << conjuntoMutaciones.size() << endl;



	//Imprimir cuántas mutaciones están asociadas al cromosoma 1:
	cout << "Mutaciones asociadas a Chr 1: " << conjuntoMutaciones.lower_bound("2", 1) - conjuntoMutaciones.begin() << endl;


	/**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
	/*
	cout<< "la mutación y las enfermedades asociadas con ID: rs147165522" << conjuntoMutaciones.find("rs147165522").first << " " << conjuntoMutaciones.find("rs147165522").second << endl;


	 */


	/**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */
	start =  high_resolution_clock::now();;

	cout<< "la mutación y las enfermedades asociadas con char:14y pos: 67769578" << conjuntoMutaciones.find("14",67769578).first << conjuntoMutaciones.find("14",67769578).second << endl;

	end =  high_resolution_clock::now();;

	tiempo_transcurrido  = duration_cast<duration<double> >(end-start);
	cout << "\nTiempo find : "<< tiempo_transcurrido.count() << endl;

	/**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
	/*
	cout<< "Número de mutaciones del cromosoma 3: " << conjuntoMutaciones.upper_bound("3",0) - conjuntoMutaciones.begin() << endl;
	*/

	//////////////Prueba de erase///////////////////

	start =  high_resolution_clock::now();;

	conjuntoMutaciones.erase("rs147165522");

	end =  high_resolution_clock::now();;

	tiempo_transcurrido  = duration_cast<duration<double> >(end-start);
	cout << "\nTiempo erase : "<< tiempo_transcurrido.count() << endl;

	/**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */

	return 0;
}
