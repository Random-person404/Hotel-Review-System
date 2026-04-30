%%writefile main.cpp
#include <iostream> // Include the iostream library for input and output
#include <fstream> // Include the fstream library for file input and output
#include <iomanip> // Include the iomanip library for input and output manipulation
#include <string> // Include the string library for string operations
#include <cstdlib> // Include the cstdlib library for general purpose functions
#include "Person.h"
#include "Traveler.h"
#include "Review.h"

using namespace std;

// Constants
const int MAX_USERS = 100;  // Maximum number of users
const int MAX_REVIEWS = 500;  // Maximum number of reviews
const int MAX_STRING_LENGTH = 200;  // Maximum length of a string
const int BASE_POINTS = 100;  // Base points for each review
const int BONUS_POINTS = 10;  // Bonus points for each review
const int BONUS_WORD_THRESHOLD = 50;  // Threshold for bonus points

//===============================Function prototypes=====================
void loadTraveler(const string& filename, string userID[], string userName[],  // Load users from a file
               string country[], string state[], string email[],
               string membership[], int points[], int& userCount);
void loadReviews(const string& filename, string userID[], int rating[],  // Load reviews from a file
                 string reviewText[], string hotelName[], int& reviewCount);
void displayMenu(); // Display the menu
int getChoice(); // Get the choice from the user
void generateReportSummary(Traveler travelers[], int travelerCount);
void displayUsersByCategory(string userID[], string userName[],  // Display users by category
                            string membership[], int points[], int userCount);
void displayTopReviewerLeaderboard(string userID[], string userName[],  // Display top reviewer leaderboard
                                    string reviewUserID[], int reviewCount,
                                    int userCount);
void displayTop3Users(string userID[], string userName[],  // Display top 3 users
                      string reviewUserID[], int reviewCount,
                      int userCount);
void displayHotelRatingSummary(string hotelName[], int rating[],  // Display hotel rating summary
                                int reviewCount);
int countWords(const string& text); // Count the words in a string
void displayAllHotels(string hotelName[], int reviewCount); // Display all hotels
void displayAllUsers(string userID[], string userName[], int userCount); // Display all users
void saveUsers(const string& filename, string userID[], string userName[],  // Save the users to a file
               string country[], string state[], string email[],
               string membership[], int points[], int userCount); // Save the users to a file
void saveReviews(const string& filename, string userID[], int rating[], // Save the reviews to a file
                 string reviewText[], string hotelName[], int reviewCount);
void sortUsersByPoints(string userID[], string userName[], string country[], // Sort the users by points
                       string state[], string email[], string membership[],
                       int points[], int userCount);
void sortHotelsByReviewCount(string hotelName[], int rating[], // Sort the hotels by review count
                              string reviewText[], string reviewUserID[],
                              int reviewCount);
void searchReviewsByKeyword(string reviewText[], string hotelName[], // Search reviews by keyword
                            string reviewUserID[], int rating[],
                            string userID[], string userName[],
                            int reviewCount, int userCount, string keyword);

//-----------validation----------------------------
bool validateUserID(const string& userID, string userIDList[], int userCount); // Validate the user ID
bool validateRating(int rating); // Validate the rating
//---------------------------------------------------

//------------for better readability-------------------
string toUpper(const string& str); // Convert a string to uppercase
bool caseInsensitiveCompare(const string& str1, const string& str2); // Compare two strings case insensitively
string findUserIDCaseInsensitive(const string& input, string userIDList[], int userCount); // Find a user ID case insensitively
//-----------------------------------------------------
//===================================================================

