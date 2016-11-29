// CIS22B Final Project
// This is a test

#include <iostream>
#include <iomanip>
#include "Book.h"
#include "Inventory.h"
#include "Order.h"
#include <ctime>
#include <string>



using namespace std;

void cashierModule(void);
void inventoryModule(void);
void reportModule(void);
void displayMainMenu(void);
void displayCashierScreen(Order *);
void displayInventoryMenu(void);
void displayBookInformationScreen(Book *);
void displayReportsMenu(void);
void displayBookLookup(void);
void displayAddBook(void);
void displayEditBook(Book *);
void bookLookup(void);
Book* displayAttributeSearch(int);
void editBook(Book *, int);

Inventory inventory;
enum bookAttribute { ISBN, TITLE, AUTHOR, PUBLISHER, WHOLESALE_COST, RETAIL_PRICE, DATE_ADDED };


int main(void)
{
	int menuOption = -1;
	system("mode 100, 50");	// sets command prompt 100 chars wide and 50 chars tall

	while (menuOption != 4)
	{
		displayMainMenu();
		cin >> menuOption;
		switch (menuOption)
		{
		case (1) :
			cashierModule();
			break;
		case (2) :
			inventoryModule();
			break;
		case (3) :
			reportModule();
			system("pause");	//debug
			break;
		case (4) :
			break;
		default:
			cout << "That is not a valid choice. Please select from the menu.";
			system("pause");
		}
	}
	inventory.writeBooks();
	return 0;
}

void cashierModule(void)
{
	Order newOrder;
	displayCashierScreen(&newOrder);
}



void displayMainMenu(void)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "*                                             Main Menu                                            *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      1. Cashier Module                                           *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      2. Inventory Database Module                                *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "*                                      3. Report Module                                            *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "*                                      4. Exit                                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *" 
		<< "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< " Enter Your Choice:";

}

void displayCashierScreen(Order * currentOrder)
{
	Book * currentBook;
	time_t rawtime = time(NULL);
	struct tm now;
	localtime_s(&now, &rawtime);
	char dateStr[30];
	int bookCounter = 0;
	strftime(dateStr, 30, "%d %b %Y %I:%M%p", &now);
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*   Serendipity Book Sellers                                                                       *"
		<< "*                                                                                                  *"
		<< "*   Date: " << dateStr << "                                                                      *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   Qty   ISBN           Title                                                     Price   Total   *"
		<< "*   ______________________________________________________________________________________________ *";
	while (bookCounter < currentOrder->getNumBooks())
	{
		currentBook = currentOrder->getBook(bookCounter);
		cout << "*" << setw(6) << currentOrder->getQuantity(bookCounter)
			<< setw(14) << currentBook->getIsbn()
			<< setw(60) << currentBook->getTitle()
			<< setw(8) << fixed << setprecision(2) << currentBook->getRetailPrice()
			<< setw(8) << fixed << setprecision(2) << currentOrder->getQuantity(bookCounter) * currentBook->getRetailPrice() << "*";
		bookCounter++;
	}
		cout << "*                     Subtotal                                                                     *"
		<< "*                     Tax                                                                          *"
		<< "*                     Total                                                                        *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*  Thank You for Shopping at Serendipity!                                                          *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************" << endl;
		//cout << ""
}

void inventoryModule(void)
{
	int menuOption = -1;
	while (menuOption != 5)
	{
		displayInventoryMenu();
		cin >> menuOption;
		cin.ignore();
		switch (menuOption)
		{
			case (1) :
				bookLookup();
				break;
			case (2) :
				displayAddBook();
				break;
			case (3) :
				//displayEditBook();
				break;
			case (4) :
				break;
			case (5) :
				break;
			default:
				cout << "That is not a valid option. Please select from the menu.";
		}
	}
}

void bookLookup(void)
{
	int menuOption = -1;
	int subMenuOption;
	Book * foundBook;
	while (menuOption != 5)
	{
		subMenuOption = -1;
		displayBookLookup();
		cin >> menuOption;
		if (menuOption != 5) // Horrible. Needs to be done properly.
		{
			while (subMenuOption != 9)
			{
				foundBook = displayAttributeSearch(menuOption - 1);
				cin >> subMenuOption;
				switch (subMenuOption)
				{
				case(1) :
					editBook(foundBook, 1);
					break;
				case(2) :
					editBook(foundBook, 2);
					break;
				case(3) :
					editBook(foundBook, 3);
					break;
				case(4) :
					editBook(foundBook, 4);
					break;
				case(5) :
					editBook(foundBook, 5);
					break;
				case(6) :
					editBook(foundBook, 6);
					break;
				case(7) :
					editBook(foundBook, 7);
					break;
				case(8) :
					editBook(foundBook, 8);
					break;
				case(9) :
					break;
				default:
					;
				}
			}
		}
	}
}

