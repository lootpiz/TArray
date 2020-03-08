//TArray.h

#ifndef _TARRAY_H
#define _TARRAY_H

#include<stdio.h>
#include<assert.h>

template <typename T>
class Array
{
public:
	/**** DATE TYPE NAME ****/
	typedef int INDEX;

	/**** ENUMERATOR ****/

	/**** NESTED CLASS ****/

	/**** MEMBER FUNCTION ****/

		//// CONSTRUCTOR ////
		Array();
		Array(int capacity);
		Array(Array& source);

		//// DESTRUCTOR ////
		~Array();

		//// CONST MEMBER FUNCTION ////
		
		//// STATIC MEMBER FUNCTION ////

		//// OPERATOR FUNCTION ////
		Array<T>& operator = (const Array& source);
		T& operator [] (int index);

		//// TYPECAST FUNCTION ////

		//// NORMAL FUNCTION ////
		INDEX AppendFront(T &item);
		INDEX AppendRear(T &item);
		INDEX InsertBefore(INDEX index, T &item);
		INDEX InsertAfter(INDEX index, T &item);
		bool DeleteFront();
		bool DeleteRear();
		bool DeleteItem(int index);
		INDEX Modify(INDEX index, T &item);
		INDEX SearchByUnique(T &item, int (*Compare)(void*, void*));
		int SearchByNonUnique(T &item, int** indexArray, int (*Compare)(void*, void*));
		INDEX SearchByBinaryUnique(T &item, int (*Compare)(void*, void*));
		int SearchByBinaryNonUnique(T &item, int** indexArray, int (*Compare)(void*, void*));
		void SortBySelection(int (*Compare)(void*, void*));
		void SortByBubble(int (*Compare)(void*, void*));
		void SortByInsertion(int (*Compare)(void*, void*));
		void Traversal();
		INDEX SetAt(INDEX index, T &item);
		void GetAt(INDEX index, T &item);
		
		//// ATTRIBUTE FUNCTION ////
		T* GetFront() const;
		T* GetRear() const;
		int GetLength() const;
		int GetCapacity() const;
		INDEX GetIndex() const;
		
		INDEX MoveFirst();
		INDEX MoveLast();
		INDEX MovePrevious();
		INDEX MoveNext();

		char* BoolTypeString(int returnBool) const;

	/**** DATA MEMBER ****/

	/**** FRIEND MEMBER ****/

