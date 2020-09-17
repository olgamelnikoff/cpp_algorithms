#ifndef DOG_H
#define DOG_H
#include <string>
#include <map>

using std::string;

class Dog
{
private:
   string name;
   string breed;
   string age;
   string gender;

public:
    Dog() = default;
    Dog(const Dog&) = default;
    Dog& operator=(const Dog&) = default;
    virtual ~Dog() = default;
    Dog(Dog&&) = default;
    Dog& operator=(Dog&&) = default;

    Dog(string, string, string, string);
    friend std::ostream& operator<<(std::ostream&, const Dog&);
    friend std::istream& operator>>(std::istream&, Dog&);
         
    std::string getBreed() const;
    std::string getName() const;
    std::string getAge() const;
    std::string getGender() const;
};
     
using DogMapDefault = std::multimap < std::string, Dog> ;

//Introducing a new multimap with the "greater" Compare function (for Task 3.4)
using DogMapDefaultReverse = std::multimap<std::string, Dog, std::greater<std::string>>;

//Insertion operator for the multimap with the default ("less") Compare funtion
std::ostream& operator<<(std::ostream& sout, const DogMapDefault& dogmap);

//Insertion operator for the multimap with the "greater" Compare funtion
std::ostream& operator<<(std::ostream& sout, const DogMapDefaultReverse& dogmap);

//A free function that removes all leading and trailing whitespaces in a supplied string (Task 3.1)
string trim(const string& str);

//Four functions that load a Dog Map from an input file (Tasks 3.2, 3.3 and 3.4)
void load_csvFile_Normal_Loop(DogMapDefault&, std::string);
void load_csvFile_Normal_Loop_Reverse_Order(DogMapDefaultReverse&, std::string);
void load_csvFile_For_Each(DogMapDefault&, std::string);
void load_csvFile_Transform(DogMapDefault&, std::string);

//A free function that returns all Dog objects in source having the same key_breed (Task 3.5)
DogMapDefault findBreedRange(DogMapDefault& source, const std::string& key_breed);

#endif /*DOG_H*/

