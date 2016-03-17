#ifndef _EXTRASTL_H_
#define _EXTRASTL_H_

#include <list>

using namespace std;

//Extra list functions

template<typename TYPE>
int lFindIndex(list<TYPE> l, TYPE it)
{
	int index = 0;
	
	
	for (list<TYPE>::iterator item = l.begin(); item != l.end(); item++, index++)
	{
		if ((*item) == it)
			return index;
	}

	return (-1);
}

/*template<typename TYPE>
list<TYPE>::iterator lAt(list<TYPE> l, int index)
{
	int pos = 0;
	list<TYPE>::iterator item = l.begin();

	while (item != l.end())
	{
		if (pos++ == index)
			break;

		item++;
	}

	return item;
}*/

#endif _EXTRASTL_H_