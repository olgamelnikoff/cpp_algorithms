#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <iterator>
#include <vector>
#include <set>
#include <functional>
#include <utility>
#include "Dog.h"

using std::cin;
using std::cout;
using std::endl;

/**
Determines if a character belongs to alphabet
@param ch The supplied character.
@return true if the supplied character is alphabetic; false if it is not
*/
bool is_alphabetic(char ch) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::size_t found = alphabet.find(ch);
    if (found == std::string::npos)
    {
        return false;
    }

    else { return true; }
}

/**
Determines if a phrase is a palindrome
@param ch The supplied phrase
@return true if the supplied character is alphabetic; false if it is not
*/
bool is_palindrome(std::string phrase) {
    std::string temp;

    //using "copy_if" algorithm to move only alphabetic characters to temp
    std::copy_if(phrase.begin(), phrase.end(), back_inserter(temp), is_alphabetic);

    //using "transform" algorithm to turn all the alphabetic characters to the lower case
    std::transform(temp.begin(), temp.end(), temp.begin(), [](char c) {return tolower(c);});

    size_t n = temp.length();
    size_t half = n / 2;

    std::string::iterator new_it = temp.begin();

    advance(new_it, n / 2);

    //using "equal" algorithm to compare the first half of the temp string
    //with its second half read reversely
    bool result = std::equal(temp.begin(), new_it, temp.rbegin());

    return result;
}

//a function testing if a phrase is a palindrome
void test_is_palindrome()
{
    std::string str_i = std::string("was it a car or A Cat I saW?");
    std::string str_u = std::string("was it A Car or a cat U saW?");
    std::cout << "the phrase \"" + str_i + "\" is " +
        (is_palindrome(str_i) ? "" : "not ") + "a palindrome\n";
    std::cout << "the phrase \"" + str_u + "\" is " +
        (is_palindrome(str_u) ? "" : "not ") + "a palindrome\n";
}

/**
A function template that finds the second largest element
@param Iterator start The iterator pointing to the first element in the range
Iterator finish The iterator pointing to the last element in the range
@return a pair that includes the second largest element in the range 
and the boolean showing if the second largest element exists
*/
template <class Iterator>
std::pair <Iterator, bool>
second_max(Iterator start, Iterator finish)
{
    //If the range is empty, return (finish - false)
    if (start == finish)
    {
        return std::make_pair(finish, false);
    }

    auto value = *start;
    bool equal = true;

    for (auto it = start; it != finish; ++it)
    {
        if (value != *it)
        {
            equal = false;
            break;
        }
    }

    //If all the values in the range are equal, return (start - false)
    if (equal)
    {
        return std::make_pair(start, false);
    }

    auto largest = start;
    auto second_largest = start;

    for (auto it = start; it != finish; ++it)
    {
        if (*largest < *it)
        {
            second_largest = largest;
            largest = it;
        }

        else if (*second_largest < *it && *largest > * it)
        {
            second_largest = it;
        }
    }
    //If the second largest element can be found, return this element + boolean "true"
    return std::make_pair(second_largest, true);
}

//a function testing second max
void test_second_max(std::vector<int> vec)
{
    // note: auto in the following statement is deduced as
    // std::pair<std::vector<int>::iterator, bool>
    auto retval = second_max(vec.begin(), vec.end());

    if (retval.second)
    {
        std::cout << "The second largest element in vec is "
            << *retval.first << std::endl;
    }
    else
    {
        if (retval.first == vec.end())
            cout << "List empty, no elements\n";
        else
            cout << "Container's elements are all equal to "
            << *retval.first << endl;
    }
}

/**
Counts strings of the supplied length in a vector using lambda function
@param vec The supplied vector
n the supplied length of a string
@return number of strings in vec that have length n
*/
int testCountStringsLambda(const std::vector<std::string>& vec, int n)
{
    //using the "count_if" algorithm with lambda function
    int count = count_if(vec.begin(), vec.end(), [n](std::string newString) {return (n == newString.length());});
    return count;
}

/**
Tests if the length of the supplied string equals to n
@param str The supplied string
n the supplied length
@return true if the supplied string has length n,
false if it does not
*/
bool countStringsFreeFun(const string& str, int n)
{
    return (str.length() == n);
}


/**
Counts strings of the supplied length in a vector 
using a free function countStringsFreeFun
@param vec The supplied vector
n the supplied length of a string
@return number of strings in vec that have length n
*/
int testCountStringsFreeFun(const std::vector<std::string>& vec, int n)
{
    using namespace std::placeholders;

    int count = count_if(vec.begin(), vec.end(), bind(countStringsFreeFun, _1, n));

    return count;

}

//A class to use as a class of the Functor below
struct stringCounter
{
    int n;
    stringCounter(int newN) : n(newN) {}
    bool operator () (std::string thisString)
    {
        if (n == thisString.length())
        {
            return true;
        }
        return false;
    }
};

