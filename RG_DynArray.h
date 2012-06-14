/**
 * @file RG_DynArray.h
 * @author Yacine Smaoui, Florian Hemmelgarn
 *
 * @brief Definition and implementation of the DynArray class
 *
 *
 */

#ifndef DYNARRAY_H_
#define DYNARRAY_H_

#include <iostream>
#include <cassert> // for assert

using namespace std;

#define  MAX_INITIAL_ARRAY_SIZE 5

/**
 * @class DynArray
 * @brief a container template class where the different components of a Grammar are stored
 * represents a dynamic array with the possibility of dynamically increase the length.
 */
template <class T > class DynArray
{

private:
	/** initial maximum size reserved for the array */
	unsigned int  uiMaxSize;
	/** the actual size of the array */
	unsigned int  uiSize;
	/** a pointer that defines the array address */
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

/**
 * @brief DynArray Constructor
 * Dynamically allocates Memory and initialises the size
 * */
template <class T > DynArray<T>::DynArray()
		: uiMaxSize(MAX_INITIAL_ARRAY_SIZE) , uiSize(0)
{
	pArray = new T [uiMaxSize];
	#ifdef DEBUG
	cout << "****DynArray constructor called" << endl ;
	#endif
}

/**
 * Destructor
 */
template <class T > DynArray<T>::~DynArray()
{
	//cout << "**DynArray destructor called" << endl ;
}

/**
 * @brief Doubles the Size of the DynArray
 *
 * called when trying to add an element to a full DynArray.
 */
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

/**
 * @brief adds an element to the DynArray
 * @param element the element to add
 */
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

/**
 * @brief prints the elements of the DynArray
 *
 * works only for Scalar types and strings for now
 */
template <class T > void DynArray<T>::printArray()
{
	unsigned int i;

		cout << "printing elements: " <<endl;
	    for (i=0; i<uiSize; i++ )
	    {
	    	cout<<pArray[i]<<endl;
	    }
}

/**
 * @brief overrides the [] operator
 *
 * The elements of the DynArray can then be accessed with the [] operator.
 * This Method also checks is the index can be accepted within the size of the DynArray.
 *
 * @param nIndex
 * @return
 */
template <class T > T& DynArray<T>::operator[]( const unsigned int nIndex )
{
	assert(nIndex >= 0 && nIndex < uiSize);

	return pArray[nIndex];

}

/**
 * @brief returns the Size of the DynArray
 * @return Size of the DynArray
 */
template <class T > unsigned int DynArray<T>::getLength()
{
	return uiSize;
}

/**
 * @brief checks the existance of a string element in the Array.
 *
 * a specialized method. works with DynArrays of type string.
 *
 * @param element the searched for element in the array.
 * @return 1 if the element exists, 0 if not .
 */
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
