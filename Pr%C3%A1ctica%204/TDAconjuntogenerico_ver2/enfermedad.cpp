#include <string>
#include "enfermedad.h"
#include <iostream>
#include <vector>

using namespace std;

enfermedad::enfermedad(){
	name = "Ninguno";
	ID = "Ninguno";
	database = "Ninguno";
}

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
	this -> name = name;
	this -> ID = ID;
	this -> database = database;
}

void enfermedad::setName(const string & name){
	this -> name = name;
}

void enfermedad::setID(const string & ID){
	this -> ID = ID;
}

void enfermedad::setDatabase(const string & database){
	this -> database = database;
}

string enfermedad::getName() const{
	return name;
}

string  enfermedad::getID() const{
	return ID;
}

string enfermedad::getDatabase() const{
	return database;
}

enfermedad & enfermedad::operator = (const enfermedad & e){
	if (this != &e){
		this -> ID = e.getID();
		this -> name = e.getName();
		this -> database = e.getDatabase();
	}
	
	return *this;
}

string enfermedad::toString() const {
	return this -> name + " : " + this -> ID + "\tDB: " + this -> database + "\n";
}

bool enfermedad::operator == (const enfermedad & e) const{
	bool igual = false;
	
	if(this != &e){
		if(name.size() == e.name.size() && ID.size() == e.ID.size() && database.size() == e.database.size() )
			igual = true;
	}
	else
		igual = true;
	
	return igual;
}


bool enfermedad::operator != (const enfermedad & e) const{
	return !(this == &e);
}

bool enfermedad::operator<(const enfermedad & e) const {
	return (name < e.getName());
}

bool enfermedad::nameContains(const string & str) const{
	bool dentro = false;
	
	if (str == ""){
		dentro = true;
	}
	
	if(name.find(str) != string::npos){
		dentro = true;
	}
	
	return dentro;
}

string enfermedad::imprime_Enf() const{
	string hola;
	
	hola = getName() + " " + getID() + " " + getDatabase();
	
	return hola;
}

ostream& operator << ( ostream& os, const enfermedad & e){
	os << e.getName() << " " << e.getID() << "\n" << e.getDatabase() << endl;
	
	return os;
}
