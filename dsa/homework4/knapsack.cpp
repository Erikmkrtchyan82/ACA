#include <iostream>
#include <vector>
#include <random>
#include <ctime>

enum class Type {
    zero_one,
    unbounded,
};

struct Item {
    int id;
    int bonus;
    int weight;
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << "weight: " << item.weight << ", " << "bonus: " << item.bonus;
    return os;
}
std::ostream& operator<<(std::ostream& os, const std::vector<Item>& items) {
    for (const Item& item : items) {
        os << "Item " << item.id << ": " << item << std::endl;
    }
    return os;
}


class Knapsack {
    int _limit;
    int _items_count;
    std::vector<Item> _items;
    std::vector<std::vector<int>> _memo;

public:
    Knapsack(int limit = 10, int count = 4): _limit(limit), _items_count(count) {
        _items = std::vector<Item>(_items_count);

        _memo = std::vector<std::vector<int>>(_items_count + 1);
        for (int i = 0; i < _items_count + 1; ++i) {
            _memo[i] = std::vector<int>(_limit + 1);
        }

        std::random_device rd;
        std::mt19937 generator(rd());

        std::uniform_int_distribution<int> counter(1, 10);

        for (int i = 0; i < _items_count; ++i) {
            int weight = counter(generator);
            int bonus = counter(generator);
            _items[i] = {i, bonus, weight};
        }
    }

    void print() {
        std::cout << "Limit: " << _limit << std::endl;
        std::cout << _items << std::endl;
    }

    void print_memo() {
        for (int i = 0; i < _items_count + 1; ++i) {
            for (int j = 0; j < _limit + 1; ++j) {
                std::cout << _memo[i][j] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    template <Type type, typename = std::enable_if_t<type == Type::zero_one>>
    void solve() {
        for (int i = 1; i < _items_count + 1; ++i) {
            for (int j = 0; j < _limit + 1; ++j) {
                const Item& item = _items[i - 1];
                if (item.weight > j) {
                    _memo[i][j] = _memo[i - 1][j];
                }
                else {
                    _memo[i][j] = std::max(_memo[i - 1][j], _memo[i - 1][j - item.weight] + item.bonus);
                }
            }
        }
    }

    template <Type type, typename = std::enable_if_t<type == Type::unbounded>>
    void solve(int = 0) {
        for (int i = 1; i < _items_count + 1; ++i) {
            for ( int j = 0; j < _limit + 1; ++j) {
                const Item& item = _items[i - 1];
                if (item.weight > j) {
                    _memo[i][j] = _memo[i - 1][j];
                }
                else {
                    _memo[i][j] = std::max(_memo[i - 1][j], _memo[i][j - item.weight] + item.bonus);
                }
            }
        }
    }

    template <Type type, typename = std::enable_if_t<type == Type::zero_one>>
    std::vector<Item> get_selected_items() {
        std::vector<Item> selected_items;
        int i = _items_count;
        int j = _limit;
        while (i > 0) {
            if (_memo[i][j] != _memo[i - 1][j]) {
                selected_items.push_back(_items[i - 1]);
                j -= _items[i - 1].weight;
            }
            --i;
        }
        return selected_items;
    }

    template <Type type, typename = std::enable_if_t<type == Type::unbounded>>
    std::vector<Item> get_selected_items(int=0) {
        std::vector<Item> selected_items;
        int i = _items_count;
        int j = _limit;
        while (i > 0) {
            if (_memo[i][j] != _memo[i - 1][j]) {
                selected_items.push_back(_items[i - 1]);
                j -= _items[i - 1].weight;
            }
            else {
                --i;
            }
        }
        return selected_items;
    }

};


int main() {

    constexpr Type type = Type::zero_one;
    Knapsack pack(8,4);
    pack.print();
    pack.solve<type>();
    pack.print_memo();

    std::cout<< "Selected items: " << std::endl;
    std::cout << pack.get_selected_items<type>() << std::endl;

    return 0;
}
