//
// Created by iagoweng on 21.09.23.
//
/**************************************************************************************************
*
* \file Simpson.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the empty functions to perform the following operations on the Simpson characters:
*       1. Print all characters to the screen
*       2. Randomize their order ('r')
*       3. Find the youngest person ('y')
*       4. Order them by first name ('f')
*       5. Order them by last name while preserving the order between equal elements ('l')
*       6. Order them by age while preserving the order between equal elements ('a')
*       7. Put all Simpsons first without affecting the general order of characters ('s')
*       8. Compute the total age of all characters ('t')
*       9. Put the last character first, without changing the order of the others ('0')
*       10. Determine the fourth oldest character as quickly as possible ('4')
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <random>
#include <string>
#include <vector>


struct Person
{
    std::string firstname;
    std::string lastname;
    int age;
};

std::ostream& operator<<( std::ostream& os, Person const& person )
{
    return os << std::setw(11) << std::left  << person.firstname
              << std::setw(10) << std::left  << person.lastname
              << std::setw(3)  << std::right << person.age;
}

struct IsYounger
{
    bool operator()(const Person& a, const Person& b) const
    {
        return a.age < b.age;
    }
};


template< typename Table >
void print( const Table& table )
{
    // TODO: Print all characters to the screen
    for( const auto& p : table ){
        std::cout << p << '\n';
    }
//    std::for_each(std::begin(table), std::end(table), [](const Person& p){std::cout << p << "\n";});
}
//------------------------------------------------------------------------------
template< typename Table >
void random_order( Table& table )
{
    // TODO: Randomize their order ('r')
    std::shuffle( table.begin(), table.end(), std::random_device{} );
}

template< typename Table >
void find_youngest( const Table& table )
{
    // TODO: Find the youngest character ('y')
    const auto pos = std::min_element( std::begin(table), std::end(table), IsYounger{} );
    std::cout << "Youngest person = " << pos->firstname << " " << pos->lastname << "\n";
}

template< typename Table >
void order_by_firstname( Table& table )
{
    // TODO: Order them by first name ('f')
    std::sort(std::begin(table), std::end(table), [](const Person& a, const Person& b){
        return a.firstname < b.firstname;
    } );
}

template< typename Table >
void order_by_lastname( Table& table )
{
    // TODO: Order them by last name while preserving the order between equal elements ('l')
    std::stable_sort(std::begin(table), std::end(table), [](const Person& a, const Person& b){
        return a.lastname < b.lastname;
    } );
}

template< typename Table >
void order_by_age( Table& table )
{
    // TODO: Order them by age while preserving the order between equal elements ('a')
    std::stable_sort(std::begin(table), std::end(table), IsYounger{});
}

template< typename Table >
void simpsons_first( Table& table )
{
    // TODO: Put all Simpsons first without affecting the general order of characters ('s')
    std::stable_partition(std::begin(table), std::end(table), [](const Person& a){
        return a.lastname=="Simpson";
    });
}

template< typename Table >
void compute_total_age( const Table& table )
{
    // TODO: Compute the total age of all characters ('t')

    const int age = std::accumulate(std::begin(table), std::end(table), int{0}, [](int age, const Person& p){
        return age + p.age;
    });

    // Alternativ:
    //const int age =
    //   [&table](){
    //      int age{};
    //    for (const Person& p : table){
    //      age+=p.age;
    //      }
    //      return age;
    //    }(); //Immediately Invoked Lambda Expression (IILE)

    std::cout << "Total age = " << age << "\n";
}

template< typename Table >
void last_to_first( Table& table )
{
    // TODO: Put the last character first, without changing the order of the others ('0').
    std::rotate(std::begin(table), std::end(table)-1, std::end(table));
    // std::end(table)-1, weil das letzte Element verschoben werden soll, deswegen wird bis zum vorletzten Element beibehalten
    // Alternativ: std::prev(std::end(table))
}

template< typename Table >
void fourth_oldest( Table& table )
{
    // TODO: Determine the fourth oldest character as quickly as possible ('4')
    //       Note that you are allowed to change the order of characters.
    std::nth_element( std::begin(table), std::begin(table)+3, std::end(table),
                      []( const Person& a, const Person& b ) {
                          return b.age < a.age;
                      } );
}




int main()
{
    std::vector<Person> table =
            { Person{ "Homer",      "Simpson",    38 }
                    , Person{ "Marge",      "Simpson",    34 }
                    , Person{ "Bart",       "Simpson",    10 }
                    , Person{ "Lisa",       "Simpson",     8 }
                    , Person{ "Maggie",     "Simpson",     1 }
                    , Person{ "Hans",       "Moleman",    33 }
                    , Person{ "Ralph",      "Wiggum",      8 }
                    , Person{ "Milhouse",   "Van Houten", 10 }
                    , Person{ "Ned",        "Flanders",   60 }
                    , Person{ "Jeff",       "Albertson",  45 }
                    , Person{ "Montgomery", "Burns",     104 } };

    char command;

    while( std::cout << "Enter command: " && std::cin >> command )
    {
        switch( command )
        {
            case 'r':
                random_order( table );
                break;

            case 'y':
                find_youngest( table );
                break;

            case 'f':
                order_by_firstname( table );
                break;

            case 'l':
                order_by_lastname( table );
                break;

            case 'a':
                order_by_age( table );
                break;

            case 's':
                simpsons_first( table );
                break;

            case 't':
                compute_total_age( table );
                break;

            case '0':
                last_to_first( table );
                break;

            case '4':
                fourth_oldest( table );
                break;

            default:
                return EXIT_SUCCESS;
        }

        print( table );
    }

    return EXIT_SUCCESS;
}