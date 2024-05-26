
#include "mapset.hpp"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cctype>
#include <fstream>

std::string to_lowercase(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

std::set<std::string> load_stopwords(std::istream& stopwords) {
    std::set<std::string> stopwords_set;
    std::ranges::istream_view<std::string> view{stopwords};

    std::ranges::for_each(view, [&](const std::string& w) {
        stopwords_set.insert(to_lowercase(w));
    });

    return stopwords_set;


std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::ranges::istream_view<std::string> view{document};

    std::ranges::for_each(view, [&](std::string w) {
        w = to_lowercase(w);
        if (stopwords.find(w) == stopwords.end()) {
            ++word_counts[w];
        }
    });

    return word_counts;

void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << "\n";
    }
}
