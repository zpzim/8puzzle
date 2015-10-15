
#include<set>
#include<cstdlib>
#include<ctime>
#include<queue>
#include<iostream>
#include<unordered_set>

#include "search_tree.h"
using namespace std;
/*
bool iterativeDeepeningAStar(search_tree_node* root, int k);
*/
bool AStar(search_tree_node* root, MemFn heuristic);
struct Comp {
  inline bool operator()(search_tree_node* a, search_tree_node* b)
  { return *a >= *b; }
};

struct Comp2 {
  inline bool operator()(search_tree_node* a, search_tree_node* b) const
  { return a -> puzzle_state == b -> puzzle_state;}
};


int main(){
	srand(time(0));
	int n = 9;	
	unordered_map<int, int> pstate, tstate;
	pstate.insert(make_pair(1,8));
	pstate.insert(make_pair(2,6));
	pstate.insert(make_pair(3,7));
	pstate.insert(make_pair(4,2));
	pstate.insert(make_pair(5,5));
	pstate.insert(make_pair(6,4));
	pstate.insert(make_pair(7,3));
	pstate.insert(make_pair(8,9));
	pstate.insert(make_pair(9,1));
	search_tree_node* root = new search_tree_node(8, pstate, 0);
	if(/*iterativeDeepeningAStar(root, 10 )*/ AStar(root, &search_tree_node::manhattan)){
		cout << "Success" << endl;
	}else{
		cout << "Failure" << endl;
	}
	delete root;
	return 0;
}
/*
bool iterativeDeepeningAStar(search_tree_node* root, int k){
	for(int i = 0; i <= k; ++i){
		if(AStarManhattan(root, i)){
			return true;
		}
	}
	return false;
}	
*/

bool AStar(search_tree_node* root, MemFn heuristic){//, int k){
	int expanded = 0;
	//unordered_set<search_tree_node*, hash<search_tree_node*>, Comp2> visited;
	priority_queue<search_tree_node*, vector<search_tree_node*>, Comp> nodes;
	nodes.push(root);
	while(!nodes.empty()){
		//cout << expanded << endl;
		search_tree_node* curr = nodes.top();
		nodes.pop();
		//curr -> print_state();
		//cout << curr->getCost() << endl;
		if (curr -> isSolved()){
			cout << "Number of expanded nodes = " << expanded << endl;
			//cout << "Number of repeat states = " << repeat << endl;
			cout << "Solution depth = " << curr -> getDepth() << endl;
			return true;
		}
		vector<search_tree_node*> children = curr->expand(heuristic);
		expanded++;
		for(auto item : children){
			//if(visited.count(item) == 0){
			//	visited.insert(item);
				nodes.push(item);
			//}else{
			//	repeat++;
			//}
		}
	}
	return false;
		
	
	


}
