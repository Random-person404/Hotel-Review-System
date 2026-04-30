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
void Traveler::addReview(string hotel, int rating, string text) {
    if (reviewCount >= 500) {
        cout << "Review limit reached!\n";
        return;
    }
    // Store the review in the composed array
    travelerReviews[reviewCount].setReviewDetails(hotel, rating, text, userID);
    reviewCount++;
}

//Add points to the traveler's loyalty profile and update membership level if needed.
void Traveler::addPoints(int pts) {
    loyaltyPoints += pts;
    updateMembership(); // Check if membership level needs to be updated after adding points
}

int Traveler::calculatePoints(const string& reviewText) const {
    int words = 0;
    bool inWord = false;
    for (size_t i = 0; i < reviewText.length(); i++) {
        if (reviewText[i] == ' ' || reviewText[i] == '\t') 
            inWord = false;
        else if (!inWord) { 
            inWord = true; 
            words++; 
        }
    }
    return (words > 50) ? 110 : 100;  // 100 base + 10 bonus if over 50 words
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

// Returns a specific review by index, allowing external code to access individual reviews for further processing or display.
Review Traveler::getReview(int index) const {
    return travelerReviews[index];
}