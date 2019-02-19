#ifndef ENGWORD_H
#define ENGWORD_H

#include "Hash.h"


class EngWord
{
private:
	// membervariables
	std::string word;
public:
	// constructors, destructor, ...
	EngWord(std::string word = "Empty ");
	virtual~EngWord();
	// definition of == operator and != operator 
	bool operator==(const EngWord &rhs);
	bool operator!=(const EngWord &rhs);
	// memberfunctions
	std::string getWord()const;
	void setWord(std::string words);
	
	
};

template<>
class Hash<EngWord>
{
public:
	unsigned int operator()(const EngWord& elem) const
	{
		//// to be implement
		//int hash = 0;
		//for (int i = 0; i < elem.getWord().length(); i++)
		//{
		//	hash += elem.getWord()[i];
		//}

		//// the integer returned is calculated from data in elem
		//return hash; // replace 0 with the calculated value

	
		
			unsigned int hashVal = 0;
			
			for (char ch : elem.getWord())
			{
				hashVal = 37 * hashVal + ch;
				//std::cout << hashVal << std::endl;
				}
				
			
				return hashVal; //% tableSize;
	}
};

EngWord::EngWord(std::string word)
{
	this->word = word;
}


EngWord::~EngWord()
{

}

inline bool EngWord::operator==(const EngWord & rhs)
{
	
	return this->word == rhs.word;
}

inline bool EngWord::operator!=(const EngWord & rhs)
{
	

	return this->word != rhs.word;
}

std::string EngWord::getWord()const
{
	return this->word;
}
inline void EngWord::setWord(std::string word)
{
	this->word = word;
}
#endif