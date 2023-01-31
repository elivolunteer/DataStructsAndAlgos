# cs302_proj2
| Mode		| Size		| Elapsed Time(s)	|
|-----------|-----------|-------------------|
| STL		| 10		| 0					|
| STL		| 100		| 0					|
| STL		| 1000		| 0					|
| STL		| 10000		| 0					|
| STL		| 100000	| 0					|
| STL		| 1000000	| 1					|
| STL		| 10000000	| 14				|
| QSORT		| 10		| 0					|
| QSORT		| 100		| 0					|
| QSORT		| 1000		| 0					|
| QSORT		| 10000		| 0					|
| QSORT		| 100000	| 0					|
| QSORT		| 1000000	| Seg. Fault		|
| QSORT		| 10000000	| Seg. Fault		|
| MERGE		| 10		| 0					|
| MERGE		| 100		| 0					|
| MERGE		| 1000		| 0					|
| MERGE		| 10000		| 0					|
| MERGE		| 100000	| 0					|
| MERGE		| 1000000	| 1					|
| MERGE		| 10000000	| 16				|
| QUICK		| 10		| 0					|
| QUICK		| 100		| 0					|
| QUICK		| 1000		| 0					|
| QUICK		| 10000		| 0					|
| QUICK		| 100000	| 0					|
| QUICK		| 1000000	| 2					|
| QUICK		| 10000000	| 32				|

##Questions
###1.
Not suprisingly, the stl sorts (both q and normal) are the fastest. They've been optimized and made by people smarter than us. Merge is next fastest, followed by quick. Though it's important to note that for the lower number of numbers, they all were really fast and similar in time.
###2.
Even though they all have the same theoretical complexity, the in lab testing shows the effect of those pesky factors that some algorithms have in front of them.
###3.
Stl sort is the best. It has been vetted by many developers and even chooses the most optimum sort based on the size of the container. It implements our fastest algorithms as well as even quicker ones. It is also extrememly easy to use and doesn't seg. fault! Out of the ones we really made, the merge sort is consistently fastest and is relativly easy to understand when implementing
