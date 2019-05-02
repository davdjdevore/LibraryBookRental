// David Devore
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

// You are not obligated to use these function declarations - they're just given as examples
void readBooks(vector<Book *> & myBooks) {

  string title;
  string aut;
  string cat;
  int id;

  Book* temp;
  ifstream inFile;
  inFile.open("books.txt");

  inFile >> id;
  inFile.ignore();

  while (!inFile.eof()){

  getline(inFile, title);
  getline(inFile, aut);
  getline(inFile, cat);
  temp = new Book(id,title, aut, cat);
  myBooks.push_back(temp);
  inFile >> id;
  inFile.ignore();
  };
  inFile.close();
    return;
}

int readPersons(vector<Person *> & myCardholders) {

  ifstream inFile;
  inFile.open("persons.txt");
  Person* temp;
  int id;
  bool active;
  string first, last;

int count = 0;
  inFile >> id;

  while (!inFile.eof()){

    inFile >> active;
    inFile >> first;
    inFile >> last;

    temp = new Person(id, active, first, last);
    myCardholders.push_back(temp);

    inFile >> id;
  };

  inFile.close();
    return 0;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    ifstream inFile;
    inFile.open("rentals.txt");
    bool found = false;
    int bookID, cardID;

    inFile >> bookID;

    while (!inFile.eof()){
      inFile >> cardID;

      for (int i=0; i < myCardholders.size(); i++){
        if( cardID == myCardholders[i]->getId()){
          for (int j=0; j < myBooks.size(); j++){
            if (bookID == myBooks[j] ->getId()){
            //  cout << "cardID "<< cardID <<" & bookID "<< bookID << " found" << endl;
              myBooks[j]->setPersonPtr(myCardholders[i]);
            }
          }
        }
      }
      inFile >> bookID;
    }

    inFile.close();
}


void openCard(vector<Person *> & myCardholders) {
  string fName, lName;
  int id;
  cout << "Please enter the first name: ";
  cin >> fName;
  cout << "Please enter the last name: ";
  cin >> lName;

  id = myCardholders[myCardholders.size()-1] -> getId() +1;

  Person* temp;
  temp = new Person(id, true, fName, lName);
  myCardholders.push_back(temp);
    return;
}

void closeCard(vector<Person *> & myCardholders) {

    int id;
    char choice;
    bool found = false;

    cout << "Please enter the card ID: ";
    cin >> id;

    for (int i; i< myCardholders.size(); i++){
    if(id == myCardholders[i] -> getId())
      {
        found = true;
        cout << "Are you sure you want to deactivate card(y/n)? ";
        cin >> choice;

        if (choice == 'y'){
          if ( myCardholders[i] -> isActive() == true){
            myCardholders[i] -> setActive(false);
            cout << "Card ID deactivated" << endl;
          }
          else if( myCardholders[i] -> isActive() == false)
            cout << "Card ID is already inactive" << endl;
        }

        if (choice == 'n')
          break;
      }


    }
    if( found ==false)
    cout << "Card ID not found" << endl;
}
/*
Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

    readBooks(books);
    readPersons(cardholders);
    readRentals(books, cardholders);

    int choice, id;
    bool found = false;
    bool found2 = false;
    int count = 0;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                cout << "Please enter the card ID: ";
                cin >> id;

                for (int i = 0; i < cardholders.size(); i++){
                  if(id == cardholders[i] -> getId()){
                    found = true;

                    cout << "Cardholder: " <<cardholders[i] ->getFirstName() << " " << cardholders[i] -> getLastName() << endl;

                    cout << "Please enter the book ID: ";
                    cin >> id;

                    for(int j = 0; j< books.size(); j++){
                      if (id == books[j] -> getId() ){
                        if(books[j] -> getPersonPtr() == nullptr){
                          books[j]->setPersonPtr(cardholders[i]);
                          cout << "Rental Completed" << endl;
                          found2 = true;
                          break;
                        }
                        if(books[j] -> getPersonPtr() != nullptr){
                          cout << "Book already checked out" << endl;
                          found2 = true;

                        }
                        break;
                      }
                      else found2 = false;

                    }
                    if(found2 == false){
                      cout << "Book not found" << endl;
                    }
                  }
                  else found = false;

                }
                if(found == false){
                  cout << "Card ID not found" << endl;
                }

                break;

            case 2:
            // Book return
                cout << "Please enter the book ID to return:";
                cin >> id;
                found = false;

                for (int i = 0; i < books.size(); i++){
                  if ( id == books[i] -> getId()){
                    cout << "Title: " << books[i] ->getTitle() << endl;
                    books[i] -> removePerson();
                    cout << "Return Completed"<< endl;
                    found = true;
                  }
                }
                if ( found == false){
                  cout <<"Book ID not found" << endl;
                }

                break;

            case 3:
                // View all available books
                for(int i=0; i< books.size(); i++){
                  if( books[i] -> getPersonPtr() == nullptr){
                    count ++;
                    cout << "Book ID: " << books[i] -> getId() << endl;;
                    cout << "Title: " << books[i] -> getTitle() << endl;
                    cout << "Author: " << books[i] -> getAuthor() << endl;
                    cout << "Category: " << books[i] -> getCategory() <<endl;
                    cout << endl;
                  }
                  if (count == 0){
                    cout << "No available books" << endl;
                  }
                }
                break;

            case 4:
                // View all outstanding rentals
                for(int i=0; i< books.size(); i++){
                  if( books[i] -> getPersonPtr() != nullptr){
                    count ++;
                    cout << "Book ID: " << books[i] -> getId() << endl;;
                    cout << "Title: " << books[i] -> getTitle() << endl;
                    cout << "Author: " << books[i] -> getAuthor() << endl;
                    cout << "Category: " << books[i] -> getCategory() <<endl;
                    cout << endl;
                  }
                  if (count == 0){
                    cout << "No outstanding rentals" << endl;
                  }
                }
                break;

            case 5:
                // View outstanding rentals for a cardholder
               found = false;
               cout << "Please enter the card ID: ";
               cin >> id;

               for (int i=0; i < books.size(); i++){
                 if(books[i] -> getPersonPtr() != nullptr){
                   for(int j=0; j < cardholders.size(); j++){
                     if(id == cardholders[j] -> getId()){
                       if( id == books[i] -> getPersonPtr() -> getId()){
                         cout << "Book ID: " << books[i] -> getId() << endl;;
                         cout << "Title: " << books[i] -> getTitle() << endl;
                         cout << "Author: " << books[i] -> getAuthor() << endl;
                         cout << "Category: " << books[i] -> getCategory() <<endl;
                         cout << endl;
                       }

                       found = true;
                     }

                   }
                   if ( found == false){
                     cout << "No books currently checked out" << endl;
                     found = true;
                   }
                 }

               }
               if (found == false){
                 cout << "Card ID not found" << endl;
               }

                break;

            case 6:
                // Open new library card
                openCard(cardholders);

                break;

            case 7:
                // Close library card
                closeCard(cardholders);

                break;

            case 8:
                // Must update records in files here before exiting the program
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
