#include <iostream>
#include <array>
#include <string>
#include <random>
#include <ctime>
#include <stack>
#include <sstream>

const int N = 8;
const int M = 10;

std::string generateRandomString(int count);

std::string str1 = generateRandomString(N);
std::string str2 = generateRandomString(M);


std::array<std::array<int, M + 1>, N + 1> memo;


std::string generateRandomString(int count) {
    // Define the set of characters to choose from
    const std::string characters = "abcdefghijklmnopqrstuvwxyz";

    // Seed the random number generator with the current time
    std::random_device rd;
    std::mt19937 generator(rd());

    // Generate a random length for the string
    std::uniform_int_distribution<int> lengthDist(count, count); // Adjust the range as needed
    int length = lengthDist(generator);

    // Create the random string
    std::string randomString(length, ' ');
    std::uniform_int_distribution<int> charDist(0, characters.size() - 1);
    for (int i = 0; i < length; ++i) {
        randomString[i] = characters[charDist(generator)];
    }

    return randomString;
}

void init() {
    for (int i = 0; i < str1.size() + 1; ++i) {
        for (int j = 0; j < str2.size() + 1; ++j) {
            if (i == 0 || j == 0) {
                memo[i][j] = 0;
            }
            else {
                memo[i][j] = -1;
            }
        }
    }
}

void print() {
    std::cout<< "STR1: " << str1 << std::endl;
    std::cout<< "STR2: " << str2 << std::endl << std::endl;

    std::cout << "MEMO: " << std::endl;

    std::cout << '\t';
    for (int i = 0; i < str2.size(); ++i)
        std::cout << "\t" << str2[i] ;
    std::cout << std::endl;

    std::ostringstream s;

    for (int i = 0; i < str1.size() + 1; ++i) {
        for (int j = 0; j < str2.size() + 1; ++j) {
            if (j == 0) {
                if (i != 0)
                    std::cout << str1[i - 1];
                std::cout << "\t";
            }
            std::cout << memo[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << s.str() << std::endl;
}

int lcs(int i, int j) {
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    // -1 because memo's first column and rows are for empty chars
    if (str1[i-1] == str2[j-1]) {
        memo[i][j] = lcs(i-1, j-1) + 1;
    }
    else {
        memo[i][j] = std::max(lcs(i-1, j), lcs(i, j-1));
    }
    return memo[i][j];
}

std::string lcs() {
    int i = str1.size();
    int j = str2.size();

    std::stack<char> str;
    while (memo[i][j] != 0) {
        if (str1[i-1] == str2[j-1]) {
            str.emplace(str1[i-1]);
            --i;
            --j;
        }
        else {
            if (memo[i][j] == memo[i-1][j])
                --i;
            else
                --j;
        }
    }
    std::string res;
    while(!str.empty()) {
        res+=str.top();
        str.pop();
    }
    return res;
}

float used_fields_count() {
    int used = 0;
    for (int i = 1; i < N + 1; ++i) {
        for (int j = 1; j < M + 1; ++j) {
            if (memo[i][j] != -1) ++used;
        }
    }
    return float(used) / ((N) * (M)) * 100;
}

int main() {
    init();

    std::cout<< "res: "<< lcs(str1.size(), str2.size())<<", "<< lcs()<< std::endl;
    print();
    std::cout << "used fields: " << used_fields_count() << '%' << std::endl;
    return 0;
}
