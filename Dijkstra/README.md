# Project 04: Path Finding
Eli Carter
CS302 Dr. Emrich
========================

This project implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


| N             | Elapsed Time  | Memory Usage (bytes)  |
|---------------|---------------|-----------------------|
| 10            | 0.0026        | 107,696               |
| 20            | 0.0034        | 187,952               |
| 50            | 0.0076        | 814,768               |
| 100           | 0.0242        | 3,031,600             |
| 200           | 0.094         | 11,918,128            |
| 500           | 0.5886        | 64,763,440            |
| 1000          | 2.335         | 258,999,088           |
|---------------|---------------|-----------------------|

## Questions:
1) I created graph and nodes objects to help with representation (thanks Ashley). The graph object contained the actual
representation which was a 1D vector of nodes. Since we knew that the graph was a grid, I knew a particular node's neighbors
would be at locations i+1, i-1, i+NUM_COLS, i-NUM_COLS. The weights were attributed of the node objects and were applied as 
dijkstras left the node.
2) I think that my implementation of dijkstras is O(n). This is because at one point every edge must be added to the multimap and then eventually processed. My main loop continues until the map it empty, meaning that it is O(n). This doesn't include comparisons
though and I'm not sure how to factor that in.
3) Looking at the time data, it seems the true complexity might be closer to n^2 as the 10, 100, and 1000 trials do not increase linearly. The memory usage also caled with some type of exponent, though this makes more sense as it will just increase based on how many nodes it has to make

