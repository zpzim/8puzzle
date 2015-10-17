
#include<iostream>

#include "search_tree.h"
using namespace std;

int search_tree_node::_N_;

//delete search tree when done
search_tree_node::~search_tree_node(){
		for(auto i : children){
			delete i;
		}

}


//Expands a node to generate its children
vector<search_tree_node*> search_tree_node::expand(MemFn heuristic){
	//cout << blank_pos - 1 << endl;
	int row = (blank_pos - 1) / _N_;
	int col = (blank_pos - 1) % _N_;
	search_tree_node* c1 = new search_tree_node(blank_pos, puzzle_state, depth + 1);
	search_tree_node* c2 = new search_tree_node(blank_pos, puzzle_state, depth + 1);
	//If we are on a corner we only have 2 moves	
	//upper left
	if(row == 0 && col == 0){
		c1->swapPos(blank_pos, blank_pos + 1);
		c2->swapPos(blank_pos, blank_pos + _N_);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
	//upper right
	}else if(row == 0 && col == _N_ - 1){
		c1->swapPos(blank_pos, blank_pos - 1);
		c2->swapPos(blank_pos, blank_pos + _N_);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
	//lower left
	}else if(row == _N_ - 1 && col == 0){
		c1->swapPos(blank_pos, blank_pos + 1);
		c2->swapPos(blank_pos, blank_pos - _N_);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
	//lower right
	}else if(row == _N_ - 1 && col == _N_ - 1){
		c1->swapPos(blank_pos, blank_pos - 1);
		c2->swapPos(blank_pos, blank_pos - _N_);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
	//if we are on an edge we have 3 moves
	//top edge
	}else if(row == 0){
		search_tree_node* c3 = new search_tree_node(blank_pos, puzzle_state, depth + 1); 
		c1->swapPos(blank_pos, blank_pos + 1);
		c2->swapPos(blank_pos, blank_pos + _N_);
		c3->swapPos(blank_pos, blank_pos - 1);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		c3->current_cost += depth + 1 + (c3 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
		children.push_back(c3);
	//bottom edge
	}else if(row == _N_ - 1){
		search_tree_node* c3 = new search_tree_node(blank_pos, puzzle_state, depth + 1);
		c1->swapPos(blank_pos, blank_pos + 1);
		c2->swapPos(blank_pos, blank_pos - _N_);
		c3->swapPos(blank_pos, blank_pos - 1);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		c3->current_cost += depth + 1 + (c3 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
		children.push_back(c3);
	//left edge
	}else if(col == 0){
		search_tree_node* c3 = new search_tree_node(blank_pos, puzzle_state, depth + 1);
		c1->swapPos(blank_pos, blank_pos + 1);
		c2->swapPos(blank_pos, blank_pos - _N_);
		c3->swapPos(blank_pos, blank_pos + _N_);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		c3->current_cost += depth + 1 + (c3 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
		children.push_back(c3);
	//right edge
	}else if(col == _N_ - 1){
		search_tree_node* c3 = new search_tree_node(blank_pos, puzzle_state, depth + 1);
		c1->swapPos(blank_pos, blank_pos - 1);
		c2->swapPos(blank_pos, blank_pos - _N_);
		c3->swapPos(blank_pos, blank_pos + _N_);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		c3->current_cost += depth + 1 + (c3 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
		children.push_back(c3);
	//If we are in the middle we have 4 moves
	}else{
		search_tree_node* c3 = new search_tree_node(blank_pos, puzzle_state, depth + 1);
		search_tree_node* c4 = new search_tree_node(blank_pos, puzzle_state, depth + 1);
		c1->swapPos(blank_pos, blank_pos - 1);
		c2->swapPos(blank_pos, blank_pos - _N_);
		c3->swapPos(blank_pos, blank_pos + _N_);
		c4->swapPos(blank_pos, blank_pos + 1);
		c1->current_cost += depth + 1 + (c1 ->* heuristic)();
		c2->current_cost += depth + 1 + (c2 ->* heuristic)();
		c3->current_cost += depth + 1 + (c3 ->* heuristic)();
		c4->current_cost += depth + 1 + (c4 ->* heuristic)();
		children.push_back(c1);
		children.push_back(c2);
		children.push_back(c3);
		children.push_back(c4);
	}
	return children;


}


//Swaps the position of the blank and another position on the board
void search_tree_node::swapPos(int blank_spot, int p2){
	int temp1 = puzzle_state.at(blank_spot);
	puzzle_state.at(blank_spot) = puzzle_state.at(p2);
	puzzle_state.at(p2) = temp1;
	blank_pos = p2;
	
}

//Manhattan distance heuristic
int search_tree_node::manhattan(){
	int a, b, acol, bcol, arow, brow;
	int cost = 0;
	for(auto item : puzzle_state){
		a = item.first - 1;
		b = item.second - 1;
		acol = a % _N_;
		arow = a / _N_;
		bcol = b % _N_;
		brow = b / _N_;
		cost += abs(brow - arow) + abs(bcol - acol);
	}
	return cost;
}

//Misplaced tile heuristic
int search_tree_node::misplaced_tile(){
	int count = 0;
	int n = _N_ * _N_;
	for( auto item : puzzle_state){
		if( item.first != item.second && item.second != n){
			count++;
		}
	}
	return 0;
}

bool search_tree_node::operator>=(const search_tree_node &other){
	if(current_cost >= other.current_cost){
		return true;
	}
	return false;

}

//Checks if puzzle is in a solved state
bool search_tree_node::isSolved(){
	int n = _N_ * _N_;
	for(int i = 1; i <= n; ++i){
		if(puzzle_state.at(i) != i){
			return false;
		}
	}
	return true;

}

//Prints the puzzle state
void search_tree_node::print_state(){
	int n = _N_ * _N_;
	for(int i = 1; i <= n; ++i){
		if(i % _N_== 1){
			cout << endl;
		}
		cout << puzzle_state.at(i) << " ";
		
	}
	cout << endl;
}
