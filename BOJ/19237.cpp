#include <iostream>
#include <vector>

using namespace std;
// 1 위 2 아 3 왼 4 오
int rule[401][5][5];
pair<int, int> map[21][21];
pair<int, int> smell[21][21];// first: 주인, second: 남은 시간
int dy[5] = {0, -1, 1, 0, 0};
int dx[5] = {0, 0, 0, -1, 1};

int N, M, k;

bool is_in(int y, int x) {
  return (y >= 1 && y <= N && x >= 1 && x <= N);
}

bool onlyone() {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      if (map[i][j].first > 1) return false;
    }
  }
  return true;
}

int answer() {
  int time = 0;
  while (!onlyone()) {
    if (time >= 1000) return -1;
    pair<int, int> next_map[21][21];
    for (int i = 0; i < 21; i++) {
      for (int j = 0; j < 21; j++) {
        next_map[i][j] = {0, 0};
      }
    }
    for (int y = 1; y <= N; y++) {
      for (int x = 1; x <= N; x++) {
        if (map[y][x].first == 0) continue;
        int num = map[y][x].first;
        int now_dir = map[y][x].second;
        bool go = false;
        for (int i = 1; i <= 4; i++) {
          int next_dir = rule[num][now_dir][i];
          int ny = y + dy[next_dir];
          int nx = x + dx[next_dir];
          if (!is_in(ny, nx)) continue;
          if (smell[ny][nx].first == 0) {
            go = true;
            if (next_map[ny][nx].first == 0 || next_map[ny][nx].first > num) {
              next_map[ny][nx] = {num, next_dir};
            }
            break;
          }
        }
        if (go) continue;
        for (int i = 1; i <= 4; i++) {
          int next_dir = rule[num][now_dir][i];
          int ny = y + dy[next_dir];
          int nx = x + dx[next_dir];
          if (smell[ny][nx].first == num) {
            if (next_map[ny][nx].first == 0 || next_map[ny][nx].first > num) {
              smell[ny][nx] = {num, k};
              smell[ny][nx] = {num, k};
              next_map[ny][nx] = {num, next_dir};
            }
            break;
          }
        }
      }
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        map[i][j] = next_map[i][j];
        if (next_map[i][j].first == 0) {
          if (smell[i][j].first == 0) continue;
          if (smell[i][j].second == 1) smell[i][j] = {0, 0};
          else smell[i][j] = {smell[i][j].first, smell[i][j].second-1};
        } else {
          smell[i][j] = {next_map[i][j].first, k};
        }
      }
    }
    time++;
  }
  return time;
}

int main() {
  cin >> N >> M >> k;
  int t[21][21], shark[401];
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cin >> t[i][j];
      smell[i][j] = {t[i][j], k};
    }
  }
  for (int i = 1; i <= M; i++) cin >> shark[i];
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      if (t[i][j]) {
        map[i][j] = {t[i][j], shark[t[i][j]]};
      }
    }
  }
  for (int i = 1; i <= M; i++) {
    for (int j = 1; j <= 4; j++) {
      for (int x = 1; x <= 4; x++) {
        cin >> rule[i][j][x];
      }
    }
  }
  cout << answer();
  return 0;
}