	/**** BIT FIELD ****/

private:
	T* front;
	T* rear;
	int capacity;
	int length;
	int index;
};
/************************************************************************/
/* Default Constructor                                                  */
/************************************************************************/
template <typename T>
Array<T>::Array()
{
	this->front = NULL;
	this->rear = NULL;
	this->capacity = 0;
	this->length = 0;
	this->index = -1;
}
/************************************************************************/
/* Constructor                                                          */
/************************************************************************/
template <typename T>
Array<T>::Array(int capacity)
{
	this->front = new T[capacity];
	assert ( this->front != NULL );
	
	this->rear = this->front +(this->capacity - 1);
	this->capacity = capacity;
	this->length = 0;
	this->index = 0;
}
/************************************************************************/
/* Copy Constructor                                                     */
/************************************************************************/
template <typename T>
Array<T>::Array(Array& source)
{
	this->front = new T[source.capacity];
	assert ( this->front != NULL );
	for(int i = 0 ; i < source.length ; i++)
	{
		this->front[i] = source.front[i];
	}

	this->rear = this->front + this->capacity;
	this->capacity = source.capacity;
	this->length = source.length;
	this->index = source.index;
}
/************************************************************************/
/* Destructor                                                           */
/************************************************************************/
template <typename T>
Array<T>::~Array()
{
	/*if( this->front != NULL )	
	{
		delete []this->front;
		this->rear = NULL;
		this->capacity = 0;
		this->length = 0;
		this->index = -1;
	}*/
}
/************************************************************************/
/* AppendFront                                                          */
/************************************************************************/
template <typename T>
Array<T>::INDEX Array<T>::AppendFront(T &item)
{
	T* temp;
	int i;
	
	temp = new T[ (this->capacity + 1) ];

	assert ( temp != NULL );

	for(i = 0 ; i < this->length ; i++) 
	{
		temp[i + 1] = this->front[i];
	}
	
	this->index = 0;
	temp[this->index] = item;

	delete []this->front;
	this->front = temp;

	this->rear = this->front + this->capacity;
	this->capacity = this->capacity + 1;
	this->length = this->length + 1;

	return this->index;
}
/************************************************************************/
/* AppendRear                                                           */
/************************************************************************/
template <typename T>
Array<T>::INDEX Array<T>::AppendRear(T &item)
{
	T* temp;
	this->index = -1;
	
	if ( this->length == this->capacity )
	{
		temp = new T[ (this->capacity+1) ];

		assert ( temp != NULL );

		for(this->index = 0 ; this->index < this->length ; this->index++) 
		{
			temp[this->index] = this->front[this->index];
		}
		
		this->index = this->length;
		temp[this->index] = item;

		//delete []this->front;
		this->front = temp;

		this->rear = (this->front + this->capacity);
		this->capacity = this->capacity + 1;
		this->length = this->length + 1;
	}
	return this->index;
}
/************************************************************************/
/* InsertBefore                                                         */
/************************************************************************/
template <class T>
Array<T>::INDEX Array<T>::InsertBefore(INDEX index, T &item)
{	
	T* temp;
	
	if( index > 0 && index <= this->capacity )
	{		
		temp = new T[ (this->capacity+1) ];

		assert ( temp != NULL );

		for(this->index=0 ; this->index < index-1 ; this->index++)
		{
			temp[this->index] = this->front[this->index];
		}
		for(this->index = index ; this->index <= this->length ; this->index++) 
		{
			temp[this->index] = this->front[ (this->index - 1 ) ];
		}
			
		this->index = index - 1;
		temp[this->index] = item;

		delete []this->front;
		this->front = temp;

		this->rear = this->front + this->capacity;
		this->capacity = this->capacity + 1;
		this->length = this->length + 1;
	}
	else
	{
		this->index = -1;
	}
	return this->index;	

}
/************************************************************************/
/* InsertAfter                                                          */
/************************************************************************/
template <class T>
Array<T>::INDEX Array<T>::InsertAfter(INDEX index, T &item)
{
	T temp;
	
	if( index >= 0 && index < this->capacity )
	{
		temp = new T[ (this->capacity+1) ];

		assert ( temp != NULL );

		for(this->index = 0 ; this->index <= index ; this->index++)
		{
			temp[this->index] = this->front[this->index];
		}
		for(this->index = index + 1 ; this->index < this->length ; this->index++) 
		{
			temp[(this->index + 1)] = this->front[this->index];
		}
			
		this->index = index + 1;
		temp[this->index] = item;

		delete []this->front;
		this->front = temp;

		this->rear = this->front + this->capacity;
		this->capacity = this->capacity + 1;
		this->length = this->length + 1;
	}
	else
	{
		this->index = -1;
	}	
	return this->index;	
}
/************************************************************************/
/* DeleteFront                                                          */
/************************************************************************/
template <class T>
bool Array<T>::DeleteFront()
{
	bool returnValue = false;
	T* temp;

	if(this->length != 0)
	{		
		temp = new T[ (this->capacity-1) ];

		assert ( temp != NULL );

		for(this->index = 1 ; this->index < this->length ; this->index++) 
		{
			temp[(this->index - 1)] = this->front[this->index];
		}
			
		delete []this->front;
		this->front = temp;

		this->rear = this->front + (this->capacity - 1);
		this->capacity = this->capacity - 1;
		this->length = this->length - 1;
		this->index = 0;

		returnValue = true;
	}
	return returnValue;
}
/************************************************************************/
/* DeleteRear                                                           */
/************************************************************************/
template <class T>
bool Array<T>::DeleteRear()
{
	bool returnValue = false;
	T* temp;

	if( this->length != 0 && this->length == this->capacity )
	{
		temp = new T[ (this->capacity-1) ];

		assert ( temp != NULL );

		for(this->index = 0 ; this->index < this->length-1 ; this->index++) 
		{
			temp[this->index] = this->front[this->index];
		}
			
		delete []this->front;
		this->front = temp;

		this->rear = this->front + (this->capacity - 1);
		this->capacity = this->capacity - 1;
		this->length = this->length - 1;
		this->index = this->length - 1;

		returnValue = true;
	}
	return returnValue;
}
/************************************************************************/
/* DeleteItem                                                           */
/************************************************************************/
template <class T>
bool Array<T>::DeleteItem(INDEX index)
{
	bool returnValue = false;
	T* temp;

	if(index >= 0 && index < this->length)
	{
		temp = new T[ (this->capacity-1) ];

		assert ( temp != NULL );

		for(this->index = 0 ; this->index < index ; this->index++) 
		{
			temp[this->index] = this->front[this->index];
		}
		for(this->index = index + 1 ; this->index < this->length ; this->index++)
		{
			temp[(this->index - 1)] = this->front[this->index];
		}
			
		delete []this->front;
		this->front = temp;

		this->rear = this->front + (this->capacity - 1);
		this->capacity = this->capacity - 1;
		this->length = this->length - 1;
		this->index = index;

		returnValue = true;
	}
	return returnValue;
}
/************************************************************************/
/* Modify                                                               */
/************************************************************************/
template <class T>
Array<T>::INDEX Array<T>::Modify(INDEX index, T &item)
{
	this->index = index;
	
	this->front[this->index] = item;
	
	return this->index;
}
/************************************************************************/
/* SearchByUnique                                                       */
/************************************************************************/
template <class T>
Array<T>::INDEX Array<T>::SearchByUnique(T &item, int (*Compare)(void*, void*))
{
	INDEX index = -1;
	int flag = 0;
	int compareValue;
	
	this->index = 0;

	while(flag == 0 && this->index < this->length)
	{
		compareValue = Compare( this->front + this->index, &item );
									
		if( compareValue == 0 )
		{
			index = this->index;
			flag = 1;
		}
		this->index = this->index + 1;
	}
	return index;
}
/************************************************************************/
/* SearchByNonUnique                                                    */
/************************************************************************/
template <class T>
int Array<T>::SearchByNonUnique(T &item, int** indexArray, int (*Compare)(void*, void*))
{
	int count = 0;
	int compareValue;
	int* temp;

	for(this->index = 0 ; this->index < this->length ; this->index++)
	{
		compareValue = Compare( &(this->front[this->index]), &item );
		if( compareValue == 0 )
		{
			count++;
		}
	}
	
	temp = new int[count];
	
	assert ( temp != NULL );
	
	count = 0;

	for(this->index = 0 ; this->index < this->length ; this->index++)
	{
		compareValue = Compare( this->front + this->index, &item );
		if( compareValue == 0 )
		{
			temp[count] = this->index;
			count++;
		}
	}
	*indexArray = temp;
 
	return count;
}
/************************************************************************/
/* SearchByBinaryUnique                                                 */
/************************************************************************/
template <class T>
Array<T>::INDEX Array<T>::SearchByBinaryUnique(T &item, int (*Compare)(void*, void*))
{
	INDEX midIndex,lowIndex,highIndex;
	int compareValue;

	lowIndex = 0;
	highIndex = this->length - 1;
	this->index = -1;
	
	while( this->index == -1 && lowIndex <= highIndex )
	{
		midIndex = (lowIndex + highIndex) / 2;

		compareValue = Compare( this->front + midIndex, &item);
	
		if( compareValue == 0 )
		{
			 this->index = midIndex;			 
		}
		else if( compareValue < 0 )
		{
			lowIndex = midIndex + 1;
		}
		else
		{
			highIndex = midIndex - 1; 
		}
	}
	return this->index;
}
/************************************************************************/
/* SearchByBinaryNonUnique                                              */
/************************************************************************/
template <class T>
int Array<T>::SearchByBinaryNonUnique(T &item, int** indexArray, int (*Compare)(void*, void*))
{
	int lowIndex, midIndex, highIndex;
	int i=0;
	int count = 0;
	int compareValue;
	int* temp;

	lowIndex = 0;
	highIndex = this->length - 1;
	midIndex = (lowIndex + highIndex) / 2;
	
	while( lowIndex <= highIndex && Compare( &(this->front[midIndex]), &item) != 0 )
	{
		compareValue = Compare(&(this->front[midIndex]), &item);
		if( compareValue < 0 )
		{
			lowIndex = midIndex + 1;
		}
		else 
		{
			highIndex = midIndex - 1;
		}
		midIndex = (lowIndex + highIndex) / 2;
	}
	if( lowIndex <= highIndex )
	{
		while( midIndex > 0 && Compare( &(this->front[midIndex - 1]), &item) == 0 )
		{
			midIndex = midIndex - 1;
		}
	}

	this->index = midIndex;

	while( midIndex < this->length && Compare( this->front + midIndex, &item) == 0 )
	{
		count++;
		midIndex++;
	}
	temp = new int[count];
	
	while( i < count )
	{
		*(temp + i) = this->index;
		this->index = this->index + 1;
		i++;
	}
	
	*indexArray = temp;
	
	return count;
}
/************************************************************************/
/* SortBySelection                                                      */
/************************************************************************/
template <class T>
void Array<T>::SortBySelection(int (*Compare)(void*, void*))
{
	int integer;
	T temp;
	int compareValue;

	for(this->index = 0 ; this->index < this->length - 1 ; this->index++)
	{
		for(integer = this->index + 1 ; integer < this->length ; integer++)
		{
			compareValue = Compare( this->front + this->index,
									this->front + integer);
			if( compareValue > 0 )
			{
				temp = this->front[this->index];
				this->front[this->index] = this->front[integer];
				this->front[integer] = temp;
			}
		}
	}
	this->index = 0;
}
/************************************************************************/
/* SortByBubble                                                         */
/************************************************************************/
template <class T>
void Array<T>::SortByBubble(int (*Compare)(void*, void*))
{
	int integer;
	T temp;
	int compareValue;

	for(this->index = this->length - 1 ; this->index >= 0 ; this->index--)
	{
		for(integer = 0 ; integer < this->index ; integer++)
		{
			compareValue = Compare( this->front + integer, this->front + (integer + 1));
			if( compareValue > 0 )
			{
				temp = this->front[integer];
				this->front[integer] = this->front[integer + 1];
				this->front[integer + 1] = temp;
			}
		}
	}
	this->index = 0;
}
/************************************************************************/
/* SortByInsertion                                                      */
/************************************************************************/
template <class T>
void Array<T>::SortByInsertion(int (*Compare)(void*, void*))
{
	int integer;
	T temp;
		
	for(this->index = 1 ; this->index < this->length ; this->index++)
	{
		temp = this->front[this->index];
		integer = this->index - 1;

		while( integer >= 0  && Compare( &temp, this->front + integer) < 0 )
		{
			this->front[integer+1] = this->front[integer];
			integer--;
		}
		this->front[integer + 1] = temp;
	}
	this->index = 0;
}
/************************************************************************/
/* Traversal                                                            */
/************************************************************************/
template <class T>
void Array<T>::Traversal()
{
	int i;
	printf("\n==== T R A V E R S A L ====\n");
	for ( i = 0 ; i < this->length ; i++ )
	{
		printf("Index = %2d Value = %2d\n", i, *(this->front + i) );
	}
	printf("===== T h e E n d =====\n");
}
/************************************************************************/
/* SetAt                                                                */
/************************************************************************/
template <class T>
Array<T>::INDEX Array<T>::SetAt(INDEX index, T &item)
{
	if( index == this->length && this->length < this->capacity )
	{
		this->index = index;
		this->front[this->index] = item;
		this->length = this->length + 1;
	}
	else
	{
		this->index = -1;
	}
	return this->index;
}
/************************************************************************/
/* GetAt                                                                */
/************************************************************************/
template <class T>
void Array<T>::GetAt(INDEX index, T &item)
{
	if( index >= 0 && index < this->capacity )
	{
		this->index = index;
		item = this->front[this->index];
	}	
}