Book* displayAttributeSearch(int attribute)
{
	string attributeStr;
	string inputValue;
	Book * foundBook;

	switch (attribute)
	{
	case (ISBN) :
		attributeStr = "ISBN";
		break;
	case (TITLE) :
		attributeStr = "Title";
		break;
	case (AUTHOR) :
		attributeStr = "Author";
		break;
	case (PUBLISHER) :
		attributeStr = "Publisher";
		break;
	case (WHOLESALE_COST) :
		attributeStr = "Wholesale Cost";
		break;
	case (RETAIL_PRICE) :
		attributeStr = "Retail Price";
		break;
	default:
		return nullptr;
	}

	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                            " << attributeStr << " Search" << endl;
	cout << "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*  Enter the " << attributeStr << " to search for: ";
	cin >> inputValue;
	foundBook = inventory.searchAttribute(attribute, inputValue);
	if (foundBook != nullptr)
	{
		cout << "****************************************************************************************************"
			 << "*  ISBN: " << foundBook->getIsbn() << endl;
		cout << "*  Title: " << foundBook->getTitle() << endl;
		cout << "*  Author: " << foundBook->getAuthor() << endl;
		cout << "*  Publisher: " << foundBook->getPublisher() << endl;
		cout << "*  Date Added: " << foundBook->getDateAddedStr();
		cout << "*  Quantity On-hand: " << setw(4) << foundBook->getQuantity() << endl;
		cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << foundBook->getWholesaleCost() << endl;
		cout << "*  Retail Price: $" << fixed << setprecision(2) << foundBook->getRetailPrice() << endl;
		cout << "*" << endl;
		cout<< "****************************************************************************************************"
			<< "*                                                                                                  *"
			<< "*                                                                                                  *"
			<< "*   Select the record you would like to change:                                                    *"
			<< "*                                                                                                  *"
			<< "*   1. ISBN                                                                                        *"
			<< "*                                                                                                  *"
			<< "*   2. Title                                                                                       *"
			<< "*                                                                                                  *"
			<< "*   3. Author                                                                                      *"
			<< "*                                                                                                  *"
			<< "*   4. Publisher                                                                                   *"
			<< "*                                                                                                  *"
			<< "*   5. Date Added                                                                                  *"
			<< "*                                                                                                  *"
			<< "*   6. Quantity On-Hand                                                                            *"
			<< "*                                                                                                  *"
			<< "*   7. Wholesale Cost                                                                              *"
			<< "*                                                                                                  *"
			<< "*   8. Retail Price                                                                                *"
			<< "*                                                                                                  *"
			<< "*   9. Return to Inventory Menu                                                                    *" 
			<< "*                                                                                                  *"
			<< "*                                                                                                  *"
			<< "*                                                                                                  *"
			<< "****************************************************************************************************"
			<< "Enter Your Choice: ";
		return foundBook;
	}
	else
	{
		cout << "****************************************************************************************************"
			<< "  No book with that " << attributeStr << " was found. Press enter to try again." << endl;
		system("pause");
		return nullptr;
	}
}

