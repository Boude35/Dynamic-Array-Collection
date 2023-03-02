#include "MovieCollection.hpp"
#include "Movie.hpp"

#include <iostream>

using namespace std;

//read values form an imput file and store them in the movieCollection
MovieCollection::MovieCollection(ifstream &catalogo)
{
	_filled = 0; // number of actual values in the array
	_size = 5; //the size of the array = 5
	_colPtr = new Movie[_size]; //create a new pointer to an array
	catalogo >> _colPtr[_filled]; // store the first value
	
  	while(catalogo)//while the file has values
  	{
  		if ( _size-1 == _filled)//if the size is not enough duplicate it
  		{
  			_size = _size*2; // duplicate the size
  			Movie *_colPtr2 = new Movie[_size]; // create a temporl array for storing the values
  			for (int i = 0; i <=_filled; i++)
  			{
  				_colPtr2[i] = _colPtr[i]; // copy all the values
  			}
  			_colPtr = new Movie[_size]; //reinizialization with the size duplicated
  			for (int i = 0; i <= _filled; i++)
  			{
  				_colPtr[i] = _colPtr2[i]; // copy the values back
  			}
  		}
  		_filled++; // add one to the variable that control values already in the array
  		catalogo >>_colPtr[_filled];//next values
  
  	}

}
//create a copy of another MovieCOllection
MovieCollection::MovieCollection(const MovieCollection &copia)
{
	_filled = 0; // number of actual values in the array
	_size = copia._size;
	_colPtr = new Movie[_size];//iniczializated instance variablea and make the pointer
	
	for (int i= 0; i<copia._filled; i++)//copy all the values
	{
		_colPtr[i] = copia._colPtr[i]; //one by one
		_filled++;//update the var
	}
}


//overload of the plus operator
const MovieCollection
MovieCollection::operator+(const MovieCollection &coleccion) const
{
	MovieCollection respuesta;
	respuesta._size = _size; //create a new Moviecollection with the size of the moviecollection that will held
	respuesta._colPtr = new Movie[respuesta._size];
	for (int i= 0; i<_filled; i++)
	{
		respuesta._colPtr[i] = _colPtr[i]; //copy the entire fisrt array
		respuesta._filled++;
	}
	
	for (int j= 0; j<coleccion._filled; j++) //copy the values of the second that are not repeated
	{
		int detector = 0;//detector of copied values
		for (int i = 0; i<_filled; i++)
		{
			if (_colPtr[i] == coleccion._colPtr[j])//if two movies are equal
			{
				detector = 1;//the values of the detector change
				break;
			}
			
		}
		if (detector!=1)
			{
			
				if ( respuesta._size-1 == respuesta._filled)//resize the array if it is too small explained line 18
  				{
  				respuesta._size = respuesta._size*2;
  				Movie *_colPtr2 = new Movie[respuesta._size];
  				for (int i = 0; i <= respuesta._filled; i++)
  					{
  						_colPtr2[i] = respuesta._colPtr[i];
  					}
  					respuesta._colPtr = new Movie[respuesta._size];
  					for (int i = 0; i <= respuesta._filled; i++)
  					{
  						respuesta._colPtr[i] = _colPtr2[i];
  					}
  				}		
				respuesta._colPtr[respuesta._filled] = coleccion._colPtr[j]; //diffrent values are copied
				respuesta._filled++;//update var
			}
	} 
	
	
	return respuesta;//return the union
}


//overloading of the / operator
const MovieCollection
MovieCollection::operator/(const MovieCollection &coleccion) const
{
	MovieCollection respuesta;
	respuesta._size = coleccion._size;//Create a new movicollection with the enough space
	respuesta._colPtr = new Movie[respuesta._size];
	for(int i=0 ; i < _filled; i++)
	{
		for (int j = 0; j < coleccion._filled; j++)//copy the values that are equal for both
		{
			if (_colPtr[i]==coleccion._colPtr[j])//if values are equal
			{
				respuesta._colPtr[respuesta._filled] = _colPtr[i];//copy them
				respuesta._filled++;//update var
			}
		}
	}
	
	
	
	
	
	
	return respuesta;//retur the intersection
}


