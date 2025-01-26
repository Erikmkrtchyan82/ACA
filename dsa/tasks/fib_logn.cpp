#include <iostream>
#include <map>
#include <cmath>

using lint = unsigned long long;

std::map<lint, lint> memo {{0, 0}, {1, 1}};

lint fib(int n) {
    if (memo.contains(n)) {
        return memo[n];
    }
    if (n % 2 == 0) {
        int k = n / 2;
        memo[n] = fib(k) * (2 * fib(k - 1) + fib(k));
    } else {
        int k = (n + 1) / 2;
        memo[n] = std::pow(fib(k), 2) + std::pow(fib(k - 1), 2);
    }
    return memo[n];
}


int main() {
    int n = 15;
    std::cout << n << ": " << fib(n) << std::endl;

    return 0;
}
