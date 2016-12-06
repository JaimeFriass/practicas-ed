#include "mutacion.h"
#include <iostream>
#include <fstream>

#include "conjunto.h"

using namespace std;

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
template<class CMP>
bool load(conjunto<mutacion,CMP>  &  cm, const string & s) {
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
		}while (cadena.find('#') != string::npos && !fe.eof());
	 
		//leo la tabla de mutaciones, una línea cada vez
		while ( !fe.eof() ){
			//cout << "leo:: "<< cadena << endl;
			// Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
			mutacion mut = mutacion(cadena);
			//cout << mut<< endl;
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
template <typename T>

int tamanio(T orig1,T orig2){
	T aux= orig2;
	int distancia = 0;
	while (aux != orig1){
		distancia++;
		aux++;
	}
	return distancia;
	
}


int main(int argc, char *argv[]){
	
	conjunto<mutacion,DecrecienteChrPos > cm;
	load(cm,"clinvar_20160831.vcf");
	
	//Imprimir número de elementos almacenados en conjuntoMutaciones
	cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<cm.size()<<endl;
	
	auto it = cm.find(*cm.begin());
	
	if (it == cm.end())
		cout << "No está."<<endl;
	else
		cout << (*it).getID() << " "  << (*it).getPos() << endl;
	
	mutacion x,y;
	
	x.setPos(0);
	x.setChr("3");
	
	y.setPos(0);
	y.setChr("4");

	
	
	cout << "En rango " << tamanio(cm.lower_bound(y),cm.lower_bound(x) )<< "pos inicio " << tamanio(cm.lower_bound(x),cm.begin() )<< " pos fin " << tamanio( cm.lower_bound(y), cm.begin() )<< endl;
	
	cm.erase(it); // borro
	
	cout << cm.size()<< endl;
	cout << cm.erase(x) << endl;
	
	int i=0;
	
	for (mutacion m:cm){
		if (i % 10 == 0)
			cout << m << endl;
		i++;
	}
	
	conjunto<mutacion,greater<mutacion> > cmg;
	
	cout << "Leo decreciente!!!" << endl;
	
	load(cmg,"clinvar_20160831.vcf");
	i = 0;
	
	cout << cmg.size() << endl;
	
	cout << cmg << endl;
	cout << "Posiciones Impares" <<endl;
	
	for (auto iti = cmg.ibegin(); iti != cmg.iend(); ++iti)
		cout << *iti << endl;
	
	conjunto<mutacion,greater<mutacion> >::secure_iterator sit = cmg.send();
	--sit;
	
	// Borro 10 elementos;
	
	for (int i = 0; i < 10; i++)
		cmg.erase(--cmg.end());
	
	
	cout << *sit << endl; // Iterador no valido, debe abortar
	
	return 0;
}
