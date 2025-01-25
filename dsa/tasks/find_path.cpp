#include <iostream>
#include <tuple>
#include <vector>

const int M = 10;
const int N = 10;

int field[M][N];
std::vector<std::tuple<int, int>> path;


void init() {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            field[i][j] = -1;
        }
    }
    for (int i = 0; i < M; ++i) {
        field[i][N-1] = 1;
    }
    for (int j = 0; j < N; ++j) {
        field[M-1][j] = 1;
    }
    path.push_back(std::make_tuple(3,4));
    path.push_back(std::make_tuple(6,4));
    path.push_back(std::make_tuple(2,7));
    path.push_back(std::make_tuple(5,5));
    path.push_back(std::make_tuple(0,4));

    for(std::tuple<int, int>& p: path) {
        field[std::get<0>(p)][std::get<1>(p)] = 0;
    }
}

void print() {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << field[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void find_paths() {
    for(int i = M-2; i >= 0; --i) {
        for(int j = N-2; j >= 0; --j) {
            if(field[i][j] == -1) {
                field[i][j] = field[i+1][j] + field[i][j+1];
            }
        }
    }
}

int main() {
    init();
    find_paths();
    print();

    return 0;
}
