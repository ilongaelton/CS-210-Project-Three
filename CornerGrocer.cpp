#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class GroceryTracker {
public:
    // Constructor loads the grocery data when the object is created
    GroceryTracker(string inputFileName);

    // Returns the number of times a specific item was purchased
    int GetItemFrequency(string item);

    // Displays every item and its numeric frequency
    void PrintAllFrequencies();

    // Displays every item as a histogram
    void PrintHistogram();

    // Creates the backup file
    void CreateBackupFile();

private:
    map<string, int> itemFrequencies;
    string inputFile;

    // Reads grocery items from the input file
    void LoadData();
};


// Constructor
GroceryTracker::GroceryTracker(string inputFileName) {
    inputFile = inputFileName;

    LoadData();
    CreateBackupFile();
}


// Reads all items and counts how many times each appears
void GroceryTracker::LoadData() {
    ifstream inFS;
    string item;

    inFS.open(inputFile);

    if (!inFS.is_open()) {
        cout << "Error: Could not open " << inputFile << endl;
        return;
    }

    while (inFS >> item) {
        itemFrequencies[item]++;
    }

    inFS.close();
}


// Returns frequency for one item
int GroceryTracker::GetItemFrequency(string item) {
    if (itemFrequencies.count(item) > 0) {
        return itemFrequencies[item];
    }

    return 0;
}


// Prints every item and its frequency
void GroceryTracker::PrintAllFrequencies() {
    for (const auto& item : itemFrequencies) {
        cout << item.first << " " << item.second << endl;
    }
}


// Prints histogram
void GroceryTracker::PrintHistogram() {
    for (const auto& item : itemFrequencies) {
        cout << item.first << " ";

        for (int i = 0; i < item.second; ++i) {
            cout << "*";
        }

        cout << endl;
    }
}


// Creates frequency.dat automatically
void GroceryTracker::CreateBackupFile() {
    ofstream outFS;

    outFS.open("frequency.dat");

    if (!outFS.is_open()) {
        cout << "Error: Could not create frequency.dat" << endl;
        return;
    }

    for (const auto& item : itemFrequencies) {
        outFS << item.first << " " << item.second << endl;
    }

    outFS.close();
}


int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");

    int menuChoice = 0;
    string searchItem;

    while (menuChoice != 4) {
        cout << endl;
        cout << "CORNER GROCER" << endl;
        cout << "------------------------" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Display item frequencies" << endl;
        cout << "3. Display histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> menuChoice;

        if (menuChoice == 1) {
            cout << "Enter item name: ";
            cin >> searchItem;

            cout << searchItem << " was purchased "
                << tracker.GetItemFrequency(searchItem)
                << " times." << endl;
        }

        else if (menuChoice == 2) {
            cout << endl;
            cout << "ITEM FREQUENCIES" << endl;
            tracker.PrintAllFrequencies();
        }

        else if (menuChoice == 3) {
            cout << endl;
            cout << "ITEM HISTOGRAM" << endl;
            tracker.PrintHistogram();
        }

        else if (menuChoice == 4) {
            cout << "Thank you for using Corner Grocer." << endl;
        }

        else {
            cout << "Invalid option. Please enter 1 through 4." << endl;
        }
    }

    return 0;
}
