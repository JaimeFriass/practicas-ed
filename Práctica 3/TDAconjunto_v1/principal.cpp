#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;
	
	/** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
  @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

bool load(conjunto &  cm, const string & s) {
 ifstream fe;
 string cadena;

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
        cm.insert(mut);
        getline(fe,cadena,'\n');
    }
    fe.close();
    return true;
  } // else
  fe.close();
  return false;
 }


int main(int argc, char *argv[]){

    conjunto conjuntoMutaciones;
    string query_str; 

    //Cargar las mutaciones en vectorSNPs
    load(conjuntoMutaciones, "clinvar_20160831.vcf");
    
    //Imprimir número de elementos almacenados en conjuntoMutaciones
    cout << "Lectura del fichero finalizada. Mutaciones cargadas: " << conjuntoMutaciones.size() << endl;

    //Imprimir cuántas mutaciones están asociadas al cromosoma 1:
    cout << "Mutaciones asociadas a Chr 1: " << conjuntoMutaciones.lower_bound("2", 1) - conjuntoMutaciones.begin() << endl;

    /**@todo ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas */
    cout<< "la mutación y las enfermedades asociadas con ID: rs147165522" << conjuntoMutaciones.find("rs147165522").first << " " << conjuntoMutaciones.find("rs147165522").second << endl;
	
	/**@todo ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas */
    cout<< "la mutación y las enfermedades asociadas con char:14y pos: 67769578" << conjuntoMutaciones.find("14",67769578).first << conjuntoMutaciones.find("14",67769578).second << endl;
	
	/**@todo ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound) */
    cout<< "Número de mutaciones del cromosoma 3: " << conjuntoMutaciones.upper_bound("3",0) - conjuntoMutaciones.begin() << endl;
	
	/**@todo Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase */

   return 0;
}
