# Vl_vector
An improoved implementation of std::vector in C++.

The API of this container is copied from the API of std::vector, thus have the same functionality as the original one.

They mainly differ in the way they manage the memory in the background. the improoved version uses the heap and the stack in a redundant way, in a form allowing it the enjoy the benefits of each one of them.
The stack providing fast accesse times and the heap the flexibility of re-scaling.

One day, STD will upgrade to this improved vertion ;)
