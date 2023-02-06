#include <iostream>
#include "fstream"
#include <bits/stdc++.h>
#include "global.h"
using namespace std;



int main() {
    ReadOnline run;
    return 0;
}



/*
 * 1- to get current date :            time_t now= time(0);
                                       char* date= ctime(&now);
   2-
 */






/*
 * Client::Client(){
    string Username,Password;
    cin>>Username>>Password;
    vector<string> InfoLines,temp;
    InfoLines = ReadFile("accounts.txt");

    for(const auto& InfoLine:InfoLines){
        temp = split(InfoLine);
        if(temp.at(2)==Username && temp.at(1)==Password){
            this->id= ToInt(temp.at(0));
            this->view= ToInt(temp.at(1));
            this->name=temp.at(2);
            this->password=temp.at(3);
            this->UserName=temp.at(4);
            this->email=temp.at(5);
            break;
        }
        else
            temp.clear();
    }
    string postfix="AdminView";  //1 for client ,, 2 for Admin
    if(this->view==1)
        postfix="ClientView";
    cout<<"Hello "<< this->name<<" | "<<postfix;
    ClientMenu();
}
 */