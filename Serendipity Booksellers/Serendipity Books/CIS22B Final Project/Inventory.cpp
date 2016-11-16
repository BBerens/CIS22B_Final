#ifndef __INVENTORY_CPP__
#define __INVENTORY_CPP__

#include "Inventory.h"
#include "Book.h"
#include <fstream>



Inventory::Inventory(void)
{
	numBooks = 0;
	readBooksFromFile();
	isbnList = new Book*[numBooks];
	isbnList = generateISBNList();
}

Inventory::~Inventory()
{
	for (int i = 0; i < numBooks; i++)
	{
		delete books[i];
	}
}

Book* Inventory::addBook(long long value)
{
	// when we add a new book we should generate a new dynamically allocated array of book pointers(books)
	Book* newBook;
	newBook = new Book(value); // temporary, need to do this with dynamic allocation
	books[numBooks] = newBook;
	numBooks++;
	isbnList = generateISBNList();
	return newBook;
}

Book* Inventory::getBook(int index)	// temporary
{
	return books[index];
}

void Inventory::readBooksFromFile()
{
	long long tempIsbn;
	char tempChar[200];
	string tempStr;
	double tempDouble;
	time_t tempDate;
	Book* bookPtr;
	fstream bookDatabase;

	bookDatabase.open("BookDatabase.txt", ios::in);
	while (getline(bookDatabase, tempStr, ','))
	{
		tempIsbn = stoll(tempStr, nullptr, 10);
		bookPtr = addBook(tempIsbn);
		getline(bookDatabase, tempStr, ',');	// messes up if there is a ',' in the title, need to choose a different char
		bookPtr->setTitle(tempStr);
		getline(bookDatabase, tempStr, ',');
		bookPtr->setAuthor(tempStr);
		getline(bookDatabase, tempStr, ',');
		bookPtr->setPublisher(tempStr);
		getline(bookDatabase, tempStr, ',');
		tempDouble = stod(tempStr, nullptr);
		bookPtr->setWholesaleCost(tempDouble);
		getline(bookDatabase, tempStr, ',');
		tempDouble = stod(tempStr, nullptr);
		bookPtr->setRetailPrice(tempDouble);
		getline(bookDatabase, tempStr, '\n');
		tempIsbn = stoll(tempStr, nullptr, 10);
		tempDate = static_cast<time_t>(tempIsbn);
		bookPtr->setDateAdded(tempDate);
	}
	bookDatabase.close();
}
void Inventory::writeBooks()
{
	fstream bookDatabase;
	bookDatabase.open("BookDatabase.txt", ios::out);
	for (int i = 0; i < numBooks; i++)
	{
		books[i]->writeToFile(bookDatabase);
	}
	bookDatabase.close();

}

Book ** Inventory::generateISBNList(void)
{
	int lowerLimit;
	int smallIndex;
	Book * temp;
	Book ** tempISBNList = nullptr;
	tempISBNList = new Book*;
	for (int i = 0; i < numBooks; i++)
	{
		tempISBNList[i] = books[i];

	}
	for (int i = 0; i < numBooks; i++)
	{
		lowerLimit = i;
		smallIndex = lowerLimit;
		for (int j = lowerLimit; j < numBooks; j++)
		{
			if (tempISBNList[j]->getIsbn() < tempISBNList[smallIndex]->getIsbn())
			{
				smallIndex = j;
			}
			temp = tempISBNList[lowerLimit];
			tempISBNList[lowerLimit] = tempISBNList[smallIndex];
			tempISBNList[smallIndex] = temp;
		}
	}
	return tempISBNList;
}

Book** Inventory::getISBNList(void)
{
	return isbnList;
}

int Inventory::getNumBooks(void)
{
	return numBooks;
}

Book * Inventory::searchISBN(long long inputISBN) const 
{
	int first = 0; // First array element
	int last = numBooks - 1; // Last array element
	int	middle; // Mid point of search
	int position = -1; // Position of search value
	bool found = false; // Flag
	while (!found && first <= last)
	{
		middle = (first + last) / 2; // Calculate mid point
		if (isbnList[middle]->getIsbn() == inputISBN) // If value is found at mid
		{
			found = true;
			position = middle;
		}
		else if (isbnList[middle]->getIsbn() > inputISBN) // If value is in lower half
			last = middle - 1;
		else
			first = middle + 1; // If value is in upper half
	}
	if (found)
		return isbnList[position];
	else
		return nullptr;
}
#endif

