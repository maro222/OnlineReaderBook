#include <iostream>
#include <bits/stdc++.h>
#include <ctime>
#include "global.h"
using namespace std;

///////////////////////////Helper Methods////////////////////////
//help in opening file,read it and return vector<string> of all lines in this file
vector<string> ReadFile(string path){
    string line;
    vector<string> lines;
    fstream fileHandler;
    fileHandler.open(path.c_str(),ios::in);

    if(fileHandler.fail()){
        cout<<"Sorry this file cannot be open\n";
        return lines;
    }

    while(getline(fileHandler,line)){
        if(line=="") continue;
        lines.emplace_back(line);
    }
    return lines;
}

//help in printing a certain line in certain file
void WriteFileLines(string path, vector<string> lines, bool append = true) {
    auto status = ios::in | ios::out | ios::app;

    if (!append)
        status = ios::in | ios::out | ios::trunc;	// overwrite

    fstream file_handler(path.c_str(), status);

    if (file_handler.fail()) {
        cout << "\n\nERROR: Can't open the file\n\n";
        return;
    }
    for (auto line : lines)
        file_handler << line << "\n";

    file_handler.close();
}

//help in splitting a line containing info of user or Admin with ',' between info and returning a vector<string> of this info
vector<string> split(string line){
    vector<string> lines;
    string temp="";
    for(int i=0;i<line.size();i++){
        if(line[i] !=',')
            temp+=line[i];
        else{
            lines.emplace_back(temp);
            temp="";
        }
    }
    lines.emplace_back(temp);
    return lines;
}

// help in casting info( id or view )form string to integer
int ToInt(string str) {
    istringstream iss(str);
    int num;
    iss >> num;

    return num;
}

//help in generating an id for user or Admin
int MaxId(int view){
    int id,max=0;
    vector<string> lines= ReadFile("accounts.txt");
    for(auto & line : lines){
        id= ToInt(line);
        vector<string> words= split(line);
        if(max<id && words.at(1) == to_string(view))
            max=id;
    }
    max++;
    return max;
    //string line= to_string(max);    //max + "0"
}

//help in generating an id for books
int BookId(){
    int id,max=0;
    vector<string> lines= ReadFile("Books.txt");
    for(auto & line : lines){
        id= ToInt(line);
        vector<string> words= split(line);
        if(max<id)
            max=id;
    }
    max++;
    return max;
}

//help in making a string from vector seperated by commas
string CommaLine(vector<string> line){
    string comma="";
    for(int i=0;i<(int)line.size();i++){
        comma+=line.at(i);
        if(i!=(int)line.size()-1)
            comma+=',';
    }
    return comma;
}

///////////////////////////Client Classes//////////////////////
//help in showing main_menu of client and sent choice of client to options()
void Client::ClientMenu() {
    bool flag=true;
    while(flag){
        int choice;
        vector<string> menu;
        cout<<"Hello "<< GetName()<<" | UserView\n";
        menu.emplace_back("menu:\n");
        menu.emplace_back("\t\t1- View profile:\n");
        menu.emplace_back("\t\t2- List and Select from My Reading History:\n");
        menu.emplace_back("\t\t3- List and Select from My Available Books:\n");
        menu.emplace_back("\t\t4- Logout:\n");

        for(const auto& line:menu)
            cout<<line;
        cout<<"Enter your choice please: ";
        cin>>choice;
        flag=options(choice);
    }
}

//help in running the choice that have been sent from menu and going to its function
bool Client::options(int choice) {
    switch (choice) {
        case 1:profile();
            return true;
        case 2:ReadingHistory();
            return true;
        case 3:AvailableBooks();
            return true;
        case 4:return false;
        default:cout<<"Invalid Option"; return true;
    }
}

//help in showing profile of client (choice 1 of options)
void Client::profile() {
    cout<<"name: "<< this->name<< "\n";
    cout<<"Email: "<< this->email<< "\n";
    cout<<"UserName: "<< this->UserName<< "\n";
}

