# Functional that is already works:
- Basic operations (+, -, *, /)
- Priority manipulating with brackets

Current state of CMakeLists only lets to build static library and add it to project with google-tests

#TODO:
- Move tests to separate project to have ability to build them and main project
- Build googletest lib separately to avoid its rebuilding
- Create simple console-based frontend (already have it in main.cpp but maybe some improvements are needed)
- Make tests for extra brackets
- Make tests for division by 0(zero)
- Add converter from one notation to other
- Add trigonometry
- Add logarithms
- Add Qt-based (or some other) frontend
- Add graphic drawing
- Add server functional (Berkley-API)

# Math problems
a/b/c - what is it?
1. (a * c)/b - same as a / (b/c)
2. (a/b)/c