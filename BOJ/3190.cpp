#include <iostream>
#include <queue>
#include <list>

using namespace std;

int N, K, L;
int road[102][102];
list<pair<int, int>> snake;

queue<pair<int, char>> q;

bool is_in(pair<int, int> dot) {
  return (dot.first >=1 && dot.second >= 1 && dot.first <= N && dot.second <= N);
}

int main() {
  cin >> N >> K;
  for (int i = 0; i < K; i++) {
    int y, x;
    cin >> y >> x;
    road[y][x] = 1;
  }
  cin >> L;
  for (int i = 0; i < L; i++) {
    int s; char d;
    cin >> s >> d;
    q.push({s, d});
  }
  int time = 0;
  snake.push_back({1,1});
  road[1][1] = -1;
  int d[2] = {0, 1};
  while (1) {
    time++;
    pair<int, int> next = {snake.front().first+d[0], snake.front().second+d[1]};
    if (road[next.first][next.second] == -1 || !is_in(next)) break;
    snake.push_front(next);
    if (road[next.first][next.second] == 0) {
      road[snake.back().first][snake.back().second] = 0;
      snake.pop_back();
    }
    road[next.first][next.second] = -1;
    if (time == q.front().first) {
      char t = q.front().second;
      q.pop();
      if (t == 'L') {
        // 0,1 -> -1,0 -> 0,-1 -> 1,0 -> 0,1
        if (d[0] == 0) {
          d[0] = -d[1];
          d[1] = 0;
        } else {
          d[1] = d[0];
          d[0] = 0;
        }
      } else {
        // 0,1->1,0->0,-1->-1,0
        if (d[0] == 0) {
          d[0] = d[1];
          d[1] = 0;
        } else {
          d[1] = -d[0];
          d[0] = 0;
        }
      }
    }
  }
  cout << time;
  return 0;
}