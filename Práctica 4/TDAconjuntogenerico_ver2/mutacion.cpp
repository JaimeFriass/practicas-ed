#include <iostream>
#include <string>
#include <vector>
#include "mutacion.h"

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
	bool extras = false;
	unsigned int k=0;
	int j = 0;
	int i = 0;

	cerr << "Invocado constructor mutacion::mutacion(str)"<<endl;
	// OBTENER CHR
	(*this).chr = str.substr(0,1);
	cerr<< "\tchr: "<<(*this).chr<<endl; 
	
	// OBTENER POS
	// En el substring que va desde el primer dígito de pos hasta rs, busca el
	// tabulador que marca el final de pos.
	string aux = str.substr(2,str.substr(2,str.find("rs")).find('\t'));
	(*this).pos = atoi(aux.c_str());
	cerr <<"\tpos: "<<(*this).pos<<endl;
	
	// OBTENER ID
	i = str.find("rs");
	(*this).ID = "";
	while(str[i] != '\t'){
		(*this).ID += str[i];
		i++;
	}
	cerr << "\tID: "<<(*this).ID<<endl;

	// OBTENER REF_ALT
	i++;
	aux = "";
	while(str[i] != '\t'){
		aux += str[i];
		i++;
	}
	(*this).ref_alt.push_back(aux);
	i++;
	aux = "";
	while(str[i] != '\t'){
		aux += str[i];
		i++;
	}
	(*this).ref_alt.push_back(aux);
	
	cerr << "\tREF_ALT: "; 
	for (int i=0; i<ref_alt.size(); i++)
		cerr << ref_alt.at(i) << " ";
	cerr << endl; 
	

	// OBTENER GENES
	i = str.find("GENEINFO");
	unsigned long sigPyC = str.substr(i, str.size() - i).find(";");
	aux = str.substr(i +9, sigPyC -9);

	for( k = 0; k < aux.size(); k++){
		if(aux[k] == '|'){
			(*this).genes.push_back(aux.substr(j, k-j));
			extras = true;
			j = k +1;
		}
	}
	if(extras)
		(*this).genes.push_back(aux.substr(j,aux.size() -1));
	else
		(*this).genes.push_back(aux);

	cerr << "\tGENES: "; 
	for (int i=0; i<genes.size(); i++)
		cerr << genes.at(i) << " ";
	cerr << endl; 


	// OBTENER COMMON
	i = str.find("COMMON");
	if(str[i +7] == '1')
		(*this).common = true;
	else
		(*this).common = false;

	cerr << "\tCOMMON: "<<common<<endl; 
	
	// OBTENER CAF
	j = 0;
	extras = false;
	i = str.find("CAF");
	if(i != -1){
		sigPyC = str.substr(i, str.size() -i).find(";");
		aux = str.substr(i +4, sigPyC -4);
		for( k = 0; k < aux.size(); k++){
			if(aux[k] == ','){
				(*this).caf.push_back(atof(aux.substr(j, k - j).c_str()));
				j = k +1;
				extras = true;
			}
		}
		if(extras)
			(*this).caf.push_back(atof(aux.substr(j, aux.size()-j).c_str()));
		else
			(*this).caf.push_back(atof(aux.c_str()));
	}
	else{
		(*this).caf.push_back(0.0);
	}
	cerr << "\tCAF: "; 
	for (int i=0; i<caf.size(); i++)
		cerr << caf.at(i) << " ";
	cerr << endl; 
		



	// OBTENER ENFERMEDADES Y CLNSIG

	unsigned long posCln = str.find("CLNSIG"); // Códigos CLNSIG
	unsigned long posID = str.find("CLNDSDBID"); // ID enf
	unsigned long posDB = str.find("CLNDSDB"); // Database Enf
	long posName = str.find("CLNDBN"); // Nombres enf
	j = 0;
	extras = false;

	if(posName != -1){
		sigPyC = str.substr(posName, str.size() -posName).find(";");
		string nomEnf = str.substr(posName + 7, sigPyC -7);

		sigPyC = str.substr(posID, str.size() -posID).find(";");
		string iDenf = str.substr(posID +10, sigPyC -10);

		sigPyC = str.substr(posDB, str.size() -posDB).find(";");
		string dBenf = str.substr(posDB +8, sigPyC - 8);
		vector<string> auxNombre, auxID, auxDB;


		for(k = 0; k < nomEnf.size(); k++){ // pilla nombres
			if(nomEnf[k] == '|'){
				auxNombre.push_back(nomEnf.substr(j, k -j));
				j = k +1;
				extras = true;
			}
		}
		if(extras)
			auxNombre.push_back(nomEnf.substr(j, nomEnf.size()-j));
		else
			auxNombre.push_back(nomEnf);
		j = 0;
		extras = false;

		for(k = 0; k < iDenf.size(); k++){	// pilla ID
			if(iDenf[k] == '|'){
				auxID.push_back(iDenf.substr(j, k -j));
				j = k +1;
				extras = true;
			}
		}
		if(extras)
			auxID.push_back(iDenf.substr(j, nomEnf.size()-j));
		else
			auxID.push_back(iDenf);
		j = 0;
		extras = false;

		for(k = 0; k < dBenf.size(); k++){	// pilla DB
			if(dBenf[k] == '|'){
				auxDB.push_back(dBenf.substr(j, k -j));
				j = k +1;
				extras = true;
			}
		}
		if(extras)
			auxDB.push_back(dBenf.substr(j, nomEnf.size()-j));
		else
			auxDB.push_back(dBenf);
		j = 0;
		extras = false;

		for(k = 0; k < auxNombre.size(); k++){
			enfermedad auxEnf(auxNombre[k], auxID[k], auxDB[k]);
			(*this).enfermedades.push_back(auxEnf);
		}

		sigPyC = str.substr(posCln, str.size() - posCln).find(";");
		string strCln = str.substr(posCln +7, sigPyC - 7);
		cerr << "\tIdentificando CLNSIG: cadena: "<<strCln<<endl;
		if(strCln.size() > 1)
			for( k = 0; k < enfermedades.size(); k+=2){
				(*this).clnsig.push_back((int)strCln[k]-48);
				cerr << "\t\tSe ha hecho push_back sobre clnsig de la cadena : "<< strCln[k]-48<<endl; 
			}

	}
	cerr << "\tEnfermedades ("<<enfermedades.size()<<"): "; 
	for (int i=0; i<enfermedades.size(); i++)
		cerr << enfermedades.at(i) << " ";
	cerr << endl; 

	cerr << "\tCLNSIG ("<<clnsig.size()<<"): "; 
	for (int i=0; i<clnsig.size(); i++)
		cerr << clnsig.at(i) << " ";
	cerr << endl; 


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

	for (unsigned int i = 0; i < ref_alt.size(); i++){
		(this -> ref_alt).push_back(ref_alt[i]);
	}
}

