# proj5

My github repo is https://github.com/elivolunteer/proj5

Contributions:
It was all written by me, with help from Ashley for class setup and some troubleshooting

Questions:
Complexity - For a single run of worddice, the complexity can be thought of like this. First, the only "nodes" that really matter is the dice and word nodes, but even then you only need as many dice as there are letters in the word. So there is 2(length of word) nodes. 2V. constants infront of the # of vertices can be ignored so it's just V. For each letter, the augmented path has to be found and there are V*E possible augmented paths. So the total complexity is O(V\*E\*\*2).
