#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
int map[8][8];
int vis[8][8];
int ret = -1;
int dy[4] = {0,0,-1,1};
int dx[4] = {1,-1,0,0};
pair<int, int> sel[3];
vector<pair<int, int>> v;

bool is_in(int y, int x) {
  return (0 <= y && y < N && 0 <= x && x < M);
}

void solution(int k) {
  if (k == 3) {
    for (int i = 0; i < 3; i++) {
      map[sel[i].first][sel[i].second] = 1;
    }
    int infected[8][8];
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        infected[i][j] = 0;
      }
    }
    queue<pair<int,int>> q;
    for (pair<int, int> dot : v) {
      q.push(dot);
    }
    while (!q.empty()) {
      pair<int,int> now = q.front();
      q.pop();
      for (int i = 0; i < 4; i++) {
        int ny = now.first+dy[i];
        int nx = now.second+dx[i];
        if (is_in(ny, nx) && !infected[ny][nx] && map[ny][nx] == 0){
          infected[ny][nx] = 1;
          q.push({ny, nx});
        }
      }
    }
    int safe=0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (map[i][j] == 0 && infected[i][j] == 0) {
          safe++;
        }
      }
    }
    if (safe > ret) {
      ret = safe;
    }
    for (int i = 0; i < 3; i++) {
      map[sel[i].first][sel[i].second] = 0;
    }
    return;
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (map[i][j] == 0 && !vis[i][j]) {
        vis[i][j] = 1;
        sel[k] = {i,j};
        solution(k+1);
        sel[k] = {0,0};
        vis[i][j] = 0;
      }
    }
  }
}
int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> map[i][j];
      if (map[i][j] == 2) {
        v.push_back({i, j});
      }
    }
  }
  solution(0);
  cout << ret;
  return 0;
}