#include <iostream>
#include <queue>

using namespace std;

int N, M;
pair<int, int> red, blue;
char board[10][10];
bool vis[10][10][10][10];
int dy[4] = {0,0,1,-1};
int dx[4] = {1,-1,0,0};

char get_board(pair<int, int> x) {
  return board[x.first][x.second];
}

int bowling(pair<int, int> *ball, int dy, int dx) {
  int d = 0;
  int y = (*ball).first;
  int x = (*ball).second;
  char next = board[y+dy][x+dx];
  while (next != '#' && next != 'O') {
    d++;
    y+=dy;
    x+=dx;
    next = board[y+dy][x+dx];
  }
  if (next == 'O') {
    d++;
    y+=dy;
    x+=dx;
  }
  *ball = {y,x};
  return d;
}

int BFS() {
  queue<pair<int, pair<pair<int,int>, pair<int,int>>>> q;
  vis[red.first][red.second][blue.first][blue.second] = true;
  q.push({0,{red, blue}});
  while (!q.empty()) {
    int time = q.front().first;
    pair<int,int> now_red = q.front().second.first;
    pair<int,int> now_blue = q.front().second.second;
    q.pop();
    if (time >= 10) break;
    for (int i = 0; i < 4; i++) {
      pair<int, int> tred = now_red;
      pair<int, int> tblue = now_blue;
      int red_d = bowling(&tred, dy[i], dx[i]);
      int blue_d = bowling(&tblue, dy[i], dx[i]);
      if (tred.first == tblue.first && tred.second == tblue.second) {
        if (get_board(tred) == 'O') continue;
        if (red_d > blue_d) {
          tred = {tred.first-dy[i], tred.second-dx[i]};
        } else {
          tblue = {tblue.first-dy[i], tblue.second-dx[i]};
        }
        if (!vis[tred.first][tred.second][tblue.first][tblue.second]) {
          vis[tred.first][tred.second][tblue.first][tblue.second] = true;
          q.push({time+1, {tred, tblue}});
        }
      } else {
        if (get_board(tblue) == 'O') continue;
        if (get_board(tred) == 'O') return time+1;
        if (!vis[tred.first][tred.second][tblue.first][tblue.second]) {
          vis[tred.first][tred.second][tblue.first][tblue.second] = true;
          q.push({time+1, {tred, tblue}});
        }
      }
    }
  }
  return -1;
}

int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
      if (board[i][j] == 'B') {
        blue = {i, j};
      } else if (board[i][j] == 'R') {
        red = {i, j};
      }
    }
  }
  cout << BFS();
  return 0;
}