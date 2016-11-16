#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ctime>


using namespace std;

class Book
{
private:
	long long isbn;
	string title;
	string author;
	string publisher;
	int quantity;
	double wholesaleCost;
	double retailPrice;
	time_t dateAdded;


public:
	static unsigned int numBooks;
	Book(long long);	// Constructor
	~Book();			// Destructor

	// Setters
	void setIsbn(long long);
	void setTitle(string);
	void setAuthor(string);
	void setPublisher(string);
	void setQuantity(int);
	void setWholesaleCost(double);
	void setRetailPrice(double);
	void setDateAdded(time_t);

	// Getters
	long long getIsbn(void) const;
	string getTitle(void) const;
	string getAuthor(void) const;
	string getPublisher(void) const;
	string getDateAddedStr(void) const;
	time_t getDateAdded(void) const;
	int getQuantity(void) const;
	double getWholesaleCost(void) const;
	double getRetailPrice(void) const;

	void Book::writeToFile(fstream&);
};

#endif