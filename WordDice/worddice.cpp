// Eli Carter
// Proj5 CS302
//Word dice solution using network flow
//Thanks to ashley for the class setup and help on infinite loop caused by BFS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef enum{SOURCE, SINK, WORD, DICE} Node_Type;

class Edge{
	public:
		//from -> to
		class Node *to; //node edge is pointing to
		class Node *from; //node edge is pointing from
		Edge(class Node *to, class Node *from, bool reverse_edge=false); //constructor for edges
		~Edge(){}; //default destructor
		Edge *reverse; //edge going the other way
		int original; //original weight per edge
		int residual; //allows for updated weighting during Edmonds-Karp
		void print_edge();
};

class Node{
	public:
		Node(int id, Node_Type type, string word = ""); //constructor for nodes
		~Node(){}; //default destructor
		int id; //node id
		Node_Type type; //type of node it is (source, sink, word or dice)
		bool letters[26] = {false}; //length 26 with letters contained in word set to 1
		int visited; //for BFS
		vector<Edge*> adj; //adjacency list
		Edge *backedge; //previous edge for Edmonds-Karp
		void print_node();
};

class Graph{
	public:
		Graph(); //constructor initializes graph with source node
		~Graph(); //destructor to deallocate memory of graph
		Node *source, *sink; //not necessary but makes code more readable
		vector<Node *> nodes; //holds the nodes
		vector<int> spellingIds; //order of flow to spell word
		int min_nodes; //min number of dice nodes
		void add_dice_to_graph(string die, int id); //add dice nodes to graph
		void add_word_to_graph(string word, int id); //add word (letter) nodes to graph
		bool BFS(); //breadth first search for Edmonds-Karp
		bool spell_word(); //runs Edmonds-Karp to see if we can spell the word
		void delete_word_from_graph(); //deletes the word nodes but leaves the dice nodes
		void print_node_order(string word); //print spelling Ids and word
		void print_graph();
};

int main(int argc, char *argv[]) {
	//get input out of files
	ifstream dice_f, words_f;
	dice_f.open(argv[1]);
	words_f.open(argv[2]);

	vector<string> dice_s;
	string tmp;
	while (dice_f >> tmp){
		dice_s.push_back(tmp);
	}
	dice_f.close();

	vector<string> words_s;
	while (words_f >> tmp){
		words_s.push_back(tmp);
	}
	words_f.close();

	//Create dice, source nodes
	Graph graph;
	int perm_node_count = 1;
	for (unsigned int i = 0; i < dice_s.size(); i++){
		graph.add_dice_to_graph(dice_s[i], perm_node_count++);
	}

	//begin loop that will run for every word in list
	for (unsigned int i = 0; i < words_s.size(); i++){
		//Create word, sink nodes
		graph.add_word_to_graph(words_s[i], perm_node_count);
		//graph.print_graph();
		//run algo
		graph.print_node_order(words_s[i]);

		//clean up for next word
		graph.delete_word_from_graph();
		graph.spellingIds.clear(); //need to clear this after every word
	}

	return 0;
}

Edge::Edge(class Node *to, class Node *from, bool reverse_edge /*=false*/){
	this->to = to;
	this->from = from;
	if (reverse_edge){
		this->original = 0;
		this->residual = 1;
	}
	else{
		this->original = 1;
		this->residual = 0;
	}
}

void Edge::print_edge(){
	cout << "       Edge from " << from->id << " to " << to->id << " OG: " << original << " Res: " << residual << endl;
}

Node::Node(int id, Node_Type type, string word /*=""*/){
	//cout << "Creating Node: " << id << " : " << word << endl;
	this->id = id;
	this->type = type;
	for (unsigned int i = 0; i < word.size(); i++){
		letters[(int)word[i]-65] = true;
	}
}

void Node::print_node(){
	cout << "   Node: " << id << " Type: " << type << " Num_edges: " << adj.size() << " Letters: ";
	for (unsigned int i = 0; i < 26; i++){
		if (letters[i] == true){
			cout << (char)(i+65);
		}
	}
	cout << endl;
	for (unsigned int i = 0; i < adj.size(); i++){
		adj[i]->print_edge();
	}
}

Graph::Graph(){
	source = new Node(0, SOURCE);
	nodes.push_back(source);
}

Graph::~Graph(){
	for (int i = nodes.size()-1; i >= 0; i--){
		delete nodes[i];
		nodes.erase(nodes.begin()+i);
	}
}

void Graph::add_dice_to_graph(string die, int id){
	Node* tmp_node = new Node(id, DICE, die);
	//add source to dice edges
	Edge* tmp_edge = new Edge(tmp_node, source);
	Edge* tmp_redge = new Edge(source, tmp_node, true);
	tmp_edge->reverse = tmp_redge;
	tmp_redge->reverse = tmp_edge;
	tmp_node->adj.push_back(tmp_redge);
	source->adj.push_back(tmp_edge);
	nodes.push_back(tmp_node);
	//return;
}

