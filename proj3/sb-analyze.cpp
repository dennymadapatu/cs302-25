// Name: Dennis Madapatu
// Date: 2/21/2025
// Description: Superball Analysis. Analyzes a given board of superball and gives the scoreable sets along with the goal cell to score them through
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

#include "disjoint.h"

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

void sb_analyze(Superball *s) {
  DisjointSetByRankWPC ds(s->r*s->c);
  unordered_map<int, set<int>> heads;
  set<int> headIndices;
  int row = s->r;
  int col = s->c;
  for(int i = 0; i < row; i++) {
    for(int j = 0; j < col; j++) {
      int index = i * col + j;
      if(s->board[index] == '.' || s->board[index] == '*') { // Skip all blanks
        continue;
      }
      if(s->goals[index] == 1 && s->mss == 1) { // An edge case where minimum scoring size is 1
        headIndices.insert(index);
        heads[index].insert(index);
      }
      if(i < row - 1) { // Checking under, as long as we aren't on the last row
        if(s->board[index] == s->board[(i + 1) * col + j]) {
          int newIndex = ds.Union(ds.Find(index), ds.Find((i + 1) * col + j));
          if(newIndex == -1) { // Both indices are the same, move on
            continue;
          }
          // Insert the attached cell and the head index for later reference
          heads[ds.Find(newIndex)].insert(index);
          headIndices.insert(ds.Find(newIndex));
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
      }
    }
  }
  // Using this to erase any smaller sets inside of larger sets, and inserting all the values in those sets into the larger set
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
  // Print formatting for the analyze
  set<int> scoredSets; // Made so the program doesn't print out sets that have already been scored
  cout << "Scoring sets:" << endl;
  for(int val : headIndices) {
    if((int) heads[val].size() >= s->mss) {
      for(int index : heads[val]) {
        if(s->goals[index] == 1) {
          if(scoredSets.find(ds.Find(index)) == scoredSets.end()) {
            int columnIndex = index % col;
            int rowIndex = index / col;
            cout << "  Size: " << heads[val].size() << "  Char: " << (char) s->board[val]
                 << "  Scoring Cell: " << rowIndex << "," << columnIndex << "\n";
            scoredSets.insert(ds.Find(index));
          }
        }
      }
    }
  }
}

int main(int argc, char **argv)
{
  Superball *s;
  s = new Superball(argc, argv);
  sb_analyze(s);
}
