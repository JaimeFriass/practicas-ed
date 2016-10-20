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
	ref_alt = m.getRel_alt();
	genes = m.getGenes();
	common = m.getCommon;
	clnsig = getClosing();
}

//para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
mutacion::mutacion(const string & str){
	string strID, str_chr, strpos, strcaf, strenfermedades, strref, strgenes, strcommon, strclnsig;
	for (int i = 0; i < str.length; i++)
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
}

void mutacion::setID(const string & id){
	ID=id;
}

void mutacion::setChr(const string & chr){
	if((atoi(chr) >= 1 && atoi(chr) <= 22) || strcmp(this -> chr, "X") == 0 || strcmp(this -> chr, "Y") == 0 || strcmp(this -> chr, "MT") == 0){
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
	for(int i = 0; i < clnsing.size(); i++){
		this -> clsing.pushback(clnsing[i]);
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

const vector<string> & mutacgetGenes () const{
	return genes;
}

bool mutacion::getCommon () const{
	return common;
}


const vector<float> & mutacion::getCaf () const{
	return caf;
}

vector<enfermedad> & mutacion::getEnfermedades () const{
	return enfermedades;
}

const vector<int> & mutacion::getClnsig () const{
	return getClnsig;
}

mutacion & mutacion::operator = (const mutacion & m){
	if (this != &m){
		setID(m.getID());
		setChr(m.getChr());
		setPos(m.getPos());
		setRef_alt(m.getRef_alt());
		setGenes(m.getGenes());
		setCommon(m.getCommon());
		setCaf(,.getCaf());
		setEnfermedades(m.getEnfermedades());
		setClnsig(m.getClnsig());
	}
	
	return this;
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
		   clnsig.size() == m.clsing.size() )
			iguales = true;
	}
	else
		iguales = true;
	
	return iguales;
}

bool operator < (const mutacion & m) const{
	bool menor = false;
	
	if(this != &m){
		if (pos < m.getPos()){
			if(chr.compare(m.getChr()) < 0){
				menor = true;
			}
		}
	}
	
	return menor;
}


ostream& operator<< ( ostream& os, const mutacion&) {
	os << ID << "\t" << chr << "\t" << pos << "\t" << ref_alt << "\t" << genes
	<< "\t" << common << "\t" << caf << "\t" << enfermedades << "\t"
	<< clnsig << endl;
	return os;
}