//=================Main function=================
int main() { 
    // Parallel arrays for travelers
    Traveler travelers[MAX_USERS];
    // Parallel arrays for reviews
    Review reviews[MAX_REVIEWS];
    int travelerCount = 0; 

    // Load data from files (open once for reading)
    travelerCount = loadUsers("users.txt", travelers); // Load users from the users.txt file
    loadReviews("reviews.txt", travelers, travelerCount); // Load reviews from the reviews.txt file

    int choice; // Choice from the user
    bool dataModified = false; // Flag to check if data has been modified

    do {
        displayMenu();
        choice = getChoice(); // Get the choice from the user

        switch(choice) {
            case 1: {   // Display reviews by user
            string targetUserID;
            cout << "\nEnter User ID: ";
            cin >> targetUserID;
            cin.ignore(1000, '\n');

            bool found = false;
            for (int i = 0; i < travelerCount; i++) {
                if (travelers[i].getUserID() == targetUserID) {
                    travelers[i].displayAllReviews();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid User ID! Please Enter a Valid User ID.\n";
            }
            break;
        }
            case 2: {   // Display reviews by hotel
    string targetHotel;
    cout << "\nEnter Hotel Name: ";
    getline(cin, targetHotel);

    bool found = false;
    cout << "\n========================================\n";
    cout << "REVIEWS FOR HOTEL: " << targetHotel << "\n";
    cout << "========================================\n";

    for (int i = 0; i < travelerCount; i++) {
        for (int j = 0; j < travelers[i].getReviewCount(); j++) {
            Review r = travelers[i].getReview(j);
            if (caseInsensitiveCompare(r.getHotelName(), targetHotel)) {
                found = true;
                cout << "\nUser: " << travelers[i].getUserName() << endl;
                cout << "Rating: " << r.getRating() << "/5" << endl;
                cout << "Review: " << r.getReviewText() << endl;
                cout << "----------------------------------------\n";
            }
        }
    }

    if (!found) {
        cout << "No reviews found for this hotel.\n";
    }
    break;
}
            case 3: {   // Display info by user
            string targetUserID;
            cout << "\nEnter User ID: ";
            cin >> targetUserID;
            cin.ignore(1000, '\n');

            bool found = false;
            for (int i = 0; i < travelerCount; i++) {
                if (travelers[i].getUserID() == targetUserID) {
                    travelers[i].display();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid User ID! Please Enter a Valid User ID.\n";
            }
            break;
        }
            case 4: {   // Display positive reviews by hotel
                string targetHotel;
                cout << "\nEnter Hotel Name: "; // Prompt the user to enter a hotel name
                getline(cin, targetHotel);
                displayPositiveReviewsByHotel(targetHotel, travelers, travelerCount);
                break; // Break out of the switch statement
            }
            case 5:   // Display summary of activities
                generateReportSummary(travelers, travelerCount);
                break;
            case 6:
                displayUsersByCategory(travelers, travelerCount); // Display users grouped by membership category
                break; // Break out of the switch statement
            case 7:
                displayTopReviewerLeaderboard(travelers, travelerCount); // Display top reviewer leaderboard
                break; // Break out of the switch statement
            case 8:
                displayTop3Users(travelers, travelerCount); // Display top 3 users
                break; // Break out of the switch statement
            case 9:
                displayHotelRatingSummary(hotelName, rating, reviewCount); // Display hotel rating summary
                break; // Break out of the switch statement
            case 10: {   // Add new review
                string newUserID, newReviewText;
                addNewReview(reviewUserID, rating, reviewText, hotelName, // Add a new review
                            reviewCount, userID, userCount, newUserID,
                            newReviewText);
                dataModified = true;
                // Update review count for the user
                for (int i = 0; i < userCount; i++) {
                    if (caseInsensitiveCompare(userID[i], newUserID)) {
                        reviewCountsPerUser[i]++; // Increment the review count for the user
                        break; // Break out of the loop
                    }
                }
                // Add points for the newly added review
                addPointsForNewReview(userID, userName, points, membership, // Add points for the newly added review
                                     newUserID, newReviewText, userCount);
                break; // Break out of the switch statement
            }
            case 11:   // Sort users by points
                sortUsersByPoints(userID, userName, country, state, email, // Sort the users by points
                                 membership, points, userCount);
                break; // Break out of the switch statement
            case 12:
                sortHotelsByReviewCount(hotelName, rating, reviewText, // Sort the hotels by review count
                                       reviewUserID, reviewCount);
                break; // Break out of the switch statement
            case 13: {
                string keyword; // Keyword to search for
                cout << "\nEnter keyword to search: ";
                getline(cin, keyword);
                searchReviewsByKeyword(reviewText, hotelName, reviewUserID, // Search reviews by keyword
                                      rating, userID, userName, reviewCount,
                                      userCount, keyword);
                break; // Break out of the switch statement
            }
            case 14:
                cout << "\nExiting program...\n"; // Exit the program
                break; // Break out of the switch statement
            default:
                cout << "\nInvalid choice! Please try again.\n"; // Invalid choice
        }

        if (choice != 14) { //if the choice is not the exit option, wait for the user to press Enter
            cout << "\nPress Enter to continue..."; // Prompt the user to press Enter
            cin.get(); // Wait for Enter key
        }

    } while (choice != 14); //if the choice is the exit option, exit the loop

    // Save data to files (open once for writing)
    saveUsers("users.txt", userID, userName, country, state, email, // Save the users to the users.txt file
              membership, points, userCount);
    if (dataModified) {
        saveReviews("reviews.txt", reviewUserID, rating, reviewText, // Save the reviews to the reviews.txt file
                   hotelName, reviewCount);
    }

    cout << "Data saved successfully!\n"; // Data saved successfully

    return 0; // Return 0 to indicate successful execution
}

int loadUsers(const string& filename, Traveler travelers[]) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Error: Cannot open " << filename << endl;
        return 0;
    }

    int i = 0;
    string id, name, country, state, email, membership;
    int points;

    while (i < MAX_USERS && getline(infile, id, '\t')) {
        getline(infile, name, '\t');
        getline(infile, country, '\t');
        getline(infile, state, '\t');
        getline(infile, email, '\t');
        getline(infile, membership, '\t');
        infile >> points;
        infile.ignore();  // clear the \n after points

        travelers[i] = Traveler(id, name, country, state,
                                email, membership, points);
        travelers[i].updateMembership(); // ensure correct membership on load
        i++;
    }

    infile.close();
    return i; // returns how many travelers were loaded
}

