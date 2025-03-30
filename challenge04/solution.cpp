// Challenge 04: Graph Paths
// Name: Dennis Madapatu
// Date: 2/15/2025
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

typedef unordered_map<char, vector<char>> adjList;

// Most of comments are notes for myself to look back on
bool BFS_Traversal(char goal, char value, adjList adjList1) { // Using Emrich's slideshow example of a BFS traversal
  queue<char> chars;
  unordered_map<char, bool> visited;
  chars.push(value);
  while(chars.size() != 0) {
    char val = chars.front(); // Pop off the front of the queue (FIFO type beat)
    chars.pop();
    if(visited[val] == true) { // Skip to next char if the one being checked has already been visited
      continue;
    }
    for(size_t i = 0; i < adjList1[val].size(); i++) {
      if(adjList1[val][i] == goal) { // If we find the goal inside of the map, return true and get out
        return true;
      }
      visited[val] = true; // Visited the value
      chars.push(adjList1[val][i]); // Push chars attached to the current node into the chars queue to check
    }
  }
  return false;
}

// Main Execution

int main(int argc, char *argv[]) {
  int nEdges;
  int nPaths;
  int graphNum = 0;
  char source;
  char destination;
  while(cin >> nEdges) {
    adjList adjList1;
    graphNum++;
    for(int i = 0; i < nEdges; i++) { // Loops through all of the edges and inputs them into the map
      cin >> source >> destination;
      adjList1[source].push_back(destination); //Pushes destination into a vector of destinations for the specific source, as a source can have more than one destination
    }
    cin >> nPaths;
    for(int i = 0; i < nPaths; i++) {
      cin >> source >> destination;
      bool valueFound = BFS_Traversal(destination, source, adjList1);
      if(valueFound == false) {
        cout << "In Graph " << graphNum << " there is no path from " << source << " to " << destination << endl;
      }
      else {
        cout << "In Graph " << graphNum << " there is a path from " << source << " to " << destination << endl;
      }
    }
    if(graphNum < 5) { // For formatting purposes
      cout << endl;
    }
  }
}


