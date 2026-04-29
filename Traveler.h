#ifndef MEMBER_TRAVELER_H
#define MEMBER_TRAVELER_H

#include "Traveler.h"
#include <string>
#include "Review.h"

using namespace std;

// Constants for fixed-size arrays as per rubric constraints
const int MAX_REVIEWS_PER_USER = 50;

//Class: Traveler
//Role: Represents a general user/traveler in the system.
//Mandatory OOP Specification: Composition (Has-A relationship with Review).

class Traveler {
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
    // Note: Passes common attributes up to the Traveler base constructor
    MemberTraveler(string id, string name, string cty, string st, string mail, string level, int pts);

    // Getters for specialized data
    string getMembershipLevel() const;
    int getLoyaltyPoints() const;

    // Setters for specialized data
    void setMemberDetails(string level, int pts);

    /**
     * Logic Location: Processing logic inside member functions.
     * Updates membership level automatically based on point thresholds.
     */
    void updateMembership();

    /**
     * Logic Location: Adds points and updates membership.
     */
    void earnPoints(int pts);

    /**
     * Overriding displayProfile to show the specialized data 
     * alongside inherited attributes.
     */
    void displayProfile() const;

    /**
     * Mandatory OOP Specification: Friend Function
     * Allows an external report utility to access private members 
     * like loyaltyPoints without breaking encapsulation.
     */
    friend void generateReportSummary();
};

#endif