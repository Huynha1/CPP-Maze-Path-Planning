# Path Planning Algorithm
In this project written in C++, a simplified path planning algorithm is implemented for a robot to move about a simple 2D environment which is a rectangular room with obstacles.
A simple 2D environment will be represented as a grid of ASCII characters. 
For example. 
```
==========
=S.......=
========.=
=......=.=
==.=.=...=
=..=..=.==
=.===.=..=
=..==G==.=
===.======
==========
```

`=` Wall

`.` Path

`S` Start point

`G` Goal point

### Directories
    .
    └── Test                  # File containing tests for this project

### How to compile and run
Change directory to code folder and run the command below.

To compile: 
`g++ -Wall -Werror -std=c++14 -O -o <executable name> Node.cpp NodeList.cpp PathPlanner.cpp main.cpp`

To run:
`./<executable name>`

After running the executable please input a 2D environment similar to the example above.

### How to run tests
Use the diff to compare the actual and expected output of the program.

`./<executable name> <testname.env > actual.out`
