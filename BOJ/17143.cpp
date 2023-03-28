#include <iostream>
#include <map>

using namespace std;

typedef struct {
    int speed;
    int dir;
    int size;
} Shark;

int R, C, M;

int ocean[100][100];
map<int, Shark> sharks;

int main() {
    cin >> R >> C >> M;
    for (int i = 0; i < M; i++) {
        int y, x;
        cin >> y >> x;
        Shark s;
        cin >> s.speed >> s.dir >> s.size;
        sharks[i+1] = s;
        ocean[y-1][x-1] = i+1;
    }
    int pos = 1;
    int sum = 0;
    while (pos < C+1) {
        for (int i = 0; i < R; i++) {
            if (ocean[i][pos-1] == 0) continue;
            sum += sharks[ocean[i][pos-1]].size;
            sharks.erase(ocean[i][pos-1]);
            ocean[i][pos-1] = 0;
            break;
        }
        int newOcean[100][100];
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                newOcean[i][j] = 0;
            }
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (ocean[i][j] == 0) continue;
                int key = ocean[i][j];
                int d = sharks[key].dir;
                int s = sharks[key].speed;
                int y = i;
                int x = j;
                s = (d == 1 || d == 2) ? s%(2*(R-1)) : s%(2*(C-1));
                while (s > 0) {
                    if (d == 1) {
                        if (y-s >= 0) {
                            y -= s;
                            s = 0;
                        } else {
                            s -= y;
                            y = 0;
                            d = 2;
                        }
                    } else if (d == 2) {
                        if (y+s < R) {
                            y += s;
                            s = 0;
                        } else {
                            s -= R-1-y;
                            y = R-1;
                            d = 1;
                        }
                    } else if (d == 3) {
                        if (x+s < C) {
                            x += s;
                            s = 0;
                        } else {
                            s -= C-1-x;
                            x = C-1;
                            d = 4;
                        }
                    } else if (d == 4) {
                        if (x-s >= 0) {
                            x -= s;
                            s = 0;
                        } else {
                            s -= x;
                            x = 0;
                            d = 3;
                        }
                    }
                }
                sharks[key].dir = d;
                if (newOcean[y][x] == 0) {
                    newOcean[y][x] = key;
                } else {
                    if (sharks[newOcean[y][x]].size < sharks[key].size) {
                        sharks.erase(newOcean[y][x]);
                        newOcean[y][x] = key;
                    } else {
                        sharks.erase(key);
                    }
                }
            }
        }
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                ocean[i][j] = newOcean[i][j];
            }
        }
        pos++;
    }
    cout << sum;
    return 0;
}