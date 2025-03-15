#include <iostream>

// The base case of container.
template< typename T, int... Extents >
struct multi_array
{
	static_assert( false,
			"Implementation is placed only in the specializations." );
};

/// Specialization for extracting the first extent.
template< typename T, int Ext1, int... Extents >
struct multi_array< T, Ext1, Extents... >
{
    using element_t = T;
    using inner_t = multi_array< T, Extents... >;

	inner_t data[ Ext1 ];
    static const size_t volume = Ext1 * inner_t::volume;
};

/// Specialization, when all extents are extracted.
template< typename T >
struct multi_array< T >
{
    using element_t = T;

	T data;  // The final cell
    static const size_t volume = 1;
};

template<typename MultiArrayType, int idx, int... indices>
struct multi_array_accessor {
    using return_t = typename MultiArrayType::element_t;

    static const return_t& get(const MultiArrayType& arr) {
        return multi_array_accessor<typename MultiArrayType::inner_t, indices...>::get(arr.data[idx]);
    }
    static return_t& get(MultiArrayType& arr) {
        return multi_array_accessor<typename MultiArrayType::inner_t, indices...>::get(arr.data[idx]);
    }
};

template<typename MultiArrayType, int idx>
struct multi_array_accessor<MultiArrayType, idx> {
    using return_t = typename MultiArrayType::element_t;

    static const return_t& get(const MultiArrayType& arr) {
        return arr.data[idx].data;
    }
    static return_t& get(MultiArrayType& arr) {
        return arr.data[idx].data;
    }
};


int main() {

    multi_array< float, 5, 4, 3 > y;
    const size_t volume = y.volume;

    using multi_array_t = decltype(y);

    multi_array_accessor<multi_array_t, 3, 2, 1>::get(y) = 50;
    const float res = multi_array_accessor<multi_array_t, 3, 2, 1>::get(y);

    std::cout << res <<std::endl;

    return 0;
}
