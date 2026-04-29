#include "Review.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Default Constructor
// Required for initializing fixed-size arrays within the User class
Review::Review() {
    hotelName = "";
    rating = 0;
    reviewText = "";
    reviewerID = "";
}

// Parameterized Constructor
Review::Review(string hName, int r, string text, string rID) {
    hotelName = hName;
    rating = r;
    reviewText = text;
    reviewerID = rID;
}

// Getters
string Review::getHotelName() const { return hotelName; }
int Review::getRating() const { return rating; }
string Review::getReviewText() const { return reviewText; }
string Review::getReviewerID() const { return reviewerID; }

// Setters
void Review::setReviewDetails(string hName, int r, string text, string rID) {
    hotelName = hName;
    rating = r;
    reviewText = text;
    reviewerID = rID;
}

//Operator Overloading: >
//Compares two Review objects based on their numerical rating.
bool Review::operator>(const Review& other) const {
    return this->rating > other.rating;
}

//Operator Overloading: <
//Compares two Review objects based on their numerical rating.
bool Review::operator<(const Review& other) const {
    return this->rating < other.rating;
}

// Displays a formatted summary of the review
void Review::displayReview() const {
    cout << "----------------------------------------" << endl;
    cout << "Hotel:  " << hotelName << endl;
    cout << "Rating: " << rating << "/5" << endl;
    cout << "Review: " << reviewText << endl;
    cout << "User:   " << reviewerID << endl;
}