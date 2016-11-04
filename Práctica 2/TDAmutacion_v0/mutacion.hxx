#include <iostream>
#include <string>
#include <vector>
#include "enfermedad.h"

using namespace std;

mutacion::mutacion(){
	chr = "1";
	pos = 1;
}

/**
 Suponemos que la mutación que nos pasan tiene bien los valores, es decir pos>1
 */
mutacion::mutacion(const mutacion& m){
	ID = m.getID();
	chr = m.getChr();
	pos = m.getPos();
	caf = m.getCaf();
	enfermedades = m.getEnfermedades();
	ref_alt = m.getRef_alt();
	genes = m.getGenes();
	common = m.getCommon();
	clnsig = getClnsig();
}

//para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
mutacion::mutacion(const string & str){
	string info = "",
	recolectora = "";
	vector<string> ref_alt_a_copiar,
	genes_a_copiar,
	database_a_copiar,
	id_enfermedad_a_copiar,
	name_enfermedad_a_copiar;
	vector<enfermedad> enfermedades_a_copiar;
	vector<int> clnsig_a_copiar;
	vector<float> caf_a_copiar;
	bool bool_a_copiar = false;					// Le damos el valor por defecto al bool que copiar en el objeto
	size_t pos_buscado = 0;
	
	// Recolectamos todos los datos que quedan separados por tabuladores:
	// Chr, Pos, ID, cadena de referencia y alternativa
	// Los copiamos en el objeto con las funciones set
	info = strtok((char *) &str[0], "\t");
	setChr(info);
	info = strtok(NULL, "\t");
	setPos( stoi(info) );
	info = strtok(NULL, "\t");
	setID(info);
	info = strtok(NULL, "\t");
	ref_alt_a_copiar.push_back(info);			// Cadena de referencia
	info = strtok(NULL, "\t");
	
	for (unsigned k = 0; k < info.size(); k++){
		if (info[k] == ','){
			ref_alt_a_copiar.push_back(recolectora);	// Añade la cadena alternativa al vector
			recolectora.clear();
		}
		else
			recolectora.push_back(info[k]);		// Añade caracteres a la cadena(s) alternativa(s)
	}
	
	ref_alt_a_copiar.push_back(recolectora);	// Añade la última cadena alternativa que se ha leido
	setRef_alt(ref_alt_a_copiar);
	strtok(NULL, "\t");								// Saltamos los dos puntos
	strtok(NULL, "\t");
	info = strtok(NULL, "\n");						// Cogemos la cadena de información con todas las etiquetas
	info.push_back('\n');							// Añadimos un '\n' al final como tope para la búsqueda
	
	// Recolectamos los datos restantes ordenados en el vector constante de string
	// Si existe la etiqueta
	// 	Dependiendo de la iteración del primer bucle lo guardamos en un vector o en otro
	for (unsigned i = 0; i < a_buscar.size(); i++){
		pos_buscado = info.find(a_buscar[i]);
		
		if ( pos_buscado != string::npos ){		// Comprobamos que la etiqueta estaba presente
			pos_buscado += a_buscar[i].size() - 1;
			recolectora.clear();
			
			// Recorremos caracter a caracter hasta llegar a un ';' o un '\n'
			// Si nos encontramos un separador
			// 	llevamos lo que posee la cadena hasta ahora al vector correspondiente
			// en caso contrario
			// 	copiamos el caracter en la cadena recolectora
			do {
				pos_buscado++;
				
				if (info[pos_buscado] == ',' || info[pos_buscado] == '|' ||
					info[pos_buscado] == ';' || info[pos_buscado] == '\n'){
					switch (i){
						case 0:
							genes_a_copiar.push_back(recolectora);
							break;
						case 1:
							database_a_copiar.push_back(recolectora);
							break;
						case 2:
							id_enfermedad_a_copiar.push_back(recolectora);
							break;
						case 3:
							name_enfermedad_a_copiar.push_back(recolectora);
							break;
						case 4:
							clnsig_a_copiar.push_back( stoi(recolectora) );
							break;
						case 5:
							if (recolectora == ".")
								recolectora = "0.0";
							
							caf_a_copiar.push_back( stof(recolectora) );
							break;
						case 6:
							if ( stoi(recolectora) == 0 )			// Si está, comprobamos que es (T or F)
								bool_a_copiar = false;
							else
								bool_a_copiar = true;
							
							break;
					}
					
					recolectora.clear();
				}
				else
					recolectora.push_back(info[pos_buscado]);
			}while(info[pos_buscado] != ';' && info[pos_buscado] != '\n');
		}
	}
	
	// Hay que asegurarse de que se hayen emparejados de tres en tres
	// el nombre, id y database de la enfermeda
	// Si no es así rellenar con una cadena [<UNKNOWN>]
	for (unsigned k = id_enfermedad_a_copiar.size(); k < name_enfermedad_a_copiar.size(); k++)
		id_enfermedad_a_copiar.push_back("[<Unknown>]");
	
	for (unsigned k = database_a_copiar.size(); k < name_enfermedad_a_copiar.size(); k++)
		database_a_copiar.push_back("[<Unknown>]");
	
	for (unsigned k = 0; k < name_enfermedad_a_copiar.size(); k++){
		enfermedades_a_copiar.push_back( enfermedad(name_enfermedad_a_copiar[k],
													id_enfermedad_a_copiar[k],
													database_a_copiar[k]) );
	}
	
	// Copiamos los contenidos de los vectores a los objetos
	setGenes(genes_a_copiar);
	setEnfermedades(enfermedades_a_copiar);
	setClnsig(clnsig_a_copiar);
	setCaf(caf_a_copiar);
	setCommon(bool_a_copiar);
	
}

