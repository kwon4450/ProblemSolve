#include <iostream>

using namespace std;

int N, M, x, y, K;
int board[20][20];
int cmd[1000];
int dy[5] = {0,0,0,-1,1};
int dx[5] = {0,1,-1,0,0};

typedef struct {
  pair<int, int> dot;
  int top;
  int bottom;
  int l;
  int r;
  int u;
  int d;
} Dice;

bool is_in(pair<int, int> a) {
  return (a.first >= 0 && a.first < N && a.second >= 0 && a.second < M);
}

void init_dice(Dice *d) {
  d->dot = {x,y};
  d->top = 0;
  d->bottom  = 0;
  d->l = 0;
  d->r = 0;
  d->u = 0;
  d->d = 0;
}

bool turn_dice(Dice *d, int dir) {
  pair<int, int> now = d->dot;
  pair<int, int> next = {now.first+dy[dir], now.second+dx[dir]};
  if (!is_in(next)) return false;
  int t = d->top;
  d->dot = next;
  if (dir == 1) { // turn_right;
    d->top = d->l;
    d->l = d->bottom;
    d->bottom = d->r;
    d->r=t;
  } else if (dir == 2) {//turn_left;
    d->top = d->r;
    d->r = d->bottom;
    d->bottom = d->l;
    d->l = t;
  } else if (dir == 3) {//turn_up;
    d->top=d->d;
    d->d=d->bottom;
    d->bottom=d->u;
    d->u=t;
  } else {
    d->top=d->u;
    d->u=d->bottom;
    d->bottom=d->d;
    d->d=t;
  }
  if (board[next.first][next.second] == 0) {
    board[next.first][next.second] = d->bottom;
  } else {
    d->bottom = board[next.first][next.second];
    board[next.first][next.second] = 0;
  }
  return true;
}

void solution() {
  Dice first;
  init_dice(&first);
  for (int i = 0; i < K; i++) {
    int dir = cmd[i];
    if (turn_dice(&first, dir))
      cout << first.top << endl;
  }
}

int main() {
  cin >> N >> M >> x >> y >> K;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      cin >> board[i][j];
    }
  }
  for (int i = 0; i < K; i++) cin >> cmd[i];
  solution();
  return 0;
}