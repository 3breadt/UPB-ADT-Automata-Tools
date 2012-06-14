/*
 * DynArray.h
 *
 *  Created on: 7 juin 2012
 *      Author: yessine
 */

#ifndef DYNARRAY_H_
#define DYNARRAY_H_

#include <iostream>
#include <cassert> // for assert

using namespace std;

template <class T > class DynArray
{

private:
	unsigned int  uiMaxSize;
	unsigned int  uiSize;
	T* pArray;
public:
	DynArray();
	~DynArray();

	void doubleSize();
	void add(T element);
	T& operator[] (const unsigned int nIndex);
	unsigned int getLength();

	int exist( T element);

	void printArray();

};

template <class T > DynArray<T>::DynArray()
		: uiMaxSize(2) , uiSize(0)
{
	pArray = new T [uiMaxSize];
	#ifdef DEBUG
	cout << "****DynArray constructor called" << endl ;
	#endif
}

template <class T > DynArray<T>::~DynArray()
{
	//delete [] pArray ;
	//cout << "**DynArray destructor called" << endl ;
}

template <class T > void DynArray<T>::doubleSize()
{
	unsigned int i;
		T* temp ;

		uiMaxSize = uiMaxSize * 2 ;
		temp = new T[uiMaxSize];

		for (i=0 ; i<uiSize; i++)
		{
			temp[i] = pArray[i];
		}

		delete [] pArray ;

		pArray = temp ;
}

template <class T > void DynArray<T>::add( T element )
{
	if(uiSize < uiMaxSize)
		{
			pArray[uiSize] = element;
			uiSize++ ;
		}
		else
		{
			this->doubleSize();
			this->add(element);
		}
}

template <class T > void DynArray<T>::printArray()
{
	unsigned int i;

		cout << "printing elements: " <<endl;
	    for (i=0; i<uiSize; i++ )
	    {
	    	cout<<pArray[i]<<endl;
	    }
}

template <class T > T& DynArray<T>::operator[]( const unsigned int nIndex )
{
	assert(nIndex >= 0 && nIndex < uiSize);

	return pArray[nIndex];

}

template <class T > unsigned int DynArray<T>::getLength()
{
	return uiSize;
}


template<> inline int DynArray<string>::exist( string element)
{
	unsigned int i;
	for(i=0; i<this->uiSize ; i++)
	{
		if (pArray[i].compare(element)==0)
		{
			return 1;

		}
	}

	return 0;

}



#endif /* DYNARRAY_H_ */