void editBook(Book * editBook, int attribute)
{
	string tempStr;
	long long tempISBN;
	int tempInt;
	double tempDouble;
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                            ISBN Search                                           *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< "*  ISBN: " << editBook->getIsbn() << endl;
	cout << "*  Title: " << editBook->getTitle() << endl;
	cout << "*  Author: " << editBook->getAuthor() << endl;
	cout << "*  Publisher: " << editBook->getPublisher() << endl;
	cout << "*  Quantity On-hand: " << setw(4) << editBook->getQuantity() << endl;
	cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << editBook->getWholesaleCost() << endl;
	cout << "*  Retail Price: $" << fixed << setprecision(2) << editBook->getRetailPrice() << endl;
	cout << "*  Date Added: " << editBook->getDateAddedStr();
	cout << "*" << endl;
	cout << "****************************************************************************************************";
	switch (attribute)
	{
	case (1) :
		cout << "Enter the new ISBN for this book: ";
		cin >> tempISBN;
		editBook->setIsbn(tempISBN);
		inventory.generateAttributeList(ISBN);
		break;
	case (2) :
		cout << "Enter the new Title for this book: ";
		cin >> tempStr;
		editBook->setTitle(tempStr);
		//inventory.generateISBNList(); need to resort by title
		break;
	case (3) :
		cout << "Enter the new Author for this book: ";
		cin >> tempStr;
		editBook->setAuthor(tempStr);
		//inventory.generateISBNList(); need to resort by author
		break;
	case (4) :
		cout << "Enter the new Publisher for this book: ";
		cin >> tempStr;
		editBook->setPublisher(tempStr);
		//inventory.generateISBNList(); need to resort by publisher
		break;
	case(5) :
		//This is tricky. Need to get date added in specific format and convert it to time_t
		break;
	case(6) :
		cout << "Enter the new Quantity On-hand for this book: ";
		cin >> tempInt;
		editBook->setQuantity(tempInt);
		//inventory.generateISBNList(); need to resort by Quantity? Maybe not. This changes all the time. Sort when you need it
		break;
	case(7) :
		cout << "Enter the new Wholesale Cost for this book: ";
		cin >> tempDouble;
		editBook->setWholesaleCost(tempDouble);
		//inventory.generateISBNList(); need to resort by wholesale cost
	case(8) :
		cout << "Enter the new Retail Price for this book: ";
		cin >> tempDouble;
		editBook->setRetailPrice(tempDouble);
		//inventory.generateISBNList(); need to resort by retail price
	case(9) :
		break;
	default :
		cout << "That is not a valid option. Please try again.";
		system("pause");
	}
}
void displayBookLookup(void)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                            Book Lookup                                           *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                     Search by:                                                   *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      1. ISBN                                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      2. Title                                                    *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      3. Author                                                   *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      4. Publisher                                                *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      5. Return to Inventory Menu                                 *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< " Enter Your Choice:";
}

void displayAddBook(void)
{
	string userInput;
	Book * currentBook = inventory.addBook();
	system("cls");
	cout << "Please enter the following information for adding a book: " << endl;
	cout << "Enter the 13 digit ISBN for the book to be added or press q and press enter to quit: ";
	getline(cin, userInput); // check for quit and follow up actions, also needs formatting
	currentBook->setIsbn(strtoll(userInput.c_str(), nullptr, 10)); // doesn't perform any checks on what the user inputs. Needs to be broken up
	cout << "Enter the title of the book or press q and press enter to quit: ";
	getline(cin, userInput); // check less than 200 chars. Or whatever the max is.
	currentBook->setTitle(userInput);
	cout << "Enter the name of the author of the book or press q and press enter to quit: "; // what do I do if they want to enter multiple authors?
	getline(cin, userInput);
	currentBook->setAuthor(userInput);
	cout << "Enter the publisher of the book or press q and press enter to quit: ";
	getline(cin, userInput);
	currentBook->setPublisher(userInput);
	cout << "Enter the wholesale cost of the book or press q and press enter to quit: ";
	getline(cin, userInput);
	currentBook->setWholesaleCost(strtod(userInput.c_str(), nullptr));
	cout << "Enter the retail price of the book or press q and press enter to quit: ";
	getline(cin, userInput);
	currentBook->setRetailPrice(strtod(userInput.c_str(), nullptr));
}

