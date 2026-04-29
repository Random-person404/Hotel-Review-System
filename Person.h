//specification file for the Person class
#ifndef PERSON_H
#define PERSON_H

//Person class declaration

class Person 
{
    protected: 
        string userID;
        string userName;
        string country;
        string state;
        string email;

    public: 
        Person();  //default constructor
        Person(string id, string name, string country, string state, string email); //overloading constructor
        //destructor
        ~Person(){}
        

    // Setters
    void setUserID(string id);
    void setUserName(string name);
    void setCountry(string c);
    void setState(string s);
    void setEmail(string e);
    
    //Getters
    string getUserID() const;
    string getUserName() const;
    string getCountry() const;
    string getState() const;
    string getEmail() const;

    //display function
    void displayBasicInfo() const;
};

#endif