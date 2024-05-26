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
    std::string word;
    
    std::copy(std::istream_iterator<std::string>(stopwords),
              std::istream_iterator<std::string>(),
              std::inserter(stopwords_set, stopwords_set.end()));

    std::set<std::string> lowercase_stopwords_set;
    std::transform(stopwords_set.begin(), stopwords_set.end(),
                   std::inserter(lowercase_stopwords_set, lowercase_stopwords_set.end()),
                   [](const std::string& s) { return to_lowercase(s); });

    return lowercase_stopwords_set;
}

std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    std::map<std::string, int> word_counts;
    std::string word;

    std::vector<std::string> words;
    std::copy(std::istream_iterator<std::string>(document),
              std::istream_iterator<std::string>(),
              std::back_inserter(words));

    for (auto& w : words) {
        w = to_lowercase(w);
        if (stopwords.find(w) == stopwords.end()) {
            ++word_counts[w];
        }
    }

    return word_counts;
}

// Function to output word counts to an output stream
void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << " " << count << "\n";
    }
}
