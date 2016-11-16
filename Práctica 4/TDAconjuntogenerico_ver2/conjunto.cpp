#include <iostream>
#include <string>
#include <vector>
#include "conjunto.h"

using namespace std;

conjunto::conjunto<T,CMP>(){
	vm.clear();
}

conjunto::conjunto<T,CMP>(conjunto & d){
	this -> vm = (d.getVM());
}

const vector<mutacion>  & conjunto::getVM(){
	return vm;
}

conjunto::iterator  conjunto::find (const conjunto::value_type & s){
	bool encontrado = false;
	conjunto::iterator it;

	for(int i = 0; i < vm.size() && !encontrado; i++){
		if(s == vm[i]){
			encontrado = true;
			iterator = vm.begin() + i;
		}
	}

	return it;
}

conjunto::const_iterator  conjunto::find (const value_type & s) const{
	conjunto::const_iterator it = find(s);

	return it;
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
	bool encontrado=false;

	if( size() > 0 ){ //si hay elementos;
		for(unsigned int i = 0 ; i < size() && !encontrado ; i++){
			if( e == vm[i] )
				encontrado=true;
		}
	}
	if(encontrado)
		return 1;
	else
		return 0;
}

conjunto::size_type conjunto::count (const string & chr, const unsigned int & pos) const{
	conjunto::size_type tamanio = 0;

	for (unsigned int i = 0; i < vm.size() && tamanio == 0; i++){
		if (vm[i].getChr() == chr || vm[i].getPos() == pos){
			tamanio = 1;
		}
	}

	return tamanio;
}

conjunto::size_type conjunto::count (const string & ID) const{
	conjunto::size_type tamanio = 0;

	for(unsigned int i = 0; i < vm.size() && tamanio == 0; i++){
		if(vm[i].getID() == ID)
			tamanio = 1;
	}

	return tamanio;
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
	return count(e.getChr(), e.getPos());
}

pair <conjunto::iterator, bool> conjunto::insert (const conjunto::value_type& val) {
	pair<conjunto::iterator, bool> par;
	par.first = find(val);

	if(par.first != vm.end()){
		par.second = false;
	}
	else{
		par.second = true;
		vm.push_back(val);
	}

	return par;
}

pair <conjunto::iterator, bool> conjunto::insert (conjunto::value_type& val) {
	return insert(val);
}

conjunto::iterator conjunto::erase (const conjunto::iterator position){
	vm.erase(position);

	return position;
}

conjunto::size_type conjunto::erase (const value_type& val){
	vm.erase(vm.begin() + val);

	/*
	Se devuelve 1 ya que este método devuelve el número de elementos
	borrados y este sólo puede ser 1
	*/
	return 1;
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

conjunto & conjunto::operator=(conjunto & org){
	if (this != &org){
		vm.clear();

		vm = org.getVM();
	}

	return *this;
}

vector<conjunto::value_type> & conjunto::operator = (vector<conjunto::value_type> aux){
	if((this -> vm) != aux){
		vm.clear();

		for(unsigned int i = 0;i < aux.size(); i++)
			vm.push_back(aux[i]);
	}

	return this -> vm;
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

conjunto::iterator conjunto::lower_bound (const conjunto::value_type& val){
	conjunto::iterator lower = vm.begin();
	bool encontrado = false;

	for(int i = 0; i < vm.size() && !encontrado; i++){
		if(vm[i] < val){
			lower++;
		}
		else{
			if(vm[i] >= val){
				encontrado = true;
			}
		}
	}

	if(encontrado){
		lower--;
	}
	else{
		lower = end();
	}

	return lower;
}

conjunto::const_iterator conjunto::lower_bound (const conjunto::value_type& val) const{
	conjunto::const_iterator it = lower_bound(val);

	return it;
}

conjunto::iterator conjunto::upper_bound (const value_type& val){
	conjunto::iterator upper = vm.begin();
	bool encontrado = false;

	for(int i = 0; i < vm.size() && !encontrado; i++){
		if(vm[i] < val){
			upper++;
		}
		else{
			encontrado = true;
		}
	}

	if(encontrado){
		upper--;
	}
	else{
		upper = end();
	}

	return upper;
}

conjunto::const_iterator conjunto::upper_bound (const value_type& val) const{
	conjunto::const_iterator it = upper_bound(val);

	return it;
}

bool conjunto::cheq_rep() const{
	bool invariante = true;

	string chr1, chr2;
	int n_chr1_aux,n_chr2_aux;

	//Comprobación de que los cromosomas son correctos y que la posición es mayor que 1
	for (unsigned int i = 0; i < vm.size() && invariante; i++){
		chr1 = vm[i].getChr();
		chr2 = vm[i + 1].getChr();
		n_chr1_aux = atoi(chr1.c_str());
		n_chr2_aux=atoi(chr2.c_str());

		if((n_chr1_aux < 1 || n_chr2_aux > 22) && chr1 != "X" && chr1 != "Y" && chr2 != "MT" && vm[i].getPos() > 0){
			invariante = false;
		}
	}

	for (unsigned int i = 0; i < vm.size() - 1 && invariante; i++){
		chr1 = vm[i].getChr();
		chr2 = vm[i + 1].getChr();

		if (chr1 == chr2 && vm[i].getPos() >= vm[i + 1].getPos()){
			invariante = false;
		}

		if(chr1 != chr2){
			if (!(vm[i+1] < vm[i])){
				invariante  = false;
			}
		}
	}

	return invariante;
}

ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C){
	for(int i = 0; i < C.size(); i++){
		sal << C.vm[i] << " ";
	}

	return sal;
}

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
