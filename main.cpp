#include <iostream> 
#include <fstream> 
#include <iomanip> 
#include <string> 
#include <cstdlib> 
#include "Person.h"
#include "Traveler.h"
#include "Review.h"

using namespace std;

// Constants
const int MAX_USERS = 100;  // Maximum number of users
const int MAX_STRING_LENGTH = 200;  // Maximum length of a string
const int BASE_POINTS = 100;  // Base points for each review
const int BONUS_POINTS = 10;  // Bonus points for each review
const int BONUS_WORD_THRESHOLD = 50;  // Threshold for bonus points

//===============================Function prototypes======================================
//load functions
int loadTravelers(const string& filename, Traveler travelers[]);
void loadReviews(const string& filename, Traveler travelers[], int);
//save functions
void saveTravelers(string, Traveler[], int);
void saveReviews(string, Traveler[], int);

void displayMenu(); // Display the menu
int getChoice(); // Get the choice from the user

void displayAllHotels(Traveler[]); // Display all hotels
void displayAllUsers(Traveler[]); // Display all users

//sort and display
void displayUsersByCategory(Traveler travelers[], int travelerCount); // Display users grouped by membership category
void displayPositiveReviewsByHotel(string targetHotel, Traveler travelers[], int travelerCount);
void displayTopReviewerLeaderboard(Traveler travelers[], int travelerCount); // Display top reviewer leaderboard
void displayTop3Users(Traveler travelers[], int travelerCount); // Display top 3 users with most reviews
void displayHotelRatingSummary(Traveler travelers[], int travelerCount); // Display hotel rating summary
void sortUsersByPoints(Traveler list[], int travelerCount); // Sort the users by points
void sortHotelsByReviewCount(const Traveler[], int);
void searchReviewsByKeyword(const Traveler[], int, string);

//friend function
void generateAnalyticsReport(Traveler travelers[], int travelerCount);

//validation
bool validateRating(int rating); // Validate the rating
bool caseInsensitiveCompare(const string& a, const string& b);
string toLowercase(const string& str);
//=================================================================================


