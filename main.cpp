/********************************************************************************************************************************
August 2023
Student Name: Gonzalo Patino
Project #3 for CS210
Program Title: Produce Item Frequency Analyzer
Program Type: Computer Science - Software Engineering Final Project

# NOTE: This program is part of a final project submission for CS210. The purpose of this program is to analyze a .txt file containing a list of produce items.
# It lists each unique produce item and calculates the frequency of occurrences. The program can display the frequency as a histogram.
# Additionally, the program offers the functionality to back up the analyzed data.

************************************************************************************************************************************/



//Some header files required:
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;


//Defining classes
class Produce {

public:
    Produce(const string& name); // constructor
    string getFrequencyHistogram() const;
    bool operator<(const Produce& other) const;
    void incrementFrequency();
    string getName() const; // getter
    int getFrequency() const; //getter

private:
    int frequency;
    string name;
};


//Constructor and Function definitions
Produce::Produce(const string& name) : name(name), frequency(1) {}

void Produce::incrementFrequency() {
    frequency++;
}

bool Produce::operator<(const Produce& other) const {
    return name < other.name;
}

string Produce::getName() const {
    return name;
}

string Produce::getFrequencyHistogram() const {
    // This function generates a histogram-style representation of the produce item's frequency.
    // For each occurrence of the produce item, an asterisk '*' is added to the histogram string.

    string histogram;
    // Loop through the frequency count and append an asterisk '*' to the histogram for each occurrence
    for (int i = 0; i < frequency; ++i) {
        histogram += "*";
    }
    return histogram;
}

int Produce::getFrequency() const {
    return frequency;
}

void SearchAndDisplayFrequency(const vector<Produce>& produceList) {
    // This function allows the user to search for the frequency of a specific produce item within the list.
    // It takes the list of Produce objects as input and interacts with the user to search for items.

    string searchWord;
    bool found = false;

    while (!found) {
        cout << "Enter a word to search for its frequency (or 'q' to quit): ";
        cin >> searchWord;

        if (searchWord == "q") {
            cout << "Exiting search." << endl;
            break;
        }

        for (const auto& produce : produceList) {
            if (produce.getName() == searchWord) {
                cout << "Frequency of " << searchWord << ": " << produce.getFrequency() << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "The word \"" << searchWord << "\" was not found in the list. Please try again." << endl;
        }
    }
}

vector<Produce> CalculateListItemFrequency(const string& filename) {
    // This function reads an input text file containing a list of produce items.
    // It creates a vector of Produce objects to hold each unique item along with its frequency.

    vector<Produce> produceList;
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Failed to open the input file." << endl;
        return produceList;
    }

    string item;
    while (getline(inputFile, item)) {
        bool found = false;
        for (auto& produce : produceList) {
            if (produce.getName() == item) {
                produce.incrementFrequency();
                found = true;
                break;
            }
        }
        if (!found) {
            produceList.push_back(Produce(item));
        }
    }

    inputFile.close();

    // Sort the produce items in alphabetic order
    sort(produceList.begin(), produceList.end());

    cout << "Input file read succesfully" << endl;
    return produceList;

}

vector<Produce> ShowListItemFrequency(const string& filename) {
    // This function reads an input text file containing a list of produce items. 
    // It creates a vector of Produce objects to hold each unique item along with its frequency.
    // It generates an output to the console
    vector<Produce> produceList;
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Failed to open the input file." << endl;
        return produceList;
    }

    string item;
    while (getline(inputFile, item)) {
        bool found = false;
        for (auto& produce : produceList) {
            if (produce.getName() == item) {
                produce.incrementFrequency();
                found = true;
                break;
            }
        }
        if (!found) {
            produceList.push_back(Produce(item));
        }
    }

    inputFile.close();

    // Sort the produce items in alphabetic order
    sort(produceList.begin(), produceList.end());

    // Output the sorted items indicating their frequency
    for (const auto& produce : produceList) {
        cout << produce.getName() << ": " << produce.getFrequency() << endl;
    }
    return produceList;
}

