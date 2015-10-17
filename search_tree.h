#ifndef _SEARCH_TREE_H_
#define _SEARCH_TREE_H_

#include<vector>
#include<unordered_map>


using namespace std;

class search_tree_node;
typedef  int (search_tree_node::*MemFn)();

class search_tree_node
{
	private:
		static int _N_;
		int blank_pos;
		int depth;
		int current_cost;
		void swapPos(int blank_spot, int p2);
		vector<search_tree_node*> children;
		
	public:
		//puzzle state
		unordered_map<int,int> puzzle_state;

		//Constructor
		search_tree_node(int blank, const unordered_map<int,int> p, int d) : blank_pos(blank), puzzle_state(p), current_cost(0), depth(d) {}

		//Destructor
		~search_tree_node();
		
		//Accessors
		int getDepth() {return depth;}
		int getCost() {return current_cost;}
		bool isSolved();

		//Mutators
		vector<search_tree_node*> expand(MemFn heuristic);
		static void setLW(int LW){ _N_ = LW; }

		//operators
		bool operator>=(const search_tree_node &other);
		
		//Heuristics
		int manhattan();
		int uniform_cost() {return 0;}
		int misplaced_tile();
		
		//Print and Debug		
		void print_state();
		
		
};


#endif
