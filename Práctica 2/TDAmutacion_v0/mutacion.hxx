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
	string strID, str_chr, strpos, strcaf, strenfermedades, strref, strgenes, strcommon, strclnsig;
	for (int i = 0; i < str.length(); i++){
		while (str[i] != '\t')
			strID = strID + str[i];
	i++;
	while (str[i] != '\t')
		str_chr = str_chr + str[i];
	i++;
	while (str[i] != '\t')
		strpos = strpos + str[i];
	i++;
	while (str[i] != '\t')
		strcaf = strcaf + str[i];
	i++;
	while (str[i] != '\t')
		strpos = strpos + str[i];
	i++;
	while (str[i] != '\t')
		strenfermedades = strenfermedades + str[i];
	i++;
	while (str[i] != '\t')
		strref = strref + str[i];
	i++;
	while (str[i] != '\t')
		strgenes = strgenes + str[i];
	i++;
	while (str[i] != '\t')
		strcommon = strcommon + str[i];
	i++;
	while (str[i] != '\t')
		strclnsig = strclnsig + str[i];
	i++;
	}
}

void mutacion::setID(const string & id){
	ID=id;
}

void mutacion::setChr(const string & chr){
	size_t lastChar;
	if((stoi(chr, &lastChar, 10) >= 1 && stoi(chr, &lastChar, 10) <= 22) || (this -> chr).compare("X") == 0 || (this -> chr).compare("Y") == 0 || (this -> chr).compare("MT") == 0){
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
