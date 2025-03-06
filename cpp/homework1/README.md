Write a function template, which will print content of provided 'std::vector<>' to the console. If it is vector of integers, an example output is:

\=\=\=<br>
[5, 32, 14, 6]<br>
\=\=\=

Write its specialization for printing vector of strings, so every string will be double-quoted. Example output is:

\=\=\=<br>
["hello", "kitty", "move", "on"]<br>
\=\=\=

Write another specialization for printing vector of characters, which will print every character in single quites. Example:

\=\=\=<br>
['f', 'h', 'Z', 'X']<br>
\=\=\=

Finally, write a specialization for printing vector of "std::pair<>" objects. In that case, each pair should apperar in brackets. If the vector consists of pairs of strings and integers, then example output is:

\=\=\=<br>
[(h:22), (ptr:7), (key:84)]<br>
\=\=\=
