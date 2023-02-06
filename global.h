#ifndef ONLINEREADERBOOK_GLOBAL_H
#define ONLINEREADERBOOK_GLOBAL_H
using namespace std;

////////////////////////////////AdminClass////////////////////////
class Admin{
private:
    int id;
    int view=1;
    string name;
    string password;
    string UserName;
    string email;
public:
    Admin()=default;
    void SetId(int);
    void SetView(int);
    void SetName(string);
    void SetPassword(string);
    void SetUserName(string);
    void SetEmail(string);
    string GetName();
    int GetView();
    void AdminMenu();
    bool options(int);
    void profile();
    void AddBooks();
};
////////////////////////////////ClientClass///////////////////
class Client{
private:
    int id;
    int view=2;
    string name;
    string password;
    string UserName;
    string email;
public:
    Client()=default;
    void ClientMenu();
    bool options(int);
    void profile();
    void AvailableBooks();
    void MyBooks(int); ///problem
    void BookOptions(int);
    void NextPage(int);
    void PreviousPage(int);
    void ReadingHistory();
    void SetId(int);
    void SetView(int);
    void SetName(string);
    void SetPassword(string);
    void SetUserName(string);
    void SetEmail(string);
    string GetName();
    int GetView();

};
/////////////////////////////////ReadOnlineClass/////////////////
class ReadOnline{
private:
    Client client;
    Admin admin;
public:
    ReadOnline();
    int AccountView();
    int AccountSign(int);
    void login(int);
    void SignUp(int);
};

#endif //ONLINEREADERBOOK_GLOBAL_H
