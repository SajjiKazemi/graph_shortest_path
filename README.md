# Finding the Shortest Path Between Any Two Nodes of a Randomly Generated Graph

## Overview

This project is designed and implemented to find the shortest path between any two nodes of a randomly generated graph using the breadth-first research technique. It marks the second phase of a broader project aimed at identifying a vertex cover for streets with intersections. The ultimate goal is to determine the vertex cover of a randomly generated graph, addressing the Vertex Cover problem, a specific type of optimization problem in graph theory. For a brief understanding of the vertex cover concept, refer to [this link](https://en.wikipedia.org/wiki/Vertex_cover#:~:text=In%20graph%20theory%2C%20a%20vertex,every%20edge%20of%20the%20graph).

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/SajjiKazemi/graph_shortest_path.git
```

## Dependencies
Create a virtual environment using the provided my_env.yml file:

```bash
conda env create -f my_env.yml
```
Activate the environment:

```bash
conda activate my_env
```

## Usage

The specification of a set of vertices begins with ‘V’, followed by a space and an integer greater than one, all in a single line. If the following integer is i, then the vertices are assumed to be identified by 1, . . . , i. The edge set specification begins with ‘E’, followed by a space and the set of edges in a single line delimited by ‘{’ and ‘}’. The two vertices of an edge are delimited by ‘<’ and ‘>’ and separated by a comma. The edges in the set are also separated by a comma, with no whitespace characters within the { }.

The only other type of input starts with an ‘s’. It requests the shortest path from the first vertex to the second specified after the 's'. The 's' is followed by a space, a vertex ID, another space, and a second vertex ID. The output consists of vertex IDs separated by ‘-’, with no whitespace within. If no path exists between the vertices, an error will be output. The graph is specified by the set of vertices V followed by the set of edges E, in that order. V and E always occur together. There is no relationship between subsequent graph specifications; when a new V specification starts, all previous information can be forgotten.

To run the project, inside the project directory, create the necessary directory:

```bash
mkdir build
```

and execute the following command line:

```bash
cmake ../
```

and then:

```bash
make
```

Run the executable file for main.cpp:


```bash
 ./main
```

Given a graph as input and assuming your executable is called main, the program will output the shortest path computed. That is, give the following input:

```bash
$ ./main

V 15

E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}

s 2 10
```

The output from your program should be:

```bash
2-8-10
```

## Contact
For any questions or feedback, feel free to reach out:

Email: sajjikazemi@uwaterloo.ca

LinkedIn: www.linkedin.com/in/sajjadkazemi
