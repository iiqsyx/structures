# std::vector
  std::vector is a dynamic array of data, which exclude memory leaks and has different functions to work faster and safer. In this folder you can see castom Vector, which in general works as std::vector. You can search more about std::vector on [cppreference](https://en.cppreference.com/w/cpp/container/vector).

## Content
- [Technology](#Technology)
- [Vector in general](#Vector-in-general)
- [Functions](#Functions)
- [Operators and constructors](#Operators-and-constructors)
- [Iterator](#Iterator)
- [Conclusion](#Conclusion)

## Technology
  You can run it on various platforms due to cmake foundation. You also will need an iostream library included before Vector.

## Vector in general
  Vector contains elements in memory as a subsequence. Vector always reserve more memory(capacity) for faster insertion.
  
![image](https://github.com/user-attachments/assets/6b762e0e-a0e8-403a-8bc5-b59fe26e97c0)

## Functions
 Vector have similar to std::vector functions such as:
 - push_back
 - pop_back
 - reserve
 - resize
 - shrink_to_fit
 - clear
 - swap
 - get_size(called "size" in std::vector)
 - get_capacity(called "capacity" in std::vector)
 - empty
 - begin
 - end

## Operators and constructors
Vector have similar to std::vector functions such as:
- Basic constructor(which initialize size and capacity as 0, and initialize allocator with passed value or defoult std::allocator)
- Copy constructor
- Copy constructor with different allocator for array's values
- Move constructor
- Operator[]
- Copy operator=
- Move operator=

## Iterator
Iterator includes:
- operator*
- operator++
- operator--
- operator==
- operator!=

## Conclusion
This Vector is not a complete copy of the vector from the STL library. 
-~<3<3<3 I'm a beginner programmer and i'll be glad to receive constructive criticism on any of my projects!
