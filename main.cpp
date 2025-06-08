#include <iostream>
#include <vector>
using namespace std;

class Book
{
public:
    string title;
    int year;
    string author;
    int number;

    Book(string t, int y, string a, int n)
    : title(t), year(y), author(a), number(n){}
};

class Record
{
public:
    string operation, title, author;
    int year;
    Record(string o, string t, int y, string a): operation(o), title(t), year(y), author(a) {}
};

class User
{
public:
    string username, password;
    vector<Record> record;
    User(string u, string p): username(u), password(p){}
};

class Admin
{
public:
    string adminname, password;
    vector<Record> record;
    Admin(string a, string p): adminname(a), password(p){}
};

class Library 
{
private:
    vector<Book> books;
    vector<User> users;
    vector<Admin> admins;
    User *current_user = nullptr;
    Admin *current_admin = nullptr;

    vector<Book> searching_year(int year) // 用年份去找要的書
    {
        vector<Book> result;
        for(int i = 0; i < books.size(); ++i)
            if(books[i].year == year)
                result.push_back(books[i]);
        
        sorting_title(result); // return之前先sort一下
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

    int finding_book(const string &title) // 找書的位置
    {
        for(int i = 0; i < books.size(); ++i)
            if(books[i].title == title)
                return i;
        return -1;
    }

    int finding_user(const string &username) // 找user
    {
        for(int i = 0; i < users.size(); ++i)
            if(users[i].username == username)
                return i;
        return -1;
    }
    int finding_admin(const string &adminname) // 找admin
    {
        for(int i = 0; i < admins.size(); ++i)
            if(admins[i].adminname == adminname)
                return i;
        return -1;
    }

public:
    void registering_user() // user註冊
    {
        string username, password1, password2;
        cout << "Enter Username: ";
        cin >> username;
        if(finding_user(username) != -1 && finding_admin(username) != -1)
            cout << "The name has already exist. Try another.\n";
        else
        {
            cout << "Enter password: ";
            cin >> password1;
        
            while(true)
            {
                cout << "Enter the password again: ";
                cin >> password2; // 密碼要確認一次
                if(password1 == password2)
                {
                    users.push_back(User(username, password1)); // 建立新用戶
                    cout << "User " << username << " has been created successfully.\n";
                    return;
                }
                else
                    cout << "Two passwords doesn't match, please try again.\n";
            }
        }
    }

    void registering_admin() // admin註冊
    {
        string adminname, password1, password2;
        cout << "Enter Adminname: ";
        cin >> adminname;
        if(finding_user(adminname) != -1 && finding_admin(adminname) != -1)
            cout << "The name has already exist. Try another.\n";
        else
        {
            cout << "Enter password: ";
            cin >> password1;
        
            while(true)
            {
                cout << "Enter the password again: ";
                cin >> password2; // 密碼要確認一次
                if(password1 == password2)
                {
                    admins.push_back(Admin(adminname, password1)); // 建立新admin
                    cout << "Admin " << adminname << " has been created successfully.\n";
                    return;
                }
                else
                    cout << "Two passwords doesn't match, please try again.\n";
            }
        }
    }
    bool login_user() // user login
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        int idx = finding_user(username); // 找看看user是否存在
        if(idx != -1 && users[idx].password == password)
        {
            current_user = &users[idx];
            cout << "Login successfully. Welcome, " << current_user->username << "!\n";
            return true;
        }
        else
        {
            cout << "Wrong username or password\n";
            return false;
        }
    }

    bool login_admin() // admin login
    {
        string adminname, password;
        cout << "Enter adminname: ";
        cin >> adminname;
        cout << "Enter password: ";
        cin >> password;
        int idx = finding_admin(adminname); // 找看看admin是否存在
        if(idx != -1 && admins[idx].password == password)
        {
            current_admin = &admins[idx];
            cout << "Login successfully. Welcome, " << current_admin->adminname << "!\n";
            return true;
        }
        else
        {
            cout << "Wrong adminname or password\n";
            return false;
        }
    }

    void logout_user() // user logout
    {
        cout << "Logout: " << current_user->username << "\n";
        current_user = nullptr;
    }

    void logout_admin() // admin logout
    {
        cout << "Logout: " << current_admin->adminname << "\n";
        current_admin = nullptr;
    }

