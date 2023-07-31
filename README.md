# `datastructures`
I created this project to brush up on my C++ and datastructures skills. The `main()` function gathers up the tests in `test/` and runs them all.

This project is a work in progress, I'm currently working on the B-tree map. Over time I want to add additional datastructures like graphs, tries, etc.

# Building and running
```bash
meson setup build
cd build
meson compile
./datastructures
```

# Learnings
## Valgrind is great
The first draft of several of these datastructures involved double `free`s and the occasional segfault. I probably would not have figured out what was going on if I hadn't used Valgrind to track down allocations. Valgrind helped me realize that most of my problems had to do with performing shallow copies of an object, allowing the original to go out of scope, and then trying to deallocate the same memory region a second time. I can also be certain I'm not leaking memory due to its heap analysis.

## `malloc`/`free` vs `new`/`delete`
Previously I had conflated the memory management techniques available in C and C++. I hadn't thought through the fact that `delete` not only deallocates memory, but also runs destructors. In fact, when deleting an array of objects with destructors, one must call `delete[]` in order to apply the destructor to each element of the array!

## `const` correctness for getters
It is occasionally necessary to have both `const` and non-`const` versions of getter methods on a class. A good pattern for this is to have the non-`const` version depend on the `const` version as in [this following StackOverflow](https://stackoverflow.com/questions/123758/how-do-i-remove-code-duplication-between-similar-const-and-non-const-member-func).
