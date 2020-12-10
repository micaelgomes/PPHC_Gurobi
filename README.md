# Solver PPCH - Gurobi

Using GUROBI to solve the discipline scheduling problem.

### build requirements
To be able to generate a build it is necessary to have the gurobi solver installed and a valid license.

### Make
- the make command, for this project, generates a new build and executes it right after: make

### Build
- To build new program version: make build

### Run
- To run program: make run


## Folder Structure

```
project
│   README.md
│   Makefile
│   ppch_model.lp
│   ppch.log
│   gurobi.log    
│
└─── bin
│   │   exec -> binary file
│   │
│       
└─── data
│   │   all problem input files. are of the .dat format and contain the parameters.
│   │
│   
└─── src
    │   main.cpp -> main file 
    │   header.cpp -> file to read input files in .dat
    │
    │
```
