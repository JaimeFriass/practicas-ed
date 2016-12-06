
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T, typename CMP>

conjunto<T,CMP>::conjunto(){
	vm.clear();
}

template <typename T, typename CMP>

conjunto<T,CMP>::conjunto(const conjunto<T,CMP> & d){
	this -> vm = (d.getVM());
}

template <typename T, typename CMP>

const vector<mutacion>  & conjunto<T,CMP>::getVM() const{
	return vm;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::iterator  conjunto<T,CMP>::find (const conjunto<T,CMP>::value_type & s){
	bool encontrado = false;
	conjunto<T,CMP>::iterator it = begin();
	
	for(int i = 0; i < vm.size() && !encontrado; i++){
		if(s == vm[i])
			encontrado = true;
		else
			it ++;
		
	}
	
	return it;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::const_iterator  conjunto<T,CMP>::find (const value_type & s) const{
	conjunto<T,CMP>::const_iterator it = find(s);
	
	return it;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::size_type conjunto<T,CMP>::count (const conjunto<T,CMP>::value_type & e) const{
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


template <typename T, typename CMP>
pair <typename conjunto<T,CMP>::iterator, bool> conjunto<T,CMP>::insert (const conjunto<T,CMP>::value_type& val) {
	pair<conjunto<T,CMP>::iterator, bool> par;
	bool fin=false;
	conjunto<T,CMP>::iterator it;
	conjunto<T,CMP>::iterator principio(vm.begin(), vm);
	conjunto<T,CMP>::iterator ultimo(vm.end(), vm);
	conjunto<T,CMP>::iterator aux(find(val));
	
	//cerr << endl << "Dentro de conjunto::insert" << endl;
	//cerr << "\tItero sobre el conjunto para encontrar su posición" << endl;
	
	//CC: ojo con el bucle usando iteradores. Conoceis la implementación del operator< en iteradores?
	//No utilicéis < para iteradores, sino == y != para controlar bucle, como en los ejemplos del guión y las transparencias.
	
	for(it = principio; it != ultimo && !fin; ){
		//        for(it = vm.begin() ;it < vm.end() -1 && !fin; ){
		//cerr << "\tElemento : "<<(*it).getID()<<endl;
		if(comp(*it, aux)){
			it++;
			//cerr << "\tEs menor, avanzo it"<<endl;
		}
		else{
			if(!comp(*it, aux) && !comp(aux, *it)){        //son iguales
				par.first = ultimo;
				par.second = false;
				fin = true;
				//cerr << "\tEs igual. Termino sin insertar."<<endl;
			}
			else{
				vm.push_back(aux);
				par.second = true;
				fin = true;
				//cerr << "\tEs mayor. LO REEMPLAZO POR val"<<endl;
				
			}
		}
	}
	
	if(!fin) {//si no se insertó
		//cerr<< "\tHemos terminado de recorrer los elementos y ninguno era mayor. Lo inserto al final"<<endl;
		//CC: OJO, así no se inserta, no me deja compilar:
		//vm[vm.end()]=val;
		//Así si:
		vm.push_back(aux);
		//o con insert , mirad manual. http://www.cplusplus.com/reference/vector/vector/insert/
		par.first = ultimo;
		par.second = true;
	}
	return par;
	
}

/*
 template <typename T, typename CMP>
 pair <typename conjunto<T,CMP>::iterator, bool> conjunto<T,CMP>::insert (const conjunto<T,CMP>::value_type& val) {
 return insert(val);
 }
 */

template <typename T, typename CMP>

typename conjunto<T,CMP>::iterator conjunto<T,CMP>::erase (const conjunto<T,CMP>::iterator position){
	erase(position);
	
	return position;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::size_type conjunto<T,CMP>::erase (const value_type& val){
	conjunto<T, CMP>::iterator it = find(val);
	conjunto<T,CMP>::iterator ultimo(vm.end(), vm);
	
	if(it != ultimo){
		erase(it);
	}
	
	/*
	 Se devuelve 1 ya que este método devuelve el número de elementos
	 borrados y este sólo puede ser 1
	 */
	return 1;
}

template <typename T, typename CMP>

void conjunto<T,CMP>::clear(){
	vm.clear();
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::size_type conjunto<T,CMP>::size() const {
	return vm.size();
}

template <typename T, typename CMP>

bool conjunto<T,CMP>::empty() const{
	return vm.empty();
}

template <typename T, typename CMP>

conjunto<T, CMP> & conjunto<T, CMP>::operator=( const conjunto<T, CMP> & org){
	if (this != &org){
		vm.clear();
		
		vm = org.getVM();
	}
	
	return *this;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::iterator conjunto<T,CMP>::begin(){
	conjunto<T,CMP>::iterator inicio(vm.begin(), vm);
	
	return inicio;
}

template <typename T, typename CMP>


typename conjunto<T,CMP>::iterator conjunto<T,CMP>::end (){
	conjunto<T,CMP>::iterator ultimo(vm.end(), vm);
	
	return ultimo;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cbegin () const{
	conjunto<T,CMP>::const_iterator const_inicio = vm.cbegin();
	
	return const_inicio;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::cend () const{
	conjunto<T,CMP>::const_iterator const_final = vm.cend();
	
	return const_final;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::iterator conjunto<T,CMP>::lower_bound (const conjunto<T,CMP>::value_type& val){
	conjunto<T,CMP>::iterator lower(vm.begin(), vm);
	bool encontrado = false;
	
	for(int i = 0; i < vm.size() && !encontrado; i++){
		if(vm[i] < val){
			lower++;
		}
		else{
			if( val < vm[i]){
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

template <typename T, typename CMP>

typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::lower_bound (const conjunto<T,CMP>::value_type& val) const{
	conjunto<T,CMP>::const_iterator it = lower_bound(val);
	
	return it;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::ibegin(){
	bool encontrado = false;
	impar_iterator aux;
	
	aux.it = vm.begin();
	aux.elvector = &vm;
	
	while(!encontrado && aux.it != vm.end() ){
		if((*aux).getPos() % 2 == 0){
			encontrado = true;
		}
		else{
			aux++;
		}
	}
	
	return aux;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::cibegin( ) const{
	bool encontrado=false;
	conjunto<T,CMP>::const_impar_iterator aux;
	
	aux.it = vm.begin();
	aux.elvector = &vm;
	
	while(!encontrado && aux.it != vm.end() ){
		if((*aux).getPos() % 2 == 0){
			encontrado = true;
		}
		else{
			aux++;
		}
	}
	
	return aux;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::impar_iterator conjunto<T,CMP>::iend(){
	bool encontrado = false;
	impar_iterator aux;
	
	aux.it = vm.end();
	aux.elvector = &vm;
	
	while(!encontrado && aux.it != vm.begin() ){
		if((*aux).getPos() % 2 == 0){
			encontrado = true;
		}
		else{
			aux.it--;
		}
	}
	
	return aux;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::const_impar_iterator conjunto<T,CMP>::ciend( ) const{
	bool encontrado = false;
	const_impar_iterator aux;
	
	aux.it = vm.end();
	aux.elvector = &vm;
	
	while(!encontrado && aux.it != vm.begin() ){
		if((*aux).getPos() % 2 == 0){
			encontrado = true;
		}
		else{
			aux.it--;
		}
	}
	
	return aux;
}

template <typename T, typename CMP>

typename conjunto<T,CMP>::iterator conjunto<T,CMP>::upper_bound (const value_type& val){
	conjunto<T,CMP>::iterator upper = vm.begin();
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

template <typename T, typename CMP>

typename conjunto<T,CMP>::const_iterator conjunto<T,CMP>::upper_bound (const value_type& val) const{
	conjunto<T,CMP>::const_iterator it = upper_bound(val);
	
	return it;
}

template <typename T, typename CMP>

bool conjunto<T,CMP>::cheq_rep() const{
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
		
		if (chr1 == chr2 && vm[i+1].getPos() > vm[i].getPos()){
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

template <typename T, typename CMP>

ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C){
	vector<T> mutaciones = C.getVM();
	
	for(int i = 0; i < C.size(); i++){
		sal << mutaciones[i] << " ";
	}
	
	return sal;
}

template<typename T, class CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::sbegin(){
	secure_iterator iter;
	
	iter.elvector = &vm;
	iter.it = vm.begin();
	
	return iter;
}

template<typename T, class CMP>
typename conjunto<T,CMP>::secure_iterator conjunto<T,CMP>::send(){
	secure_iterator iter;
	
	iter.elvector = &vm;
	iter.it = vm.end();
	
	return iter;
}

template<typename T, class CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::csbegin() const{
	const_secure_iterator iter;
	
	iter.elvector = &vm;
	iter.it = vm.cbegin();
	
	return iter;
}

template<typename T, class CMP>
typename conjunto<T,CMP>::const_secure_iterator conjunto<T,CMP>::csend() const{
	const_secure_iterator iter;
	
	iter.elvector = &vm;
	iter.it = vm.cend();
	
	return iter;
}
