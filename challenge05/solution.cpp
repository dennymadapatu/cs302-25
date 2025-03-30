// Name: Dennis Madapatu
// Date: 3/5/2025
// Challenge 5: Minimum Spanning Tree

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

int primsAlg(multimap<char, pair<char, int>> weights, int nVertices, vector<string> &pathsTaken) { // Return the total weight, and pathsTaken is utilized through pass-by reference
  int totalCost = 0;
  set<char> visited;
  vector<pair<int, pair<char, char>>> edges; // This is our frontier
  char charSource = 'A'; // Starting at 'A'
  visited.insert(charSource);
  auto range = weights.equal_range(charSource); // Taken from GeeksForGeeks: https://www.geeksforgeeks.org/multimap-associative-containers-the-c-standard-template-library-stl/
  while((int) visited.size() != nVertices) { // When there are the same amount of vertices in visited, we know we have visited every vertex
    for(auto it = range.first; it != range.second; ++it) { // Putting things in our frontier
      char destination = it->second.first;
      int weight = it->second.second;
      edges.push_back({weight, {charSource, destination}});
    }
    sort(edges.begin(), edges.end());
    for(size_t i = 0; i < edges.size(); i++) { // Checking through each possible edge, starting from the first index after sorting
      char currentSource = edges[i].second.first;
      char currentDestination = edges[i].second.second;
      int currentWeight = edges[i].first;
      if((visited.find(currentDestination) == visited.end())) { // Didn't find the destination being checked in visited, this is a new node
        totalCost += currentWeight; // Immediately increment cost
        if(currentSource > currentDestination) { // Just adjustments so that the earlier letter is in the front for the path
          string path = "";
          path += currentDestination;
          path += currentSource;
          pathsTaken.push_back(path);
        }
        else {
          string path = "";
          path += currentSource;
          path += currentDestination;
          pathsTaken.push_back(path);
        }
        visited.insert(currentDestination); // Update visited
        range = weights.equal_range(currentDestination); // Update range
        charSource = currentDestination; // Update charSource
        break;
      }
    }
  }
  return totalCost; // Return the total cost at the end
}
// Main Execution

int main(int argc, char *argv[]) {
  int nVertices = 0;
  while(cin >> nVertices) {
    multimap<char, pair<char, int>> weights;
    // Use these nested for loops to take in the data 
    for(int i = 0; i < nVertices; i++) { // nVertices by nVertices board
      for(int j = 0; j < nVertices; j++) {
        int weight = 0;
        cin >> weight;
        if(weight > 0) {
          char source = (char) (i + 'A');
          char destination = (char) (j + 'A');
          weights.insert({source, {destination, weight}});
        }
      }
    }
    vector<string> pathsTaken;
    int totalWeight = primsAlg(weights, nVertices, pathsTaken);
    cout << totalWeight << endl;
    sort(pathsTaken.begin(), pathsTaken.end());
    for(size_t i = 0; i < pathsTaken.size(); i++) {
      if(cin.eof() && (i == pathsTaken.size() - 1)) { // For formatting purposes
        cout << pathsTaken[i];
      }
      else {
        cout << pathsTaken[i] << endl;
      }
    }
    if(!(cin.eof())) {
      cout << endl;
    }
  }
}
