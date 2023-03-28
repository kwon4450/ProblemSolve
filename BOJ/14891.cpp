#include <iostream>

using namespace std;

int sawtooth[4][8], K;

void rotation(int num, int dir) {
    if (dir == 1) {
        int t = sawtooth[num][7];
        for (int i = 7; i > 0; i--) {
            sawtooth[num][i] = sawtooth[num][i-1];
        }
        sawtooth[num][0] = t;
    } else {
        int t = sawtooth[num][0];
        for (int i = 0; i < 7; i++) {
            sawtooth[num][i] = sawtooth[num][i+1];
        }
        sawtooth[num][7] = t;
    }
}

void check(int num, int dir, int *infos){
    infos[num] = dir;
    if (num == 0) {
        if (sawtooth[num][2] != sawtooth[num+1][6] && infos[num+1] == 0) 
            check(num+1, -dir, infos);
    } else if (num == 3) {
        if (sawtooth[num][6] != sawtooth[num-1][2] && infos[num-1] == 0) 
            check(num-1, -dir, infos);
    } else {
        if (sawtooth[num][2] != sawtooth[num+1][6] && infos[num+1] == 0) 
            check(num+1, -dir, infos);
        if (sawtooth[num][6] != sawtooth[num-1][2] && infos[num-1] == 0) 
            check(num-1, -dir, infos);
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            char t;
            cin >> t;
            sawtooth[i][j] = t-'0';
        }
    }
    cin >> K;
    for (int i = 0; i < K; i++) {
        int num, dir;
        cin >> num >> dir;
        int infos[4] = {0, };
        check(num-1, dir, infos);
        for (int i = 0; i < 4; i++) {
            if (infos[i] != 0)
                rotation(i, infos[i]);
        }
    }
    int sum = 0;
    int m = 1;
    for (int i = 0; i < 4; i++) {
        sum += sawtooth[i][0]*m;
        m*=2;
    }
    cout << sum;
    return 0;
}