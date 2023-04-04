#include <iostream>
#include <queue>
#include <map>

using namespace std;

int dy[9] = {0,-1,-1, 0, 1, 1, 1, 0, -1};
int dx[9] = {0, 0,-1,-1,-1, 0, 1, 1, 1};

int next_dir(int i) {
  return (i == 8) ? 1 : i+1;
}

bool is_in(pair<int, int> a) {
  return (a.first >= 0 && a.first < 4 && a.second >= 0 && a.second < 4);
}

bool is_equal(pair<int, int> a, pair<int, int> b) {
  return (a.first == b.first && a.second == b.second);
}

int clock(int dir) {
  if (dir == 1) return 12;
  else if (dir == 2) return 11;
  else if (dir == 3) return 9;
  else if (dir == 4) return 7;
  else if (dir == 5) return 6;
  else if (dir == 6) return 5;
  else if (dir == 7) return 3;
  else if (dir == 8) return 1;
  else return 0;
}

int DFS(int eating, int dir, pair<int, int> shark, map<int, pair<int, int>> n2dot, vector<vector<pair<int, int>>> ocean) {
  int ret = eating;
  ocean[shark.first][shark.second] = {0, 0};
  for (int i = 1; i <= 16; i++) {
    pair<int, int> now_dot = n2dot[i];
    pair<int, int> n_info = ocean[now_dot.first][now_dot.second];
    if (n_info.first != i) continue;
    int now_dir = n_info.second;
    do {
      pair<int, int> next_dot = {now_dot.first+dy[now_dir], now_dot.second+dx[now_dir]};
      if (!is_in(next_dot) || is_equal(next_dot, shark)) {
        now_dir = next_dir(now_dir);
      } else {
        pair<int, int> next_info = ocean[next_dot.first][next_dot.second];
        if (next_info.first == 0) { // 그쪽으로 이동
          ocean[next_dot.first][next_dot.second] = {n_info.first, now_dir}; // 이동하는 코드
          ocean[now_dot.first][now_dot.second] = {0, 0}; // 원래 있던 곳은 0,0으로 세팅
          n2dot[n_info.first] = next_dot;
        } else { // 둘이 swap
          ocean[now_dot.first][now_dot.second] = ocean[next_dot.first][next_dot.second];
          ocean[next_dot.first][next_dot.second] = {n_info.first, now_dir};
          n2dot[n_info.first] = next_dot;
          n2dot[next_info.first] = now_dot;
        }
        break;
      }
    } while (now_dir != n_info.second);
  }
  pair<int, int> next_shark = {shark.first+dy[dir], shark.second+dx[dir]};
  while (is_in(next_shark)) {
    int eat = ocean[next_shark.first][next_shark.second].first;
    if (eat == 0) {
      next_shark = {next_shark.first+dy[dir], next_shark.second+dx[dir]};
      continue;
    }
    int next_dir = ocean[next_shark.first][next_shark.second].second;
    int x = DFS(eating+eat, next_dir, next_shark, n2dot, ocean);
    if (x > ret) ret = x;
    next_shark = {next_shark.first+dy[dir], next_shark.second+dx[dir]};
  }
  return ret;
}

int main() {
  vector<vector<pair<int, int>>> ocean(4);
  map<int, pair<int, int>> n2d;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int num, dir;
      cin >> num >> dir;
      ocean[i].push_back({num, dir});
      n2d[num] = {i,j};
    }
  }
  int n = ocean[0][0].first;
  int dir = ocean[0][0].second;
  pair<int, int> shark = {0, 0};
  cout << DFS(n, dir, shark, n2d, ocean);
  return 0;
}