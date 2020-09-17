#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstddef>
#include <stdexcept>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include <iterator>
#include "Dog.h"

using std::stringstream;
using std::string;
using std::size_t;
using std::runtime_error;
using std::cin;
using std::cout;
using std::endl;

//Constructor
Dog:: Dog(string n, string b, string a, string g) :
    name(n), breed(b), age(a), gender(g) { }

//Getters
std::string Dog:: getBreed() const { return breed; }
std::string Dog:: getName() const { return name; }
std::string Dog:: getAge() const { return age; }
std::string Dog:: getGender() const { return gender; }

//Insertion and extraction operators for the "Dog" objects
std::ostream& operator<<(std::ostream& sout, const Dog& dog) {
    sout << dog.name << ", " << dog.breed << ", " << dog.age << ", " << dog.gender;
    return sout;
}
std::istream& operator>>(std::istream& sin, Dog& dog) {
    std::getline(sin, dog.name, ','); dog.name = trim(dog.name);
    std::getline(sin, dog.breed, ','); dog.breed = trim(dog.breed);
    std::getline(sin, dog.age, ','); dog.age = trim(dog.age);
    std::getline(sin, dog.gender); dog.gender = trim(dog.gender);
    return sin;                                         
}

//Insertion operators for dogmaps:
std::ostream& operator<<(std::ostream& sout, const DogMapDefault& dogmap) {
    for (const auto& dog : dogmap) { // C++14
        std::cout << std::setw(25) << dog.first << " --> " << dog.second << std::endl; 
    }
    //for (const auto& <breed, dog> : dogmap) { // C++17
    //    std::cout << std::setw(25) << breed << " --> " << dog << std::endl;
    //}
    return sout;
}

std::ostream& operator<<(std::ostream& sout, const DogMapDefaultReverse& dogmap) {

    for (const auto& dog : dogmap) { // C++14
        std::cout << std::setw(25) << dog.first << " --> " << dog.second << std::endl;
    }
    //for (const auto& <breed, dog> : dogmap) { // C++17
    //    std::cout << std::setw(25) << breed << " --> " << dog << std::endl;
    //}
    return sout;
}

/**
Removes any leading and trailing whitespaces in a supplied string.
@param str The supplied string.
@return A copy of the supplied string, with any leading and trailing whitespace removed.
*/
string trim(const string& str)
{  
    string str_copy(str);

    //Create a string of whitespaces
    string whitespaces = " \t,\v,\f,\n,\r";

    //Create a variable to extract leading whitespaces using method "find_first_not_of"
    size_t found_leading = str_copy.find_first_not_of(whitespaces);

    //Erase the found leading whitespaces
    if (found_leading != 0)
    {
        str_copy.erase(0, found_leading);
    }

    //Create a variable to extract trailing whitespaces using method "find_last_not_of"
    size_t found_trailing = str_copy.find_last_not_of(whitespaces);

    //Erase the found trailing whitespaces
    if (found_trailing!= std::string::npos)
    {
        str_copy.erase(found_trailing + 1);
    }
    else
    {
        str_copy.clear();
    }
    return str_copy;
}

/**
Loads a dogMap from an Input file
@param dog_map The dog map to be filled out;
filename The file to read the dogMap from
*/
void load_csvFile_Normal_Loop(DogMapDefault& dog_map, std::string filename) {
    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    std::string line;
    while (std::getline(input_file_stream, line)) { // read a line
        std::stringstream my_line_stream(line); // turn the line into an input stream
        Dog dog{};
        my_line_stream >> dog;                  // initialize dog using Dog's operator>>
        dog_map.emplace(dog.getBreed(), dog);   // insert dog into dog_map
    }
    input_file_stream.close(); // Close file
}

/**
Loads a dogMap sorted in a reverse order from an Input file
@param dog_map The dog map to be filled out;
filename The file to read the dogMap from
*/
void load_csvFile_Normal_Loop_Reverse_Order(DogMapDefaultReverse& dog_map, std::string filename) {
    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    std::string line;
    while (std::getline(input_file_stream, line)) {        // read a line
        std::stringstream my_line_stream(line); // turn the line into an input stream
        Dog dog{};
        my_line_stream >> dog;                  // initialize dog using Dog's operator>>
        dog_map.emplace(dog.getBreed(), dog);   // insert dog into dog_map
    }
    input_file_stream.close(); // Close file

}

/**
Loads a dogMap from an Input file
@param dog_map The dog map to be filled out;
filename The file to read the dogMap from
*/
void load_csvFile_For_Each(DogMapDefault& dog_map, std::string filename) {
    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    //Get start of input stream and end of input stream iterators
    std::istream_iterator<Dog>start{ input_file_stream };
    std::istream_iterator<Dog>end{};

    //Copy Dog elements from input to dog_map using the 'for_each' algorithm
    for_each
    (start, end, [&dog_map](Dog dog) {return dog_map.emplace(dog.getBreed(), dog);});
    input_file_stream.close(); // Close file
}

/**
Loads a dogMap from an Input file
@param dog_map The dog map to be filled out;
filename The file to read the dogMap from
*/
void load_csvFile_Transform(DogMapDefault& dog_map, std::string filename) {
    std::ifstream input_file_stream(filename); // Create an input file stream
    if (!input_file_stream.is_open()) {        // Check that the file is open
        cout << "Could not open file " + filename << endl;
        throw std::runtime_error("Could not open file " + filename);
    }
    //Get start of input stream and end of input stream iterators
    std::istream_iterator<Dog>input_stream_begin{ input_file_stream };
    std::istream_iterator<Dog>input_stream_end{};

    //Copy Dog elements from input to dog_map using the 'transform' algorithm
    transform(input_stream_begin, input_stream_end, std::inserter(dog_map, dog_map.begin()),
        [](Dog dog) {return std::pair <std::string, Dog>(dog.getBreed(), dog);});
    input_file_stream.close(); // Close file
}

/**
Outputs all the records corresponding to the specified breed
@param source The source dog map; 
key_breed The string indicating the breed constituting the key of the record
@return A new dog map that contains all Dog objects in source
having the same key_breed.
*/

DogMapDefault findBreedRange(DogMapDefault& source, const std::string& key_breed)
{
    std::multimap <std::string, Dog>::iterator first = source.begin();
    std::multimap <std::string, Dog>::iterator last = source.end();

    //Create a supplemental vector to store all the keys from source
    std::vector<string> myvector;

    //Filling out the vector
    for (std::multimap<string, Dog>::iterator it = first; it != last; ++it)
    {
        myvector.push_back((*it).first);
    }

    //Applying the "equal_range" algorithm to find out the range
    //of the key_breed
    std::pair< std::vector <string>::iterator, std::vector <string>::iterator> bounds;
    bounds = std::equal_range(myvector.begin(), myvector.end(), key_breed);

    //first and last positions of the key_breed range
    int first_position = bounds.first - myvector.begin();
    int last_position = bounds.second - myvector.begin();

    //Projecting the key_breed range of the vector to the 
    //multimap
    std::multimap <std::string, Dog>::iterator new_first = source.begin();

    //First position of the key_breed range
    advance(new_first, first_position);

    std::multimap <std::string, Dog>::iterator new_last = source.begin();
    
    //Last position of the key_breed range
    advance(new_last, last_position);

    //Creating a new map using the key_breed range
    DogMapDefault target(new_first, new_last);

    //Outputting the new map
    return target;
}

