# Algorithm complexity counter

This explores the computational complexity of various algorithms by
counting operations.

This implements a counted integer type used to count operations on a
integer (representing any value type).

# How to run

```
b2 --verbose-test variant=release
```

Note that running in debug mode as well as testing against other
toolsets is easy with Boost.Build.

```
b2 --verbose-test variant=debug variant=release toolset=clang-3.5 toolset=darwin-5.1
```