/**
Counts strings of the supplied length in a vector
using a Functor of class stringCounter
@param vec The supplied vector
n the supplied length of a string
@return number of strings in vec that have length n
*/
int testCountStringsFunctor(const std::vector<std::string>& vec, int n)
{
    stringCounter countsStringsFunctor(n);
    int count = count_if(vec.begin(), vec.end(), countsStringsFunctor);
    return count;
}

/**
Defines a multiset object, copies strings into it 
and sorts these strings according to their lexicographic order
*/
void multisetUsingMyComparator()
{
    //Defining a class Comparator
    //that ensures sorting
    //strings lexicographically
    struct Comparator {

        bool operator () (std::string string_one, std::string string_two) const
        {
            if (string_one.length() == string_two.length())
            {
                return (string_one < string_two);
            }
            else if (string_one.length() < string_two.length()) {

                return true;
            }
            return false;
        }
    };

    std::multiset<std::string, Comparator> strSet; // an empty set

    // a set that uses the default std::less<int> to sort the set elements
    std::vector<std::string> vec{ "C", "BB", "A", "CC", "A", "B",
                                  "BB", "A", "D", "CC", "DDD", "AAA" };

    // copy the vector elements to our set.
    // We  must use a general (as oppsed to a front or back) inserter.

    std::copy(vec.begin(), vec.end(),                // source start and finish
        std::inserter(strSet, strSet.begin())); // destination start with
                                                // a general inserter

// create an ostream_iterator for writing to cout,
// using a space " " as a separator
    std::ostream_iterator<std::string> out(std::cout, " ");

    // output the set elements to cout separating them with a space
    std::copy(strSet.begin(), strSet.end(), out);
}

int main()
{

    // Problem 4:
    test_is_palindrome();
    cout << "\n";
    
    // Problem 5:
    std::vector<int> v1{  }; // zero elements
    test_second_max(v1);
    
    std::vector<int> v2{ 1, 1 }; // all elements equal
    test_second_max(v2);
    
    std::vector<int> v3{ 1, 1, 3, 3, 7, 7 }; // at least with two distict elements
    test_second_max(v3);
    cout << "\n";
    
    // Problem 6:
    std::vector<std::string> vecstr
    { "count_if", "Returns", "the", "number", "of", "elements", "in", "the",
       "range", "[first", "last)", "for", "which", "pred", "is", "true."
    };
    std::cout << testCountStringsLambda(vecstr, 5) << std::endl;
    std::cout << testCountStringsFreeFun(vecstr, 5) << endl;
    std::cout << testCountStringsFunctor(vecstr, 5) << std::endl;
    std::cout << "\n";
    
    // Problem 7:
    multisetUsingMyComparator();
    std::cout << "\n";

    
    //Task 3.1
    DogMapDefault dogMap;
    load_csvFile_Normal_Loop(dogMap, "C:\\Users\\vmeln\\Source\\Repos\\Asgt5_Task_1\\Asgt5_Task_1\\dogDB.csv");
    cout << dogMap << endl;
    
    //Task 3.2
    DogMapDefault dogMap2;
    load_csvFile_For_Each(dogMap2, "C:\\Users\\vmeln\\Source\\Repos\\Asgt5_Task_1\\Asgt5_Task_1\\dogDB.csv");
    cout << dogMap2 << endl;

    //Task 3.3
    DogMapDefault dogMap3;
    load_csvFile_Transform(dogMap3, "C:\\Users\\vmeln\\Source\\Repos\\Asgt5_Task_1\\Asgt5_Task_1\\dogDB.csv");
    cout << dogMap3 << endl;

    //Task 3.4
    DogMapDefaultReverse dogMap4;
    load_csvFile_Normal_Loop_Reverse_Order(dogMap4, "C:\\Users\\vmeln\\Source\\Repos\\Asgt5_Task_1\\Asgt5_Task_1\\dogDB.csv");
    cout << dogMap << endl;
    
    //Task 3.5
    DogMapDefault dogMap5;
    load_csvFile_Normal_Loop(dogMap5, "C:\\Users\\vmeln\\Source\\Repos\\Asgt5_Task_1\\Asgt5_Task_1\\dogDB2.csv");

    DogMapDefault breedRangeMap1 = findBreedRange(dogMap5, "Greyhound");
    cout << breedRangeMap1 << "----------" << endl;

    DogMapDefault breedRangeMap2 = findBreedRange(dogMap5, "Lakeland Terrier");
    cout << breedRangeMap2 << "----------" << endl;

    DogMapDefault breedRangeMap3 = findBreedRange(dogMap5, "Pug");
    cout << breedRangeMap3 << "----------" << endl;

    DogMapDefault breedRangeMap4 = findBreedRange(dogMap5, "Xyz");
    cout << breedRangeMap4 << "----------" << endl;

    //Testing "trim" method:
    string newString = trim("  Hello  ");
    cout << newString << endl;
}