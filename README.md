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

## Problem 3. 2-approximation Metric Steiner Tree
Command: python3 metric_steiner_2_apprx.py

Input: A weighted, undirected graph in edge list format from file 'weighted_graph.txt' and the required vertices of the Steiner tree from 'required_vertices.txt'

Output: Edges of the metric steiner tree in format [[v1,v2], [v2,v3]]


## Problem 5. The 3/2-approximation (Christofides) for the metric Traveling Salesman problem

Input: A weighted, undirected graph in edge list format from file 'weighted_graph.txt'.

Output: Implements the 3/2-approximation (Christofides) for the metric Traveling Salesman problem using the input graph. Results of intermediate steps of the algorithm are shown before displaying the final TSP tour and it's associated cost.

To execute the code:
Run the python script '_32_approx_metricTSP.py' with 'weighted_graph.txt' as the input graph within the working directory.
