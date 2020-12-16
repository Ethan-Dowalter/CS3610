/**
 *        @file: main.cc
 *      @author: Ethan Dowalter
 *        @date: September 8, 2020
 *       @brief: Prime number finder
 */

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;


/// Function that searches through a vector for a target value, returns true if target is found
bool search(vector <int> list, int target);

/// Displays elements of a vector
void display(vector <int> list);



int main(int argc,char* argv[]){
    /// Check for correct input
    if (argc < 2)
    {
        cout << "Missing argument" << endl;
    }
    else if (argc > 2)
    {
        cout << "Too many arguments" << endl;
    }
    
    /// Generate array of all whole numbers from [2,n], where n is the input
    size_t search_limit = stoi(argv[1]);        //user input that is the maximum search value
    vector <int> num_list;                      //list of all whole numbers from [2,n]
    for (size_t i = 2; i <= search_limit; i++)
    {
        num_list.push_back(i);
    }
    
    /// Generate the list of prime numbers using the Sieve of Eratosthenes, by first creating a list of all composite numbers.
    vector <int> prime_list;                    //list of all primes from [2,n]
    vector <int> composite_list;                //list of all composite numbers from [2,n]

    for (size_t i = 2; i <= floor(sqrt(search_limit)); i++)
    {
        if (search(composite_list, i) == false)                 //check if i is already in composite_list, if not then it must be a prime number
        {
            for (size_t k = 2 * i - 2; k < search_limit - 1; k+=i)      //go through all multiples of i until the search_limit
            {
                if (search(composite_list, num_list.at(k)) == false)    //make sure not to add numbers that are already in composite_list
                {
                    composite_list.push_back(num_list.at(k));
                }
            } 
        }
    }

    /// The remaining numbers not in composite_list are therefore prime, and can be added to prime_list
    for (size_t i = 2; i < search_limit; i++)
    {
        if (search(composite_list, i) == false)
        {
            prime_list.push_back(i);
        }
    }

    /// Display the results
    cout << "Prime: [";
    display(prime_list);
    cout << ']' << endl;

    cout << "Composite: [";
    display(composite_list);
    cout << ']' << endl;
            
    return 0;
}



bool search(vector <int> list, int target){
    for (size_t i = 0; i < list.size(); i++)
    {
        if (target == list.at(i))
        {
            return true;
        }
    }
    
    return false;
}

void display(vector <int> list){
    for (size_t i = 0; i < list.size() - 1; i++)
    {
        cout << list.at(i) << ", ";
    }
    cout << list.at(list.size() - 1);
}