void Graph::add_word_to_graph(string word, int id){
	for (unsigned int i = 0; i < word.size(); i++){
		Node* tmp_node = new Node(id+i, WORD, string(1,word[i]));
		//add dice to word edges
		for (unsigned int j = 0; j < nodes.size(); j++){
			if (nodes[j]->type == DICE){
				//check if the letter is in the dice
				if (nodes[j]->letters[(int)word[i]-65] == true){
					Edge* tmp_edge = new Edge(tmp_node, nodes[j]);
					Edge* tmp_redge = new Edge(nodes[j], tmp_node, true);
					tmp_edge->reverse = tmp_redge;
					tmp_redge->reverse = tmp_edge;
					tmp_node->adj.push_back(tmp_redge);
					nodes[j]->adj.push_back(tmp_edge);
				}
			}
		}
		nodes.push_back(tmp_node);
	}
	sink = new Node(id+word.size(), SINK);
	//add word to sink edges
	for (unsigned int i = 0; i < nodes.size(); i++){
		if (nodes[i]->type == WORD){
			Edge* tmp_redge = new Edge(nodes[i], sink, true);
			Edge* tmp_edge = new Edge(sink, nodes[i]);
			tmp_edge->reverse = tmp_redge;
			tmp_redge->reverse = tmp_edge;
			nodes[i]->adj.push_back(tmp_edge);
			sink->adj.push_back(tmp_redge);
		}
	}

	nodes.push_back(sink);
	//return;
}

void Graph::delete_word_from_graph(){
	//loop through right half of graph
	for (int i = nodes.size()-1; i >= 0; i--){
		//loop through right half of graph
		if (nodes[i]->type == WORD || nodes[i]->type == SINK){
			//delete edges attached
			for (int j = nodes[i]->adj.size()-1; j >= 0; j--){
				Edge* removing = nodes[i]->adj[j];
				Edge* removing_r = removing->reverse;
				Node* that_side = removing->to;
				Node* this_side = removing->from;
				//erase from node on both sides of the edge
				vector<Edge*>::iterator this_it, that_it;
				this_it = find(this_side->adj.begin(),this_side->adj.end(),removing);
				that_it = find(that_side->adj.begin(),that_side->adj.end(),removing_r);
				delete removing;
				delete removing_r;
				this_side->adj.erase(this_it);
				that_side->adj.erase(that_it);
			}
			delete nodes[i];
			nodes.erase(nodes.begin()+i);
		}
	}
	//reset the edges around source
	for (unsigned int i = 0; i < source->adj.size(); i++){
		source->adj[i]->original = 1;
		source->adj[i]->residual = 0;
		source->adj[i]->reverse->original = 0;
		source->adj[i]->reverse->residual = 1;
	}
}

void Graph::print_graph(){
	cout << "This graph conatins:" << endl;
	for (unsigned int i = 0; i < nodes.size(); i++){
		nodes[i]->print_node();
	}
}

bool Graph::BFS(){
	for (unsigned int i = 0; i < this->nodes.size(); i++){
		nodes[i]->backedge = nullptr;
		nodes[i]->visited = false;
	}

	//vector<int> visited;
	queue<Node*> frontier;
	frontier.push(source);

	while (!frontier.empty()){
		//cout << "   BFS looking" << endl;
		Node* tmp = frontier.front();
		frontier.pop();

		tmp->visited = true;

		if(tmp->type == SINK) return true;

		//check if this is visited or not
		//visited.push_back(tmp->id);

		for (unsigned int i = 0; i < tmp->adj.size(); i++){
			if (tmp->adj[i]->to->visited == false && tmp->adj[i]->original == 1){
				tmp->adj[i]->to->backedge = tmp->adj[i]->reverse;
				frontier.push(tmp->adj[i]->to);
			}
		}
	}

	return false;
}

bool Graph::spell_word(){
	//continue until there are no more paths
	while (this->BFS() == true){
		//cout << "BFS found a path" << endl;
		//this->print_graph();
		//follow backedges from sink to source
		Node* it = sink;
		while (it->id != 0){
			//swap the orgs and res
			it->backedge->original = 1;
			it->backedge->residual = 0;
			it->backedge->reverse->original = 0;
			it->backedge->reverse->residual = 1;
			it = it->backedge->to;
		}
	}
	//if all of the edges coming out of sink have residual of 0 then it must be spelled
	unsigned int num_letter_paths = 0;
	for (unsigned int i = 0; i < sink->adj.size(); i++){
		if (sink->adj[i]->residual == 0){
			num_letter_paths++;
		}
	}
	if (sink->adj.size() == num_letter_paths){
		return true;
	}
	else{
		return false;
	}
}

void Graph::print_node_order(string word){
	// check if word can be found
	if (this->spell_word()){
		for (unsigned int i = 0; i < sink->adj.size(); i++){
			Node* letter = sink->adj[i]->to;
			if (i == 0){
				for (unsigned int j = 0; j < letter->adj.size(); j++){
					if (letter->adj[j]->original == 1){
						cout << letter->adj[j]->to->id - 1;
					}
				}
			}
			else{
				for (unsigned int j = 0; j < letter->adj.size(); j++){
					if (letter->adj[j]->original == 1){
						cout << "," << letter->adj[j]->to->id - 1;
					}
				}
			}
		}
		cout << ": " << word << endl;

	}
	else{
		cout << "Cannot spell " << word << endl;
	}
}