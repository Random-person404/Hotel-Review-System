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

	//overloading constructor
    Traveler(string id, string name, string cty, string st, string mail, string level, int pts);
    
    //detructor
    ~Traveler(){}

    // Getters 
    string getMembershipLevel() const;
    int getLoyaltyPoints() const;
    int getReviewCount() const;

    // Setters
    void setMemberDetails(string level, int pts, int rc);

    //Add Reviews
    void addReview(string hotel, int rating, string text);

    //Updates membership level automatically based on point thresholds.
    void updateMembership();

    //Logic Location: Adds points and updates membership.
    void addPoints(int pts);

    //Calculate points for a review based on its content (e.g., length, rating).
    int calculatePoints(const string& reviewText) const;

    //Overriding displayProfile to show the specialized data 
    //alongside inherited attributes.
    void displayProfile() const;

    //Display all reviews written by the traveler.
    void displayAllReviews() const;

    // display a specific review by index
    Review getReview(int index) const;
    
    friend void generateAnalyticsReport(Traveler travelers[], int travelerCount);
};

#endif