//overloading of the = operator
MovieCollection& MovieCollection::operator=(const MovieCollection &coleccion)
{
	for(int i=0; i<coleccion._filled; i++)
	{
		if ( _size-1 == _filled)//if the size is not enough duplicate it (step by step line 18)
  		{
  			_size = _size*2;
  			Movie *_colPtr2 = new Movie[_size];
  			for (int i = 0; i <=_filled; i++)
  			{
  				_colPtr2[i] = _colPtr[i];
  			}
  			_colPtr = new Movie[_size];
  			for (int i = 0; i <= _filled; i++)
  			{
  				_colPtr[i] = _colPtr2[i];
  			}
  		}
		_colPtr[i] = coleccion._colPtr[i];//copy all the values
		_filled++;//update var
	}
	
	return *this;
	
	
	
}

//overloading of the += operator
MovieCollection& MovieCollection::operator+=(const Movie &pelicula)
{
		int detector = 0; //detector repeated values
		for (int i = 0; i<_filled; i++)//make sure that movie is not repeated
		{
		
			if (_colPtr[i] == pelicula)//if the an array movie equals the movie pretended to remove
			{
				detector = 1;//vhange the value
				break;
			}
			
		}
		if (detector!=1)
			{
				if ( _size-1 == _filled)//resize the array
  				{
  				_size = _size*2;
  				Movie *_colPtr2 = new Movie[_size];
  				for (int i = 0; i <=_filled; i++)
  					{
  						_colPtr2[i] = _colPtr[i];
  					}
  					_colPtr = new Movie[_size];
  					for (int i = 0; i <= _filled; i++)
  					{
  						_colPtr[i] = _colPtr2[i];
  					}
  				}		
				_colPtr[_filled] = pelicula;//cadd the movie
				_filled++;
			}
	
	
	return *this;//return a copy of the array but updated
}

// iverloading of the operator += but with two MovieCollections
MovieCollection& MovieCollection::operator+=(const MovieCollection &coleccion)
{
	
	
	for (int j= 0; j<coleccion._filled; j++)//compare the values to dtect repeated ones
	{
		int detector = 0;
		for (int i = 0; i<_filled; i++)
		{
			if (_colPtr[i] == coleccion._colPtr[j])// if two movies are equal
			{
				detector = 1;//chanfe the values
				break;//exit
			}
			
		}
		if (detector!=1)//if values are different
			{
				if ( _size-1 == _filled)//resize the array
  				{
  				_size = _size*2;
  				Movie *_colPtr2 = new Movie[_size];
  				for (int i = 0; i < _filled; i++)
  					{
  						_colPtr2[i] = _colPtr[i];
  					}
  					_colPtr = new Movie[_size];
  					for (int i = 0; i < _filled; i++)
  					{
  						_colPtr[i] = _colPtr2[i];
  					}
  				}		
				_colPtr[_filled] = coleccion._colPtr[j];//copy it to the left array
				_filled++;//update var
			}
	}
	
	
	return *this;//return a copy of the array but updated
}
	
	
	
	
	

//overloading of the -= operator with a movie
MovieCollection& MovieCollection::operator-=(const Movie &pelicula)
{
	for(int i=0 ; i <_filled; i++)
	{
		if (_colPtr[i]==pelicula)//find the movie in the array
			{
			
				for(int j = i; j< _filled; ++j)
					_colPtr[j] = _colPtr[j+1];//remove themovie and update the array
				_filled--;//update the variable
			}
	}
	
	return *this;//return a copy but with the movie removed
}
//overloading of the -= operator with another Moviecollection
MovieCollection& MovieCollection::operator-=(const MovieCollection &coleccion)
{

	for(int i=0 ; i < _filled; i++)
	{
		for (int j = 0; j < coleccion._filled; j++)
		{
			if (_colPtr[i]==coleccion._colPtr[j])//find the same movie in the different arrays
			{
				for(int j = i; j< _filled; ++j)
					_colPtr[j] = _colPtr[j+1];//remove it and update the array
				_filled--;
			}
		}
	}
	
	return *this;
	
}


//print the value of the movie COllection
ostream&
MovieCollection::print(ostream &os) const
{
	for (int i = 0; i<_filled; i++)
		os << _colPtr[i] <<endl;//print all the movies
	return os;
}
//overloading of the << operator
ostream& operator<<(ostream &os, const MovieCollection &coleccion)
{
  return coleccion.print(os);
}
//function that clear the array
void MovieCollection::clear()
{
	_filled = 0;//array has no value inside
	_colPtr = new Movie[_filled];//new array with 0 values in it
	
	
}

