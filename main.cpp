#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define eb emplace_back
#define ef emplace_front
#define endl '\n'
using namespace std;

int np, nn;
bool isHead(int i, vector<vector<int>> &vcg) { // whether net_Ii is a head or not.
    if (vcg[i][i] == -1) return false; // the net is already inserted into a track.
    for (int j = 1; j <= nn; j++) {
        if (vcg[j][i] > 0 && j != i) return false;
    }
    return true;
}

bool interval_comp(pair<int, pair<int, int>> &lhs, pair<int, pair<int, int>> &rhs) {
    if (lhs.second.first > rhs.second.first) {
        return true;
    }
    else if (lhs.second.first == rhs.second.first){
        if (lhs.second.second > rhs.second.second) return true;
        else return false;
    }
    else return false;
}

unordered_map<int, pair<int, int>> sort(map<int, pair<int, int>> &interval) {
    vector<pair<int, pair<int, int>>> tmp;
    for (auto &elem: interval) {
        tmp.eb(elem);
    }
    sort(tmp.begin(), tmp.end(), interval_comp);
    unordered_map<int, pair<int, int>> intervalS;
    for (auto &elem: tmp) {
        intervalS[elem.first] = elem.second;
    }
    return intervalS;
}

// bool acyclic(int n, int a, int b, vector<vector<int>> &vcg) {
//     vector<vector<vector<int>>> mats = {{{0}}};
//     vector<vector<int>> tmp;
//     for (int i = 1; i <= nn; i++) {
//         vector<int> ttmp(nn, 0);
//         for (int j = 1; j <= nn; j++) {
//             ttmp[i-1][j-1] += vcg[i][j];
//         }
//         tmp.eb(ttmp);
//     }
//     mats.eb(tmp);
//     bool start = false;
//     while (true) {
//         if (start) {

//         }
//     }
// }

vector<int> X, Y;
void print_result(map<int, pair<int, int>> &interval, vector<vector<int>> &track) {
    for (int i = 1; i <= np; i++) {
        cout << " " << setw(2) << i << "  ";
    }
    cout << endl;
    for (auto &elem: X) {
        cout << "  " << elem << "  ";
    }
    cout << endl;
    for (int i = 1; i <= 5*np; i++) cout << "-";
    cout << endl;
    cout << "  |____|\n";
    for (int i = 1; i <= track.size()+1; i++) {
        for (auto &elem: track) {

        }
        cout << endl;
    }
    for (int i = 1; i <= 5*np; i++) cout << "-";
    cout << endl;
    for (auto &elem: Y) {
        cout << "  " << elem << "  ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> np >> nn;
    vector<vector<int>> vcg(np, vector<int>(np, 0));
    map<int, pair<int, int>> interval; // len: nn
    int tmp = np;
    int col = 1;
    while (tmp--) {
        int ix, iy;
        cin >> ix >> iy; X.eb(ix); Y.eb(iy);
        if (interval.count(ix)) {
            if (col > interval[ix].second) interval[ix].second = col;
        }
        else if (ix != 0) interval[ix] = make_pair(col, 0);
        if (interval.count(iy)) {
            if (col > interval[iy].second) interval[iy].second = col;
        }
        else if (iy != 0) interval[iy] = make_pair(col, 0);
        col++;

        if (ix == 0 || iy == 0) continue;
        vcg[ix][iy] = 1;
    }

    cout << "VCG: " << endl;
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < np; j++) {
            if (vcg[i][j]) cout << i << "->" << j << endl;
            // cout << vcg[i][j] << " ";
        }
        // cout << endl;
    }

    // cout << "before sorted: \n";
    // for (auto &elem: interval) {
    //     cout << "I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]\n";
    // }

    cout << "after sorted: \n";
    auto intervalS = sort(interval);
    for (auto &elem: intervalS) {
        cout << "I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]\n";
    }

    int watermark = 0;
    vector<vector<int>> track;
    while (!intervalS.empty()) {
        if (track.size() > np) break;
        cout << "track_" << track.size()+1 << ":\n";
        // cout << "  heads: " << endl;
        // for (int i = 1; i <= nn; i++) {
        //     if (isHead(i, vcg)) cout << "  I"<<i<<"["<<interval[i].first<<", "<< interval[i].second<<"]\n";
        // }
        vector<int> toBeDel; toBeDel.reserve(100);
        for (auto &elem: intervalS) {
            if (elem.second.first <= watermark) continue;
            if (!isHead(elem.first, vcg)) continue;
            for (auto &elem: vcg[elem.first]) elem = -1; // update VCG, remove the head net, after inserted into the track.
            toBeDel.eb(elem.first);
            watermark = elem.second.second;
            cout << "\troute I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]: watermark = " << watermark << ".\n";
        }
        track.eb(toBeDel);
        for (auto &elem: toBeDel) intervalS.erase(elem);
        watermark = 0;
    }

    // cout << "heads: " << endl;
    // for (int i = 1; i <= nn; i++) {
    //     if (isHead(i, vcg)) cout << "I"<<i<<"["<<interval[i].first<<", "<< interval[i].second<<"]\n";
    // }

    print_result(interval, track);
}