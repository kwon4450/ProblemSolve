#include <iostream>

using namespace std;

int N;
long long B, C;
long long room[1000000];
int main() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> room[i];
  }
  cin >> B >> C;
  long long cnt = 0;
  for (int i = 0; i < N; i++) {
    long long t = room[i];
    t-=B;
    cnt ++;
    if (t < 0) continue;
    cnt += (t%C == 0) ?t/C:t/C+1;
  }
  cout << cnt;
  return 0;
}