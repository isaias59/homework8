#include "process_numbers.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <ranges>
#include <fstream>
#include <iostream>


void split_odd_even(std::istream& numbers, std::ostream& odds, std::ostream& evens) {
    std::vector<int> num_list((std::istream_iterator<int>(numbers)), std::istream_iterator<int>());

    std::ranges::sort(num_list);

    // Copy odd numbers to odds stream
    std::copy_if(num_list.begin(), num_list.end(), std::ostream_iterator<int>(odds, " "),
        [](int n) { return n % 2 != 0; });
    odds << "\n";

    // Copy even numbers to evens stream
    std::copy_if(num_list.begin(), num_list.end(), std::ostream_iterator<int>(evens, "\n"),
        [](int n) { return n % 2 == 0; });
}
