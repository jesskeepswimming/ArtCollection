#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;


// Practice Exercise 1:
//      Group #28
//      Kate Harvey, ID# 20829173
//      Jessica Lui, ID#


// define an artwork class:
class Artwork {
    string artist_name, title;
    unsigned int year_made; // unsigned means value always positive

public:
    // empty (default) constructor
    Artwork() : year_made(0) {} // constructor has the same name as the class

    // parametric constructor (with parameters)
    Artwork(string new_artist, string new_title, unsigned int new_year) :
        artist_name(new_artist), title(new_title), year_made(new_year) {}

    // overloaded operator ==
    bool operator==(const Artwork& rhs) const /* const ensures object is not modified */ {
        bool are_equal = artist_name == rhs.artist_name;
        are_equal = are_equal && title == rhs.title;
        are_equal = are_equal && year_made == rhs.year_made;
        return are_equal; // returns true iff all three statements are true
    }
};

// create SoldArtwork, a derived class of Artwork
class SoldArtwork : public Artwork { // colon indicates inheritance
    string customer_name, customer_address;
    double sale_amount;

public:
    // empty constructor
    SoldArtwork() : sale_amount(0) {}

    // parametric constructor
    SoldArtwork(string new_customer_name, string new_customer_address, double new_sale_amount, Artwork new_artwork) :
        customer_name(new_customer_name), customer_address(new_customer_address), sale_amount(new_sale_amount), Artwork(new_artwork)
            /*calling Artwork implicit constructor */ {}

    // overload operator
    bool operator==(const SoldArtwork& rhs) const {
        bool are_equal = customer_name == rhs.customer_name;
        are_equal = are_equal && customer_address == rhs.customer_address;
        are_equal = are_equal && sale_amount == rhs.sale_amount;
        are_equal = are_equal && static_cast<Artwork>(rhs) == static_cast<Artwork>(*this);
            // static_cast allows casting (using) objects as different types
            // in this case, the SoldArtwork is being treated as Artwork (upcasting)
            // works because every instance of SoldArtwork is also an instance of Artwork (does not work the other way)
        return are_equal;
    }
};

class ArtCollection {
    vector<Artwork> my_artwork; // collection of Artwork objects (private attribute)
    vector<SoldArtwork> my_sold_artwork; // collection of SoldArtwork objects (also private)

public:
    // method signature (specifies name and parameters only)

	bool insert_artwork(const Artwork& artwork_info) {
        bool has_duplicate = false;

        for(int entry = 0 ; entry < my_artwork.size() && !has_duplicate /* exits loop when has_duplicate */ ; entry++) {
            // loop through vector and compare all elements to passed element
            if(my_artwork[entry] == artwork_info) {
                has_duplicate = true;
            }
        }
        // if no duplicate is found, insert the given Artwork object into the Artwork vector:
        if(!has_duplicate) my_artwork.push_back(artwork_info); // push_back appends an element to the end of a vector

        // return true if insertion worked; else return false
        return !has_duplicate;
    }

    // place SoldArtwork into the corresponding vector:
    bool sell_artwork(const SoldArtwork& artwork_info) {
        bool have_sold = false;

        // find the corresponding Artwork object
        for(int entry = 0 ; entry < my_artwork.size() && !have_sold ; entry ++) {
            if(my_artwork[entry] == static_cast<Artwork>(artwork_info)) { // static cast SoldArtwork to Artwork (SoldArtwork inherits from Artwork)
                // move the current entry (to be removed) to the end of the list then pop_back to remove
                swap(my_artwork[entry], my_artwork[my_artwork.size() - 1]);
                my_artwork.pop_back();
                // add artwork_info to my_sold_artwork
                my_sold_artwork.push_back(artwork_info);
                have_sold = true;
            }
        }
        return have_sold;
    }

    bool operator==(const ArtCollection& rhs) const {
        // check if any two ArtCollection objects are the same
        bool are_equal = true;

        if(my_artwork.size() != rhs.my_artwork.size() || my_sold_artwork.size() != rhs.my_sold_artwork.size())
            are_equal = false;

        if(are_equal) {
            sort(my_artwork.begin(), my_artwork.end());
            sort(my_sold_artwork.begin(), my_sold_artwork.end());
            sort(rhs.my_artwork.begin(), rhs.my_artwork.end());
            sort(rhs.my_sold_artwork.begin(), rhs.my_sold_artwork.end());

            for(int entry = 0 ; entry < my_artwork.size() ; entry ++) {
                if(!(my_artwork[entry] == rhs.my_artwork[entry])) {
                    are_equal = false;
                }
            }

            for(int entry = 0 ; entry < my_sold_artwork.size() ; entry ++) {
                if(!(my_sold_artwork[entry] == rhs.my_sold_artwork[entry])) {
                    are_equal = false;
                }
            }
        }
        return are_equal;
    }

	vector<Artwork> get_art() {
		return my_artwork;
	}

    // external function that has direct access to private members of ArtCollection:
    friend ArtCollection operator+(const ArtCollection& lhs, const ArtCollection& rhs);
};

ArtCollection operator+(const ArtCollection& lhs, const ArtCollection& rhs) {
    // combine two ArtCollection objects

    ArtCollection target(lhs); // copy constructor
    for(unsigned int index = 0 ; index < rhs.my_artwork.size() ; index ++) {
        target.my_artwork.push_back(rhs.my_artwork[index]);
    }

    for(unsigned int index = 0 ; index < rhs.my_sold_artwork.size() ; index ++) {
        target.my_sold_artwork.push_back(rhs.my_sold_artwork[index]);
    }
    return target;
}

/*
// insert_artwork method definition (specifies actual code)
bool ArtCollection::insert_artwork(const Artwork& artwork_info) {
    // ArtCollection:: is the scope operator (what insert_artwork belongs to)
    return true;
}

// sell_artwork method definition
bool ArtCollection::sell_artwork(const SoldArtwork& artwork_info) {
    return true;
}
*/

class ArtCollectionTest {
    // write methods to check ArtCollection functionality
    vector<Artwork> test_values;

public:
    ArtCollectionTest() {
		Artwork a1("Van Gogh", "Starry Night", 1750), a2("Art", "Artist", 2021);
        test_values.push_back(a1);
        test_values.push_back(a2);
	}
	
	/*void setup() {
        Artwork a1("Van Gogh", "Starry Night", 1750), a2("Art", "Artist", 2021);
        test_values.push_back(a1);
        test_values.push_back(a2);
    }*/

    void test_insert_artwork() {
        ArtCollection test_collection;
        
        cout << (test_collection.insert_artwork(test_values[0]) ? 
            "Test insert_artwork passed" : "Test insert_artwork failed") << endl;
        assert(test_collection.get_art.size() == 1);
        cout << "Test my_artwork.size() passed" << endl;
        
        assert(test_collection.insert_artwork(test_values[1]));
        cout << "Test 2 for my_artwork.insert_artwork() passed" << endl;
        assert(test_collection.get_art.size() == 2);
        cout << "Test 2 my_artwork.size() passed" << endl;

        assert(!(test_collection.insert_artwork(test_values[2])));
        cout << "Test 3 for my_artwork.insert_artwork() passed" << endl;
        assert(test_collection.get_art.size() == 2);
        cout << "Test 3 my_artwork.size() passed" << endl;

    }
    
    void run() {
        //setup();
        test_insert_artwork();
        // tear_down();
    }
};


int main () {
    ArtCollectionTest newtest;
	newtest.run();
}