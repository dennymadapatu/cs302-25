// Name: Dennis Madapatu
// Date: 2/28/2025
// Description: Plays superball but it's kinda doodoo at it
#include "disjoint.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>

using namespace std;

class Superball {
  public:
    Superball(int argc, char **argv);
    int r;
    int c;
    int mss;
    int empty;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
};

void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-analyze rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < (int) strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if ((int) s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
}
// sb-analyze code, with a few additions like scoreableSets
void sb_analyze(Superball *s, DisjointSetByRankWPC &ds, unordered_map<int, set<int>> &heads, set<int> &headIndices, set<int> &scoreableSets) {
  int row = s->r;
  int col = s->c;
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      int index = i * col + j;
      if(s->board[index] == '.' || s->board[index] == '*') { // Skip all blanks
        continue;
      }
      if(s->goals[index] == 1 && s->mss == 1) { // another edge case
        headIndices.insert(index);
        heads[index].insert(index);
      }
      if(i < row - 1) { // Checking under, as long as we aren't on the last row
        if(s->board[index] == s->board[(i + 1) * col + j]) {
          int newIndex = ds.Union(ds.Find(index), ds.Find((i + 1) * col + j));
          if(newIndex == -1) { // 
            continue;
          }
          heads[ds.Find(newIndex)].insert(index);
          headIndices.insert(ds.Find(newIndex));
          if(s->goals[index] == 1) {
            scoreableSets.insert(index);
          }
          else if(s->goals[newIndex] == 1) {
            scoreableSets.insert(newIndex);
          }
        }
      }
      if(s->board[index] == s->board[index + 1]) { // checks to the right
        if((index + 1) % col == 0) { // We reached a new row, doesn't count
          continue;
        }
        int newIndex = ds.Union(ds.Find(index), ds.Find(index + 1));
        if(newIndex == -1) {
          continue;
        }
        heads[ds.Find(newIndex)].insert(index);
        headIndices.insert(ds.Find(newIndex));
        if(s->goals[index] == 1) {
          scoreableSets.insert(index);
        }
        else if(s->goals[newIndex] == 1) {
          scoreableSets.insert(newIndex);
        }
      }
    }
  }
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      int index = i * col + j;
      if(ds.Find(index) != index) {
        heads.erase(index);
        heads[ds.Find(index)].insert(index);
        heads[ds.Find(index)].insert(ds.Find(index));
      }
    }
  }
}

int scoringIndex(Superball *s, set<int> headsval) { // Gives back the index inside of a set that is scorable
  for(int index : headsval) {
    if(s->goals[index] == 1) {
      return index;
    }
  }
  return -1; // Return -1 if there is no scoring cell found in the set
}

int swappableCellCheck(Superball *s, int index) { // Right = 1; Left = 2; Up = 3; Down = 4
  int col = s->c;
  if(index + 1 < (int) s->board.size()) { // Out of bounds check for the end of the board
    if(((s->board[index + 1] != '.') && (s->board[index + 1] != '*')) && ((index + 1) % col != 0) && (s->board[index] != s->board[index + 1])) {
      return 1;
    }
  }
  if(index != 0) { // Out of bounds check for the start of the board
    if(((s->board[index - 1] != '.') && (s->board[index - 1] != '*')) && (((index - 1) % col != (col - 1)) && (s->board[index] != s->board[index - 1]))) {
      return 2;
    }
  }
  if(index >= col) { // Out of bounds check for checking above the first row
    if(((s->board[index - col] != '.') && (s->board[index - col] != '*')) && (s->board[index] != s->board[index - col])) {
      return 3;
    }
  }
  if(index + col >= (int) s->board.size()) { // Out of bounds check for checking below the last row
    if(((s->board[index + col] != '.') && (s->board[index + col] != '*')) && (s->board[index] != s->board[index + col])) {
      return 4;
    }
  }
  return -1; // If all the checks are failed, then there was no goal cell that was swappable
}