// Reads reviews.txt once — assigns each review to matching Traveler
void loadReviews(const string& filename, Traveler travelers[], int travelerCount) {
    ifstream infile(filename);
    if (!infile) {
        cout << "Error: Cannot open " << filename << endl;
        return;
    }

    string uid, reviewText, hotelName;
    int rating;
    string line;

    while (getline(infile, uid, '\t')) {
        infile >> rating;
        infile.ignore();  // clear \t after rating
        getline(infile, reviewText, '\t');
        getline(infile, hotelName);

        // Find the matching traveler and add review to them
        for (int i = 0; i < travelerCount; i++) {
            if (travelers[i].getUserID() == uid) {
                travelers[i].addReview(hotelName, rating, reviewText);
                break;
            }
        }
    }

    infile.close();
}

void displayMenu() {   // Display the menu
    cout << "\n========================================\n";
    cout << "  HOTEL REVIEW & MEMBERSHIP SYSTEM\n";
    cout << "========================================\n";
    cout << "1.  Display all reviews by a specific user\n";
    cout << "2.  Display all reviews for a specific hotel\n";
    cout << "3.  Display complete user information\n";
    cout << "4.  Display positive reviews (4-5) for a hotel\n";
    cout << "5.  Display summary of activities\n";
    cout << "6.  Display users grouped by membership category\n";
    cout << "7.  Top Reviewer Leaderboard\n";
    cout << "8.  Show Top 3 users with most reviews\n";
    cout << "9.  Hotel Rating Summary\n";
    cout << "10. Add New Review\n";
    cout << "11. Sort Users by Points (Highest to Lowest)\n";
    cout << "12. Sort Hotels by Number of Reviews\n";
    cout << "13. Search Reviews by Keyword\n";
    cout << "14. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice: ";
}

int getChoice() {
    int choice; // Choice from the user
    int attempts = 0; // Number of attempts
    const int MAX_ATTEMPTS = 3; // Maximum number of attempts

    while (attempts < MAX_ATTEMPTS) {
        if (cin >> choice) {
            cin.ignore(1000, '\n'); // Clear the input buffer
            if (choice >= 1 && choice <= 14) {
                return choice; // Return the choice
            } else {
                cout << "Invalid choice! Please enter a number between 1 and 14.\n"; // Invalid choice
                cout << "Enter your choice: "; // Prompt the user to enter a choice
            }
        } else {    //if the input is not a number, clear the error flag and clear the invalid input
            cin.clear(); // Clear error flag
            cin.ignore(1000, '\n'); // Clear invalid input
            cout << "Invalid input! Please enter a number.\n"; // Invalid input
            cout << "Enter your choice: "; // Prompt the user to enter a choice
        }
        attempts++;
    }

    // If max attempts reached, return exit option
    cout << "\nToo many invalid attempts. Exiting...\n"; // Too many invalid attempts
    return 14; // Exit option
}

void displayReviewsByUser(string userID[], string reviewText[], // Display reviews by user
                          string hotelName[], int rating[],
                          int reviewCount, string targetUserID) {
    bool found = false; // Flag to check if the user ID is found
    cout << "\n========================================\n";
    cout << "REVIEWS BY USER: " << targetUserID << "\n"; // Display the reviews by user
    cout << "========================================\n";

    for (int i = 0; i < reviewCount; i++) {
        if (userID[i] == targetUserID) {
            found = true;
            cout << "\nHotel: " << hotelName[i] << endl; // Display the hotel name
            cout << "Rating: " << rating[i] << "/5" << endl;
            cout << "Review: " << reviewText[i] << endl; // Display the review text
            cout << "----------------------------------------\n";
        }
    }

    if (!found) {
        cout << "No reviews found for this user.\n"; // No reviews found for this user
    }
}