//help in reading books file and showing all books(lines) in books file and sent choice of client to BookOptions()
void Client::AvailableBooks() {
    map<int,string > id_book;
    vector<string> books;
    books = ReadFile("books.txt");
    cout<<"Menu\n";
    for(const auto& book : books){
        vector<string> temp;
        temp=split(book);
        cout<<temp.at(0)<<" "<<temp.at(2)<<"\n";
        id_book[ToInt(temp.at(0))]=temp.at(2);
    }
    cout<<"Which Book Do You Want to Read?\nEnter your choice:";
    int choice;
    cin>>choice;
    for(pair<int,string> item: id_book){
        if(item.first==choice)
            MyBooks(choice);
    }
}

//help in reading the book that I choose and get its info from clientBook_map
void Client::MyBooks(int choice){
    int IdClient,IdBook;
    vector<string> lines= ReadFile("client_book.txt");
        for(const auto& line : lines ) {
            vector<string> temp = split(line);
            IdBook = ToInt(temp.at(1));
            IdClient = ToInt(temp.at(0));
            if (IdBook == choice && IdClient == this->id) {    // if it has been chosen once before
                cout << "Current Page: " << temp.at(2) << temp.at(3) << temp.at(4) << "\n";
                int i=  ToInt(temp.at(2));
                cout << "content: " << temp.at(4+i )<<"\n";  //5-->start of content + 2--> current page
                BookOptions(choice);
                return;
            }
        }
    // else it is first time to read ths book(so we have to append it and set time)
        vector <string> line,books= ReadFile("Books.txt");
        for(const auto& book:books) {
            vector<string> temp = split(book);
            if (ToInt(temp.at(0)) == choice) {
                line.emplace_back(to_string(this->id));
                line.emplace_back(temp.at(0));
                line.emplace_back(to_string(1));
                line.emplace_back("/");
                line.emplace_back(temp.at(4));
                for (int i = 5; i < temp.size(); i++)
                    line.emplace_back(temp.at(i));
                time_t now = time(0);
                char *date = ctime(&now);
                line.emplace_back(date);
                break;
            }
        }
        string str= CommaLine(line);
        line.clear();
        line.emplace_back(str);
        WriteFileLines("client_book.txt",line);
        MyBooks(choice);
}

//help in choosing one option from BookOptions
void Client::BookOptions(int IdBook) {
    int choice;
    cout<<"Menu\n\t\t1: NextPage\n\t\t2: PreviousPage\n\t\t3: StopReading";
    cout<<"Enter your move please: ";
    cin>>choice;
    switch(choice){
        case 1:NextPage(IdBook);break;
        case 2:PreviousPage(IdBook);break;
        case 3:return;
        default : cout<<"Invalid choice,try again\n"; BookOptions(IdBook);
    }
}

//help in showing the next page of chosen book
void Client::NextPage(int IdBook) {
    int choice;
    vector<string>temp,NewBooks ,OldBooks= ReadFile("client_book.txt");
    for(const auto& book:OldBooks){
        temp= split(book);
        if(this->id== ToInt(temp.at(0)) && IdBook== ToInt(temp.at(1))){
            temp.at(2)= to_string(ToInt(temp.at(2))+1);
            NewBooks.emplace_back(CommaLine(temp));
            choice= ToInt(temp.at(1));
        }
        else
        NewBooks.emplace_back(CommaLine(temp));
    }
    WriteFileLines("client_book.txt",NewBooks,false);
    MyBooks(choice);
}

//help in showing the previous page of chosen book
void Client::PreviousPage(int IdBook) {
    int choice;
    vector<string>temp,NewBooks ,OldBooks= ReadFile("client_book.txt");
    for(const auto& book:OldBooks){
        temp= split(book);
        if(this->id== ToInt(temp.at(0)) && IdBook== ToInt(temp.at(1))){
            temp.at(2)= to_string(ToInt(temp.at(2))-1);
            NewBooks.emplace_back(CommaLine(temp));
            choice= ToInt(temp.at(1));
        }
        else
        NewBooks.emplace_back(CommaLine(temp));
    }
    WriteFileLines("client_book.txt",NewBooks,false);
    MyBooks(choice);
}

