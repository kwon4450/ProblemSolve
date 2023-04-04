#include <iostream>
#include <queue>
#include <list>

using namespace std;

int N;
int ocean[20][20];
int dy[4] = {-1,0,1,0};
int dx[4] = {0,-1,0,1};
pair<int, int> baby;
list<pair<int, int>> fishes[7];

bool isIn(pair<int, int> dot) {
  return (0<=dot.first && 0<=dot.second && dot.first < N && dot.second < N);
}

int get_distance(pair<int, int> a, pair<int, int> b, int size) {
  int vis[20][20];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      vis[i][j] = 0;
    }
  }
  queue<pair<int, int>> q;
  vis[a.first][a.second] = 1;
  q.push(a);
  
  while (!q.empty()) {
    pair<int, int> now = q.front();
    q.pop();
    if (now.first == b.first && now.second == b.second) {
      return vis[now.first][now.second]-1;
    }
    for (int i = 0; i < 4; i++) {
      pair<int, int> next = {now.first+dy[i], now.second+dx[i]};
      if (isIn(next) && ocean[next.first][next.second] <= size && vis[next.first][next.second] == 0) {
        vis[next.first][next.second] = vis[now.first][now.second]+1;
        q.push(next);
      }
    }
  }
  return -1;
} 

int answer() {
  int size = 2;
  int eating = 0;
  int time = 0;
  int y = baby.first;
  int x = baby.second;
  while (1) {
    int mind = -1;
    pair<int, int> dest = {20, 20};
    for (int s = 1; s < size; s++) {
      if (s > 6) break;
      list<pair<int, int>> now = fishes[s];
      for (auto it : now) {
        if (ocean[it.first][it.second] != s) continue;
        int d = get_distance({y,x}, it, size);
        if (d==-1) continue;
        if (mind == -1 || mind > d) {
          mind =d;
          dest = it;
        } else if (mind == d) {
          if (dest.first > it.first) {
            dest = it;
          } else if (dest.first == it.first) {
            if (dest.second > it.second) {
              dest = it;
            }
          }
        }
      }
    }
    if (mind == -1) break;
    time+=mind;
    ocean[dest.first][dest.second] = 0;
    eating ++;
    if (eating == size) {
      size++;
      eating = 0;
    }
    y = dest.first;
    x = dest.second;
  }
  return time;
}

int main() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> ocean[i][j];
      if (ocean[i][j] == 9) {
        baby = {i, j};
        ocean[i][j] = 0;
      }
      else if (ocean[i][j] > 0) {
        fishes[ocean[i][j]].push_back({i,j});
      }
    }
  }
  cout << answer();
  return 0;
}