/************************************************************************/
/* Inline Function                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////GetFront
template <class T>
inline T* Array<T>::GetFront() const
{
	return this->front;
}
//////////////////////////////////////////////////////////////////////////GetRear
template <class T>
inline T* Array<T>::GetRear() const
{
	return this->rear;
}
//////////////////////////////////////////////////////////////////////////GetLength
template <class T>
inline int Array<T>::GetLength() const
{
	return this->length;
}
//////////////////////////////////////////////////////////////////////////GetCapacity
template <class T>
inline int Array<T>::GetCapacity() const
{
	return this->capacity;
}
//////////////////////////////////////////////////////////////////////////GetIndex
template <class T>
inline Array<T>::INDEX Array<T>::GetIndex() const
{
	return this->index;
}
//////////////////////////////////////////////////////////////////////////MoveFirst
template <class T>
inline Array<T>::INDEX Array<T>::MoveFirst()
{
	INDEX index = 0;
	return index;
}
//////////////////////////////////////////////////////////////////////////MoveLast
template <class T>
inline Array<T>::INDEX Array<T>::MoveLast()
{
	this->index = this->capacity - 1;

	return this->index;
}
//////////////////////////////////////////////////////////////////////////MovePrevious
template <class T>
inline Array<T>::INDEX Array<T>::MovePrevious()
{
	if(this->index > 0)
	{
		this->index = this->index - 1;
	}
	return this->index;
}
//////////////////////////////////////////////////////////////////////////MoveNext
template <class T>
inline Array<T>::INDEX Array<T>::MoveNext()
{
	if(this->index < this->capacity-1)
	{
		this->index = this->index + 1;
	}
	return this->index;
}

//////////////////////////////////////////////////////////////////////////BoolTypeString
template <class T>
inline char* Array<T>::BoolTypeString(int returnBool) const
{
	char* boolTypeString[2] = {"FALSE", "TRUE"};
	return boolTypeString[returnBool];
}

/************************************************************************/
/* Operator Function                                                    */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////Operator[]
template <class T>
T& Array<T>::operator [] (int index)
{
	return this->front[index];
}
//////////////////////////////////////////////////////////////////////////Operator=
template <class T>
Array<T>& Array<T>::operator = (const Array& source)
{
	this->front = new T[source.capacity];

	assert ( this->front != NULL );
	for(int i = 0 ; i < source.length ; i++)
	{
		this->front[i] = source.front[i];
	}
	this->rear = this->front + this->capacity;
	this->capacity = source.capacity;
	this->length = source.length;
	this->index = source.index;	

	return (*this);
}

#endif