vector<Produce> CalculateListItemFrequencyH(const string& filename) {
    // This function reads an input text file containing a list of produce items.
    // It creates a vector of Produce objects to hold each unique item along with its frequency.
    //It generates an output to the console as a histogram

    vector<Produce> produceList;
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Failed to open the input file." << endl;
        return produceList;
    }


    string item;
    while (getline(inputFile, item)) {
        bool found = false;
        for (auto& produce : produceList) {
            if (produce.getName() == item) {
                produce.incrementFrequency();
                found = true;
                break;
            }
        }
        if (!found) {
            produceList.push_back(Produce(item));
        }
    }

    inputFile.close();


    // Sort the produce items alphabetically
    sort(produceList.begin(), produceList.end());


    // Display the histogram-style frequency
    for (const auto& produce : produceList) {
        cout << produce.getName() << ": " << produce.getFrequencyHistogram() << endl;
    }

    return produceList;
}

void writeToFile(const vector<Produce>& produceList) {
    //Creates a backup as a .txt file to the project directory. This will list the produce items with their frequency

    // output stream starts
    ofstream outputFile("backup.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open the output file." << endl;
        return;
    }

    for (const auto& produce : produceList) {
        outputFile << produce.getName() << ": " << produce.getFrequency() << endl;
    }

    outputFile.close();
    cout << "Results written to backup.txt" << endl;
}

enum State {
	MENU_OPTION_1,
	MENU_OPTION_2,
	MENU_OPTION_3,
    MENU_OPTION_4

};

void ShowMenu(State* myState) {
    int userInput = 0;

    // Display menu options
    cout << "\n===================================================" << endl;
    cout << "       WELCOME TO PRODUCE MENU- Gonzalo Patino" << endl;
    cout << "===================================================" << endl;
    cout << "Please select an option from the menu below:" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "1. Find produce item frequency in the input list" << endl;
    cout << "2. Show list of produce items and their frequency" << endl;
    cout << "3. Show produce items and frequency as a histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Enter your choice: ";

    cin >> userInput;

    switch (userInput) {
    case 1:
        *myState = MENU_OPTION_1;
        break;
    case 2:
        *myState = MENU_OPTION_2;
        break;
    case 3:
        *myState = MENU_OPTION_3;
        break;
    case 4:
        *myState = MENU_OPTION_4;
        break;
    default:
        cout << "Invalid option" << endl;
    }
}


int main() {
    //Initialize variables
    string inputFileName = "inputFile.txt";
    State* myStatePtr;
    State currentState = MENU_OPTION_1;
    myStatePtr = &currentState;

    //My program starts here

    //I) Read input file and create a vector called produceList to hold Produce objects. This vector will contain produce items along with their frequency
    vector<Produce> produceList = CalculateListItemFrequency(inputFileName);

    //Create an output file to store the list of produce items and their frequency in the project directory.
    writeToFile(produceList);

    //Enter the main menu loop
    while (currentState != MENU_OPTION_4) {
        //Display the menu
        ShowMenu(myStatePtr);

        // Handle user's menu choice
        switch (currentState) {

        case MENU_OPTION_1:
            cout << "Current state: MENU_OPTION_1" << endl;
            // Perform actions for MENU_OPTION_1 state
            SearchAndDisplayFrequency(produceList);
            break;

        case MENU_OPTION_2:
            cout << "Current state: MENU_OPTION_2" << endl;
            // Perform actions for MENU_OPTION_2 state
            cout << endl;
            ShowListItemFrequency(inputFileName);
            break;

        case MENU_OPTION_3:
            cout << "Current state: MENU_OPTION_3" << endl;
            // Perform actions for MENU_OPTION_3 state
            CalculateListItemFrequencyH(inputFileName);
            cout << endl;
          
            break;

        case MENU_OPTION_4:
            cout << "Current state: MENU_OPTION_4" << endl;
            // Perform actions for MENU_OPTION_4 state
            //Exit
            break;

        default:
            std::cout << "Invalid state" << endl;
            break;
        }

    }
    // The user has chosen to exit
    cout << "You have exited" << endl;

	return 0;
}