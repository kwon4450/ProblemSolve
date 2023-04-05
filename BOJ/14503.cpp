#include <iostream>

using namespace std;

int N, M, r, c, d;
int room[50][50];
int vis[50][50];
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

bool is_in(int y, int x) {
  return (y >= 0 && x >= 0 && y < N && x < M);
}

bool not_clean(int y, int x) {
  for (int i = 0; i < 4; i++) {
    int ny = y+dy[i];
    int nx = x+dx[i];
    if (!is_in(ny, nx)) continue;
    if (room[ny][nx] == 0 && vis[ny][nx] == 0) return true;
  }
  return false;
}

bool can_go(int y, int x) {
  return (is_in(y,x) && room[y][x] == 0);
}

int next_dir(int dir) {
  return (dir == 0) ? 3 : dir-1;
}

int solution(int y, int x, int dir) {
  int ret = 0;
  while (1) {
    if (vis[y][x] == 0) {
      ret++;
      vis[y][x] = 1;
    }
    if (not_clean(y,x)) {
      for (int i = 0; i < 4; i++) {
        dir = next_dir(dir);
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (can_go(ny, nx) && !vis[ny][nx]) {
          y = ny; x = nx;
          break;
        }
      }
    } else {
      if (!can_go(y-dy[dir], x-dx[dir])) break;
      y-=dy[dir]; x-=dx[dir]; // 후진
    }
  }
  return ret;
}

int main() {
  cin >> N >> M >> r >> c >> d;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> room[i][j];
    }
  }
  cout << solution(r, c, d);
  return 0;
}