void displayEditBook(Book * displayBook)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                         Book Information                                         *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*  ISBN: " << displayBook->getIsbn() << "*******************************************************************************"
		<< "*  Title: " << displayBook->getTitle() << "*" << endl; // need to ensure string is of a fixed length
	cout << "*  Author: " << displayBook->getAuthor() << "*" << endl; //need to ensure string is of a fixed length
	cout << "*  Publisher: " << displayBook->getPublisher() << "*" << endl;
	cout << "*  Date Added: " << displayBook->getDateAddedStr() << "*" << endl;
	cout << "*  Quantity On-hand: " << setw(4) << displayBook->getQuantity() << endl;
	cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << displayBook->getWholesaleCost() << endl;
	cout << "*  Retail Price: $" << fixed << setprecision(2) << displayBook->getRetailPrice() << endl;
	cout << "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   Select the record you would like to change:                                                    *"
		<< "*                                                                                                  *"
		<< "*   1. Title                                                                                       *"
		<< "*                                                                                                  *"
		<< "*   2. Author                                                                                      *"
		<< "*                                                                                                  *"
		<< "*   3. Publisher                                                                                   *"
		<< "*                                                                                                  *"
		<< "*   4. Date Added                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   5. Quantity On-Hand                                                                            *"
		<< "*                                                                                                  *"
		<< "*   6. Wholesale Cost                                                                              *"
		<< "*                                                                                                  *"
		<< "*   7. Retail Price                                                                                *"
		<< "*                                                                                                  *"
		<< "*   8. Return to Inventory Menu                                                                    *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************";
}
void displayInventoryMenu(void)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                          Inventory Menu                                          *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      1. Look Up a Book                                           *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      2. Add a Book                                               *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      3. Edit a Book's Record                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      4. Delete a Book                                            *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      5. Return to the Main Menu                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< " Enter Your Choice:";
}

void displayBookInformationScreen(Book * displayBook)
{
	system("cls");
	cout << "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                      Serendipity Booksellers                                     *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                         Book Information                                         *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*  ISBN: " << displayBook->getIsbn() << "*******************************************************************************"
		<< "*  Title: " << displayBook->getTitle() << "*" << endl; // need to ensure string is of a fixed length
	cout << "*  Author: " << displayBook->getAuthor() << "*" << endl; //need to ensure string is of a fixed length
	cout << "*  Publisher: " << displayBook->getPublisher() << "*" << endl;
	cout << "*  Date Added: " << displayBook->getDateAddedStr() << "*" << endl;
	cout << "*  Quantity On-hand: " << setw(4) << displayBook->getQuantity() << endl;
	cout << "*  Wholesale Cost: $" << fixed << setprecision(2) << displayBook->getWholesaleCost() << endl;
	cout << "*  Retail Price: $" << fixed << setprecision(2) << displayBook->getRetailPrice() << endl;
	cout << "*                                                                                                  *"
		<< "****************************************************************************************************"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   Select the record you would like to change:                                                    *"
		<< "*                                                                                                  *"
		<< "*   1. Title                                                                                       *"
		<< "*                                                                                                  *"
		<< "*   2. Author                                                                                      *"
		<< "*                                                                                                  *"
		<< "*   3. Publisher                                                                                   *"
		<< "*                                                                                                  *"
		<< "*   4. Date Added                                                                                  *"
		<< "*                                                                                                  *"
		<< "*   5. Quantity On-Hand                                                                            *"
		<< "*                                                                                                  *"
		<< "*   6. Wholesale Cost                                                                              *"
		<< "*                                                                                                  *"
		<< "*   7. Retail Price                                                                                *"
		<< "*                                                                                                  *"
		<< "*   8. Return to Inventory Menu                                                                    *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "*                                                                                                  *"
		<< "****************************************************************************************************";
}

void reportModule(void)
{
	displayReportsMenu();
}
void displayReportsMenu(void)
{
	system("cls");
	cout << "*******************************************************************************" << endl
		<< "*                                                                             *" << endl
		<< "*                                                                             *" << endl
		<< "*                           Serendipity Booksellers                           *" << endl
		<< "*                                                                             *" << endl
		<< "*                                   Reports                                   *" << endl
		<< "*                                                                             *" << endl
		<< "*                                                                             *" << endl
		<< "*                         1. Inventory Listing                                *" << endl
		<< "*                                                                             *" << endl
		<< "*                         2. Inventory Wholesale Value                        *" << endl
		<< "*                                                                             *" << endl
		<< "*                         3. Inventory Retail Value                           *" << endl
		<< "*                                                                             *" << endl
		<< "*                         4. Listing by Quantity                              *" << endl
		<< "*                                                                             *" << endl
		<< "*                         5. Listing by Cost                                  *" << endl
		<< "*                                                                             *" << endl
		<< "*                         5. Listing by Age                                   *" << endl
		<< "*                                                                             *" << endl
		<< "*                         5. Return to the Main Menu                          *" << endl
		<< "*                                                                             *" << endl
		<< "*                         Enter Your Choice:                                  *" << endl
		<< "*                                                                             *" << endl
		<< "*******************************************************************************" << endl;
}