int goalCellCheck(Superball *s, int index) { // Right = 1; Left = 2; Up = 3; Down = 4
  int col = s->c;
  if(index + 1 < (int) s->board.size()) { // Out of bounds check for the end of the board
    if((s->goals[index + 1] == 1) && (s->board[index + 1] != '*') && ((index + 1) % col != 0)) {
      return 1;
    }
  }
  if(index != 0) { // Out of bounds check for the start of the board
    if((s->goals[index - 1] == 1) && (s->board[index - 1] != '*') && ((index - 1) % col != (col - 1))) {
      return 2;
    }
  }
  if(index >= col) { // Out of bounds check for checking above the first row
    if((s->goals[index - col] == 1) && (s->board[index - col] != '*')) {
      return 3;
    }
  }
  if(index + col >= (int) s->board.size()) { // Out of bounds check for checking below the last row
    if((s->goals[index + col] == 1) && (s->board[index + col] != '*')) {
      return 4;
    }
  }
  return -1; // If all the checks are failed, then there was no goal cell that was swappable
}

string rowColFormat(Superball *s, int index1, int index2) {
  int col = s->c;
  int rowIndex1 = index1 / col;
  int colIndex1 = index1 % col;
  int rowIndex2 = index2 / col;
  int colIndex2 = index2 % col;
  string retStatement = to_string(rowIndex1) + " " + to_string(colIndex1) + " " + to_string(rowIndex2) + " " + to_string(colIndex2);
  return retStatement;
}

