#include <iostream>
#include <string>
#include <vector>
#include "conjunto.h"
#include "mutacion.h"
#include "enfermedad.h"

using namespace std;

conjunto::conjunto(){
	vm.clear();
}

conjunto::conjunto(const conjunto & d){
	this -> vm = d.getVM();
}

mutacion conjunto::getVM(){
	return vm;
}

pair<conjunto::value_type,bool>  conjunto::find (const string & chr, const unsigned int & pos) const{
	bool encontrado = false;
	conjunto aux;
	
	pair <conjunto::value_type, bool> par(aux, encontrado);
	
	for(int i = 0; i < vm.size() && !encontrado; i++){
		if(vm[i].getChr() == chr || vm[i].getPos() == pos) {
			par.first = vm[i];
			par.second = true;
		}
	}
	
	return par;
}

pair<conjunto::value_type,bool>  conjunto::find (const string & ID) const{
	bool encontrado=false;
	conjunto aux;
	
	pair <conjunto::value_type, bool> par(aux, encontrado);
	
	for(int i=0; i < vm.size() && !encontrado ; i++){
		if(vm[i].getID == ID) {
			par.first = vm[i];
			par.second = true;
		}
	}
	
	return par;
	
}

pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e) const{
	return find(e.getChr(), e.getPos());
	
}
conjunto::size_type conjunto::count (const string & chr, const unsigned int & pos) const{
	conjunto::size_type tamanio = 0;
	
	for (int i = 0; i < vm.size() && tamanio == 0; i++){
		if (vm[i].getChr() == chr || vm[i].getPos() == pos){
			tamanio = 1;
		}
	}
	
	return tamanio;
}

conjunto::size_type conjunto::count (const string & ID) const{
	conjunto::size_type tamanio = 0;
	
	for(int i=0; i < vm.size() && tamanio == 0; i++){
		if(vm[i].getID() == ID)
			tamanio = 1;
	}
	
	return tamanio;
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
	return count(e.getChr(), e.getPos());
}

bool conjunto::insert( const conjunto::value_type & e){
	pair <conjunto::value_type, bool> par = find(e);
	bool insertado = par.second;
	
	if(!insertado){
		vm.push_back(e);
	}
	
	return insertado;
}

bool conjunto::erase(const string & chr, const unsigned int & pos){
	bool correcto = false;
	
	if ( (vm.at(vm.begin() + (pos - 1))).getChr() == chr){
		vm.erase(vm.begin() + (pos -1));
		
		correcto = true;
	}
	
	return correcto;
}

bool conjunto::erase(const string & ID){
	bool correcto = false;
	
	for (int i = 0; i < vm.size(); i++)
	{
		if(vm[i].getID() == ID)
		{
			vm.erase( vm.begin() + i );
			correcto = true;
		}
	}
	
	return correcto;
}

bool conjunto::erase(const conjunto::value_type & e){
	return erase(e.getID());
}

void conjunto::clear(){
	vm.clear();
}

conjunto::size_type conjunto::size() const {
	return vm.size();
}

bool conjunto::empty() const{
	return vm.empty();
}

conjunto & conjunto::operator=(const conjunto & org){
	if (this != &org){
		this -> vm = org.getVM();
	}
	
	return *this;
}

conjunto::iterator conjunto::begin(){
	conjunto::iterator inicio = vm.begin();
	
	return inicio;
}


conjunto::iterator conjunto::end (){
	conjunto::iterator ultimo = vm.end();
	
	return ultimo;
}

conjunto::const_iterator conjunto::cbegin () const{
	conjunto::const_iterator const_inicio = vm.cbegin();
	
	return const_inicio;
}

conjunto::const_iterator conjunto::cend () const{
	conjunto::const_iterator const_final = vm.cend();
	
	return const_final;
}

conjunto::iterator conjunto::lower_bound (const string & chr, const unsigned int & pos){
	conjunto::iterator lower = begin();
	
	while((*lower).getChr() != chr && (*lower).getPos() != pos && lower != end() ) {
		lower++;
	}
	
	lower--;
	
	return lower;
}

conjunto::iterator conjunto::lower_bound (const conjunto::value_type & e){
	return lower_bound(e.getChr(), e.getPos());
}

conjunto::iterator conjunto::upper_bound (const string & chr, const unsigned int & pos){
	conjunto::iterator upper = begin();
	
	while ( (*upper).getChr() != chr && (*upper.getPos() != pos && upper != end() ))
		upper++;
	
	
	return upper;
}



conjunto::iterator conjunto::upper_bound (const conjunto::value_type & e) const{
	return upper_bound(e.getChr(), e.getPos());
}

bool conjunto::cheq_rep() const{
	bool invariante = true;
	const string crom[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "X", "Y", "MT"};
	const int num_crom = 25;
	
	string chr1, chr2;
	
	//Comprobación de que los cromosomas son correctos y que la posición es mayor que 1
	for (int i = 0; i < vm.size() && invariante; i++){
		chr1 = vm[i].getChr();
		
		if((stoi(chr1) < 1 || stoi(chr2)) > 22 && chr1 != "X" && chr1 != "Y" && chr2 != "MT" && vm[i].getPos() > 0){
			invariante = false;
		}
	}
	
	for (int i = 0; i < vm.size() - 1 && invariante; i++){
		chr1 = vm[i].getChr();
		chr2 = vm[i + 1].getChr();
		
		if (chr1 == chr2 && vm[i].getPos() >= vm[i + 1].getPos()){
			invariante = false;
		}
		
		if(chr1 != chr2){
			if (!(vm[i] > vm[i + 1])){
				invariante  = false;
			}
		}
	}
	
	return invariante;
}

ostream &  operator << ( ostream & sal, const conjunto & C){
	for(int i = 0;i < C.size();i++)
		sal << vm[i] << " ";
}