//Métodos consultores

void mutacion::setID(const string & id){
	ID = id;
}

void mutacion::setChr(const string & chr){
	if((stoi(chr) >= 1 && stoi(chr) <= 22) || (this -> chr).compare("X") == 0 || (this -> chr).compare("Y") == 0 || (this -> chr).compare("MT") == 0){
		(this -> chr) = chr;
	}
}

void mutacion::setPos(const unsigned int & pos){
	if (pos > 0){
		(this -> pos) = pos;
	}
}

void mutacion::setRef_alt(const vector<string> & ref_alt){
	(this -> ref_alt).clear();
	
	for (int i = 0; i < ref_alt.size(); i++){
		(this -> ref_alt).push_back(ref_alt[i]);
	}
}

void mutacion::setGenes (const vector<string> & genes){
	(this -> genes).clear();
	
	for (int i = 0; i < genes.size(); i++){
		(this -> genes).push_back(genes[i]);
	}
}

void mutacion::setCommon (const bool & common){
	this -> common = common;
}

void mutacion::setCaf (const vector<float> & caf){
	(this -> caf).clear();
	
	for (int i = 0; i < caf.size(); i++){
		(this -> caf).push_back(caf[i]);
	}
}

void mutacion::setEnfermedades (const vector<enfermedad> & enfermedades){
	(this -> enfermedades).clear();
	
	for(int i = 0; i < enfermedades.size(); i++){
		this -> enfermedades = enfermedades;
	}
}

void mutacion::setClnsig (const vector<int> & clnsig){
	for(int i = 0; i < clnsig.size(); i++){
		this -> clnsig.push_back(clnsig[i]);
	}
}

string mutacion::getID() const{
	return ID;
}

string mutacion::getChr() const{
	return chr;
}

unsigned int mutacion::getPos() const{
	return pos;
}

const vector<string> & mutacion::getRef_alt () const{
	return ref_alt;
}

const vector<string> & mutacion::getGenes() const{
	return genes;
}

bool mutacion::getCommon () const{
	return common;
}


const vector<float> & mutacion::getCaf () const{
	return caf;
}

const vector<enfermedad> & mutacion::getEnfermedades () const{
	return enfermedades;
}

const vector<int> & mutacion::getClnsig () const{
	return clnsig;
}

//Sobrecarga de operadores

mutacion & mutacion::operator = (const mutacion & m){
	if (this != &m){
		setID(m.getID());
		setChr(m.getChr());
		setPos(m.getPos());
		setRef_alt(m.getRef_alt());
		setGenes(m.getGenes());
		setCommon(m.getCommon());
		setCaf(m.getCaf());
		setEnfermedades(m.getEnfermedades());
		setClnsig(m.getClnsig());
	}
	
	return *this;
}

bool mutacion::operator == (const mutacion & m) const{
	bool iguales = false;
	if(this != &m){
		if(m.ID.size() == ID.size() &&
		   chr.size() == m.chr.size() &&
		   pos == m.pos &&
		   ref_alt.size() == m.ref_alt.size() &&
		   genes.size() == m.genes.size() &&
		   common == m.common &&
		   m.caf.size() == caf.size() &&
		   enfermedades.size() == m.enfermedades.size() &&
		   clnsig.size() == m.clnsig.size() )
			iguales = true;
	}
	else
		iguales = true;
	
	return iguales;
}

bool mutacion::operator < (const mutacion & m) const{
	bool menor = false;
	
	if(this != &m){
		if ((getPos()) < m.getPos()){
			if(chr.compare(m.getChr()) < 0){
				menor = true;
			}
		}
	}
	
	return menor;
}

//Métodos auxiliares

string mutacion::imprime_Ref() const{
	string hola;
	
	for (int i = 0; i < ref_alt.size(); i++){
		hola = hola + " " + ref_alt[i];
	}
	
	return hola;
}

string mutacion::imprime_Genes() const{
	string hola;
	
	for (int i = 0; i < genes.size(); i++){
		hola = hola + " " + genes[i];
	}
	
	return hola;
}

string mutacion::imprime_Caf() const{
	string hola;
	
	for (int i = 0; i < genes.size(); i++){
		hola = hola + " " + to_string(caf[i]);
	}
	
	return hola;
}

string mutacion::imprime_Enfermedades() const{
	string hola;
	
	for(int i = 0; i < enfermedades.size(); i++){
		hola = hola + " " + enfermedades[i].imprime_Enf();
	}
	
	return hola;
}

ostream& operator<< ( ostream& os, const mutacion& m) {
	os << m.getID() << "\t" << m.getChr() << "\t" << m.getPos() << "\t" << m.imprime_Ref() << "\t" << m.imprime_Genes()
	<< "\t" << m.getCommon() << "\t" << m.imprime_Caf() << "\t" << m.imprime_Enfermedades() << "\t" << endl;
	
	return os;
}
