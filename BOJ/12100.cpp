#include <iostream>

using namespace std;

int N;
int board[22][22];
int vis[5]; // 1 : up , 2 : right, 3 : down, 4 : left
int ret = -1;
int ans[5];

void simulation(int t[22][22], int type) {
    if (type == 1) { // up
        for (int j = 1; j <= N; j++) {
            int idx = 1;
            int data = -1;
            for (int i = 1; i <= N; i++) {
                if (t[i][j] == 0) continue;
                if (t[i][j] == data) {
                    t[idx++][j] = data*2;
                    data = -1;
                } else {
                    if (data != -1) {
                        t[idx++][j] = data;
                    }
                    data = t[i][j];
                }
            }
            if (data != -1 && idx <= N) t[idx++][j] = data;
            while (idx <= N) t[idx++][j] = 0;
        }
    } else if (type == 2) {
        for (int j = 1; j <= N; j++) {
            int idx = N;
            int data = -1;
            for (int i = N; i > 0; i--) {
                if (t[i][j] == 0) continue;
                if (t[i][j] == data) {
                    t[idx--][j] = data*2;
                    data = -1;
                } else {
                    if (data != -1) {
                        t[idx--][j] = data;
                    }
                    data = t[i][j];
                }
            }
            if (data != -1 && idx > 0) t[idx--][j] = data;
            while (idx > 0) t[idx--][j] = 0;
        }
    } else if (type == 3) {
        for (int i = 1; i <= N; i++) {
            int idx = 1;
            int data = -1;
            for (int j = 1; j <= N; j++) {
                if (t[i][j] == 0) continue;
                if (t[i][j] == data) {
                    t[i][idx++] = data*2;
                    data = -1;
                } else {
                    if (data != -1) {
                        t[i][idx++] = data;
                    }
                    data = t[i][j];
                }
            }
            if (data != -1 && idx <= N) t[i][idx++] = data;
            while (idx <= N) t[i][idx++] = 0;
        }
    } else {
        for (int i = 1; i <= N; i++) {
            int idx = N;
            int data = -1;
            for (int j = N; j > 0; j--) {
                if (t[i][j] == 0) continue;
                if (t[i][j] == data) {
                    t[i][idx--] = data*2;
                    data = -1;
                } else {
                    if (data != -1) {
                        t[i][idx--] = data;
                    }
                    data = t[i][j];
                }
            }
            if (data != -1 && idx > 0) t[i][idx--] = data;
            while (idx > 0) t[i][idx--] = 0;
        }
    }
    return;
}

void back(int k) {
    if (k == 5) {
        int t[22][22];
        for (int i = 0; i <= N+1; i++) {
            for (int j = 0; j <= N+1; j++) {
                t[i][j] = board[i][j];
            }
        }
        for (int i = 0; i < 5; i++) {
            simulation(t, vis[i]);
        }
        int x = -1;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (x < t[i][j]) x = t[i][j];
            }
        }
        if (x > ret) {
            ret = x;
            for (int i = 0; i < 5; i++) ans[i] = vis[i];
        }
        return;
    }
    for (int i = k; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            vis[i] = j+1;
            back(k+1);
            vis[i] = 0;
        }
    }
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> board[i][j];
        }   
    }
    back(0);
    cout << ret;
    return 0;
}