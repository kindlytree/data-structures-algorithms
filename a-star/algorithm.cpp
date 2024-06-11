#include "algorithm.h"
#include "puzzle.h"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

enum METHOD {UCWEL=0, ASTARWEL };

//generation neighbours(sucessors) of current state according to the up,right,down,left moving direction of the 0 tile 
//if the direction if not legal for moving, just skip this moving step.
//return the all candidate states placed in std::vector container. 
std::vector<Puzzle*> getSuccessors(Puzzle* p)
{
    //up,right,down,left order
    std::vector<Puzzle*>successors;
    if(p->canMoveUp()){
        Puzzle* p_u = p->moveUp();
        successors.emplace_back(p_u);
    }
    if(p->canMoveRight()){
        Puzzle* p_r = p->moveRight();
        successors.emplace_back(p_r);
    }
    if(p->canMoveDown()){
        Puzzle* p_d = p->moveDown();
        successors.emplace_back(p_d);
    }
    if(p->canMoveLeft()){
        Puzzle* p_l = p->moveLeft();
        successors.emplace_back(p_l);
    } 
    return successors;       
}


//check whether the two puzzle states are equal
//the two states are equal if and only if the state string are the same.
bool areStatesEqual(Puzzle* a, Puzzle* b)
{
    std::string a_str = a->toString();
    std::string b_str = b->toString(); 
    return a_str == b_str;

}

