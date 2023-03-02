#ifndef _MOVIECOLLECTION_HPP_
#define _MOVIECOLLECTION_HPP_

#include "Movie.hpp"

#include<iostream>
#include <fstream>

using namespace std;

#define MAX_SIZE 100

class MovieCollection
{
private:
	Movie *_colPtr; //pointer to the array
	int _size; //size of the array
	int _filled;//actual number of Movies in the array
	
public:
	MovieCollection(): _size(5), _filled(0) {_colPtr = new Movie[_size];}; //simple constructor inizializate the variable to be able to hold 5 values
  	MovieCollection(ifstream &catalogo); // constructor for reading from a imput file
  	MovieCollection(const MovieCollection &copia); // creates a copia of another MovieCollection
  	
  	
  	const MovieCollection operator+(const MovieCollection &coleccion) const;//overloading of + operator
  	const MovieCollection operator/(const MovieCollection &coleccion) const; //overloading of / operator
  	MovieCollection& operator=(const MovieCollection &coleccion);// overloading of = opertaor
	MovieCollection& operator+=(const Movie &pelicula); // overloading of += operator
	MovieCollection& operator+=(const MovieCollection &coleccion);//overloadinf of += operator with two moviecollections
	MovieCollection& operator-=(const MovieCollection &coleccion);//overloadinf of -= operator with two moviecollections
	
	MovieCollection& operator-=(const Movie &pelicula);//overloadinf of -= operator
	
	void clear(); // make the array seems empty
	ostream& print(ostream &nose) const; // print the values of the moviecollection

	friend ostream& operator<<(ostream &os, const MovieCollection &coleccion);
  	
};

#endif
