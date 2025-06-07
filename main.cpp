#include <iostream>
using namespace std;

class Book // good
{
public:
    string title;
    int year;
    string author;
    int number;

    Book(string t, int y, string a, int n)
    : title(t), year(y), author(a), number(n){}
};

class Library
{
private:
    vector<Book> books;

    vector<Book> searching_year(int year) // 用年去找
    {
        vector<Book> result;
        for(int i = 0; i < books.size(); ++i)
        {
            if(books[i].year == year)
                result.push_back(books[i]);
        }
        sorting_title(result);
        return result;
    }

    void sorting_title(vector<Book> &result) // 用insertion sort排字典序
    {
        for (int i = 1; i < result.size(); ++i) 
        {
            Book key = result[i];
            int j = i - 1;
            while (j >= 0 && result[j].title > key.title) 
            {
                result[j + 1] = result[j];
                j--;
            }
            result[j + 1] = key;
        }
    }

public:
    void adding() // 加書
    {
        string title, author;
        int year, number;
        
        cout << "Enter Book Name: ";
        cin >> title;
        
        cout << "Enter Published Year: ";
        cin >> year;
        cin.ignore();
        
        cout << "Enter Book Author: ";
        cin >> author;
        
        cout << "Enter the Number of Available Copies: ";
        cin >> number;
        cin.ignore();

        books.push_back(Book(title, year, author, number));
        cout << "The book has been added to the system.\n";
    }

    void searching() // 找書
    {
        cout << "Search by:\n";
        cout << "1. Year";

        int choice;
        cin >> choice;

        if(choice == 1)
        {
            cout << "Enter Year: ";
            int year;
            cin >> year;
            cin.ignore();
            vector<Book> found = searching_year(year);
            if(found.empty()) cout << "There is no book published in " << year << ".\n";
            else
            {
                cout << "Name\tAuthor\tYear\tNumber of Available Copies\n";
                for(auto &i : found)
                    cout << i.title << "\t" << i.author << "\t" << i.year << "\t" << i.number << "\n";
            }
        }
    }
    
    void checking();
    void returning();
    void listing();
};

int main()
{
    Library lib;
    while(true)
    {
        cout << "\\Welcome to Library Management System/\n";
        cout << "1. Add a Book\n";
        cout << "2. Search Books\n";
        cout << "3. Check out a Book\n";
        cout << "4. Return a Book\n";
        cout << "5. List all books";
        cout << "6. Exit\n";
        cout << "Enter operation: ";
        
        int op;
        cin >> op;
        if(op == 1) lib.adding();
        else if(op == 2) lib.searching();
        else if(op == 3) lib.checking();
        else if(op == 4) lib.returning();
        else if(op == 5) lib.listing();
        else if(op ==  6) 
        {
            cout << "Bye Bye!\n";
            break;
        }
    }

    return 0;
}