void displayReviewsByHotel(string userID[], string reviewText[], // Display reviews by hotel
                           string hotelName[], int rating[],
                           string userName[], int reviewCount,
                           string targetHotel) {
    bool found = false; // Flag to check if the hotel name is found
    cout << "\n========================================\n";
    cout << "REVIEWS FOR HOTEL: " << targetHotel << "\n"; // Display the reviews for the hotel
    cout << "========================================\n";

    for (int i = 0; i < reviewCount; i++) {
        if (caseInsensitiveCompare(hotelName[i], targetHotel)) {
            found = true;
            cout << "\nUser ID: " << userID[i] << endl; // Display the user ID
            cout << "Rating: " << rating[i] << "/5" << endl;
            cout << "Review: " << reviewText[i] << endl; // Display the review text
            cout << "----------------------------------------\n";
        }
    }

    if (!found) {
        cout << "No reviews found for this hotel.\n"; // No reviews found for this hotel
    }
}

void displayUserInfo(string userID[], string userName[], string country[],  // Display user information
                     string state[], string email[], string membership[],
                     int points[], int userCount, string targetUserID) {
    for (int i = 0; i < userCount; i++) { // Loop through the users
        if (userID[i] == targetUserID) {
            cout << "\n========================================\n";
            cout << "USER INFORMATION\n"; // Display the user information
            cout << "========================================\n";
            cout << "User ID: " << userID[i] << endl; // Display the user ID
            cout << "Name: " << userName[i] << endl; // Display the name
            cout << "Country: " << country[i] << endl; // Display the country
            cout << "State: " << state[i] << endl; // Display the state
            cout << "Email: " << email[i] << endl; // Display the email
            cout << "Membership: " << membership[i] << endl; // Display the membership
            cout << "Points: " << points[i] << endl; // Display the points
            cout << "========================================\n";
            return;
        }
    }
}

void displayPositiveReviewsByHotel(string targetHotel, Traveler travelers[], int travelerCount) {
    bool found = false;
    cout << "\n========================================\n";
    cout << "POSITIVE REVIEWS (4-5) FOR: " << targetHotel << "\n";
    cout << "========================================\n";

    for (int i = 0; i < travelerCount; i++) {
        for (int j = 0; j < travelers[i].getReviewCount(); j++) {
            Review r = travelers[i].getReview(j);
            if (r.getHotelName() == targetHotel && r.getRating() >= 4) {
                found = true;
                cout << "\nUser: " << travelers[i].getUserName() << endl;
                cout << "Rating: " << r.getRating() << "/5" << endl;
                cout << "Review: " << r.getReviewText() << endl;
                cout << "----------------------------------------\n";
            }
        }
    }

    if (!found) {
        cout << "No positive reviews found for this hotel.\n";
    }
}

// Friend function — can access private members of Traveler directly
void generateReportSummary(Traveler travelers[], int travelerCount) {
    int totalPoints = 0;
    int totalReviews = 0;

    for (int i = 0; i < travelerCount; i++) {
        totalPoints += travelers[i].loyaltyPoints;   // accessing private member directly
        totalReviews += travelers[i].reviewCount;    // accessing private member directly
    }

    cout << "\n========================================\n";
    cout << "SUMMARY OF ACTIVITIES\n";
    cout << "========================================\n";
    cout << "Total Number of Users:   " << travelerCount << endl;
    cout << "Total Number of Reviews: " << totalReviews << endl;
    cout << "Total Points Awarded:    " << totalPoints << endl;
    cout << "========================================\n";
}

void displayUsersByCategory(Traveler travelers[], int travelerCount) {
    string categories[] = {"Platinum", "Gold", "Silver", "Basic"};
    int catCount = 4;

    cout << "\n========================================\n";
    cout << "USERS GROUPED BY MEMBERSHIP CATEGORY\n";
    cout << "========================================\n";

    for (int c = 0; c < catCount; c++) {
        cout << "\n--- " << categories[c] << " ---\n";
        bool hasUsers = false;
        for (int i = 0; i < travelerCount; i++) {
            if (travelers[i].getMembershipLevel() == categories[c]) {
                hasUsers = true;
                cout << travelers[i].getUserID() << " - "
                     << travelers[i].getUserName()
                     << " (Points: " << travelers[i].getLoyaltyPoints() << ")\n";
            }
        }
        if (!hasUsers) {
            cout << "No users in this category.\n";
        }
    }
    cout << "========================================\n";
}


