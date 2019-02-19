#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>

// function object template
template <typename Key>
class Hash
{
public:
	unsigned int operator()(const Key & key) const;  
};


#endif

//template<typename Key>
//inline unsigned int Hash<Key>::operator()(const Key & key) const
//{
//	unsigned int hash = 0;
//	for (int i = 0; i < key.length(); i++)
//		hash += int(key)[i];
//		
//	//int index = hash % hashTableSize??
//	// return index??
//	return hash;
//}
