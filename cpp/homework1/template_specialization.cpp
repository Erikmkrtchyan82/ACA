#include <iostream>
#include <vector>

template<typename T>
void print(const std::vector<T>& arr) {
    std::cout << '[';
    for (int i = 0; i < arr.size() - 1; ++i) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr.back() << ']' << std::endl;
}

template<>
void print<std::string>(const std::vector<std::string>& arr) {
    std::cout << '[';
    for (int i = 0; i < arr.size() - 1; ++i) {
        std::cout << '"' << arr[i] << "\", ";
    }
    std::cout << '"' << arr.back() << '"' << ']' << std::endl;
}

template<>
void print<char>(const std::vector<char>& arr) {
    std::cout << '[';
    for (int i = 0; i < arr.size() - 1; ++i) {
        std::cout << '\'' << arr[i] << "',";
    }
    std::cout << '\'' << arr.back() << '\'' << ']' << std::endl;
}

template<typename U, typename V>
void print(const std::vector<std::pair<U, V>>& arr) {
    std::cout << '[';
    for (auto it = arr.begin(); it != arr.end() - 1; ++it) {
        std::cout << '(' << it->first << ':' << it->second << "), ";
    }
    std::cout << '(' << arr.back().first << ':' << arr.back().second  << ')' << ']' << std::endl;
}

int main() {
    std::vector<int> arr{1, 2, 3, 4, 5};
    print(arr);

    std::vector<std::string> arr2{"abc", "def", "ghi"};
    print(arr2);

    std::vector<char> arr3{'a', 'b', 'c'};
    print(arr3);

    std::vector<std::pair<std::string, int>> arr4{{"abc", 1}, {"def", 2}, {"ghi", 3}};
    print(arr4);

    return 0;
}
