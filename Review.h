#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>
#include <string>

using namespace std;

//Class: Review
//Role: Represents a single traveler's experience at a hotel.
//This class is designed to be composed within the User class (Composition).

class Review {
private:
    string hotelName;
    int rating;
    string reviewText;
    string reviewerID;

public:
    // Default Constructor - Required for fixed-size arrays
    Review();
    ~Review(){}

    // Parameterized Constructor
    Review(string hName, int r, string text, string rID);

    // Getters
    string getHotelName() const;
    int getRating() const;
    string getReviewText() const;
    string getReviewerID() const;

    // Setters
    void setReviewDetails(string hName, int r, string text, string rID);

//Mandatory OOP Specification: Operator Overloading
//Overloads the '>' operator to compare the quality (rating) of two review objects.
    bool operator>(const Review& other) const;

//Overloads the '<' operator for additional comparison logic.
    bool operator<(const Review& other) const;

// Display function to summarize the review data
    void displayReview() const;

//Mandatory OOP Specification: Friend Function
//Allows the external report generator to access private members of Review.
    friend void generateAnalyticsReport(); 
};

#endif