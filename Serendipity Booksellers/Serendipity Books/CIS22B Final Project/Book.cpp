#include "Book.h"
#include <ctime>
#include <fstream>
 
Book::Book(long long value)
{
	isbn = value;
	quantity = 0;
	dateAdded= time(NULL);
}

Book::~Book()
{
	;	// placeholder
}
string Book::getDateAddedStr(void) const
{ 
	char dateStr[26];
	ctime_s(dateStr, sizeof(dateStr), &dateAdded);
	return dateStr; 
}

void Book::writeToFile(fstream & file)
{
	file << isbn << ",";
	file << title << ",";
	file << author << ",";
	file << publisher << ",";
	file << wholesaleCost << ",";
	file << retailPrice << ",";
	file << dateAdded << endl;
}



time_t Book::getDateAdded(void) const { return dateAdded; }
void Book::setDateAdded(time_t value){ dateAdded = value; }
void Book::setIsbn(long long value){ isbn = value; }
long long Book::getIsbn(void) const{ return isbn; }
void Book::setTitle(string value){ title = value; }
string Book::getTitle(void) const{ return title; }
void Book::setAuthor(string value){ author = value; }
string Book::getAuthor(void) const{ return author; }
void Book::setPublisher(string value){ publisher = value; }
string Book::getPublisher(void) const{ return publisher; }

void Book::setQuantity(int value){ quantity = value; }
int Book::getQuantity(void) const{ return quantity; }
void Book::setWholesaleCost(double value){ wholesaleCost = value; }
double Book::getWholesaleCost(void) const{ return wholesaleCost; }
void Book::setRetailPrice(double value){ retailPrice = value; }
double Book::getRetailPrice(void) const { return retailPrice; }