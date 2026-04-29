#ifndef TRAVELER_H
#define TRAVELER_H

#include <iostream>
#include <string>
#include "Review.h"
#include "Person.h"

using namespace std;

// Constants for fixed-size arrays as per rubric constraints
const int MAX_REVIEWS_PER_USER = 50;

//Class: Traveler
//Role: Represents a general user/traveler in the system.
//Mandatory OOP Specification: Composition (Has-A relationship with Review).

class Traveler:public Person{
protected:
    // Basic traveler information
    string userID;
    string userName;
    string country;
    string state;
    string email;

    // Composition: An array of Review objects owned by this Traveler
    Review travelerReviews[MAX_REVIEWS_PER_USER];
    int reviewCount;

public:
    // Default Constructor
    Traveler();
    // Destructor
    ~Traveler(){}

    // Parameterized Constructor
    Traveler(string id, string name, string cty, string st, string mail);

    // Getters
    string getUserID() const;
    string getUserName() const;
    string getCountry() const;
    string getState() const;
    string getEmail() const;
    int getReviewCount() const;

    // Setters
    void setTravelerInfo(string id, string name, string cty, string st, string mail);

    //Logic Location: Processing logic inside member functions.
    //Adds a review to the traveler's history.
    bool addReview(string hotel, int rate, string text);

    // Displays the traveler's basic profile
    void displayProfile() const;

    // Displays all reviews authored by this traveler
    void displayAllReviews() const;
};

#endif