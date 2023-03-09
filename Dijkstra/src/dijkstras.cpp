// dijsktras.cpp
// Eli Carter
// CS302 Proj4
// implementation of dijsktras algo that can be used on 
// many different text based maps

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

//Structs borrowed from Ashley's slides
struct Node{
    int row = 0;
    int col = 0;
    char type = ' ';
    int distance = -1;
    Node *backedge = NULL;
    bool visited = false;
    void print();
};
struct Graph{
    vector<Node> graph;
    map<char, int> edge_weights;
    int MAP_ROWS;
    int MAP_COLS;
    void print();
};

void print_frontier(multimap<int,vector<Node*>> frontier){
    multimap<int, vector<Node*>>::iterator it;
	for (it = frontier.begin(); it != frontier.end(); ++it){
        cout << it->first  << " : (" << it->second.at(0)->row << "," << it->second.at(0)->col << ") -> (";
        cout << it->second.at(1)->row << "," << it->second.at(1)->col << ")" << endl;
    }
    cout << endl;
}

// Main Execution
int main(int argc, char *argv[]) {
    // board setup
    Graph graph;

    // Meta data about the game setup
    int num_types;
    cin >> num_types;
    for (int i = 0; i < num_types; i++){
        char type;
        cin >> type;
        int cost;
        cin >> cost;
        graph.edge_weights[type] = cost;
    }

    // build graph
    cin >> graph.MAP_ROWS >> graph.MAP_COLS;
    for (int i = 0; i < graph.MAP_ROWS*graph.MAP_COLS; i++){
        Node tmp;
        tmp.row = i / graph.MAP_COLS;
        tmp.col = i % graph.MAP_COLS;
        cin >> tmp.type;
        graph.graph.push_back(tmp);
    }

    int start_r, start_c, end_r, end_c;
    cin >> start_c >> start_r >> end_c >> end_r;

    // Dijsktras
    multimap<int,vector<Node*>> frontier;
    //initial set up
    graph.graph[end_c*graph.MAP_COLS+end_r].visited = true;
    graph.graph[end_c*graph.MAP_COLS+end_r].distance = 0;
    frontier.insert(pair <int, vector<Node*>> (0, {NULL,&graph.graph[end_c*graph.MAP_COLS+end_r]}));
    Node* curr = frontier.begin()->second.at(1);

    while(!frontier.empty()){
        // pop smallest path out and move there 
        if (frontier.begin()->first != 0){
            //print_frontier(frontier);
            //chcek if we've been here
            if (frontier.begin()->second.at(1)->visited == true){
                frontier.erase(frontier.begin());
                continue;
            }
            curr = frontier.begin()->second.at(1);
            Node* prev = frontier.begin()->second.at(0);
            curr->backedge = prev;
            curr->visited = true;
            curr->distance = prev->distance + graph.edge_weights[curr->type];
            frontier.erase(frontier.begin());
        }
        else{
            frontier.erase(frontier.begin());
        }

        // check the four surrounding squares if valid and if not visited
        //check above
        Node* checking = &graph.graph[curr->col + (curr->row-1)*graph.MAP_COLS];
        if (curr->row > 0 && checking->visited == false){
            int cummulative = curr->distance + graph.edge_weights[checking->type];
            frontier.insert(pair <int, vector<Node*>> (cummulative, {curr,checking}));
        }
        //check below
        checking = &graph.graph[curr->col + (curr->row+1)*graph.MAP_COLS];
        if (curr->row < graph.MAP_ROWS-1 && checking->visited == false){
            int cummulative = curr->distance + graph.edge_weights[checking->type];
            frontier.insert(pair <int, vector<Node*>> (cummulative, {curr,checking}));
        }
        //check right
        checking = &graph.graph[curr->col+1 + curr->row*graph.MAP_COLS];
        if (curr->col < graph.MAP_COLS-1 && checking->visited == false){
            int cummulative = curr->distance + graph.edge_weights[checking->type];
            frontier.insert(pair <int, vector<Node*>> (cummulative, {curr,checking}));
        }
        //check left
        checking = &graph.graph[curr->col-1 + curr->row*graph.MAP_COLS];
        if (curr->col > 0 && checking->visited == false){
            int cummulative = curr->distance + graph.edge_weights[checking->type];
            frontier.insert(pair <int, vector<Node*>> (cummulative, {curr,checking}));
        }
    }

    //Print total dist
    cout << graph.graph[start_c*graph.MAP_COLS+start_r].distance << endl;
    Node* trace = &graph.graph[start_c*graph.MAP_COLS+start_r];
    while (trace != NULL){
        cout << trace->row << " " << trace->col << endl;
        trace = trace->backedge;
    }
    return 0;
}

void Graph::print(){
    for (int i = 0; i < MAP_ROWS*MAP_COLS; i++){
        if (i % MAP_COLS == 0){
            cout << endl;
        }
        printf("%4d",graph[i].distance);
    }
}
void Node::print(){
    cout << "Node loc: (" << col << "," << row << ") Type: " << type << " Distance: " << distance << endl;
}