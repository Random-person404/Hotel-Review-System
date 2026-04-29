#ifndef MEMBER_TRAVELER_H
#define MEMBER_TRAVELER_H

#include "Traveler.h"
#include <string>

using namespace std;

/**
 * Class: MemberTraveler
 * Role: Represents a registered user with a loyalty profile.
 * Mandatory OOP Specification: Inheritance (Parent: Traveler, Child: MemberTraveler).
 * Demonstrates: Adding specialized data (membershipLevel and loyaltyPoints).
 */
class MemberTraveler : public Traveler {
private:
    // Specialized Data (New attributes not found in the base class)
    string membershipLevel;
    int loyaltyPoints;

public:
    // Default Constructor
    MemberTraveler();

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