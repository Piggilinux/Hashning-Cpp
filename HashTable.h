#ifndef HASHTABLE_H
#define HASHTABLE_H

enum Status{EMPTY, USED, DELETED};

template <typename HashElement>
class HashTable
{
private:
	// member variables for you to decide on
	int nrOfElements;
	int hashTableSize;
	// but it is required that you use an array (not a vector) for the table
	// använde 2 paralella arrayer en som håller reda på värden och en för Status.
	HashElement *table;
	Status *status;
	
	unsigned int myHash(const HashElement& elem) const 
	{ 
		static Hash<HashElement> hashFunc; 
		return hashFunc(elem) % hashTableSize; // hashFunc(elem) is a call of the defined operator() for HashElement
	}
	
	
public:
	HashTable(int hashTableSize = 101); 
	HashTable(const HashTable& aTable) = delete;
	virtual ~HashTable();
	HashTable& operator=(const HashTable& aTable) = delete;

	int findPos(const HashElement& elem)const;
	int contains(const HashElement& elem) const; // returns index or -1
	bool insert(const HashElement& elem);
	bool remove(const HashElement& elem);

	const HashElement& get(int index) const; 
	void makeEmpty();
	double loadFactor() const;
	int getNrOfElements() const;
	int getHashTableSize() const;
};

#endif

template<typename HashElement>
inline HashTable<HashElement>::HashTable(int hashTableSize)
{
	this->nrOfElements = 0;
	this->hashTableSize = hashTableSize;
	status = new Status[hashTableSize];
	this->table = new HashElement[hashTableSize];
	for (int i = 0; i < this->hashTableSize; i++)
		status[i] = EMPTY;
	
}

template<typename HashElement>
inline HashTable<HashElement>::~HashTable()
{
	delete[] table;
	delete[] status;
}

template<typename HashElement>
inline int HashTable<HashElement>::findPos(const HashElement & elem) const
{
	// Hashar ordet
	int locPos = this->myHash(elem);


		while(status[locPos] != EMPTY && table[locPos] != elem) // ändrade == USED till  != EMPTY
	{
		locPos++; 
		if (locPos >= this->hashTableSize)
		{
			locPos = 0;
		}
	}
		//std::cout << locPos << std::endl;
	return locPos;
}

template<typename HashElement>
inline int HashTable<HashElement>::contains(const HashElement & elem) const
{
	int contain = this->findPos(elem); 
	signed int found = -1;

	// Kompliterat
	if(status[contain] == DELETED || table[contain] != elem) 
		contain = found;

	return contain; // returnerar -1 ifall platsen kan användas
}

template<typename HashElement>
inline bool HashTable<HashElement>::insert(const HashElement & elem)
{
	bool isFree = false;
	int pos = contains(elem);//findPos(elem);

	if (pos == -1)
	{
		pos = this->myHash(elem);
		while (status[pos] == USED) // ändrade == USED till  != EMPTY
		{
			pos++; 
			if (pos >= this->hashTableSize)
			{
				pos = 0;
			}
		}
	}
	

	// om pos inte redan har elemtenet lägg till
	if (this->table[pos] != elem)
	{
		this->table[pos] = elem;
		this->status[pos] = USED;
		this->nrOfElements++;
		isFree = true;
	}
	else if (this->table[pos] == elem && this->status[pos] == DELETED) // om elementet redan finns men är "deleted", ändra till "used"
	{
		this->status[pos] = USED;
		this->nrOfElements++;
		isFree = true;
	}
	
	return isFree;
}

template<typename HashElement>
inline bool HashTable<HashElement>::remove(const HashElement & elem)
{
	bool removed = false;
	int pos = this->contains(elem); 

	if (pos != -1 && status[pos] != DELETED) // existerar elementet, ta bort.
	{
		this->status[pos] = DELETED;
		this->nrOfElements--;
		removed = true;
	}
	return removed;
}

template<typename HashElement>
inline const HashElement & HashTable<HashElement>::get(int index) const
{
	return this->table[index];
}

template<typename HashElement>
inline void HashTable<HashElement>::makeEmpty()
{
	for (int i = 0; i < this->hashTableSize; i++) // ska man hasha här?
	{
		this->status[i] = EMPTY
	}
	this->nrOfElements = 0;
}

template<typename HashElement>
inline double HashTable<HashElement>::loadFactor() const 
{
	return double(this->nrOfElements) / double(this->hashTableSize);
}

template<typename HashElement>
inline int HashTable<HashElement>::getNrOfElements() const
{
	return this->nrOfElements;
}

template<typename HashElement>
inline int HashTable<HashElement>::getHashTableSize() const
{
	return this->hashTableSize;
}



