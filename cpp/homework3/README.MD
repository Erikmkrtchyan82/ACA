# multi_array.cpp

- Add a `static constexpr int volume = ...` field to the `multi_array` template, which will indicate the total number of cells in that structure.

- Implement the `multi_array_accessor` template, whose parameters will be the multi_array itself and a variadic sequence of indices. The goal is to provide access to specific cells.


# tuple.cpp

- Modify the `getter` of the `tuple` class so that an index overflow results in a compile-time error. Remember that `tuple` indices are known at compile time.

- Implement the equality comparison operator `operator==` for two `tuple` instances.
