#include <iostream>


template< typename... Types >
struct tuple {
	static_assert(
			false,
			"The non-specialized 'tuple<>' should never be instantiated." );
};

/// The specialization of 'tuple' which should be instantiated.
template< typename HeadType, typename... BodyTypes >
struct tuple< HeadType, BodyTypes... > {
	typedef HeadType head_type;                // Type of the first value
	typedef tuple< BodyTypes... > inner_type;  // Type of nested tuple

    static const size_t size = sizeof...(BodyTypes) + 1;

	HeadType _head;               // First value of the tuple
	tuple< BodyTypes... > _body;  // The remaining values

	/// Constructor
	tuple( const HeadType& head_, BodyTypes... body_ )
		: _head( head_ ),
		  _body( body_... )
		{}
};

/// The "exit-branch" for tuple class.
template<>
struct tuple<> {
    size_t size = 0;
};


/// This class implements access to tuple fields by index.
template< typename TupleType, unsigned int Index >
struct getter
{
	/// Type of the nested tuple.
	typedef typename TupleType::inner_type inner_tuple_type;

    static_assert(Index < TupleType::size, "IndexOutOfBound");

	/// Type of the field at 'Index'.
	typedef typename getter<
			inner_tuple_type,
			Index - 1 >::type type;

	/// Type of the getter, to work with nested tuple.
	typedef getter<
			inner_tuple_type,
			Index - 1 > inner_getter_type;

	/// Const / non-const access to the field at 'Index'.
	static const type& get( const TupleType& t )
		{ return inner_getter_type::get( t._body ); }
	//
	static type& get( TupleType& t )
		{ return inner_getter_type::get( t._body ); }
};

/// Specialization for the "exit-branch".
template< typename TupleType >
struct getter< TupleType, 0 >
{
	/// Type of the field at 'Index'.
	typedef typename TupleType::head_type type;

	/// Const / non-const access to the field at 'Index'.
	static const type& get( const TupleType& t )
		{ return t._head; }
	//
	static type& get( TupleType& t )
		{ return t._head; }
};

template<typename... H1, typename... H2>
bool operator==(const tuple<H1...>& tuple1, const tuple<H2...>& tuple2) {
    return false;
}

template<typename... H1>
bool operator==(const tuple<H1...>& tuple1, const tuple<H1...>& tuple2) {
    return (tuple1._head == tuple2._head) && tuple1._body == tuple2._body;
}
template<>
bool operator==(const tuple<>& tuple1, const tuple<>& tuple2) {
    return true;
}


int main() {

    tuple< float, std::string, int > t2( 9.1f, "pairwise", 70 );

    using tuple_t = decltype(t2);

    std::cout << "The second item is : "
            << getter< tuple_t, 1 >::get( t2 ) << std::endl;

    getter< tuple_t, 2 >::get( t2 ) += 12;
    std::cout << "The third item is : "
            << getter< tuple_t, 2 >::get( t2 ) << std::endl;
    // std::cout << "The fourth item is : "
            // << getter< tuple_t, 3 >::get( t2 ) << std::endl; // Compile error

    std::cout << std::endl;


    tuple< float, std::string, int > t3( 9.1f, "pairwise", 82 );

    const bool x = t2 == t3;
    std::cout << x <<  std::endl;

    return 0;
}
