#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Book.h"
#include <string>


using namespace std;

class Inventory
{
private:
	Book* books[100];	// unsorted array, in order of when they were added
	int numBooks;
	Book ** authorList;
	Book ** isbnList;
	Book ** TitleList;
	Book ** PublisherList;

public:
	Inventory(void);
	~Inventory();
	Book* addBook(long long);
	Book* getBook(int);	// temporary
	Book** searchAuthor(string);
	Book** searchTitle(string);
	Book** searchIsbn(long long);
	Book** searchPublisher(string);
	void writeBooks(void);
	void readBooksFromFile(void);
	Book** generateISBNList(void);
	Book** getISBNList(void);
	int getNumBooks(void);
	Book * searchISBN(long long) const;

};
#endif