void sortIndicesByReviewCount(Traveler travelers[], int travelerCount, int sortedIndices[]) {
    for (int i = 0; i < travelerCount; i++) {
        sortedIndices[i] = i;
    }

    for (int i = 0; i < travelerCount - 1; i++) {
        for (int j = 0; j < travelerCount - i - 1; j++) {
            if (travelers[sortedIndices[j]].getReviewCount() < 
                travelers[sortedIndices[j+1]].getReviewCount()) {
                int temp = sortedIndices[j];
                sortedIndices[j] = sortedIndices[j+1];
                sortedIndices[j+1] = temp;
            }
        }
    }
}

void displayTopReviewerLeaderboard(Traveler travelers[], int travelerCount) {
    int sortedIndices[MAX_USERS];
    for (int i = 0; i < travelerCount; i++) {
        sortedIndices[i] = i;
    }
    sortIndicesByReviewCount(travelers, travelerCount, sortedIndices);

    cout << "\n========================================\n";
    cout << "TOP REVIEWER LEADERBOARD\n";
    cout << "========================================\n";
    cout << setw(5) << "Rank" << setw(10) << "User ID"
         << setw(25) << "Name" << setw(15) << "Review Count\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < travelerCount; i++) {
        int idx = sortedIndices[i];
        cout << setw(5) << (i + 1)
             << setw(10) << travelers[idx].getUserID()
             << setw(25) << travelers[idx].getUserName()
             << setw(15) << travelers[idx].getReviewCount() << endl;
    }
    cout << "========================================\n";
}

void displayTop3Users(Traveler travelers[], int travelerCount) {
    int sortedIndices[MAX_USERS];
    for (int i = 0; i < travelerCount; i++) {
        sortedIndices[i] = i;
    }
    sortIndicesByReviewCount(travelers, travelerCount, sortedIndices);

    cout << "\n========================================\n";
    cout << "TOP 3 USERS WITH MOST REVIEWS\n";
    cout << "========================================\n";
    for (int i = 0; i < 3 && sortedIndices[i] != -1; i++) {
        int idx = sortedIndices[i];
        cout << (i + 1) << ". " << travelers[idx].getUserID() << " - " << travelers[idx].getUserName()
             << " (" << travelers[idx].getReviewCount() << " reviews)\n";
    }
    cout << "========================================\n";
}

void displayHotelRatingSummary(string hotelName[], int rating[],  // Display hotel rating summary
                                int reviewCount) {
    // Get unique hotels
    string uniqueHotels[MAX_REVIEWS]; // Initialize the unique hotels to 0
    int hotelCount = 0; // Initialize the hotel count to 0

    for (int i = 0; i < reviewCount; i++) {
        bool found = false; // Flag to check if the hotel is found
        for (int j = 0; j < hotelCount; j++) {
            if (uniqueHotels[j] == hotelName[i]) {
                found = true; // Set the found flag to true
                break;
            }
        }
        if (!found) {
            uniqueHotels[hotelCount++] = hotelName[i]; // Set the unique hotels to the hotel name
        }
    }

    cout << "\n========================================\n";
    cout << "HOTEL RATING SUMMARY\n"; // Display the hotel rating summary
    cout << "========================================\n";
    cout << setw(30) << "Hotel Name" << setw(20) << "Average Rating"
         << setw(20) << "Total Reviews\n"; // Display the hotel name, average rating, and total reviews
    cout << "----------------------------------------\n";

    for (int i = 0; i < hotelCount; i++) {
        double totalRating = 0; // Initialize the total rating to 0
        int count = 0;
        for (int j = 0; j < reviewCount; j++) {
            if (hotelName[j] == uniqueHotels[i]) {
                totalRating += rating[j];
                count++;
            }
        }
        double avgRating = count > 0 ? totalRating / count : 0; // Calculate the average rating
        cout << setw(30) << uniqueHotels[i]
             << setw(20) << fixed << setprecision(2) << avgRating
             << setw(20) << count << endl; // Display the hotel name, average rating, and total reviews
    }
    cout << "========================================\n";
}

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

