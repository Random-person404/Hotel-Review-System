#include "Traveler.h"
#include <iostream>

using namespace std;

// Default Constructor
Traveler::Traveler() {
    userID = "";
    userName = "";
    country = "";
    state = "";
    email = "";
    reviewCount = 0;
}

// Parameterized Constructor
Traveler::Traveler(string id, string name, string cty, string st, string mail) {
    userID = id;
    userName = name;
    country = cty;
    state = st;
    email = mail;
    reviewCount = 0;
}

// Getters
string Traveler::getUserID() const { return userID; }
string Traveler::getUserName() const { return userName; }
string Traveler::getCountry() const { return country; }
string Traveler::getState() const { return state; }
string Traveler::getEmail() const { return email; }
int Traveler::getReviewCount() const { return reviewCount; }

// Setters
void Traveler::setTravelerInfo(string id, string name, string cty, string st, string mail) {
    userID = id;
    userName = name;
    country = cty;
    state = st;
    email = mail;
}

//Logic Location: Processing logic inside member functions.
//Adds a new review to the internal fixed-size array.
//Returns true if successful, false if the array is full.
bool Traveler::addReview(string hotel, int rate, string text) {
    if (reviewCount < MAX_REVIEWS_PER_USER) {
        // Use the setter from the Review class to populate the object in the array
        travelerReviews[reviewCount].setReviewDetails(hotel, rate, text, userID);
        reviewCount++;
        return true;
    } else {
        cout << "Error: Review limit reached for user " << userID << endl;
        return false;
    }
}

//Add points to the traveler's loyalty profile and update membership level if needed.
void Traveler::addPoints(int pts) {
    loyaltyPoints += pts;
    updateMembership(); // Check if membership level needs to be updated after adding points
}

//Updates the membership level based on the current loyalty points.
void Traveler::updateMembership() { 
    if (loyaltyPoints >= 10000) {
        membershipLevel = "Platinum";
    } else if (loyaltyPoints >= 5000) {
        membershipLevel = "Gold";
    } else if (loyaltyPoints >= 1000) {
        membershipLevel = "Silver";
    } else {
        membershipLevel = "Basic";
    }
}   

// Displays the traveler's basic profile information
void Traveler::displayProfile() const {
    cout << "========================================" << endl;
    cout << "TRAVELER PROFILE: " << userID << endl;
    cout << "========================================" << endl;
    cout << "Name:    " << userName << endl;
    cout << "Country: " << country << endl;
    cout << "State:   " << state << endl;
    cout << "Email:   " << email << endl;
    cout << "Total Reviews: " << reviewCount << endl;
    cout << "----------------------------------------" << endl;
}

// Iterates through the composed array and calls display logic for each review
void Traveler::displayAllReviews() const {
    if (reviewCount == 0) {
        cout << "No reviews authored by this traveler yet." << endl;
        return;
    }

    cout << "REVIEWS AUTHORED BY " << userName << ":" << endl;
    for (int i = 0; i < reviewCount; i++) {
        travelerReviews[i].displayReview();
    }
}