//=================Main function==================================================
int main() { 
    // Parallel arrays for travelers
    Traveler travelers[MAX_USERS];
    int travelerCount = 0; 

    // Load data from files (open once for reading)
    travelerCount = loadTravelers("users.txt", travelers); // Load users from the users.txt file
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
	                    travelers[i].displayProfile();
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
                generateAnalyticsReport(travelers, travelerCount);
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
                displayHotelRatingSummary(travelers, travelerCount); // Display hotel rating summary
                break; // Break out of the switch statement
            case 10: {   // Add new review
                string targetID;
                int idx = -1;

                // Step 1 — keep asking until valid user ID
                while (idx == -1) {
                    cout << "\nEnter User ID: ";
                    cin >> targetID;
                    cin.ignore(1000, '\n');

                    for (int i = 0; i < travelerCount; i++) {
                        if (caseInsensitiveCompare(travelers[i].getUserID(), targetID)) {
                        idx = i;
                        break;
                        }
                    }
                    if (idx == -1) {
                        cout << "Invalid User ID! Please try again.\n";
                    }
                }

                // Step 2 — keep asking until valid rating
                int rating = 0;
                while (rating < 1 || rating > 5) {
                    cout << "Enter Rating (1-5): ";
                    if (cin >> rating) {
                        cin.ignore(1000, '\n');
                        if (rating < 1 || rating > 5) {
                            cout << "Invalid rating! Enter a number between 1 and 5.\n";
                        }
                    } else {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Enter a number between 1 and 5.\n";
                        rating = 0;
                    }
                }

                // Step 3 — get review text and hotel name
                string reviewText, hotelName;
                cout << "Enter Review Text: ";
                getline(cin, reviewText);
                cout << "Enter Hotel Name: ";
                getline(cin, hotelName);

                // Step 4 — store review and update points
                travelers[idx].addReview(hotelName, rating, reviewText);
                travelers[idx].addPoints(travelers[idx].calculatePoints(reviewText));

                cout << "\nReview added successfully!\n";
                cout << "New Points Total: " << travelers[idx].getLoyaltyPoints() << endl;
                cout << "Membership Level: " << travelers[idx].getMembershipLevel() << endl;
                break;
            }
            case 11:   // Sort users by points
                sortUsersByPoints(travelers, travelerCount);
                break; // Break out of the switch statement
            case 12:
                sortHotelsByReviewCount(travelers, travelerCount); // Sort hotels by number of reviews
                break; // Break out of the switch statement
            case 13: {
                string keyword; // Keyword to search for
                cout << "\nEnter keyword to search: ";
                getline(cin, keyword);
                searchReviewsByKeyword(travelers, travelerCount, keyword); // Search reviews by keyword
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
    saveTravelers("users.txt", travelers, travelerCount);
    saveReviews("reviews.txt", travelers, travelerCount);

    cout << "Data saved successfully!\n"; 

    return 0; // Return 0 to indicate successful execution
}
//==============================================================================================

int loadTravelers(const string& filename, Traveler travelers[]) {
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

// Reads reviews.txt once and assigns each review to matching Traveler
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
    for (int i = 0; i < 3 && i < travelerCount; i++) {
        int idx = sortedIndices[i];
        cout << (i + 1) << ". " << travelers[idx].getUserID() << " - " << travelers[idx].getUserName()
             << " (" << travelers[idx].getReviewCount() << " reviews)\n";
    }
    cout << "========================================\n";
}

void displayHotelRatingSummary(Traveler travelers[], int travelerCount) {
     string uniqueHotels[500];
    double totalRatings[500] = {0};
    int hotelReviewCount[500] = {0};
    int hotelCount = 0;

    // Loop through all travelers and their reviews
    for (int i = 0; i < travelerCount; i++) {
        for (int j = 0; j < travelers[i].getReviewCount(); j++) {
            Review r = travelers[i].getReview(j);
            string hotel = r.getHotelName();

            // Check if hotel already exists in uniqueHotels
            bool found = false;
            for (int k = 0; k < hotelCount; k++) {
                if (caseInsensitiveCompare(uniqueHotels[k], hotel)) {
                    totalRatings[k] += r.getRating();
                    hotelReviewCount[k]++;
                    found = true;
                    break;
                }
            }
            // If hotel not found, add it
            if (!found) {
                uniqueHotels[hotelCount] = hotel;
                totalRatings[hotelCount] = r.getRating();
                hotelReviewCount[hotelCount] = 1;
                hotelCount++;
            }
        }
    }

    // Display results
    cout << "\n========================================\n";
    cout << "HOTEL RATING SUMMARY\n";
    cout << "========================================\n";
    cout << setw(30) << "Hotel Name"
         << setw(20) << "Average Rating"
         << setw(20) << "Total Reviews\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < hotelCount; i++) {
        double avg = hotelReviewCount[i] > 0 ? 
                     totalRatings[i] / hotelReviewCount[i] : 0;
        cout << setw(30) << uniqueHotels[i]
             << setw(20) << fixed << setprecision(2) << avg
             << setw(20) << hotelReviewCount[i] << endl;
    }
    cout << "========================================\n";
}

