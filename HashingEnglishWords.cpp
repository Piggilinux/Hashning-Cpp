#include "EngWord.h"
#include "Hash.h"
#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <crtdbg.h>


double loadAmount(HashTable<EngWord> &hashTable);
bool addWord(std::string word, HashTable<EngWord> &hashTable);
bool readFromFile(std::string filename, EngWord arr[]);
void findWordsFromList(std::string findWords, HashTable<EngWord> &hashTable);
bool remove(std::string word, HashTable<EngWord> &hashTable);
void addArrToTable(EngWord arr[], HashTable<EngWord> &hashTable);



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	HashTable<EngWord> hashTable(2503);
	EngWord arr[1100];
	std::string word;
	
	//1. läs från fil och 
	if (readFromFile("engWords", arr) == true)
	{
		std::cout << "The file Has been read!" << std::endl;
	}
	else
		std::cout << "Could't read from file....";

	//2. addar array till hashTable
	addArrToTable(arr, hashTable);

	std::cout << "\n*****************************************\n" << std::endl;

	

		int menu = -1;
		while (menu != 0)
		{
			std::cout << "1.Add word. " << std::endl;
			std::cout << "2.Remove word" << std::endl;
			std::cout << "3.Does word exist?" << std::endl;
			std::cout << "0.Quit" << std::endl;

			std::cin >> menu;
			std::cin.ignore();

			switch (menu)
			{
			case 1:
			{
				std::cout << "Enter word to add: ";
				getline(std::cin, word);

				if (addWord(word, hashTable) == true) 
					std::cout << "Word added!" << std::endl; 
				else
					std::cout << "Word already exists!" << std::endl;
				break;
			}
			case 2:
			{
				std::cout << "Enter word to remove: ";
				getline(std::cin, word);
			
				if(remove(word, hashTable) == true)
					std::cout << "Word removed!" << std::endl;
				else
					std::cout << "Couldn't find word..!" << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "Enter word(s): ";
				getline(std::cin, word);

				findWordsFromList(word, hashTable);
				break;
			}
			}
		}
		

	system("pause");
}

double loadAmount(HashTable<EngWord> &hashTable)
{
	return hashTable.loadFactor();
}

bool addWord(std::string word, HashTable<EngWord> &hashTable)
{
	bool added = false;
	if (hashTable.insert(word) == true)
		added = true;

	return added;
}
bool readFromFile(std::string filename, EngWord arr[]) // filename == EngWord.txt
{
	bool read = false;

	std::string fileToRead = filename + ".txt";
	std::ifstream inFromFile;
	inFromFile.open(fileToRead);

	std::string word;
	for (int i = 0; i < 999; i++)
	{
		inFromFile >> word;
		arr[i] = word; // lägger in dom lästa orden i en array

		read = true;
	}
	inFromFile.close();
	return read;
}

void findWordsFromList(std::string findWords, HashTable<EngWord> &hashTable)
{
	EngWord word;
	std::string tmp;

	findWords = findWords.substr(0, findWords.length()); // ignorerar "tomrum"
	std::istringstream partCounter(findWords);

	do 
	{
		partCounter >> tmp;  // skriver ut ord för ord till tmp
		word.setWord(tmp);
		if (hashTable.contains(word) == -1) // om -1 returneras så finns inte ordet
			std::cout << tmp << std::endl;
	} while (partCounter); // gör till alla ord har gåtts igenom
}


bool remove(std::string word, HashTable<EngWord>& hashTable)
{
	bool removed = false;

	if (hashTable.remove(word) == true)
		removed = true;
	return removed;
}

void addArrToTable(EngWord arr[], HashTable<EngWord> &hashTable)
{
	//2. Adda ord från texfilen
	for (int i = 0; i < 999; i++)
	{
		addWord(arr[i].getWord(), hashTable);
	}
	//3. LoadAmount
	double amount = loadAmount(hashTable);
	std::cout << "The Loadamount is " << amount << std::endl;
}
