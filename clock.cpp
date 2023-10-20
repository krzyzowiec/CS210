/*
 * clock.cpp
 *
 *  Date: 09/15/2023
 *  Author: Robert Rak
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

// Input variables
string input;
vector<std::string> tokens;
string token;

// Misc declarations
char delimiter = ':';
vector<int> time_clock(3);
bool quit = false;
int menu_choice;
int hour;

enum Period
{
    HOUR = 1,
    MINUTE = 2,
    SECOND = 3
};

// Initializes the time vector, where position 0 contains the hours, position 1, the minutes, and position 2, the seconds 
void initialize_time(vector<int>& time) {
    time.clear();

    // User enters time in the format of "hours:minutes:seconds" to initialize the clock (ex. 3:22:1 or 03:22:01)
    cout << "Please enter the current time in 24-hour format (ex. 15:22:01 or 15:22:1) to initialize the clock: " << endl;
    getline(std::cin, input);
    istringstream iss(input);
    
    // Handle splitting based on delimeter
    while (getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    // Convert string tokens to integers
    for (int i = 0; i < 3; ++i) {
        switch (i) {
            case 0:
                time[0] = stoi(tokens.at(i));
                if (time[0] > 23) time[0] = 23;  // Bounds checking
                break;
            case 1:
                time[1] = stoi(tokens.at(i));
                if (time[1] > 59) time[1] = 59;  // Bounds checking
                break;
            case 2:
                time[2] = stoi(tokens.at(i));
                if (time[2] > 59) time[2] = 59;  // Bounds checking
                break;
            }
        }
    }

// Increases time according to type provided, while also handling overflow
void increment_time(vector<int>& time, Period period) {
    switch (period) {
        case HOUR:
            if (time[0] == 24) {
                time[0] = 1;
            }
            else time[0] += 1;
            break;
        case MINUTE:
            if (time[1] == 59) {
                time[1] = 0;
                time[0] += 1;
            }
            else time[1] += 1;
            break;
        case SECOND:
            if (time[2] == 59) {
                time[2] = 0;
                time[1] += 1;               
            }
            else time[2] += 1;
            
            // Handle cascade (if minutes happen to be 59 at the same time as seconds)
            if (time[1] == 60) {
                time[1] = 0;
                time[0] += 1;
                }

            if (time[0] == 25) {
                time[0] = 1;
            }
            break;
    }
}


// Prints the 12 and 24 hour clocks alongside each other
void print_time(vector<int>& time) {
    
    const char* clock_header = R"(
**************************      **************************
*      12-Hour Clock     *      *      24-Hour Clock     *
)";

    const char* clock_footer = R"(
**************************      **************************
)";

    // Handle special case conversion of 12-hour clock
    hour = time[0];
    if (hour > 12) hour = abs(hour - 12);

    // Expressions here determine when to add "0" to a string after conversion, which is when the integer is less than ten.
    string twenty_four_hours = ((time[0] < 10) ? ("0" + to_string(time[0])) : to_string(time[0]));
    string twelve_hours = ((hour < 10) ? ("0" + to_string(hour)) : to_string(hour));
    string minutes = ((time[1] < 10) ? ("0" + to_string(time[1])) : to_string(time[1]));
    string seconds = ((time[2] < 10) ? ("0" + to_string(time[2])) : to_string(time[2]));

    // Format the two different times
    string twelve_time = twelve_hours + ":" + minutes + ":" + seconds + " " + (time[0] < 12 ? "AM" : "PM");
    string twenty_four_time = twenty_four_hours + ":" + minutes + ":" + seconds;

    // Combine into final output
    cout << clock_header;
    cout << "*       " << twelve_time << "      *";
    cout << "      ";
    cout << "*        " << twenty_four_time << "        *";
    cout << clock_footer << endl;
}

// Displays the user menu
void show_menu() {
    
    const char* menu = R"(
                **************************
                * 1 -- Add One Hour      *
                * 2 -- Add One Minute    *
                * 3 -- Add One Second    *
                * 4 -- Exit Program      *
                **************************
)";

    cout << menu << endl;
}

int main()
{

initialize_time(time_clock);

while (quit != true) {
    print_time(time_clock);
    show_menu();
    
    cout << "Menu Choice: ";
    cin >> menu_choice;

    // Handles non-numeric input
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Invalid menu choice! Valid choices are between 1 through 4." << endl;
        cin >> menu_choice;
        }

    switch (menu_choice) {
        case 1:
            increment_time(time_clock, Period::HOUR);
            break;
        case 2:
            increment_time(time_clock, Period::MINUTE);
            break;
        case 3:
            increment_time(time_clock, Period::SECOND);
            break;
        case 4:
            quit = true;
            break;
        default:
            cout << "Invalid menu choice! Valid choices are between 1 through 4." << endl;
            break;
    }
}


return 0;
}