//comparing function used for stl functions make_heap and push_heap
//the function is used for the g cost comparision of two puzzle states in uniform cast search algorithm.
bool myComparision(Puzzle* state1, Puzzle* state2)`
{
    return state1->getGCost() > state2->getGCost();
}

//comparing function used for stl functions make_heap and push_heap
//the function is used for the f cost(g cost + h cost) comparision of two puzzle states in a star search algorithm.
bool myComparisionvh(Puzzle* state1, Puzzle* state2)
{
    return (state1->getGCost()+state1->getHCost()) > (state2->getGCost()+state1->getHCost());
}

// Function to check if a state is alreay present in the expanded list
bool isStateExpanded(Puzzle* state, const std::vector<Puzzle*>& expanded) {
    for (auto s : expanded) {
        if (areStatesEqual(s, state)) {
            return true;
        }
    }
    return false;
}

// Function to check if a state is alreay present in the expanded list
//expanded_state_map is the auxiliary data structure to speed up the search process 
bool isStateExpanded(Puzzle* state, std::map<std::string, Puzzle*>&expanded_state_map) {
    bool found = false;

    std::string pullze_state_str = state->toString();
    std::map<std::string, Puzzle*>::iterator iter = expanded_state_map.find(pullze_state_str);
    if(iter != expanded_state_map.end()){
        found = true;
    }
    return found;
}

// Function to check if a state is present in the frontier
// we first pop the state from the priority queue iteratively until the state is found or state does existes.
// when states founded or we poped the whole queue,we then push the poped state to the queue(back to original queue)
bool isStateInFrontier(Puzzle* state, std::vector<Puzzle*>& frontier, int method) {
    vector<Puzzle*> temp;
    bool found = false;
    
    while (!frontier.empty()) {
        // Puzzle* top = frontier.top();
        // frontier.pop();
        Puzzle* top = frontier.front();
        std::pop_heap(frontier.begin(), frontier.end());
        frontier.pop_back();
        
        if (areStatesEqual(top, state)) {
            found = true;
            temp.push_back(top);
            break;
        }  
        temp.push_back(top);
    }
    
    for (auto s : temp) {
        frontier.push_back(s);
        if(method == METHOD::UCWEL)
        {
            std::push_heap(frontier.begin(), frontier.end(), myComparision);
        }else if (method == METHOD::ASTARWEL)
        {
            std::push_heap(frontier.begin(), frontier.end(), myComparisionvh);
        }
        //frontier.push(s);
    }
    //std::make_heap(frontier.begin(), frontier.end(), myComparision);
    return found;
}

//function to check whether puzzle state has alreay been added to the priority queue
//frontier_state_map is the auxiliary data structure to speed up the search process 
bool isStateInFrontier(Puzzle* state, std::map<std::string, Puzzle*>&frontier_state_map) {
    bool found = false;

    std::string pullze_state_str = state->toString();
    std::map<std::string, Puzzle*>::iterator iter = frontier_state_map.find(pullze_state_str);
    if(iter != frontier_state_map.end()){
        found = true;
    }
    return found;
}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  UC with Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string uc_explist(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;

    // cout << "------------------------------" << endl;
    // cout << "<<uc_explist>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	//srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	//maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	//numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY
    
    //we use std::vector to store the states as priority queue(PQ, min heap)
    //we use make_heap,push_heap,pop_heap std function to maintain the PQ
    std::vector<Puzzle*> frontier;//priority queue storage for puzzle states, it's priority is the g cost of the state, the smaller the higher priority.
    std::vector<Puzzle*> expandedList;  // expaned list for recording the list which has been explored in the search process.
    Puzzle* initialPuzzle = new Puzzle(initialState, goalState);
    frontier.push_back(initialPuzzle);//initial vector data for heap storage;
    std::make_heap(frontier.begin(), frontier.end(), myComparision);//stl make_heap template function to generate heap from the vector
    Puzzle* statePath = nullptr;
    std::map<std::string, Puzzle*>frontier_state_map;//map data structure to store the puzzle states been added to the priority queue.
    std::map<std::string, Puzzle*>expanded_state_map;//map data structure to store the puzzle states been added to the expanded list.
    frontier_state_map.insert(std::pair<std::string, Puzzle*>(initialPuzzle->toString(), initialPuzzle));

    while (!frontier.empty()) {
        Puzzle* currentState = frontier.front();//fetch heap top
        std::pop_heap(frontier.begin(), frontier.end());//pop the top element of the heap to the last position of the vector
        frontier.pop_back();//remove the last element, the above two lines code combined to implement priority queue pop operation.
        if(currentState->goalMatch()){
            //find the goal state, stop search.
            statePath = currentState;
            break;
        }

        //debug code for intermidate seach state ouput
        //std::cout << currentState->getPathLength() << ": " << frontier.size() << " : " << expandedList.size() << std::endl;
        
        //update the current maxQLength state.
        if(frontier.size() > maxQLength){
            maxQLength = frontier.size();
        }

        // the currently explored state is added to the expaned list.
        expandedList.emplace_back(currentState);
        expanded_state_map.insert(std::pair<std::string, Puzzle*>(currentState->toString(), currentState));

        // call fuction to get the available successors(neighbors) of the current puzzle state
        std::vector<Puzzle*> successors = getSuccessors(currentState);

        for (auto successor : successors) {
            // if the successor has  been expanded before just skip the later part of current iteration.
            if(isStateExpanded(successor, expanded_state_map)){
                numOfAttemptedNodeReExpansions++;
                delete successor;
                continue;
            }
            //the successor's state is alreay in the frontier_state_map, there is no need to push and just skip the later part of current iteration.
            if(isStateInFrontier(successor, frontier_state_map))
            {
                numOfDeletionsFromMiddleOfHeap++;
                delete successor;
                continue;
            }

            //push the current neighbor to the priority queue
            frontier.push_back(successor);
            //heapify the priority queue
            std::make_heap(frontier.begin(), frontier.end(), myComparision);
            frontier_state_map.insert(std::pair<std::string, Puzzle*>(successor->toString(), successor));
        }
        delete currentState;
    }
	
	
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	//path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
    path = statePath->getPath();
	pathLength = path.size();
    numOfStateExpansions = expandedList.size();
    std::cout << path << std::endl;
	return path;		
		
}




///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////
string aStar_ExpandedList(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){
											 
   string path;
   clock_t startTime;
   
   numOfDeletionsFromMiddleOfHeap=0;
   numOfLocalLoopsAvoided=0;
   numOfAttemptedNodeReExpansions=0;


    // cout << "------------------------------" << endl;
    // cout << "<<aStar_ExpandedList>>" << endl;
    // cout << "------------------------------" << endl;
	actualRunningTime=0.0;	
	startTime = clock();
	//srand(time(NULL)); //RANDOM NUMBER GENERATOR - ONLY FOR THIS DEMO.  YOU REALLY DON'T NEED THIS! DISABLE THIS STATEMENT.
	//maxQLength= rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY.
	//numOfStateExpansions = rand() % 200; //AT THE MOMENT, THIS IS JUST GENERATING SOME DUMMY VALUE.  YOUR ALGORITHM IMPLEMENTATION SHOULD COMPUTE THIS PROPERLY

    std::vector<Puzzle*> frontier;
    std::vector<Puzzle*> expandedList;  
    Puzzle* initialPuzzle = new Puzzle(initialState, goalState);
    frontier.push_back(initialPuzzle);//initial vector data for heap storage;
    std::make_heap(frontier.begin(), frontier.end(), myComparisionvh);//stl make_heap template function to generate heap from the vector
    Puzzle* statePath = nullptr;
    std::map<std::string, Puzzle*>frontier_state_map;
    std::map<std::string, Puzzle*>expanded_state_map;
    frontier_state_map.insert(std::pair<std::string, Puzzle*>(initialPuzzle->toString(), initialPuzzle));

    while (!frontier.empty()) {
        Puzzle* currentState = frontier.front();//fetch heap top
        std::pop_heap(frontier.begin(), frontier.end());
        frontier.pop_back();
        //frontier.pop();
        if(currentState->goalMatch()){
            statePath = currentState;
            break;
        }

        //std::cout << currentState->getPathLength() << ": " << frontier.size() << " : " << expandedList.size() << std::endl;
        if(frontier.size() > maxQLength){
            maxQLength = frontier.size();
        }

        expandedList.emplace_back(currentState);
        expanded_state_map.insert(std::pair<std::string, Puzzle*>(currentState->toString(), currentState));

        std::vector<Puzzle*> successors = getSuccessors(currentState);

        for (auto successor : successors) {
            if(isStateExpanded(successor, expanded_state_map)){
                numOfAttemptedNodeReExpansions++;
                delete successor;
                continue;
            }
            if(isStateInFrontier(successor, frontier_state_map))
            {
                numOfDeletionsFromMiddleOfHeap++;
                delete successor;
                continue;
            }
            //call heristic function to update h cost
            successor->updateHCost(heuristic);
            frontier.push_back(successor);
            std::make_heap(frontier.begin(), frontier.end(), myComparisionvh);
            frontier_state_map.insert(std::pair<std::string, Puzzle*>(successor->toString(), successor));
        }
        delete currentState;
    }
//***********************************************************************************************************
	actualRunningTime = ((float)(clock() - startTime)/CLOCKS_PER_SEC);
	//path = "DDRRLLLUUURDLUDURDLUU"; //this is just a dummy path for testing the function
    path = statePath->getPath();
	pathLength = path.size();
    std::cout << path << std::endl;
	return path;		
}