void sortUsersByPoints(Traveler travelers[], int travelerCount) {
    // Use a temparaily array so we can change the order in this temp array not the actual array
    int tempArray[MAX_USERS];
    for (int i = 0; i < travelerCount; i++) {
        tempArray[i] = i;                       //intialize the array so like [1,2,3,4,5]
    }

    // Bubble sort by points using operator>
    for (int i = 0; i < travelerCount - 1; i++) {
        for (int j = 0; j < travelerCount - i - 1; j++) {
            if (travelers[tempArray[j]].getLoyaltyPoints() < 
                travelers[tempArray[j+1]].getLoyaltyPoints()) {
                // Swap position in this temp array
                int temp = tempArray[j];
                tempArray[j] = tempArray[j+1];
                tempArray[j+1] = temp;
            }
        }
    }   //after bubble sort the array would be like [4,3,5,1,2] which means the position has changed

    // Display using sorted indices
    cout << "\n========================================\n";
    cout << "USERS SORTED BY POINTS (Highest to Lowest)\n";
    cout << "========================================\n";
    cout << left << setw(10) << "User ID" 
         << setw(25) << "Name"
         << setw(15) << "Membership" 
         << setw(10) << "Points" << endl;
    cout << "----------------------------------------\n";

    for (int i = 0; i < travelerCount; i++) {
        int index = tempArray[i];                     //now we print using ori array but with sorted arrangement
        cout << left << setw(10) << travelers[index].getUserID()
             << setw(25) << travelers[index].getUserName()
             << setw(15) << travelers[index].getMembershipLevel()
             << setw(10) << travelers[index].getLoyaltyPoints() << endl;
    }
    cout << "========================================\n";
}

void sortHotelsByReviewCount(const Traveler list[], int travelerCount) {
    // Parallel local arrays for temporary processing 
    string uniqueHotels[500]; 
    int hotelReviewCounts[500] = {0};
    int hotelCount = 0;

    // 1. DATA EXTRACTION: Traverse the Object Hierarchy
    for (int i = 0; i < travelerCount; i++) {
        // Traveler class must provide access to its reviews via a getter or internal loop
        for (int r = 0; r < list[i].getReviewCount(); r++) {
            string currentHotel = list[i].getReview(r).getHotelName();
            
            bool found = false;
            for (int j = 0; j < hotelCount; j++) {
                if (uniqueHotels[j] == currentHotel) {
                    hotelReviewCounts[j]++;
                    found = true;
                    break;
                }
            }
            if (!found && hotelCount < 500) {
                uniqueHotels[hotelCount] = currentHotel;
                hotelReviewCounts[hotelCount] = 1;
                hotelCount++;
            }
        }
    }

    // 2. BUBBLE SORT: High to Low
    for (int i = 0; i < hotelCount - 1; i++) {
        for (int j = 0; j < hotelCount - i - 1; j++) {
            if (hotelReviewCounts[j] < hotelReviewCounts[j+1]) {
                // Swap counts
                int tempCount = hotelReviewCounts[j];
                hotelReviewCounts[j] = hotelReviewCounts[j+1];
                hotelReviewCounts[j+1] = tempCount;
                // Swap names
                string tempName = uniqueHotels[j];
                uniqueHotels[j] = uniqueHotels[j+1];
                uniqueHotels[j+1] = tempName;
            }
        }
    }

    // 3. DISPLAY RESULTS
    cout << "\n========================================" << endl;
    cout << left << setw(30) << "Hotel Name" << "Total Reviews" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < hotelCount; i++) {
        cout << left << setw(30) << uniqueHotels[i] << hotelReviewCounts[i] << endl;
    }
}

