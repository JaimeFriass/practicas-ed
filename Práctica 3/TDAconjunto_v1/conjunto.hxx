
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

conjunto::value_type conjunto::getVM(){
	return vm;
}

pair<conjunto::value_type,bool>  conjunto::find (const string & chr, const unsigned int & pos) const{
	
}