//help in showing all the books that user has been read
void Client::ReadingHistory() {
    int cnt=1;
    vector<string> books= ReadFile("Books.txt"),clientBook= ReadFile("client_book.txt");
    for(const auto& cb:clientBook){
        vector<string> tempClientBook= split(cb);
        if(tempClientBook.at(0)==to_string(this->id)){
            for(const auto& book:books){
                vector<string> tempBook= split(book);
                if(tempBook.at(0)== tempClientBook.at(1)){
                    cout<<cnt++<<":"<<tempBook.at(2)<<"--"<<tempClientBook.at(tempClientBook.size()-1)<<"\n";
                }
            }
        }
    }
}

//Mutators(setters)
void Client::SetId(int id) {
    this->id=id;
}
void Client::SetView(int view) {
    this->view=view;
}
void Client::SetUserName(string UserName) {
    this->UserName=UserName;
}
void Client::SetName(string name) {
    this->name=name;
}
void Client::SetPassword(string password) {
    this->password=password;
}
void Client::SetEmail(string email) {
    this->email=email;
}

//Accessors(getters)
string Client::GetName() {
    return this->name;
}
int Admin::GetView() {
    return this->view;
}

///////////////////////////Admin Classes//////////////////////

void Admin::AdminMenu() {
    bool flag=true;
    while(flag){
        int choice;
        vector<string> menu;
        cout<<"Hello "<< GetName() <<" | AdminView\n";
        menu.emplace_back("menu:\n");
        menu.emplace_back("\t\t1- View profile\n");
        menu.emplace_back("\t\t2- Add Books\n");
        menu.emplace_back("\t\t3- Logout\n");
        for(const auto& line:menu)
            cout<<line;
        cout<<"Enter your choice ,please: ";
        cin>>choice;
        flag=options(choice);
    }
}

bool Admin::options(int choice) {
    switch (choice) {
        case 1: profile();  return true;
        case 2: AddBooks(); return true;
        case 3: return false;
    }
}

void Admin::profile() {
    cout<<"name: "<< this->name<<"\n";
    cout<<"Email: "<< this->email<<"\n";
    cout<<"UserName: "<< this->UserName<<"\n";
}

void Admin::AddBooks() {
    vector<string> line;
    string ISBN,title,AuthorName,content,temp;
    int pages;
    line.emplace_back(to_string(BookId()));
    cout<<"Enter ISBN: ";                                               cin>>ISBN;                  line.emplace_back(ISBN);
    cout<<"Enter title: ";                cin.ignore();        getline(cin,title);           line.emplace_back(title);
    cout<<"Enter Author name: ";          cin.ignore();        getline(cin,AuthorName);      line.emplace_back(AuthorName);
    cout<<"enter numbers of pages: ";                                   cin>>pages;                 line.emplace_back(to_string(pages));
    for(int i=0;i<pages;i++){
        cout<<"Enter content of page: ";
        cin>>content;
        line.emplace_back(content);
    }
    temp= CommaLine(line);
    line.clear();
    line.emplace_back(temp);
    WriteFileLines("Books.txt",line);
}

//Mutators(setters)
void Admin::SetEmail(string email) {
    this->email=email;
}
void Admin::SetName(string name) {
    this->name=name;
}
void Admin::SetPassword(string password) {
    this->password=password;
}
void Admin::SetUserName(string UserName) {
    this->UserName=UserName;
}
void Admin::SetView(int) {
    this->view=view;
}
void Admin::SetId(int) {
    this->id=id;
}

//Accessors(getters)
string Admin::GetName() {
    return this->name;
}
int Client::GetView() {
    return this->view;
}


///////////////////////////ReadOnline Classes//////////////////////
//help in running the program and call AccountView()
ReadOnline::ReadOnline() {
    AccountView();
}

//help in showing_menu of application and choose between Admin and client and sent view to
int ReadOnline::AccountView() {
    int view;
    cout<<"Menu:\n"<<"\t1- Admin\n"<<"\t2- Client\n";
    cout<<"Enter your choice please: ";
    cin >> view;
    AccountSign(view);
}

