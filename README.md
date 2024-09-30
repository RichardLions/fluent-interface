# Fluent Interface

This repository demonstrate an example use case for using a fluent interface to construct an object with literals, types and strong types. Each style reduces the ambiguity between types to reduce misuse.

Note: Does not take into account the use of Named Arguments.

## Pros and Cons

### [Literals](circle_literals.h)

Pros:
* Common style
* Simple to understand
* Extending the constructor parameter list triggers compile errors for all call sights

Cons:
* Easy to mix up the order of parameters with the same type
* Literal types do not express meaning
* Large parameter lists can become hard to maintain

Extra:
* Using literal operator when passing in parameters can help express meaning
* Using the explicit keyword reduces the number of accepted types

### [Types](circle_types.h)

Pros:
* Common style
* Simple to understand
* Improved type meaning
* Extending constructor parameter list triggers compile errors for all call sights
* Reduced parameter list by creating types out of related types

Cons:
* The order of the constructor parameters with the same type may still be mixed up
* Large parameter lists can become hard to maintain

Extra:
* Using literal operator when passing in parameters can help express meaning
* Using the explicit keyword reduces the number of accepted types

### [Strong Types](circle_strongtypes.h)

Pros:
* Cannot mix up constructor parameters
* Can pass constructor parameters in any order
* Strong types fully convey meaning

Cons:
* Cannot enforce required constructor parameters
* Cannot mix styles. All types used must be strong types
* Boiler plate code

Extra:
* Removing the Fluent Interface would enable the enforcement of required constructor parameters. However this would reduce the reason for using strong types.

### Performance

The results from the benchmarks showed each style performed equally within an acceptable margin of error. However it is important to support constructing objects in place (std::vector::emplace_back(...)) because this method had the best performance.

### Recommendation

Strongly typing every constructor parameter is appealing and enforces type correctness. However in the example I found the boiler plate code mounted up quickly and started to add additional layers of indirection, resulting in an interface that was hard to use. I would recommend using common techniques for strongly typing literals and creating types from related types. This combined with well named parameters should create an interface that is easy to use and understand.

## Setup

This repository uses the .sln/.proj files created by Visual Studio 2022 Community Edition.
Using MSVC compiler, Preview version(C++23 Preview). 

### Catch2
The examples for how to use the pattern are written as Unit Tests.

Launching the program in Debug or Release will run the Unit Tests.

Alternative:
Installing the Test Adapter for Catch2 Visual Studio extension enables running the Unit Tests via the Test Explorer Window. Setup the Test Explorer to use the project's .runsettings file.

### vcpkg
This repository uses vcpkg in manifest mode for it's dependencies. To interact with vcpkg, open a Developer PowerShell (View -> Terminal).

To setup vcpkg, install it via the Visual Studio installer. To enable/disable it run these commands from the Developer PowerShell:
```
vcpkg integrate install
vcpkg integrate remove
```

To add additional dependencies run:
```
vcpkg add port [dependency name]
```

To update the version of a dependency modify the overrides section of vcpkg.json. 

To create a clean vcpkg.json and vcpkg-configuration.json file run:
```
vcpkg new --application
```

### TODO
- [x] Implementation
- [x] Unit Tests
- [x] Benchmarks
