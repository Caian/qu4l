# qu4l
A preprocessor macro to create classes and structs with full name qualification, including namespaces

## Test results
Branch          | Build         | Tests coverage
----------------|-------------- | --------------
master          | [![Build Status](https://travis-ci.org/Caian/qu4l.svg?branch=master)](https://travis-ci.org/Caian/qu4l) | [![codecov.io](https://codecov.io/github/Caian/qu4l/coverage.svg?branch=master)](https://codecov.io/github/Caian/qu4l)

## Usage

### Basics

To create a simple class or a struct:

```c++
QU4L_MAKE_ENTITY(
    (hello)(world),
    class, hello_world, , /* { */

    static const int i = 5;
    int j;

public:

    hello_world() : j(i)
    {
    }

    int get_value() const
    {
        return i;
    }

    /* }; */ , get_id, "::")
```

### Inheritance and other attributes

Classes and structs can also use inheritance and other attributes like `final`, although they will **not** be considered in the qualification:

```c++
QU4L_MAKE_ENTITY(
    (hello)(world),
    class, hello_world, : public base_class, /* { */

    static const int i = 5;
    int j;

public:

    hello_world() : j(i)
    {
    }

    int get_value() const
    {
        return i;
    }

    /* }; */ , get_id, "::")
```

### Templates

It is also possible to declare templates:

```c++
QU4L_MAKE_ENTITY(
    (hello)(world),
    template <typename T>
    struct, hello_world, , /* { */

    T value;

    /* }; */ , get_id, "::")
```

Currently the templates are **not** qualified in the class name. This can be mitigated by overriding the id method (see bellow).

### Changing the access to the generated static id method

The id method is generated at the bottom of the class, so it is possible to
change its access by adding public / protected / private modifiers to the end
of the body:

```c++
QU4L_MAKE_ENTITY(
    (hello)(world),
    struct, hello_world, , /* { */

// Turn the original id function private
private:

    /* }; */ , get_id, "::")
```
### Custom id methods

The generated id method can be turned into an intermediate step of a more complex id process, like qualifying a template instantiation. To do that, you must create the id method yourself as required by the interface defined in your project and use the generated one:

```c++
QU4L_MAKE_ENTITY(
    (hello)(world),
    template <typename T>
    struct, hello_world, , /* { */

    // Create a public id function that is different from the generated
    static std::string get_id()
    {
        return std::string(_get_id()) + "/" + T::get_id();
    }

// Turn the original id function private and use a different name than the interface
private:

    /* }; */ , _get_id, "::")
```
