#include "Book.h"

Book::Book(string title, string author, int publicationYear, int pageCount) {
	this->title = title; 
	this->author = author; 
	this->publicationYear = publicationYear; 
	this->pageCount = pageCount; 

}

string Book::getTitle() const {
	return title;
}

string Book::getAuthor() const {
	return author; 
}

int Book::getPublicationYear() const {
	return publicationYear; 
}

int Book::getPageCount() const {
	return pageCount;
}

int Book::calculateAge(int currentYear) const {
	return currentYear - publicationYear; 
}