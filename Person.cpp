//Implementation file for the Person class
 #include "Person.h"
 #include <iostream>
 include namespace std;

 //==========Contructors===========
 //Default constructor
 Person::Person(){
    userID="";
    userName="";
    country="";
    state="";
    email="";
 }

 //Overloading constructor
 Person::Person(string id, string name, string c, string s, string e){
    userID=id;
    userName=name;
    country=c;
    state=s;
    email=e;
 }

//============Setters===============
//setUserID assigns a value to userID
void Person::setUserID(string id){
    userID=id;
}

//setUserName assigns a value to userName
void Person::setUserName(string name){
    userName=name;
}

//setCountry assigns a value to country
void Person::setCountry(string c){
    country=c;
}

//setCountry assigns a value to country
void Person::setState(string s){
    state=s;
}

//setCountry assigns a value to country
void Person::setEmail(string e){
    email=e;
}

//============Getters===========
//getUserID returns the value in the userID
string Person::getUserID() const{
    return userID;
}

//getUserName returns the value in the userName
string Person::getUserName() const{
    return userName;
}

//getCountry returns the value in the country
string Person::getCountry() const{
    return country;
}

//getState returns the value in the state
string Person::getState() const{
    return state;
}

//getEmail returns the value in the email
string Person::getEmail() const{
    return email;
}

//=========display function===========
void displayBasicInfo() const{
        cout << "\n========================================\n";
        cout << "USER INFORMATION\n"; // Display the user information
        cout << "========================================\n";
        cout << "User ID: " << userID << endl; // Display the user ID
        cout << "Name: " << userName << endl; // Display the name
        cout << "Country: " << country << endl; // Display the country
        cout << "State: " << state << endl; // Display the state
        cout << "Email: " << email << endl; // Display the email
}