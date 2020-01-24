#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//PURPOSE: represents an instance of Artwork or one piece of Artwork
class Artwork {
	string artist_name, title;
	unsigned int year_made;
public:
	// empty/default constructor
	Artwork() {
		year_made (0);
	} 
	
	// parametric constructor
	Artwork(string new_artist, string new_title, unsigned int new_year) {
		artist_name(new_artist), title(new_title), year_made(new_year); 
	}
		
	// overloaded operator==
	bool operator == (const Artwork& rhs) const { //ensure that the object is not modified
		bool are_equal = artist_name == rhs.artist_name;
		are_equal = are_equal && title == rhs.title;
		are_equal = are_equal && year_made == rhs.year_made;
		return are_equal;
	}
};



//PURPOSE: represents a Sold piece of Artwork
class SoldArtwork: public Artwork {
	string cust_name, cust_addr;
	double sale_amount;
	
public:
	//empty/default constructor
	SoldArtwork () {
		sale_amount(0);
	} 
	
	//parametric constructor
	SoldArtwork (string new_cust_name, string new_cust_adr, double new_sale_amount, Artwork new_artwork){ 
	    cust_name(new_cust_name), cust_addr(new_cust_addr), sale_amount(new_sale_amount), Artwork(new_artwork); /*calling Artwork constructor */ {}
	}	
	
	bool operator == (const SoldArtwork& rhs){
		bool are_equal = cust_name == rhs.cust_name;
		are_equal = are_equal && cust_addr == rhs.cust_addr;
		are_equal = are_equal && sale_amount == rhs.sale_amount;
		//following line calls the Artwork '==' fct since both objects are Artworks
		are_equal = are_equal && static_cast<Artwork>(rhs) == static_cast<Artwork>(*this);
		
		return are_equal;
	}
};

class ArtCollection {
    vector<Artwork> my_artwork;
    vector<SoldArtwork> my_sold_artwork;

public:

    bool insert_artwork(const Artwork& artwork_info) {
        // use bool to keep track of duplicate detection
        bool has_duplicate = false;
        // iterate through my_artwork to chack for duplicate values
        for (int entry = 0; entry < my_artwork.size(); ++entry) {
            if (my_artwork[entry] == artwork_info) {
                has_duplicate = true;
            }
        }           
        // insert given artwork into Artwork vector
        
        if (has_duplicate == false) {
            my_artwork.push_back(artwork_info);
        }
        
        return !has_duplicate; 
        
    }
    
    // facilitates a sake of Artwork and placement of SolidArtwork instance into corrosponding vector
    bool sell_artwork(const SoldArtwork& artwork_info) {
        bool have_sold = false;
        // iterate through my_artwork to find the Artwork that matches artwork_info
        for (int entry = 0; entry < my_artwork.size(); ++entry) {
            if (my_artwork[entry] == static_cast<Artwork>(artwork_info)) { 
            
                swap(my_artwork[entry], my_artwork[my_artwork.size()-1]);
                my_artwork.pop_back();
                my_sold_artwork.push_back(artwork_info);
                have_sold = true;
                
            }
        }
        
        return have_sold;
    }
    
    
    bool operator == (const ArtCollection& rhs) const { //ensure that the object is not modified	
		bool are_equal = *this.myArtwork  == rhs.myArtwork;
		are_equal = are_equal && *this.my_sold_artwork == rhs.myArtwork;
		//following line calls the Artwork '==' fct since both objects are Artworks
		are_equal = are_equal && static_cast<Artwork>(rhs) == static_cast<Artwork>(*this);
		return ;
	}
	
	
	bool operator + (const ArtCollection& rhs) const { //ensure that the object is not modified	
		return ;
	}
	
	
};


// for methods defined outside the class, we need scope operator in front of their namw
bool ArtCollection::insert 
    


bool ArtCollection::insert_artwork(const Artwork& artwork_info {
    return true;
}

bool ArtCollection::sell_artwork(const SoldArtwork& artwork_info {
    return true;

}

void igor() {

}

int main () {
	Artwork a1, a2;
	SoldArtwork s1, s2; 
	a1 = sa1;
}

