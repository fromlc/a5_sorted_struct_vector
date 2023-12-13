//------------------------------------------------------------------------------
// a5_sorted_struct_vector.cpp
// 
// -reads data from file mlb_pitchers.csv into a vector of Pitcher structs
// -each data line contains a MLB pitcher's name and number of career wins
// -sorts the vector elements with sort() using comparison function
// -displays all elements of the sorted vector
//------------------------------------------------------------------------------
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//------------------------------------------------------------------------------
// debug mode toggle
//------------------------------------------------------------------------------
//#define _LCDEBUG

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
// sort() custom comparison function
//------------------------------------------------------------------------------
bool compare_pitchers(Pitcher& p1, Pitcher& p2) {

    return (p1.wins < p2.wins);
}

//------------------------------------------------------------------------------
// local functions
//------------------------------------------------------------------------------
void open_datafile(ifstream&);
void read_pitcher_data(ifstream&, vector<Pitcher>&);
// inline function does not generate an actual call so no reference needed
inline void display_pitcher_vector(vector<Pitcher>&);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    ifstream myfile;
    open_datafile(myfile);

    vector<Pitcher> vps { };
    read_pitcher_data(myfile, vps);

    myfile.close();

    cout << "\nVector before sort\n\n";
    display_pitcher_vector(vps);

    // sort the vector of Pitchers using custom comparison function
    sort(vps.begin(), vps.end(), compare_pitchers);

    cout << "\nSorted vector\n\n";
    display_pitcher_vector(vps);

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

//------------------------------------------------------------------------------
// read file data into passed vector
//------------------------------------------------------------------------------
void read_pitcher_data(ifstream& inf, vector<Pitcher>& vp) {

    string pitcher_line;
    while (getline(inf, pitcher_line)) {

        // get index of first comma in file data line
        size_t comma_index = pitcher_line.find(',');

        // set up vector element with initialization list

        Pitcher p {
        // text before comma goes in struct name field as string
            pitcher_line.substr(0, comma_index),
        // text after comma goes in struct wins field as int
            stoi(pitcher_line.substr(comma_index + 1))
        };

#ifdef _LCDEBUG
        // display file data with struct data for debug
        cout << pitcher_line << '\n';
        cout << p.name << ' ' << p.wins << "\n\n";
#endif

        // append a copy of p to vector
        vp.push_back(p);
    }

}

//------------------------------------------------------------------------------
// display vector elements
//------------------------------------------------------------------------------
inline void display_pitcher_vector(vector<Pitcher>& vp) {

    for (Pitcher& p_element : vp) {

        cout << p_element.name << ' ' << p_element.wins << '\n';
    }
}

