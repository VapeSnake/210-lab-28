//COMSC-210 | Lab 28 | Noel Mier-Luna
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void shuffle_trip(list<Goat> &trip); // Added new function prototypes for our new algorithm functions.
void reverse_trip(list<Goat> &trip);
void goat_birthday(list<Goat> &trip);
void find_goat_by_name(list<Goat> trip);
void copy_trip(list<Goat> trip, list<Goat> &copy);
void unique_trip(list<Goat> &trip);
void reset_trip(list<Goat> &trip);
void remove_goats_by_age(list<Goat> &trip, int age);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Shuffling goats.\n";
                shuffle_trip(trip);
                break;
                
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}
// Now adding 8 more features of <algorithm>
int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Shuffle goats\n"; // uses std::shuffle.
    cout << "[5] Reverse goats\n"; // uses std::reverse.
    cout << "[6] Goat Birthday (increment age)\n"; // uses std::for_each.
    cout << "[7] Find goat by name\n"; // uses std::find.
    cout << "[8] Copy list of goats\n"; // uses std::copy.
    cout << "[9] Make list unique (remove duplicates)\n"; // uses std::unique.
    cout << "[10] Reset trip (clear list)\n"; // uses std::clear.
    cout << "[11] Remove goats by age\n"; // uses std::remove and std::erase.
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void shuffle_trip(list<Goat> &trip) {
    vector<Goat> temp(trip.begin(), trip.end()); // Copy the list to a vector for shuffling since std::shuffle works with random access iterators.
    random_device random;
    mt19937 g(random()); // Initialize a random number generator.
    shuffle(temp.begin(), temp.end(), g);
    trip.assign(temp.begin(), temp.end());

    //display the shuffled trip
    for (const auto& goat : trip) {
        cout << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")\n";
    }
}