void mutacion::setGenes (const vector<string> & genes){
	(this -> genes).clear();

	for (unsigned int i = 0; i < genes.size(); i++){
		(this -> genes).push_back(genes[i]);
	}
}

void mutacion::setCommon (const bool & common){
	this -> common = common;
}

void mutacion::setCaf (const vector<float> & caf){
	(this -> caf).clear();

	for (unsigned int i = 0; i < caf.size(); i++){
		(this -> caf).push_back(caf[i]);
	}
}

void mutacion::setEnfermedades (const vector<enfermedad> & enfermedades){
	(this -> enfermedades).clear();

	for(unsigned int i = 0; i < enfermedades.size(); i++){
		this -> enfermedades = enfermedades;
	}
}

void mutacion::setClnsig (const vector<int> & clnsig){
	for(unsigned int i = 0; i < clnsig.size(); i++){
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

		else
			iguales=false;
	}
	else
		iguales =true;

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

	for (unsigned int i = 0; i < ref_alt.size(); i++){
		hola = hola + " " + ref_alt[i];
	}

	return hola;
}

string mutacion::imprime_Genes() const{
	string hola;

	for (unsigned int i = 0; i < genes.size(); i++){
		hola = hola + " " + genes[i];
	}

	return hola;
}

string mutacion::imprime_Caf() const{
	string hola;

	for (unsigned int i = 0; i < genes.size(); i++){
		hola = hola + " " + to_string(caf[i]);
	}

	return hola;
}

string mutacion::imprime_Enfermedades() const{
	string hola;

	for(unsigned int i = 0; i < enfermedades.size(); i++){
		hola = hola + " " + enfermedades[i].imprime_Enf();
	}

	return hola;
}

ostream& operator<< ( ostream& os, const mutacion& m) {
	os << m.getID() << "\t" << m.getChr() << "\t" << m.getPos() << "\t" << m.imprime_Ref() << "\t" << m.imprime_Genes()
	<< "\t" << m.getCommon() << "\t" << m.imprime_Caf() << "\t" << m.imprime_Enfermedades() << "\t" << endl;

	return os;
}
