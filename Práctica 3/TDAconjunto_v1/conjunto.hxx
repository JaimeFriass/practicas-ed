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
pair<conjunto::value_type,bool>  find (const string & chr, const unsigned int & pos) const{
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
pair<conjunto::value_type,bool>  find (const string & ID) const{
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
pair<conjunto::value_type,bool>  find (const conjunto::value_type & e) const{
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

conjunto::size_type count (const string & chr, const unsigned int & pos) const{
	int encontrado=0;
	
	for(int i=0;i< const_iterator && encontrado !=1 ;i++){
		if(vm[i].getChr==chr || vm[i].getPos()==pos)
			encontrado=1;
	}
	return encotrado;
}

conjunto::size_type count (const string & ID) const{
	int encontrado=0;
	
	for(int i=0;i< const_iterator && encontrado !=1 ;i++){
		if(vm[i].getID==ID)
			encontrado=1;
	}
	
	return encontrado;
}
conjunto::size_type count (const conjunto::value_type & e) const{
	int encontrado=0;
	
	for(int i=0;i< const_iterator && encontrado !=1;i++){
		if(vm[i].getID==e.getID)
			encontrado=1;
	}
	
	return encontrado;
}

bool insert( const conjunto::value_type & e){
	int esta_pos_chr=count(e.getChr , e.getPos);
	int esta_ID=count(e);
	
	//no están:
	if( esta_ID==0 && esta_pos_chr==0){
		if(empty()){
			
  }
	}
