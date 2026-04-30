#ifndef TRAVELER_H
#define TRAVELER_H

#include "Review.h"
#include "Person.h"
#include <string>

using namespace std;

class Traveler : public Person {
private:
    // Specialized Data (New attributes not found in the base class)
    string membershipLevel;
    int loyaltyPoints;
    int reviewCount;
    Review travelerReviews[500]; 

public:
    // Default Constructor
    Traveler();

    // Parameterized Constructor
    // Note: Passes common attributes up to the Traveler base constructor
    Traveler(string id, string name, string cty, string st, string mail, string level, int pts);

    // Getters for specialized data
    string getMembershipLevel() const;
    int getLoyaltyPoints() const;
    int getReviewCount() const;

    // Setters for specialized data
    void setMemberDetails(string level, int pts, int rc);

    //Add Reviews
    void addReview();

    //Logic Location: Processing logic inside member functions.
    //Updates membership level automatically based on point thresholds.
    void updateMembership();

    //Logic Location: Adds points and updates membership.
    void addPoints(int pts);

    //Overriding displayProfile to show the specialized data 
    //alongside inherited attributes.
    void displayProfile() const;

    //Display all reviews written by the traveler.
    void displayAllReviews() const;

    // display a specific review by index
    Review getReview(int index) const;
    
    friend void generateReportSummary(Traveler travelers[], int travelerCount);
};

#endif