//help in showing_menu between login and SignUp and choose one of them
int ReadOnline::AccountSign(int view) {
    int choice;
    cout<<"Menu:\n"<<"\t1- Login\n"<<"\t2- SignUp\n";
    cout<<"Enter your choice please: ";
    cin >> choice;
    if(choice==1)
        login(view);
    else SignUp(view);
}

//help in taking inputs(info) from user and assigning it in data members (Admin or Client) and put it in string and append it in account.txt file
void ReadOnline::SignUp(int view) {
    vector<string>lines;
    string line="";
    string name,password,username,email;
    if(view==1){            //Admin-SignUp(view==1) So, We assign info(inputs) in admin data member
        admin.SetId(MaxId(view));                                         line+= to_string(MaxId(view)) + ",";   //to string cast int to string
        admin.SetView(view);                                              line+= to_string(view) + ",";       //to string cast int to string
        cout<<"Enter UserName(no_spaces):";     cin>>username;            line+= username + ",";
        cout<<"Enter Password(no_spaces):";     cin>>password;            line+= password + ",";
        cout<<"Enter name (no_spaces) :";       cin>>name;                line+= name + ",";
        cout<<"Enter email(no_spaces) :";       cin>>email;               line+= email + ",";
        admin.SetUserName(username);
        admin.SetPassword(password);
        admin.SetName(name);
        admin.SetEmail(email);
        lines.emplace_back(line);
        WriteFileLines("accounts.txt",lines);
        admin.AdminMenu();
    }
    else{                   //Admin-SignUp(view==2) So, We assign info(inputs) in client data member
        client.SetId(MaxId(view));                                        line+= to_string(MaxId(view)) + ",";
        client.SetView(view);                                             line+= to_string(view) + ",";
        cout<<"Enter UserName(no_spaces):";     cin>>username;            line+= username + ",";
        cout<<"Enter Password(no_spaces):";     cin>>password;            line+= password + ",";
        cout<<"Enter name (no_spaces) :";       cin>>name;                line+= name + ",";
        cout<<"Enter email(no_spaces) :";       cin>>email;               line+= email + ",";
        client.SetUserName(username);
        client.SetPassword(password);
        client.SetName(name);
        client.SetEmail(email);
        lines.emplace_back(line);
        WriteFileLines("accounts.txt",lines);
        client.ClientMenu();
    }
}

//help in comparing inputs(info) with info of each line in account.txt file and assigning the convenient ones in dataMembers(Client or Admin)
void ReadOnline::login(int view) {
    string Username,Password;
    cout<<"Enter UserName and Password respectively: ";
    cin>>Username>>Password;
    vector<string> InfoLines,temp;
    InfoLines = ReadFile("accounts.txt");

    if(view==1){
        for(const auto& InfoLine:InfoLines){
            temp = split(InfoLine);
            if(temp.at(2)==Username && temp.at(3)==Password && ToInt(temp.at(1))==admin.GetView()){
                this->admin.SetId(ToInt(temp.at(0))) ;
                this->admin.SetView(ToInt(temp.at(1)));
                this->admin.SetName(temp.at(2));
                this->admin.SetPassword(temp.at(3));
                this->admin.SetUserName(temp.at(4));
                this->admin.SetEmail(temp.at(5));
                break;
            }
            else
                temp.clear();
        }
        if(temp.empty())
            cout<<"Invalid Register";
        else
            admin.AdminMenu();
    }
    else if(view==2){
        for(const auto& InfoLine:InfoLines){
            temp = split(InfoLine);
            if(temp.at(2)==Username && temp.at(3)==Password  && ToInt(temp.at(1))==client.GetView()){
                this->client.SetId(ToInt(temp.at(0))) ;
                this->client.SetView(ToInt(temp.at(1)));
                this->client.SetName(temp.at(2));
                this->client.SetPassword(temp.at(3));
                this->client.SetUserName(temp.at(4));
                this->client.SetEmail(temp.at(5));
                break;
            }
            else
                temp.clear();
        }
        if(temp.empty())
            cout<<"Invalid Register";
        else
            client.ClientMenu();
    }
    else cout<<"Invalid register";
}