string scoreOrSwap(Superball *s, DisjointSetByRankWPC ds, unordered_map<int, set<int>> heads, set<int> headIndices, unordered_map<char, set<int>> tilesoutsideSet, set<int> scoreableSets) {
  string retStatement;
  string rowCol;
  int col = s->c;
  if(headIndices.size() == 0) { // No heads, meaning there are no sets. Just do a random swap in this case
    int i = 0;
    int index1 = -1;
    int index2 = 0;
    while(index2 == 0) {
      if(index1 != -1) {
        if(s->board[i] != '.' && s->board[i] != '*') {
          index2 = i;
        }
      }
      else {
        if(s->board[i] != '.' && s->board[i] != '*') {
          index1 = i;
        }
      }
      i++;
    }
    rowCol = rowColFormat(s, index1, index2);
    retStatement = "SWAP " + rowCol;
    return retStatement;
  }
  if(scoreableSets.size() != 0) { // There are scoreable sets
    int goalCell = 0;
    int headIndex = 0;
    int biggestSize = 0;
    for(int scoreableIndex : scoreableSets) {
      int setSize = (int) heads[ds.Find(scoreableIndex)].size();
      if(setSize > biggestSize) {
        goalCell = scoreableIndex;
        headIndex = ds.Find(scoreableIndex);
        biggestSize = setSize;
      }
    }
    if(biggestSize >= s->mss) { // Score the biggest set 
      int rowIndex = goalCell / col;
      int colIndex = goalCell % col;
      retStatement = "SCORE " + to_string(rowIndex) + " " + to_string(colIndex);
      return retStatement;
    }
    else {
      for(int index : heads[headIndex]) { // Go into other sets and try to build them to be larger
        int swapNum = swappableCellCheck(s, index);
        int swapIndex = 0;
        switch (swapNum) {
          case 1:
            swapIndex = index + 1;
            break;
          case 2:
            swapIndex = index - 1;
            break;
          case 3:
            swapIndex = index - col;
            break;
          case 4:
            swapIndex = index + col;
            break;
        }
        if(swapNum == -1) {
          continue;
        }
        if(swapIndex > 0) {
          if(tilesoutsideSet[(char) s->board[headIndex]].size() != 0) { // Finding individual tiles of the same color
            int sameCharIndex = *(tilesoutsideSet[(char) s->board[headIndex]].begin());
            rowCol = rowColFormat(s, swapIndex, sameCharIndex);
            retStatement = "SWAP " + rowCol;
            return retStatement;
          }
          else {
            continue;
          }
        }
      }
    }
  }
  else { // There aren't any scoreable sets
    int headIndex = 0;
    int biggestSize = 0;
    for(int index : headIndices) {
      if(biggestSize < (int) heads[index].size()) { // Want to find the biggest set, along with its head index
        headIndex = ds.Find(index);
        biggestSize = heads[index].size();
      }
    }
    for(int index : heads[headIndex]) { // Go into the biggest set available
      int goalNum = goalCellCheck(s, index); // Right = 1; Left = 2; Up = 3; Down = 4
      int goalCellIndex = 0;
      switch (goalNum) {
        case 1:
          goalCellIndex = index + 1;
          break;
        case 2:
          goalCellIndex = index - 1;
          break;
        case 3:
          goalCellIndex = index - col;
          break;
        case 4:
          goalCellIndex = index + col;
          break;
      }
      if(goalNum == -1) {
        continue;
      }
      if(goalCellIndex > 0) { // Found a goal cell
        if(tilesoutsideSet[(char) s->board[headIndex]].size() != 0) { // There is an exchangable tile of the same color
          int charIndex = *(tilesoutsideSet[(char) s->board[headIndex]].begin());
          rowCol = rowColFormat(s, charIndex, goalCellIndex);
          retStatement = "SWAP " + rowCol;
          return retStatement;
        }
        else {
          continue;
        }
      }
      else {
        for(int index : heads[headIndex]) { // Try to build the set up even if we can't score
          int swapNum = swappableCellCheck(s, index);
          int swapCellIndex = 0;
          switch (swapNum) {
            case 1:
              swapCellIndex = index + 1;
              break;
            case 2:
              swapCellIndex = index - 1;
              break;
            case 3:
              swapCellIndex = index - col;
              break;
            case 4:
              swapCellIndex = index + col;
              break;
          }
          if(swapNum == -1) {
            continue;
          }
          if(swapCellIndex > 0) { // There is an exchangable tile of the same color
            if(tilesoutsideSet[(char) s->board[headIndex]].size() != 0) {
              int charIndex = *(tilesoutsideSet[(char) s->board[headIndex]].begin());
              rowCol = rowColFormat(s, swapCellIndex, charIndex);
              retStatement = "SWAP " + rowCol;
              return retStatement;
            }
            else { // There is no other same colored tiles. Break out
              continue;
            }
          }
        }
      }
    }
  }
  // Just do a random swap at the end to make sure a swap is made at least
  int i = 0;
  int index1 = -1;
  int index2 = 0;
  while(index2 == 0) {
    if(index1 != -1) {
      if(s->board[i] != '.' && s->board[i] != '*') {
        index2 = i;
      }
    }
    else {
      if(s->board[i] != '.' && s->board[i] != '*') {
        index1 = i;
      }
    }
    i++;
  }
  rowCol = rowColFormat(s, index1, index2);
  retStatement = "SWAP " + rowCol;
  return retStatement;
}

int main(int argc, char **argv) {
  // Setting everything up from analyze
  Superball *s;
  s = new Superball(argc, argv);
  int row = s->r;
  int col = s->c;
  unordered_map<int, set<int>> heads;
  set<int> headIndices;
  unordered_map<char, set<int>> tilesoutsideSet;
  DisjointSetByRankWPC ds(s->r*s->c);
  set<int> scoreableSets;
  sb_analyze(s, ds, heads, headIndices, scoreableSets);
  for(int i = 0; i < row; i++) { // Grabbing individual tiles for later use
    for(int j = 0; j < col; j++) {
      int index = i * col + j;
      if(s->board[index] == '.' || s->board[index] == '*') {
        continue;
      }
      if((ds.Find(index) == index) && (headIndices.find(index) == headIndices.end())) { // Putting in solo tiles
        tilesoutsideSet[s->board[index]].insert(index); 
      }
    }
  }
  cout << scoreOrSwap(s, ds, heads, headIndices, tilesoutsideSet, scoreableSets) << endl; // Gives the swap or score statement
  return 0;
}
