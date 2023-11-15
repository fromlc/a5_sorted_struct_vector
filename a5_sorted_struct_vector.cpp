//------------------------------------------------------------------------------
// a6_sorted_struct_vector.cpp
// 
// -reads data from file mlb_pitchers.csv into a vector of structs
// -each data line contains a MLB pitcher's
//       name,
//       number of wins,
//       number of losses, and
//       career ERA
// 
//      ERA is how many runs a pitcher allows per nine innings.
//      A lower ERA is better.
// 
// -sorts the vector elements with sort()
// -display all elements of the sorted vector.
//------------------------------------------------------------------------------
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// debug mode toggle
//------------------------------------------------------------------------------
#define _LCDEBUG

//------------------------------------------------------------------------------
// input file
//------------------------------------------------------------------------------
namespace f {

    const string INPUT_FILE_NAME = "mlb_pitchers.csv";
    constexpr int INPUT_FILE_OPEN_ERROR = 1;
}

//------------------------------------------------------------------------------
// data structures
//------------------------------------------------------------------------------
struct Pitcher {
    
    string name;
    int wins;
};

//------------------------------------------------------------------------------
// sort() comparison function
//------------------------------------------------------------------------------
bool compare_pitchers(Pitcher& p1, Pitcher& p2) {

    return (p1.wins < p2.wins);
}

//------------------------------------------------------------------------------
// local functions
//------------------------------------------------------------------------------
void open_datafile(ifstream&);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    ifstream myfile;
    open_datafile(myfile);

    vector<Pitcher> vps { };

    cout << '\n' << "Vector before sort\n\n";

    // read file data into vector
    while (true) {

        string pitcher_line;
        getline(myfile, pitcher_line);

        // check for file read error or end of file
        if (!myfile.good()) {
            break;
        }

        // get index of first comma in file data line
        size_t comma_index = pitcher_line.find(',');

        // set up vector element with initialization list

        Pitcher p { 
        // text before comma goes in struct name field
            pitcher_line.substr(0, comma_index),
        // text after comma goes in struct wins field as int
             stoi(pitcher_line.substr(comma_index + 1))
        // stoi() is string to int library function
        };

        // display file data with struct data for debug
#ifdef _LCDEBUG
        cout << pitcher_line << '\n';
#endif
        cout << p.name << ' ' << p.wins << "\n\n";

        // append a copy of p to vector
        vps.push_back(p);
    }

    // close your data file right after you're done with it
    myfile.close();

    // sort the vector of Pitchers using custom comparison function
    std::sort(vps.begin(), vps.end(), compare_pitchers);

    cout << "Sorted vector\n\n";

    // use reference to prevent element copy
    for (Pitcher& p_element : vps) {

        cout << p_element.name << ' ' << p_element.wins << '\n';
    }

    return 0;
}

//------------------------------------------------------------------------------
// -opens input file f::INPUT_FILE_NAME
// -sets ifstream reference parameter for caller's use
//------------------------------------------------------------------------------
void open_datafile(ifstream& fdata) {

    fdata.open(f::INPUT_FILE_NAME);

    if (!fdata.is_open()) {

        cout << "Unable to open file";
        exit(f::INPUT_FILE_OPEN_ERROR);
    }
}

