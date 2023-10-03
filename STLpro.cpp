/**************************************************************************************************
*
* \file STLpro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Solve the following tasks on a vector of integers by means of STL algorithms:
*       - Compute the product of all elements in the vector
*       - Extract all numbers <= 5 from the vector
*       - Compute the (numerical) length of the vector
*       - Compute the ratios v[i+1]/v[i] for all elements v[i] in v
*       - Move the range [v[3],v[5]] to the beginning of the vector
*
**************************************************************************************************/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>


using Ints    = std::vector<int>;
using Doubles = std::vector<double>;


template< typename T >
void printVector( std::vector<T> const& numbers )
{
    std::cout << "(";
    std::for_each( std::begin(numbers), std::end(numbers), []( T value ){ std::cout << " " << value; } );
    std::cout << " )";
}


int computeProduct( Ints const& ints )
{
    int result = 0;
    result = std::accumulate(std::begin(ints), std::end(ints), 1, std::multiplies<>());
    return result;
}


Ints extractInts( Ints const& ints )
{
    Ints to_vector;
    std::copy_if(std::begin(ints), std::end(ints), std::back_inserter(to_vector), [](int x){return x <= 5;});
    return to_vector;
}


double computeLength( Ints const& ints )
{
    Ints d = ints;
    std::for_each(d.begin(), d.end(), [](int& x) { x = x * x; });
    double p = std::sqrt(std::accumulate(d.begin(), d.end(), 0));
    return p;
}


Doubles computeRatios( Ints const& ints )
{
    // ints.size() - 1U calculates the size of the ints collection minus 1 and casts it to an unsigned integer (U).
    // 0.0 initializes all elements of the ratios object to 0.0. It seems like ratios is a collection of doubles.
    Doubles ratios(ints.size() - 1U, 0.0);
    std::transform(std::begin(ints) + 1U, std::end(ints),
                   std::begin(ints),
                   std::begin(ratios),
                   [](double liczebnik, double mianownik){return liczebnik/mianownik;});
    return ratios;
}


Ints moveRange( Ints const& ints )
{
    Ints result (ints);
    std::rotate(std::begin(result), std::begin(result) + 3U, std::end(result));
//    std::move(std::begin(ints) + 3U, std::end(ints) + 4U, std::begin(result));
    return result;
}


int main()
{
    Ints ints{ 1, 5, 2, 8, 7, 10, 4 };

    // Compute the product of all elements in v
    {
        std::cout << " Product of all elements: expected = 22400, actual = ";
        int const product = computeProduct( ints );
        std::cout << product << "\n";
    }

    // Extract all numbers <= 5 from the vector
    {
        std::cout << " All values <= 5: expected = ( 1 5 2 4 ), actual = ";
        printVector( extractInts( ints ) );
        std::cout << "\n";
    }

    // Compute the numerical length of the vector
    {
        std::cout << " Numerical length of the vector: expected = 16.0935, actual = ";
        double const length = computeLength( ints );
        std::cout << length << "\n";
    }

    // Compute the ratios v[i+1]/v[i] for all elements v[i] in v
    {
        std::cout << " Ratios: expected = ( 5 0.4 4 0.875 1.42857 0.4 ), actual = ";
        printVector( computeRatios( ints ) );
        std::cout << "\n";
    }

    // Move the range [v[3],v[5]] to the beginning of the vector
    {
        std::cout << " Moved range: expected = ( 8 7 10 4 1 5 2 ), actual = ";
        printVector( moveRange( ints ) );
        std::cout << "\n";
    }
}