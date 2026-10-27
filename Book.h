#ifndef BOOK_H 
#define BOOK_H 
#include <string>

using namespace std; 

class Book {
private:
	string title;
	string author;
	int publicationYear;
	int pageCount;


public:
	Book(string title, string author, int publicationYear, int pageCount);

	string getTitle() const; 
	string getAuthor() const; 
	int getPublicationYear() const; 
	int getPageCount() const; 

	int calculateAge(int currentYear) const; 

};

#endif 