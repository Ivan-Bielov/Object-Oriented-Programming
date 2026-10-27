# include <iostream>
#include <vector>
#include "Book.h"

using namespace std; 

int main() {
	vector<Book> catalog;
	catalog.push_back(Book("Kobzar", "Taras Shevchenko", 1840, 115));
	catalog.push_back(Book("Kassandra", "Lesya Ukrainka", 1907, 69));
	catalog.push_back(Book("The C++ Programming Language", "Bjarne Stroustrup", 2010, 1335));
	catalog.push_back(Book("1984", "George Orwell", 1949, 300));
	catalog.push_back(Book("Clean Code: A Handbook of Agile Software Craftsmanship", "Robert C. Martin", 2008, 464));
	catalog.push_back(Book("I See You Are Interested in Darkness", "", 2020, 664));

	int currentYear = 2026;

	cout << "Library catalog:" << endl << endl;

	for (int i = 0; i < catalog.size(); i++) {
		cout << "Title: " << catalog[i].getTitle() << endl;
		cout << "Author: " << catalog[i].getAuthor() << endl;
		cout << "Year: " << catalog[i].getPublicationYear() << endl;
		cout << "Pages: " << catalog[i].getPageCount() << endl;
		cout << "Age: " << catalog[i].calculateAge(currentYear) << " years" << endl;
		cout << endl;
	}

	return 0;
}
