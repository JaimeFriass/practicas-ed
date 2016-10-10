/* 
 * mutacion.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __MUTACION_H
#define __MUTACION_H

#include <string>
#include <iostream> 
#include <vector>

#include "enfermedad.h"
//! Clase mutacion, asociada a la definición de una mutación/SNP 
/*! mutacion::mutacion,  .....
 * 
 @todo Implementa esta clase, junto con su documentación asociada

*/


class mutacion {
 private:
  string ID;
  string chr; 
  unsigned int pos; 
  std::vector<string> ref_alt; 
  std::vector<string> genes; 
  bool common;
  std::vector<float> caf;
  std::vector<enfermedad> enfermedades;
  std::vector<int> clnsig;

 public:

  mutacion();
  mutacion(const mutacion& m);
  mutacion(const string & str);   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
 
  void setID(const string & id);
  void setChr(const string & chr);
  void setPos(const unsigned int & pos);
  void setRef_alt(const std::vector<string> & ref_alt);
  void setGenes (const std::vector<string> & genes);  
  void setCommon (const bool & common);
  void setCaf (const std::vector<float> & caf);
  void setEnfermedades (const std::vector<enfermedad> & enfermedades);
  void setClnsig (const std::vector<int> & clnsig);  
  
  string getID( ) const;
  string getChr( ) const;
  unsigned int getPos( ) const;
  const std::vector<string> & getRef_alt () const;
  const std::vector<string> & getGenes () const;
  bool getCommon () const;
  const std::vector<float> & getCaf () const;
  const std::vector<enfermedad> & getEnfermedades () const;
  const std::vector<int> & getClnsig () const;
    

  mutacion & operator=(const mutacion & m);
  bool operator==(const mutacion & m) const;
  bool operator<(const mutacion & m) const;      //El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros). 

};

  ostream& operator<< ( ostream& , const mutacion& );   //Imprimir TODOS los campos del objeto mutación.


#include "mutacion.hxx"
#endif