    void adding() // 加一本書
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
        current_admin->record.push_back(Record("Add      ",title,year,author));
        cout << "The book has been added to the system.\n";
    }

    void searching() // 用年份找書
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
    
    void checking() // 借書
    {
        string title;
        cout << "Book Name: ";
        cin >> title;
        int idx = finding_book(title);
        if(idx == -1) 
        {
            cout << "The Book can't be found.\n";
            return;
        }
        else if(books[idx].number <= 0) 
        {
            cout << "All books have been lent out\n";
            return;
        }
        else
        {   
            books[idx].number--;
            cout << "Borrow Successfully!\n";
            if(current_user) current_user->record.push_back(Record("Check out", books[idx].title, books[idx].year, books[idx].author));
            if(current_admin) current_admin->record.push_back(Record("Check out", books[idx].title, books[idx].year, books[idx].author));
        }
    }
    
    void returning() // 還書
    {
        string title;
        cout << "Book Name: ";
        cin >> title;
        int idx = finding_book(title);
        if(idx == -1)
        {
            cout << "Can't find this book.\n";
            return;
        }
        else
        {
            books[idx].number++;
            cout << "Return Successfully!\n";
            if(current_user) current_user->record.push_back(Record("Return   ", books[idx].title, books[idx].year, books[idx].author));
            if(current_admin) current_admin->record.push_back(Record("Return   ", books[idx].title, books[idx].year, books[idx].author));
        }
    }

    void listing() // 列出所有書 一樣按照字典序
    {
        if(books.empty()) cout << "There is no any book.\n";
        else
        {
            vector<Book> copy = books;
            sorting_title(copy);
            cout << "Name\tAuthor\tYear\tNumber of Available Copies\n";
            for(auto &i : copy)
                    cout << i.title << "\t" << i.author << "\t" << i.year << "\t" << i.number << "\n";
        }
    }

    void recording_user() // 記錄user的opertaions
    {
        cout << "--- User Records for " << current_user->username << " ---\n";
        cout << "Operation" << "\t" << "Title" << "\t" << "Year" << "\t" << "Author\n";
        for(auto &i : current_user->record)
            cout << i.operation << "\t" << i.title << "\t" << i.year << "\t" << i.author << "\n";
    }
    
    void recording_admin() // 記錄admin的operations
    {
        cout << "--- Admin Records for " << current_admin->adminname << " ---\n";
        cout << "Operation" << "\t" << "Title" << "\t" << "Year" << "\t" << "Author\n";
        for(auto &i : current_admin->record)
            cout << i.operation << "\t" << i.title << "\t" << i.year << "\t" << i.author << "\n";
    }

    void upgrade_user()
    {
        cout << "Users: ";
        for(auto &u : users) 
            cout << u.username << " ";
        cout << "\n";

        cout << "Promote user: "; 
        string name; 
        cin >> name;

        int i = finding_user(name);
        if(i < 0) 
        {
            cout << "No such user.\n"; 
            return;
        }
        admins.emplace_back(users[i].username, users[i].password);
        users.erase(users.begin()+i);
        cout << "Promoted.\n";
    }

    void downgrade_admin()
    {
        cout << "Admins: ";
        for(auto &i : admins) 
            cout << i.adminname << " ";
        cout << "\n";

        cout << "Demote admin: "; 
        string name; 
        cin >> name;

        int i = finding_admin(name);
        if(i < 0) 
        {
            cout << "No such admin.\n"; 
            return;
        }
        users.emplace_back(admins[i].adminname, admins[i].password);
        admins.erase(admins.begin()+i);
        cout << "Demoted.\n";
    }

    void deleting_user()
    {
        cout << "Users: ";
        for(auto &u : users) 
            cout << u.username << " ";
        cout << "\n";

        cout << "Delete user: "; 
        string name; 
        cin >> name;

        int i = finding_user(name);
        if(i < 0)
        { 
            cout << "No such user.\n";
            return; 
        }
        users.erase(users.begin() + i);
        cout << "Deleted.\n";
    }
};

int main()
{
    Library lib;
    bool user_logged = false;
    bool admin_logged = false;
    while(true)
    {
        if(admin_logged) // admin登入後
        {
            cout << "1. Add a book.\n";
            cout << "2. Search a book by published year.\n";
            cout << "3. Check out a book.\n";
            cout << "4. Return a book.\n";
            cout << "5. List all books.\n";
            cout << "6. Print Records.\n";
            cout << "7. Personnel Management.\n";
            cout << "8. Log out.\n"; 
            int user_op;
            cin >> user_op;
            if(user_op == 1) lib.adding();
            else if(user_op == 2) lib.searching();
            else if(user_op == 3) lib.checking();
            else if(user_op == 4) lib.returning();
            else if(user_op == 5) lib.listing();
            else if(user_op == 6) lib.recording_admin();
            else if(user_op == 7) 
            {
                cout << "1. Upgrade Users.\n";
                cout << "2. Downgrade Admins.\n";
                cout << "3. Delete Users.\n";
                int ma;
                cin >> ma;
                if(ma == 1) lib.upgrade_user();
                else if(ma == 2) lib.downgrade_admin();
                else if(ma == 3) lib.deleting_user();
            }
            else if(user_op == 8)
            {
                lib.logout_admin();
                admin_logged = false;
            }

        }
        else if(user_logged) // user登入後
        {
            cout << "1. Check out a book.\n";
            cout << "2. Return a book.\n";
            cout << "3. List all books.\n";
            cout << "4. Print Records.\n";
            cout << "5. Log out.\n";
            int user_op;
            cin >> user_op;
            if(user_op == 1) lib.checking();
            else if(user_op == 2) lib.returning();
            else if(user_op == 3) lib.listing();
            else if(user_op == 4) lib.recording_user();
            else if(user_op == 5)
            { 
                lib.logout_user();
                user_logged = false;
            }
        }
        else // 沒有人登入時
        {
            cout << "\\Welcome to Library Management System/\n";
            cout << "1. User Register.\n";
            cout << "2. Admin Register.\n";
            cout << "3. User Login.\n";
            cout << "4. Admin Login.\n";
            cout << "5. Exit.\n";
        
            int num; 
            cin >> num;

            if(num == 1) lib.registering_user();
            else if(num == 2) lib.registering_admin();
            else if(num == 3) user_logged = lib.login_user();
            else if(num == 4) admin_logged = lib.login_admin();
            else if(num == 5) break;
        }
    }
    return 0;
}