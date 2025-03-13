#include <iostream>
#include <vector>


// ---------------------------------------------------- pow -------------------------------------
template<int A, size_t N>
struct pow {
    static const int value = pow<A, N - 1>::value * A;
};

template<int A>
struct pow<A, 0> {
    static const int value = 1;
};
// ----------------------------------------------------------------------------------------------

// ---------------------------------------------------- max3 ------------------------------------
template<int A, int B, int C>
struct max3 {
    static const int value = A * (A >= B && A >= C) + B * (B >= A && B >= C) + C * (C >= A && C >= B);
};
// ----------------------------------------------------------------------------------------------

// ---------------------------------------------------- modulo ----------------------------------
template<int N>
struct modulo {
    static const int value = -N * (N < 0) + N * (N >= 0);
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- check_if --------------------------------
template<int A, int B>
struct check_if {
    static const bool value = false;
};

template<int A>
struct check_if<A, A> {
    static const bool value = true;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- is_pointer ------------------------------
template<typename T>
struct is_pointer {
    static const bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static const bool value = true;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- is_array --------------------------------
template<typename T>
struct is_array {
    static const bool value = false;
};

template<typename T, size_t N>
struct is_array<T[N]> {
    static const bool value = true;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- is_same ---------------------------------
template<typename U, typename V>
struct is_same {
    static const bool value = false;
};
template<typename U>
struct is_same<U, U> {
    static const bool value = true;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- rank ------------------------------------
template<typename T>
struct rank {
    static const unsigned int value = 1;
};

template<typename T, size_t N>
struct rank<T[N]> {
    static const unsigned int value = N * rank<T>::value;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- digit_num -------------------------------
template<unsigned int num>
struct digit_num {
    static const unsigned int value = 1 + digit_num< num / 10 >::value;
};

template<>
struct digit_num<0> {
    static const unsigned int value = 0;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- add_pointer ------------------------------
template<typename T>
struct add_pointer {
    using type = T*;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- remove_extent ---------------------------
template<typename T>
struct remove_extent {
    using type = T;
};

template<typename T, size_t N>
struct remove_extent<T[N]> {
    using type = T;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- decay -----------------------------------
template <typename T>
struct decay {
    using type = T;
};

template <typename T>
struct decay<T&> {
    using type = decay<T>::type;
};

template <typename T>
struct decay<T*> {
    using type = decay<T>::type;
};

template <typename T, size_t N>
struct decay<T[N]> {
    using type = decay<T>::type;
};
// ----------------------------------------------------------------------------------------------


// ---------------------------------------------------- type_name_printer -----------------------
template<typename T>
struct type_name_printer {
    static std::string print() {
        return std::string();
    }
};

template<>
struct type_name_printer<int> {
    static std::string print() {
        return "int";
    }
};

template<>
struct type_name_printer<double> {
    static std::string print() {
        return "double";
    }
};

template<>
struct type_name_printer<float> {
    static std::string print() {
        return "float";
    }
};

template<typename T>
struct type_name_printer<T*> {
    static std::string print() {
        return type_name_printer<T>::print() + '*';
    }
};

template<typename T>
struct type_name_printer<T&> {
    static std::string print() {
        return type_name_printer<T>::print() + '&';
    }
};

template<typename T, size_t N>
struct type_name_printer<T[N]> {
    static std::string print() {
        return type_name_printer<T>::print() + '[' + std::to_string(N) + ']';
    }
};

template<typename T>
struct type_name_printer<std::vector<T>> {
    static std::string print() {
        return "std::vector<" + type_name_printer<T>::print() + '>';
    }
};
// ----------------------------------------------------------------------------------------------


template<typename U, typename V>
void check() {
    if (!std::is_same<U, V>::value) {
        std::cout << type_name_printer<U>::print() << " and " << type_name_printer<V>::print() << " must be same " << std::endl;
    }
}

int main() {
    {
        std::cout << digit_num<59>::value << std::endl; // 2
        std::cout << digit_num<66554433>::value << std::endl; // 8
    }

    {
        int arr1[10][34];
        std::cout << is_array<decltype(arr1)>::value << std::endl; // true
        std::cout << is_array<decltype(arr1[0])>::value << std::endl; //false ?

        int y[3];
        std::cout << is_array<decltype(y)>::value << std::endl; // true

        int x = 9;
        std::cout << is_array<decltype(x)>::value << std::endl; // false
    }

    check<int**, add_pointer<int*>::type>();
    check<int, remove_extent<int[40]>::type>();

    check<int[5], remove_extent<int[4][5]>::type>();
    check<int, decay<int**[4][5]>::type>();
    check<int, decay<int*>::type>();


    rank<int[5][5]>::value; // 25

    pow<2, 5>::value;

    modulo<-30>::value;



    return 0;
}
