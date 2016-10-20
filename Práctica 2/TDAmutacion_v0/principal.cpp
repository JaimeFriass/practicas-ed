
#include "mutacion.h"
#include "enfermedad.h"
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
/** @brief lee un fichero de mutaciones, linea a linea
 @param[in] s nombre del fichero
 @param[in,out] vm vector sobre el que se lee
 @return true si la lectura ha sido correcta, false en caso contrario
 */

bool load(vector<mutacion> &  vm, const string & s) {
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
		 // Insertar mutación en el vector
		 vm.push_back(mut);
		 getline(fe,cadena,'\n');
	 }
	 fe.close();
	 return true;
 } // else
	fe.close();
	return false;
}


/** @brief Recorre un vector de mutaciones y devuelve cuántas de estas mutaciones están asociadas a un nombre de enfermedad s
 @param[in] vm vector de mutaciones
 @param[in] s texto asociado al nombre de la enfermedad.
 @return int número de mutaciones asociadas a enfermedades cuyo nombre contiene s
 */

int cuentaMutacionesEnfermedad(vector<mutacion> &  vm, const string & s) {
	
	vector <enfermedad> enfermedades; //para almacenar las enfermedades asociadas a cada mutación
	int cont_mutaciones = 0;          //para almacenar el número de mutaciones asociadas a enfermedades que contienen s
	
	for (int i = 0; i < vm.size(); i++){    //recorrer vector de mutaciones vm
		// para cada mutación, obtener sus enfermedades asociadas:
		enfermedades = vm[i];
		
		int j = 0;
		//recorrer el vector de enfermedades para ver si hay alguna cuyo nombre contiene s
		while (j < enfermedad.size()){
			//utilizar el método enfermedades[j].nameContains(s)
			if(enfermedades[j].nameContains(s)){
				//si alguna enfermedad de enfermedades estaba asociada a s, incrementar contador.
				cont_mutaciones++;
			}
		}
	}
	
	return cont_mutaciones;
}


int main(int argc, char *argv[]){
	
	vector<mutacion> vectorSNPs;
	string query_str;
	
	if (argc>1){
		query_str = argv[1];      //Término de búsqueda indicado por el usuario
	}else{
		query_str = "cancer";     //Default query: "cancer"
	}
	
	//Cargar las mutaciones en vectorSNPs
	load(vectorSNPs, "clinvar_20160831.vcf");
	
	//Imprimir número de elementos almacenados en vectorSNPs (130867 mutaciones totales)
	cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<vectorSNPs.size()<<endl;
	
	//Imprimir cuántas mutaciones están asociadas a la enfermedad indicada en query_str
	cout << "Mutaciones asociadas a " <<query_str <<": "<< cuentaMutacionesEnfermedad(vectorSNPs, query_str)<< endl;
	
	return 0;
}
