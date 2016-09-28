ANTLR4 + C++ proof of concept

To build:

clone https://github.com/DanMcLaughlin/antlr4 somewhere and build it
`mvn compile && cd runtime/Cpp && cmake . && make`

edit generate.sh as necessary - ROOT should point to the antlr4 repo

also edit CMakeLists.txt so that ANTLR4 is set to the antlr4 repo


```
cmake .
make
./antlr4test
```

type some expression (like 1+1) and hit control-D.
