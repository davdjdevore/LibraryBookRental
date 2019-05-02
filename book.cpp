#include "book.h"

Book::Book(int id, string bookName, string auth, string cat) {
    bookID = id;
    title = bookName;
    author = auth;
    category = cat;
    personPtr = nullptr;
}

string Book::getTitle() {
    return title;
}

string Book::getAuthor() {
    return author;
}

string Book::getCategory() {
    return category;
}

int Book::getId() {
    return bookID;
}
void Book::setPersonPtr(Person * ptr) {

  personPtr = new Person(ptr -> getId(), ptr -> isActive(), ptr -> getFirstName(), ptr -> getLastName());
}

void Book::removePerson(){
  personPtr = nullptr;
}

Person * Book::getPersonPtr() {

    return personPtr;
}
