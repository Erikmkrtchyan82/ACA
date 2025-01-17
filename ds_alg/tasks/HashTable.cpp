#include <iostream>
#include <array>
#include <string>


// Node_begin
template<typename T>
struct Node {
    Node* next;
    T value;
    Node(T val): value(val) {}

    template<typename U>
    friend std::ostream& operator <<(std::ostream& ost, const Node<U>* node);
};

template<typename T>
std::ostream& operator <<(std::ostream& ost, const Node<T>* node) {
    while (node != nullptr) {
        ost << " " << node->value;
        node = node->next;
    }
    return ost;
}
// Node_end


// HashTable_begin
template<typename T>
struct HashTable {
private:
    using Node_t = Node<T>;
    static constexpr size_t _size = 20;
    std::array<Node_t*, _size> _container{nullptr};
public:
    void insert(T obj) {
        int hash = obj.hash();
        int idx = hash % _size;
        Node_t* prev = _container[idx];
        _container[idx] = new Node_t(obj);
        _container[idx]->next = prev;
    }

    bool insert_unique(T obj) {
        if (search(obj) != nullptr) {
            return false;
        }
        insert(obj);
        return true;
    }

    Node_t* search(T obj) {
        Node_t* ptr = _container.at(obj.hash() % _size);
        while (ptr != nullptr) {
            if (ptr->value == obj) {
                return ptr;
            }
            ptr = ptr->next;
        }
        return ptr;
    }

    ~HashTable() {
        for(Node_t* item: _container) {
            while (item != nullptr) {
                Node_t* ptr = item->next;
                delete item;
                item = ptr;
            }
        }
    }
public:
    template<typename U>
    friend std::ostream& operator<<(std::ostream& ost, const HashTable<U>& hash);
};

template<typename T>
std::ostream& operator<<(std::ostream& ost, const HashTable<T>& hash) {
    for (int i = 0; i < hash._size; ++i) {
        ost << i << ": ";
        if (hash._container[i] != nullptr) {
            ost << hash._container[i];
        }
        ost << std::endl;
    }
    return ost;
}
// HashTable_end


// String_begin
struct String {
private:
    std::string _str;
public:
    String(const char* str): _str(str) {}

    int hash() const {
        int h = 0;
        for (int i = 0; i < _str.size(); ++i) {
            h += _str[i] * i;
        }
        return h;
    }

    bool operator==(const String& other) {
        return _str == other._str;
    }

    friend std::ostream& operator <<(std::ostream& ost, const String& str);
};

std::ostream& operator <<(std::ostream& ost, const String& str) {
    ost << " " << str._str << " [" << str.hash() << "]";
    return ost;
}
// String_end


// Point3D_begin
struct Point3D {
private:
    int _x, _y, _z;
    const int c_1 = 1;
    const int c_2 = 2;
    const int c_3 = 3;

public:
    Point3D(int x, int y, int z): _x(x), _y(y), _z(z) {}

    int hash() const {
        return _x * c_1 + _y * c_2 + _z * c_3;
    }

    bool operator==(const Point3D& other) {
        return  _x == other._x &&
                _y == other._y &&
                _z == other._z;
    }

    friend std::ostream& operator <<(std::ostream& ost, const Point3D& point);
};

std::ostream& operator <<(std::ostream& ost, const Point3D& point) {
    ost << " (" << point._x << ", " << point._y << ", " << point._z << ") [" << point.hash() << "]";;
    return ost;
}
// Point3D_end


void test_string() {
    HashTable<String> hash;
    hash.insert("ABC");
    hash.insert("Lorem");
    hash.insert("Ipsum");
    hash.insert("Flan");
    hash.insert("fstan");

    std::cout << hash << std::endl;
}


void test_point() {
    HashTable<Point3D> hash;
    hash.insert(Point3D(1, 2, 3));
    hash.insert(Point3D(4, 5, 8));
    hash.insert(Point3D(2, 8, 9));
    hash.insert(Point3D(10, 11, 12));
    hash.insert(Point3D(13, 13, 15));
    hash.insert(Point3D(16, 17, 23));
    hash.insert(Point3D(30, 1, 0));

    std::cout << hash << std::endl;
}


int main() {
    test_string();
    test_point();
    return 0;
}
