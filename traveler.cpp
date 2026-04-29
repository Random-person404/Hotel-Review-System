#include "Traveler.h"
#include "Review.h"
#include <iostream>
#include <string>

using namespace std;
const int MAX_REVIEWS = 500;

// Default Constructor
Traveler::Traveler() {
    membershipLevel="";
    loyaltyPoints = 0;
    reviewCount = 0;
}

// Parameterized Constructor
Traveler::Traveler(string id,string name, string city, string st, string mail, string level, int pts) 
: Person(id, name, city, st, mail) {
    membershipLevel=level;
    loyaltyPoints = pts;
    reviewCount = 0;
}

// Getters
int Traveler::getReviewCount() const { return reviewCount; }
string Traveler::getMembershipLevel() const { return membershipLevel; }
int Traveler::getLoyaltyPoints() const { return loyaltyPoints; }

// Setter
void Traveler::setMemberDetails(string level, int pts, int rc) {
    membershipLevel = level;
    loyaltyPoints = pts;
    reviewCount = rc;
}

//Logic Location: Processing logic inside member functions.
//Adds a new review to the internal fixed-size array.
//Returns true if successful, false if the array is full.
void Traveler::addReview() {
    if (reviewCount >= MAX_REVIEWS) {
        cout << "Maximum review limit reached!\n"; // Maximum review limit reached
        return;
    }

    int newRating; // Initialize the new rating to 0
    string newHotelName; // Initialize the new hotel name to 0
    string newReviewText; // Initialize the new review text to an empty string

    cout << "\n========================================\n";
    cout << "ADD NEW REVIEW\n";
    cout << "========================================\n";

    cout << "Enter Rating (1-5): "; // Prompt the user to enter a rating
    cin >> newRating; 

    // Get Review Text
    cout << "Enter Review Text: ";
    cin.ignore(1000, '\n'); 
    getline(cin, newReviewText);

    // Get Hotel Name
    cout << "Enter Hotel Name: ";
    getline(cin, newHotelName);

    travelerReviews[reviewCount].setReviewDetails(newHotelName, newRating, newReviewText, userID);
    reviewCount++;

    cout << "\nReview added successfully!\n";
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
    Person::displayBasicInfo();
    cout << "Total Reviews: " << reviewCount << endl;
    cout << "Membership: " << membershipLevel << endl;
    cout << "Loyalty point: " << loyaltyPoints << endl;
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