int calculateReviewPoints(const string& reviewText) {
    int points = BASE_POINTS; // Initialize the points to the base points
    int wordCount = countWords(reviewText); // Count the words in the review text
    if (wordCount > BONUS_WORD_THRESHOLD) {
        points += BONUS_POINTS; // Add the bonus points to the points
    }
    return points;
}

string getMembershipCategory(int points) {  // Get the membership category for a user
    if (points >= 10000) {
        return "Platinum"; // Return the platinum category
    } else if (points >= 5000) {
        return "Gold"; // Return the gold category
    } else if (points >= 1000) {
        return "Silver"; // Return the silver category
    } else {
        return "Basic"; // Return the basic category
    }
}

// Helper function to compare membership levels (higher number = higher tier)
int getMembershipLevel(const string& category) { // Get the membership level for a category
    if (category == "Platinum") return 4; // Return the platinum level
    if (category == "Gold") return 3;
    if (category == "Silver") return 2; // Return the silver level
    if (category == "Basic") return 1;
    return 0; // Return the basic level
}

// Update membership categories based on current points (without changing points)
void updateMembershipCategories(string userID[], string userName[],  // Update the membership categories
                                 int points[], string membership[],
                                 int userCount) {
    for (int i = 0; i < userCount; i++) {
        membership[i] = getMembershipCategory(points[i]); // Set the membership category to the points
    }
}

// Add points for a newly added review and update membership
void addPointsForNewReview(string userID[], string userName[], int points[],  // Add points for a newly added review
                           string membership[], string newUserID,
                           string newReviewText, int userCount) {
    // Calculate points for the new review
    int reviewPoints = calculateReviewPoints(newReviewText); // Calculate the points for the new review

    // Find the user and add points
    for (int i = 0; i < userCount; i++) {
        if (userID[i] == newUserID) { // If the user ID is the same as the new user ID
            int oldPoints = points[i]; // Set the old points to the points
            string oldCategory = membership[i];
            points[i] += reviewPoints; // Add points to existing points
            string newCategory = getMembershipCategory(points[i]);
            membership[i] = newCategory;

            // Show points update message
            cout << "\n========================================\n";
            cout << "POINTS UPDATED\n";
            cout << "========================================\n";
            cout << userName[i] << " (" << userID[i] << ") received "
                 << reviewPoints << " points for the new review.\n";
            cout << "Previous points: " << oldPoints << "\n";
            cout << "New total points: " << points[i] << "\n";
            cout << "Membership category: " << newCategory << "\n";

            // Show upgrade notification if moved to higher category
            if (oldCategory != newCategory &&
                getMembershipLevel(newCategory) > getMembershipLevel(oldCategory)) {
                cout << "\n*** UPGRADE! ***\n";
                cout << "Congratulations! " << userName[i] << " has been upgraded from "
                     << oldCategory << " to " << newCategory << "!\n";
            }
            cout << "========================================\n\n";
            break;
        }
    }
}

void addNewReview(string reviewUserID[], int rating[], string reviewText[],  // Add a new review
                  string hotelName[], int& reviewCount,
                  string userID[], int userCount, string& newUserID,
                  string& newReviewText) {
    if (reviewCount >= MAX_REVIEWS) {
        cout << "Maximum review limit reached!\n"; // Maximum review limit reached
        return;
    }

    int newRating; // Initialize the new rating to 0
    string newHotelName; // Initialize the new hotel name to 0

    cout << "\n========================================\n";
    cout << "ADD NEW REVIEW\n";
    cout << "========================================\n";

    // Get User ID with validation (prevent infinite loop)
    bool validUser = false;
    int attempts = 0;
    const int MAX_ATTEMPTS = 5;
    while (!validUser && attempts < MAX_ATTEMPTS) {
        cout << "Enter User ID: ";
        if (cin >> newUserID) {
            cin.ignore(1000, '\n'); // Clear the input buffer
            // Convert to correct case
            newUserID = findUserIDCaseInsensitive(newUserID, userID, userCount);
            validUser = validateUserID(newUserID, userID, userCount);
            if (!validUser) {
                attempts++;
                if (attempts < MAX_ATTEMPTS) {
                    cout << "Invalid User ID! Please try again.\n";
                } else {
                    cout << "Too many invalid attempts. Cancelling review addition.\n";
                    return;
                }
            }
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                cout << "Invalid input! Please enter a valid User ID.\n";
            } else {
                cout << "Too many invalid attempts. Cancelling review addition.\n";
                return;
            }
        }
    }

    // Get Rating with validation (prevent infinite loop)
    bool validRating = false; // Flag to check if the rating is valid
    attempts = 0; // Initialize the attempts to 0
    while (!validRating && attempts < MAX_ATTEMPTS) {
        cout << "Enter Rating (1-5): "; // Prompt the user to enter a rating
        if (cin >> newRating) {
            cin.ignore(1000, '\n'); // Clear the input buffer
            validRating = validateRating(newRating); // Validate the rating
            if (!validRating) {
                attempts++;
                if (attempts < MAX_ATTEMPTS) {
                    cout << "Invalid Rating! Please enter a number between 1 and 5.\n";
                } else {
                    cout << "Too many invalid attempts. Cancelling review addition.\n";
                    return;
                }
            }
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            attempts++;
            if (attempts < MAX_ATTEMPTS) {
                cout << "Invalid input! Please enter a number between 1 and 5.\n";
            } else {
                cout << "Too many invalid attempts. Cancelling review addition.\n";
                return;
            }
        }
    }

    // Get Review Text
    cout << "Enter Review Text: ";
    getline(cin, newReviewText);

    // Get Hotel Name
    cout << "Enter Hotel Name: ";
    getline(cin, newHotelName);

    // Add review to arrays
    reviewUserID[reviewCount] = newUserID;
    rating[reviewCount] = newRating;
    reviewText[reviewCount] = newReviewText;
    hotelName[reviewCount] = newHotelName;
    reviewCount++;

    cout << "\nReview added successfully!\n";
}

