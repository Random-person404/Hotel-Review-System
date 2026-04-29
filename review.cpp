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


// Calculate number of words added in review
int countWords(const string& text) {
    int wordCount = 0; // Initialize the word count to 0
    bool inWord = false;
    for (size_t i = 0; i < text.length(); i++) {
        if (text[i] == ' ' || text[i] == '\t') {
            inWord = false; // Set the in word flag to false
        } else if (!inWord) {
            inWord = true; // Set the in word flag to true
            wordCount++;
        }
    }
    return wordCount;
}

// Calculate calculate for a review
int calculateReviewPoints(const string& reviewText) {
    int points = BASE_POINTS; // Initialize the points to the base points
    int wordCount = countWords(reviewText); // Count the words in the review text
    if (wordCount > BONUS_WORD_THRESHOLD) {
        points += BONUS_POINTS; // Add the bonus points to the points
    }
    return points;
}

// Displays a formatted summary of the review
void Review::displayReview() const {
    cout << "----------------------------------------" << endl;
    cout << "Hotel:  " << hotelName << endl;
    cout << "Rating: " << rating << "/5" << endl;
    cout << "Review: " << reviewText << endl;
    cout << "User:   " << reviewerID << endl;
}