
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <cctype>
#include <iterator>

using namespace std;


const unordered_set<string> stopWords = {
    "a", "an", "the", "and", "or", "but",
    "if", "as", "at", "by", "for", "from",
    "in", "into", "of", "on", "to", "with",
    "is", "am", "are", "was", "were", "be",
    "been", "being", "have", "has", "had",
    "do", "does", "did", "can", "could",
    "will", "would", "should", "may", "might",
    "this", "that", "these", "those", "it",
    "they", "them", "their", "he", "him", "his",
    "she", "her", "we", "us", "our", "you",
    "your", "i", "me", "my", "who", "what",
    "when", "where", "which", "how", "all",
    "any", "some", "no", "not", "more", "most",
    "other", "only", "also", "very", "just",
    "there", "here", "because", "while", "than"
};


map<string, vector<int>> buildInvertedIndex(istream& input) {

    map<string, vector<int>> invertedIndex;

    string document(
        (istreambuf_iterator<char>(input)),
        istreambuf_iterator<char>()
    );

    string word;
    int position = 0;

    for (size_t i = 0; i < document.length(); i++) {

        char ch = document[i];

        if (isalpha(static_cast<unsigned char>(ch))) {

            word += static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }

        else if (ch == '-' && !word.empty() &&
                 i + 1 < document.length() &&
                 isalpha(static_cast<unsigned char>(document[i + 1]))) {

            word += '-';
        }

        else if (!word.empty()) {

            if (stopWords.find(word) == stopWords.end()) {
                invertedIndex[word].push_back(position);
            }

            position++;
            word.clear();
        }
    }

    if (!word.empty()) {

        if (stopWords.find(word) == stopWords.end()) {
            invertedIndex[word].push_back(position);
        }
    }

    return invertedIndex;
}

void saveInvertedIndex(
    const map<string, vector<int>>& invertedIndex,
    const string& filename
) {

    ofstream output(filename);

    if (!output.is_open()) {
        cerr << "Error: Could not create output file." << endl;
        return;
    }

    output << "{\n";

    for (auto it = invertedIndex.begin();
         it != invertedIndex.end(); ++it) {

        output << "  \"" << it->first << "\": [";

        for (size_t i = 0; i < it->second.size(); i++) {

            output << it->second[i];

            if (i < it->second.size() - 1) {
                output << ", ";
            }
        }

        output << "]";

        if (next(it) != invertedIndex.end()) {
            output << ",";
        }

        output << "\n";
    }

    output << "}\n";
    output.close();

    cout << "Inverted index successfully saved to "
         << filename << endl;
}

#ifndef INVERTED_INDEX_BENCHMARK

int main() {

    ifstream input("input.txt");

    if (!input.is_open()) {
        cerr << "Error: Could not open input.txt" << endl;
        return 1;
    }

    map<string, vector<int>> invertedIndex =
        buildInvertedIndex(input);

    input.close();

    saveInvertedIndex(invertedIndex, "inverted_index.json");

    cout << "\nInverted Index:\n";

    for (const auto& entry : invertedIndex) {

        cout << entry.first << ": ";

        for (int position : entry.second) {
            cout << position << " ";
        }

        cout << endl;
    }

    return 0;
}

#endif