// Helper function to convert string to uppercase
string toUpper(const string& str) {
    string result = str;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'a' && result[i] <= 'z') {
            result[i] = result[i] - 'a' + 'A';
        }
    }
    return result;
}

// Helper function for case-insensitive string comparison
bool caseInsensitiveCompare(const string& str1, const string& str2) {   // Compare two strings case insensitively
    if (str1.length() != str2.length()) return false;
    for (size_t i = 0; i < str1.length(); i++) {
        char c1 = str1[i];
        char c2 = str2[i];
        // Convert to uppercase for comparison
        if (c1 >= 'a' && c1 <= 'z') c1 = c1 - 'a' + 'A';
        if (c2 >= 'a' && c2 <= 'z') c2 = c2 - 'a' + 'A';
        if (c1 != c2) return false;
    }
    return true;
}

bool validateUserID(const string& userID, string userIDList[], int userCount) {   // Validate the user ID
    string upperInput = toUpper(userID);
    for (int i = 0; i < userCount; i++) {
        if (caseInsensitiveCompare(userIDList[i], upperInput)) {
            return true;
        }
    }
    return false;
}

// Find user ID with case-insensitive matching and return the correct case
string findUserIDCaseInsensitive(const string& input, string userIDList[], int userCount) {
    string upperInput = toUpper(input);
    for (int i = 0; i < userCount; i++) {
        if (caseInsensitiveCompare(userIDList[i], upperInput)) {
            return userIDList[i]; // Return the correct case from the list
        }
    }
    return input; // Return original if not found
}

bool validateRating(int rating) {   // Validate the rating
    return (rating >= 1 && rating <= 5);
}

void saveUsers(const string& filename, string userID[], string userName[],  // Save the users to a file
               string country[], string state[], string email[],
               string membership[], int points[], int userCount) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Cannot open " << filename << " for writing\n";
        return;
    }

    for (int i = 0; i < userCount; i++) {
        outFile << userID[i] << "\t" << userName[i] << "\t"
                << country[i] << "\t" << state[i] << "\t"
                << email[i] << "\t" << membership[i] << "\t"
                << points[i] << endl;
    }

    outFile.close();
}

void saveReviews(const string& filename, string userID[], int rating[],     // Save the reviews to a file
                 string reviewText[], string hotelName[], int reviewCount) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Cannot open " << filename << " for writing\n";
        return;
    }

    for (int i = 0; i < reviewCount; i++) {
        outFile << userID[i] << "\t" << rating[i] << "\t"
                << reviewText[i] << "\t" << hotelName[i] << endl;
    }

    outFile.close();
}

// Additional Features Implementation

