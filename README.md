# AdvAlgoProject
COT5405 - Advanced Algorithms Project

Due Date: 4/22/2022

Group members: Noah O'Connor, Hussain Akram, Michael Styron, Ashwati Nair, Humaira Mauni

## 1- Maximum-Weight-Independent Set in a graphic matroid
Please run the following command:
```bash
ruby 1-MWI-set.rb input.txt
```

When run on correct input, it should print out the max-independent set with maximum weight as follows:

```console
foo@bar:~$ ruby 1-MWI-set.rb input.txt
[["1", "2", "3", "0"], 2.5]
```
Here 2.5 is the max-weight of the path of nodes(acyclic) in sequence to they are printed

## Problem 2. (genSteinerReduction.cpp) General Steiner tree reduction to Metric Steiner tree
Input: 
    - The input files to this program should be placed in the same directory as where the file is being ran. 
    - The format specified by "Example of Steiner Tree Input.pdf" was referenced to write the parseing of the files for the program.
    
    - Weighted undirected graph which should be provided by the file weighted_graph.txt
    - Required nodes in the solution which should be provided by the file required_vertices.txt.
    
Output: 
    - After running this program it will output a complete weighted graph satisfying the triangle inequality in the same format used for the input file thus completing       the metric closure on the provided input. Edges in this case are listed redundantly. I.e) 0--1 with a weight of 0.5 will also be printed later as 1--0 0.5.             Additionally the set of required vertices will be printed, this will be the same as the required vertices given as input.
    
Assumptions:
    The graph given as input is a connected graph. (You can reach all vertices through some means if vertices are not directly connected)
    
Running the program:

    To run the program first compile it by typing:
      g++ -std=c++11 genSteinerReduction.cpp -o steiner.exe

    Now you can type ./steiner.exe to execute the program assuming you have weighted


## Problem 3. 2-approximation Metric Steiner Tree
Command: python3 metric_steiner_2_apprx.py

Input: A weighted, undirected graph in edge list format from file 'weighted_graph.txt' and the required vertices of the Steiner tree from 'required_vertices.txt'

Output: Edges of the metric steiner tree in format [[v1,v2], [v2,v3]]

## Problem 4: The 2-approximation for metric Travelling Salesman Problem

Input: A weighted, undirected graph in edge list format from file 'weighted_graph.txt'. The input file should be placed in the same directory as the code file.

Output: The result is in format [v1 --> v2 --> ... --> v1] and the cost of the tour. Intermediate results such as number of nodes, Minimum Spanning tree of the input graph and Euler Circuit are also displayed. 

Command: Included a script file to execute the '2-approx_metricTSP.cpp' file. The name of the script file is '2TSP.sh'. Execute the following command.
./2TSP.sh


## Problem 5. The 3/2-approximation (Christofides) for the metric Traveling Salesman problem

Input: A weighted, undirected graph in edge list format from file 'weighted_graph.txt'.

Output: Implements the 3/2-approximation (Christofides) for the metric Traveling Salesman problem using the input graph. Results of intermediate steps of the algorithm are shown before displaying the final TSP tour and it's associated cost.

To execute the code:

Import libraries:

pip install --user itertools

pip install --user networkx

Run script:
Run the python script 'python3.5 _32_approx_metricTSP.py' with 'weighted_graph.txt' as the input graph within the working directory.
