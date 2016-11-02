
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

value_type conjunto::getVM(){
	return vm;
}
