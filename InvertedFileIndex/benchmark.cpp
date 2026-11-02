
#define INVERTED_INDEX_BENCHMARK
#include "main.cpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <sstream>

string generateDocument(int numberOfWords) {

    vector<string> words = {
        "The", "brown", "cat", "and", "the",
        "blue", "rat", "live", "in", "the",
        "brown", "house", "They", "enjoy",
        "live", "music", "concerts"
    };

    string document;

    for (int i = 0; i < numberOfWords; i++) {
        document += words[i % words.size()] + " ";
    }

    return document;
}

TEST_CASE("Inverted Index Performance") {

    SECTION("100 words") {

        string data = generateDocument(100);

        BENCHMARK("100 words") {
            istringstream input(data);
            return buildInvertedIndex(input);
        };
    }

    SECTION("500 words") {

        string data = generateDocument(500);

        BENCHMARK("500 words") {
            istringstream input(data);
            return buildInvertedIndex(input);
        };
    }

    SECTION("1000 words") {

        string data = generateDocument(1000);

        BENCHMARK("1000 words") {
            istringstream input(data);
            return buildInvertedIndex(input);
        };
    }

    SECTION("5000 words") {

        string data = generateDocument(5000);

        BENCHMARK("5000 words") {
            istringstream input(data);
            return buildInvertedIndex(input);
        };
    }

    SECTION("10000 words") {

        string data = generateDocument(10000);

        BENCHMARK("10000 words") {
            istringstream input(data);
            return buildInvertedIndex(input);
        };
    }
}