void searchReviewsByKeyword(const Traveler travelers[], int travelerCount, string keyword)
{
	cout << "===============================================================================================" << endl;
   	cout << left << setw(15) << "User ID";
   	cout << setw(30) << "Hotel Name ";
  	cout << "Review Statement" << endl;
   	cout << "===============================================================================================" << endl;
    	
    bool found = false;	
    keyword = toLowercase(keyword);   // Convert the keyword to lowercase 
	keyword = " " + keyword + " ";    // Add spaces before and after keyword to match whole words only exp: search "good" wont come out "goodness"
	
    // Loop through all review statements
	for (int i = 0; i < travelerCount; i++)        //loop thru all traveler
    {
    	for(int j=0; j<travelers[i].getReviewCount(); j++){    //loop thru all review for each traveler
    		Review r = travelers[i].getReview(j);            //store temp review variable so later can get and print stuff inside
    		string review = " " + toLowercase(r.getReviewText()) + " ";  // Convert the review statement to lowercase and add spaces at both ends
    	
	        for (int k = 0; k < review.length(); k++) { //loop thru every single character
    			if (ispunct(review[k]))                 //if found punctuation
        		review[k] = ' ';                       //turn the punctuation into space
			}
	        // Check if the keyword exists in the review
			if (review.find(keyword) != string::npos)      //string::nops means not found
	        {
	        	found = true;
	            cout << left << setw(15) << travelers[i].getUserID();
	            cout << setw(20) << travelers[i].getUserName();
	            cout << setw(30) << r.getHotelName();
	            cout << setw(10) << r.getRating();
	            cout << r.getReviewText() << endl;
	    	}
		}
    }

    	if(!found){
    	cout << "Keyword " << keyword << " not found. " << endl;
	}
}

bool validateRating(int rating) {   // Validate the rating
    return (rating >= 1 && rating <= 5);
}

void saveTravelers(string filename, Traveler travelers[], int travelerCount) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Cannot open " << filename << " for writing\n";
        return;
    }

    for (int i = 0; i < travelerCount; i++) {
        outFile << travelers[i].getUserID() << "\t" << travelers[i].getUserName() << "\t"
                << travelers[i].getCountry() << "\t" << travelers[i].getState() << "\t"
                << travelers[i].getEmail() << "\t" << travelers[i]. getMembershipLevel() << "\t"
                << travelers[i].getLoyaltyPoints() << endl;
    }
    outFile.close();
}

void saveReviews(string filename, Traveler travelers[], int travelerCount) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error: Cannot open reviews.txt for writing\n";
        return;
    }

    for (int i = 0; i < travelerCount; i++) {
        for (int j = 0; j < travelers[i].getReviewCount(); j++) {
            Review r = travelers[i].getReview(j);
            outFile << r.getReviewerID() << "\t"
                    << r.getRating()     << "\t"
                    << r.getReviewText() << "\t"
                    << r.getHotelName()  << "\n";
        }
    }

    outFile.close();
}

// Friend function that can access private members of Traveler directly
// Friend function of Traveler � accesses private members directly
void generateAnalyticsReport(Traveler travelers[], int travelerCount) {
    int totalPoints = 0;
    int totalReviews = 0;
    string topUser = "";
    int topCount = 0;

    for (int i = 0; i < travelerCount; i++) {
        totalPoints += travelers[i].loyaltyPoints;   // private member of Traveler
        totalReviews += travelers[i].reviewCount;    // private member of Traveler

        if (travelers[i].reviewCount > topCount) {
            topCount = travelers[i].reviewCount;
            topUser = travelers[i].userName;         // protected member of Person, accessible via Traveler
        }
    }

    cout << "\n========================================\n";
    cout << "SYSTEM ANALYTICS REPORT\n";
    cout << "========================================\n";
    cout << "Total Travelers:         " << travelerCount << endl;
    cout << "Total Reviews:           " << totalReviews << endl;
    cout << "Total Points Awarded:    " << totalPoints << endl;
    cout << "Most Active Reviewer:    " << topUser
         << " (" << topCount << " reviews)" << endl;
    cout << "========================================\n";
}

//------------------------------------------------------------------------------------
// This function converts all characters in the input string to lowercase
string toLowercase(const string& str) {
    string lowerStr = str;             //copy original string into this temporaly string
    for (int i = 0; i < lowerStr.length(); i++) {    //loop to go thru every letter
        lowerStr[i] = tolower(lowerStr[i]);        //convert all letter to lowercase one by one
    }
    return lowerStr;        //return the temparaily string that is now all lowercase
}

//compare two data while making both tolowercase
bool caseInsensitiveCompare(const string& a, const string& b) {
    return toLowercase(a) == toLowercase(b);
}