void sortUsersByPoints(string userID[], string userName[], string country[],  // Sort the users by points
                       string state[], string email[], string membership[],
                       int points[], int userCount) {
    // Create index array for sorting
    int indices[MAX_USERS]; // Initialize the indices to 0
    for (int i = 0; i < userCount; i++) {
        indices[i] = i;
    }

    // Bubble sort by points (highest to lowest)
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            if (points[indices[j]] < points[indices[j+1]]) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }

    cout << "\n========================================\n";
    cout << "USERS SORTED BY POINTS (Highest to Lowest)\n";
    cout << "========================================\n";
    cout << setw(10) << "User ID" << setw(25) << "Name"
         << setw(15) << "Membership" << setw(10) << "Points\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < userCount; i++) {
        int idx = indices[i];
        cout << setw(10) << userID[idx] << setw(25) << userName[idx]
             << setw(15) << membership[idx] << setw(10) << points[idx] << endl;
    }
    cout << "========================================\n";
}

void sortHotelsByReviewCount(string hotelName[], int rating[],  // Sort the hotels by review count
                              string reviewText[], string reviewUserID[],
                              int reviewCount) {
    // Get unique hotels and count reviews
    string uniqueHotels[MAX_REVIEWS];
    int hotelReviewCounts[MAX_REVIEWS] = {0};
    int hotelCount = 0;

    for (int i = 0; i < reviewCount; i++) {
        bool found = false;
        int hotelIdx = -1;
        for (int j = 0; j < hotelCount; j++) {
            if (uniqueHotels[j] == hotelName[i]) {
                found = true;
                hotelIdx = j;
                break;
            }
        }
        if (!found) {
            uniqueHotels[hotelCount] = hotelName[i];
            hotelReviewCounts[hotelCount] = 1;
            hotelCount++;
        } else {
            hotelReviewCounts[hotelIdx]++;
        }
    }

    // Bubble sort by review count (highest to lowest)
    for (int i = 0; i < hotelCount - 1; i++) {
        for (int j = 0; j < hotelCount - i - 1; j++) {
            if (hotelReviewCounts[j] < hotelReviewCounts[j+1]) {
                // Swap counts
                int tempCount = hotelReviewCounts[j];
                hotelReviewCounts[j] = hotelReviewCounts[j+1];
                hotelReviewCounts[j+1] = tempCount;

                // Swap hotel names
                string tempName = uniqueHotels[j];
                uniqueHotels[j] = uniqueHotels[j+1];
                uniqueHotels[j+1] = tempName;
            }
        }
    }

    cout << "\n========================================\n";
    cout << "HOTELS SORTED BY NUMBER OF REVIEWS\n";
    cout << "========================================\n";
    cout << setw(30) << "Hotel Name" << setw(20) << "Number of Reviews\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < hotelCount; i++) {
        cout << setw(30) << uniqueHotels[i]
             << setw(20) << hotelReviewCounts[i] << endl;
    }
    cout << "========================================\n";
}

void searchReviewsByKeyword(string reviewText[], string hotelName[],  // Search reviews by keyword
                            string reviewUserID[], int rating[],
                            string userID[], string userName[],
                            int reviewCount, int userCount, string keyword) {
    bool found = false; // Flag to check if the keyword is found

    cout << "\n========================================\n";
    cout << "SEARCH RESULTS FOR KEYWORD: \"" << keyword << "\"\n";
    cout << "========================================\n";

    // Convert keyword to lowercase for case-insensitive search
    string keywordLower = keyword;
    for (size_t i = 0; i < keywordLower.length(); i++) {
        if (keywordLower[i] >= 'A' && keywordLower[i] <= 'Z') {
            keywordLower[i] = keywordLower[i] - 'A' + 'a';
        }
    }

    for (int i = 0; i < reviewCount; i++) {
        // Convert review text to lowercase for comparison
        string reviewLower = reviewText[i];
        for (size_t j = 0; j < reviewLower.length(); j++) {
            if (reviewLower[j] >= 'A' && reviewLower[j] <= 'Z') {
                reviewLower[j] = reviewLower[j] - 'A' + 'a';
            }
        }

        // Check if keyword exists in review text
        if (reviewLower.find(keywordLower) != string::npos) {
            found = true;

            // Find user name
            string userNameDisplay = "Unknown";
            for (int j = 0; j < userCount; j++) {
                if (reviewUserID[i] == userID[j]) {
                    userNameDisplay = userName[j];
                    break;
                }
            }

            cout << "\nUser: " << userNameDisplay << " (" << reviewUserID[i] << ")\n";
            cout << "Hotel: " << hotelName[i] << endl;
            cout << "Rating: " << rating[i] << "/5" << endl;
            cout << "Review: " << reviewText[i] << endl;
            cout << "----------------------------------------\n";
        }
    }

    if (!found) {
        cout << "No reviews found containing the keyword \"" << keyword << "\".\n";
    }
    cout << "========================================\n";
}