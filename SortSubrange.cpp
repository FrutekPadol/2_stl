//
// Created by iagoweng on 03.10.23.
//
/**************************************************************************************************
*
* \file SortSubrange.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'sort_subrange' algorithm in the following example. The algorithm should
*       take four iterators, which specify the total range of elements and the subrange to be
*       sorted.
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>


// TODO: Implement the 'sort_subrange()' algorithm
template<typename Iterator, typename unary>
void sort_subrange(Iterator first, Iterator last, Iterator range_start, Iterator range_end, unary p)
{
    // Check if range is nonzero
    if (range_start == range_end) return;
    // Check if sub range begins at the beginning
    if (first != range_start)
    {
        std::nth_element(first, range_start, last, p);
    }
    std::partial_sort(range_start, range_end, last, p);

}
template<typename Iterator>
void sort_subrange(Iterator first, Iterator last, Iterator range_start, Iterator range_end)
{
    sort_subrange(first, last, range_start, range_end, std::less<>());
}

int main()
{

    std::vector<int> v{ 3, 2, 11, 5, 4, 6, 12, 7, 8, 9, 1, 10 };

    // Sort the subrange [begin+2,begin+6) within the range [begin,end) in ascending order
    sort_subrange( v.begin(), v.end(), v.begin()+2, v.begin()+6 );

    std::cout << "\n (";
    for( int i : v )
       std::cout << ' ' << i;
    std::cout << " )\n\n";

    // Sort the subrange [begin+3,begin+7) within the range [begin,end) in descending order
    sort_subrange( v.begin(), v.end(), v.begin()+3, v.begin()+7, std::greater<>() );

    std::cout << "\n (";
    for( int i : v )
       std::cout << ' ' << i;
    std::cout << " )\n\n";


    return EXIT_SUCCESS;
}