# C++ Assignment 6: Reinforcement Learning

The project includes ValueIteration.h, ValueIteration.cpp, driver.cpp, as well as a Makefile.

ValueIteration.h contains all the header declarations for the ValueIteration class, which is responsible for performing the Value Iteration algorithm on the specified grid-world environment and producing the required results to answer the assignment questions.

ValueIteration.cpp contains the method definitions for the ValueIteration class.

driver.cpp is the program calls the necessary ValueIteration class methods and writes the results to the Results.txt file.

## How to use the program

The program directory structure is as follows:

Assignment6_CHNJAR003
bin - contains the output executables
build - contains the object files (emptied on "make clean")
include - contains all the project header files
src - contains the application source files

### The structure of the command line execution is as follows:

NB: make use of the "make run" command to execute the program and produce the results.

NB: the executable is located in the bin directory

```bash
./bin/rlValIt
```

Navigate to the Assignment6_CHNJAR003 directory in Terminal and utilise the provided Makefile to compile the program source code using:

```bash
make
```

The following command can be used to run the executable with the dataset and write the results to "Results.txt", which will be created in the main assignment directory:

```bash
make run
```

Use the following command to remove the binary files and executable from the build and bin folders respectively:

```bash
make clean
```

## Authors

**CHNJAR003**
