#include <iostream>
#include <string>
#include <vector>
#include "conjunto.h"
#include "mutacion.h"

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
	bool encontrado=false;
	
	conjunto aux();
	
	for(int i=0;i< const_iterator && encontrado !=true ;i++){
		if(vm[i].getChr==chr || vm[i].getPos()==pos)
			encontrado=true;
	}
	
	if(encontrado)
		aux.insert(vm[i]);
	
	return   <aux,encontrado>;
}
pair<conjunto::value_type,bool>  conjunto::find (const string & ID) const{
	bool encontrado=false;
	
	conjunto aux();
	
	for(int i=0;i< const_iterator && encontrado !=true ;i++){
		if(vm[i].getID==ID)
			encontrado=true;
	}
	
	if(encontrado)
		aux.insert(vm[i]);
	
	return   <aux,encontrado>;
	
}
pair<conjunto::value_type,bool>  conjunto::find (const conjunto::value_type & e) const{
	bool encontrado=false;
 
	conjunto aux();
 
	for(int i=0;i< const_iterator && encontrado !=true ;i++){
		if(vm[i].getID==e.getID)
			encontrado=true;
	}
	if(encontrado)
		aux.insert(vm[i]);
	
	return   <aux,encontrado>;
	
}
conjunto::size_type conjunto::count (const str & chr, const unsigned int & pos) const{
	int encontrado=0;
	
	for(int i=0;i< const_iterator && encontrado !=1 ;i++){
		if(vm[i].getChr==chr || vm[i].getPos()==pos)
			encontrado=1;
	}
	
	return encotrado;
}

conjunto::size_type conjunto::count (const str & ID) const{
	int encontrado=0;
	
	for(int i=0;i< const_iterator && encontrado !=1 ;i++){
		if(vm[i].getID==ID)
			encontrado=1;
	}
	
	return encontrado;
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
	int encontrado=0;
	
	for(int i=0;i< const_iterator && encontrado !=1;i++){
		if(vm[i].getID==e.getID)
			encontrado=1;
	}
	
	return encontrado;
}

bool conjunto::insert( const conjunto::value_type & e){
	bool insertado=false;
	int esta_pos_chr=count(e.getChr , e.getPos);
	int esta_ID=count(e);
	
	//no están:
	if( esta_ID==0 && esta_pos_chr==0){
		if(empty()){
			value_type = e;
			size_type = 1;
			const_iterator = 1;
			insertado=true;
		}
		else{
			for(int i=0;i<cons_iterator && insertado!=true;i++){
				if(this.value_type > e ) //creo que lo machaca y no se como evitarlo
					value_type=e;
				insertado=true;
			}
			size_type++;
			const_iterator++;
		}
		
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
	if (vm.at(vm.begin() + (pos - 1))).getID() == ID) {
		vm.erase(vm.begin() + (pos - 1));
		correcto = true;
		
	}
	return correcto;
}

bool conjunto::erase(const conjunto::value_type & e){
	encontrado=false;
	if(size_type!=0){
		for(int i=0;i<const_iterator && encontrado != true;i++){
			if(vm[i].getID==e.getID)
				encontrado=true;
		}
		if(encontrado){
			for(int j=i; j<const_iterator;j++)
				vm[j]=vm[j+1];
			size_type--;
		}
	}
	return encontrado;
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
		this -> vm == org.getVM();
	}
	
	return *this;
}

conjunto::iterator conjunto::begin(){
	conjunto::iterator inicio = vm.begin();
	
	return inicio;
}


conjunto::iterator conjunto::end (){
	conjunto::iterator final = vm.end();
	
	return final;
}

conjunto::const_iterator conjunto::cbegin () const{
	conjunto::const_iterator const_inicio = vm.cbegin();
	
	return const_inicio;
}

conjunto::const_iterator conjunto::cend () const{
	conjunto::const_iterator const_final = vm.cend();
	
	return const_final;
}

conjunto::iterator conjunto::lower_bound (const string & chr, const unsigned int & pos) const{
	
if(!empty()){
 bool encontrado=false;
   while(this->value.type >= e && size_type <=i){
      i++;
      encontrado=true;
   }
  if(encontrado)
      conjunto::iterator anterior=vm[i-1];
  else
    conjunto::iterator anterior=vm.end();        
  return anterior;  
}
	
}

conjunto::iterator upper_bound (const conjunto::value_type & e) const{
if(!empty()){
 bool encontrado=false;
    for(int i=0;i<size_type  && encontrado!=true;i++)
      if(this->value.type > e)
        encontrado=true;
    if(encontrado)
      conjunto::iterator siguiente =vm[i];
    else
      conjunto::iterator siguiente =vm.end();
  return siguiente;
}
	
}

ostream &  operator << ( ostream & sal, const conjunto & C){
  for(int i=0;i<C.size_type;i++)
    sal<<vm[i];
}

bool conjunto::value_type::operator<(const &v_type){
  if(value_type.getChr() < v_type.getChr() && value_type.getPos() < v_type.getPos())
      return true;
  else
    return false;
}
bool conjunto::value_type::operator>(const &v_type){
  if(value_type.getChr() > v_type.getChr() && value_type.getPos() > v_type.getPos())
      return true;
  else
    return false;
}
bool conjunto::value_type::operator >=(const &v_type){
  if(value_type.getChr() >= v_type.getChr() && value_type.getPos() >= v_type.getPos())
      return true;
  else
    return false;
}
