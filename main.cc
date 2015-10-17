
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
	int N = 0;
	int n = 0;
	srand(time(0));
	cout << "1. 8-puzzle" << endl;
	cout << "2. 15-puzzle" << endl;
	cout << "3. 24-puzzle" << endl;
	cout << "Enter a choice (1 - 3): " << endl;
	int choice = 0;
	cin >> choice;
	switch(choice){
	case 1:
		N = 3;
		n = 9;
		break;
	case 2:
		N = 4;
		n = 16;
		break;
	case 3:
		N = 5;
		n = 25;
		break;
	default:
		cout << "invalid choice" << endl;
		break;
	}
	unordered_map<int, int> pstate;
	int elementCount = 1;
	int item = 0;
	int bpos = 0;
	for(int i = 0; i < N; ++i){
		cout << "Please enter row " << i + 1 << " of the start state of the puzzle (" << N << ") elements." << endl;
		for(int j = 1; j <= N; ++j){
			cin >> item;
			if(item == n){
				bpos = elementCount;
			}
 			pstate.insert(make_pair(elementCount, item));
			++elementCount;
		}
	}
	
	/*
	pstate.insert(make_pair(1,16));
	pstate.insert(make_pair(2,15));
	pstate.insert(make_pair(3,14));
	pstate.insert(make_pair(4,13));
	pstate.insert(make_pair(5,12));
	pstate.insert(make_pair(6,11));
	pstate.insert(make_pair(7,10));
	pstate.insert(make_pair(8,9));
	pstate.insert(make_pair(9,8));
	pstate.insert(make_pair(10,7));
	pstate.insert(make_pair(11,6));
	pstate.insert(make_pair(12,5));
	pstate.insert(make_pair(13,4));
	pstate.insert(make_pair(14,3));
	pstate.insert(make_pair(15,2));
	pstate.insert(make_pair(16,1));
	//pstate.insert(make_pair(1,8));
	//pstate.insert(make_pair(2,6));
	//pstate.insert(make_pair(3,7));
	//pstate.insert(make_pair(4,2));
	//pstate.insert(make_pair(5,5));
	//pstate.insert(make_pair(6,4));
	//pstate.insert(make_pair(7,3));
	//pstate.insert(make_pair(8,9));
	//pstate.insert(make_pair(9,1));
	*/
	search_tree_node::setLW(N);
	cout << bpos << endl;
	search_tree_node* root = new search_tree_node(bpos, pstate, 0);
	
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
			curr -> print_state();
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
