#include <iostream>
#include <vector>
#include "sequence.h"
using namespace std;
int main() {
 vector<Sequence> sequence_list;
 // n is number of sequence
 int n;
 cin >> n;
 for (int i = 0;i < n;i++){
  Sequence tmp_seq;
  cin >> tmp_seq;
  sequence_list.push_back(tmp_seq);
 }
  sort_list(sequence_list);
  cout << sequence_list;
}
