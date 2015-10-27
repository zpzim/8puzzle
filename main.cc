
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
	cout << "Select puzzle size (warning: 15-puzzle and 24-puzzle are very slow and will use a lot of memory, they may even run out of memory)." << endl;
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
		return 0;
		break;
	}
	search_tree_node::setLW(N);
	cout << "Select search heuristic." << endl;
	cout << "1. Uniform Cost(very slow, may run out of memory)" << endl;
	cout << "2. Misplaced Tile(slow, may run out of memory)" << endl;
	cout << "3. Manhattan Distance(fast)" << endl;
	cout << "Enter a choice (1 - 3): " << endl;
	choice = 0;
	cin >> choice;
	MemFn h;
	switch(choice){
	case 1:
		h = &search_tree_node::uniform_cost;
		break;
	case 2:
		h = &search_tree_node::misplaced_tile;
		break;
	case 3:
		h = &search_tree_node::manhattan;
		break;
	default:
		cout << "invalid choice" << endl;
		return 0;
		break;
	}
	unordered_map<int, int> pstate;
	int elementCount = 1;
	int item = 0;
	int bpos = 0;

	cout << "Select puzzle input type." << endl;
	cout << "1. User Selects" << endl;
	cout << "2. Random" << endl;
	cout << "Enter a choice (1 - 2): " << endl;
	choice = 0;
	cin >> choice;
	bool userInput = false;
	switch(choice){
	case 1:
		userInput = true;
		break;
	case 2:
		userInput = false;
		break;
	default:
		cout << "invalid choice" << endl;
		return 0;
		break;
	}
	if(userInput){
		bool valid = false;
		while(!valid){
			pstate = unordered_map<int,int>();
			bpos = 0;
			item = 0;
			elementCount = 1;
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
			search_tree_node test(bpos, pstate, 0);
			valid = test.isSolvable();
			if(!valid){
				cout << "The puzzle you entered is not solvable, please enter a new puzzle." << endl;
			}
		}
	}else{
		cout << "Generating solvable puzzle... " << endl;
		vector<int> positions(n);
		for(int i = 0; i < n; ++i){
			positions.at(i) = i + 1;
		}
		bool valid = false;
		while(!valid){
			bpos = 0;
			pstate = unordered_map<int,int>();
			vector<int> p = positions;
			for(int i = 1; i <= n; ++i){
				int pos = rand() % p.size();
				if(p[pos] == n){
					bpos = i;
				}
				pstate.insert(make_pair(i, p[pos]));
				p.erase(p.begin() + pos);
			}
			search_tree_node test(bpos, pstate, 0);
			valid = test.isSolvable();
			
		}



	}
	
	//cout << bpos << endl;
	search_tree_node* root = new search_tree_node(bpos, pstate, 0);
	cout << "solving the following puzzle with A* and the provided heuristic..." << endl;
	root -> print_state();
	cout << "Entering a*" << endl;
	if(/*iterativeDeepeningAStar(root, 10 )*/ AStar(root, h)){
		cout << "Success" << endl;
	}else{
		cout << "Failure" << endl;
	}
	//delete root;
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
	long long expanded = 0;
	long long totalNodesGenerated = 1;
	//unordered_set<search_tree_node*, hash<search_tree_node*>, Comp2> visited;
	priority_queue<search_tree_node*, vector<search_tree_node*>, Comp> nodes;
	nodes.push(root);
	long long maxQueueLength = 1;
	
	while(!nodes.empty()){
		//cout << expanded << endl;
		search_tree_node* curr = nodes.top();
		nodes.pop();
		//curr -> print_state();
		//cout << curr->getCost() << endl;
		if (curr -> isSolved()){
			curr -> print_state();
			cout << "Number of expanded nodes = " << expanded << endl;
			cout << "Total nodes generated = " << totalNodesGenerated << endl;
			cout << "Max queue length = " << maxQueueLength << endl;
			cout << "Solution depth = " << curr -> getDepth() << endl;
			return true;
		}
		vector<search_tree_node*> children = curr->expand(heuristic);
		expanded++;
		totalNodesGenerated += children.size();
		for(auto item : children){
			//if(visited.count(item) == 0){
			//	visited.insert(item);
				nodes.push(item);
			//}else{
			//	repeat++;
			//}
		}
		if(nodes.size() > maxQueueLength){
			maxQueueLength = nodes.size();
		}
		delete curr;
	}
	return false;
		
	
	


}
