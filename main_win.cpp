#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define eb emplace_back
#define ef emplace_front
#define endl '\n'
using namespace std;

int np, nn; // # of pin, # of net
bool isHead(int i, vector<vector<int>> &vcg) { // whether net_Ii is a head or not.
    if (vcg[i][i] == -1) return false; // the net is already inserted into a track.
    for (int j = 1; j <= nn; j++) {
        if (vcg[j][i] > 0 && j != i) return false;
    }
    return true;
}

// sort interval by the begin of it
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
// sort interval by the begin of it
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
    // if ((A^n)ji = (A)ij = 1) then detect a cycle: i->j->i.
// }

vector<int> X, Y; // to record the name of pins
void print_result(map<int, pair<int, int>> &interval, vector<vector<int>> &track) {
    int dig = 1; int NP = np;
    while (NP/10 > 0) {
        NP = NP / 10;
        dig++;
    }
    cout << "\nThe resulting routing graph: \n";
    cout << "col:";
    for (int i = 1; i <= np; i++) {
        for (int j = 1; j <= 3-dig; j++) cout << " ";
        cout << setw(dig) << i; cout << "  ";
    }
    dig = 1; int NN = nn;
    while (NN/10 > 0) {
        NN = NN / 10;
        dig++;
    }
    cout << "\npin:";
    for (int i = 1; i <= np; i++) {
        for (int j = 1; j <= 3-dig; j++) cout << " ";
        cout << setw(dig) << X[i]; cout << "  ";
    }
    cout << "\n    ";
    for (int i = 1; i <= 5*np; i++) cout << "-";
    cout << "\n";

    // plot the routing channel
    vector<vector<char>> result(track.size(), vector<char>(np*5, ' '));
    // string wire_char = "*#@$%^&+?><~abcdefghijklmnofqrstuvwxyzABCEFGHIJKMNOPQSTVWXYZ:;";
    // vector<char> wire; wire.reserve(wire_char.size());
    // for (auto &c: wire_char) wire.eb(c);
    for (int i = 0; i < track.size(); i++) { // print the result track by track
        for (int n = 0; n < track[i].size(); n++) { // iterate through the track in the order of start of the nets
            int net = track[i][n];
            int start = interval[track[i][n]].first; // start of the net
            int terminal = interval[track[i][n]].second; // end of the net
            for (int j = start; j <= terminal; j++) {
                if (X[j] == net) {
                    for (int k = i; k >= 0; k--) {
                        if (j == start && k == i) result[k][2+(j-1)*5] = 'R';
                        else if (j == terminal && k == i) result[k][2+(j-1)*5] = 'L';
                        else {
                            if (k == 0) result[k][2+(j-1)*5] = '|';
                            else result[k][2+(j-1)*5] = '|';
                        }
                    }
                }
                else if (Y[j] == net) {
                    for (int k = i; k < track.size(); k++) {
                        if (j == start && k == i) result[k][2+(j-1)*5] = 'R';
                        else if (j == terminal && k == i) result[k][2+(j-1)*5] = 'L';
                        else {
                            if (k == track.size()-1) result[k][2+(j-1)*5] = '|';
                            else result[k][2+(j-1)*5] = '|';
                        }
                    }
                }
            }
            for (int j = 0; j < np*5; j++) {
                if (j < 2+(start-1)*5 || j > 2+(terminal-1)*5) continue;
                if (result[i][j] == ' ') {
                    // result[i][j] = wire[i%wire.size()];
                    if (i <= track.size()/2) result[i][j] = '_';
                    else result[i][j] = '-';
                }
            }
        }
    }
    for (auto &row: result) {
        cout << "    ";
        for (auto &elem: row) {
            if (elem == 'U') cout << "^";
            else if (elem == 'D') cout << "v";
            else if (elem == 'R') cout << ">";
            else if (elem == 'L') cout << "<";
            else cout << elem;
        }
        cout << endl;
    }

    cout << "    ";
    for (int i = 1; i <= 5*np; i++) cout << "-";
    cout << "\n    ";
    for (int i = 1; i <= np; i++) cout << "  " << Y[i] << "  ";
    cout << endl;

    cout << "Number of tracks: " << track.size() << endl;

    int len = 0;
    for (int i = 0; i < track.size(); i++) {
        for (int j = 0; j < track[i].size(); j++) {
            int net = track[i][j];
            len += interval[net].second - interval[net].first;
            int x = 0, y = 0;
            for (int k = 1; k <= np; k++) {
                if (X[k] == net) x++;
                if (Y[k] == net) y++;
            }
            len += (i+1)*x;
            len += (track.size()-i)*y;
        }
    }
    cout << "Overall wire length: " << len << endl;

    int via = 0;
    for (int k = 1; k <= np; k++) {
        if (X[k] != 0) via++;
        if (Y[k] != 0) via++;
    }
    cout << "Number of vias: " << via << endl;
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    
    ifstream in(argv[1]);
    
    X.eb(0), Y.eb(0); // dummy element
    in >> np >> nn;
    vector<vector<int>> vcg(np, vector<int>(np, 0));
    map<int, pair<int, int>> interval; // len: nn
    int tmp = np;
    int col = 1;
    while (tmp--) {
        int ix, iy;
        in >> ix >> iy; X.eb(ix); Y.eb(iy);
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

    // cout << "before sorted: \n";
    // for (auto &elem: interval) {
    //     cout << "I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]\n";
    // }

    cout << "Sorted intervals of nets: \n";
    auto intervalS = sort(interval);
    for (auto &elem: intervalS) {
        cout << "  I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]\n";
    }

    cout << "\nVertical constraint: " << endl;
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < np; j++) {
            if (vcg[i][j]) cout << "  I" << i << "->I" << j << endl;
            // cout << vcg[i][j] << " ";
        }
        // cout << endl;
    }

    int watermark = 0;
    vector<vector<int>> track;
    while (!intervalS.empty()) {
        if (track.size() > np) break;
        cout << "\ntrack_" << track.size()+1 << ":\n";
        cout << "  head(s): ";
        for (int i = 1; i <= nn; i++) {
            if (isHead(i, vcg)) cout << "I" << i << ", ";
        }
        cout << endl;
        vector<int> nets; nets.reserve(100);
        for (auto &elem: intervalS) {
            if (elem.second.first <= watermark) continue;
            if (!isHead(elem.first, vcg)) continue;
            for (auto &elem: vcg[elem.first]) elem = -1; // update VCG, remove the head net, after inserted into the track.
            nets.eb(elem.first);
            watermark = elem.second.second;
            cout << "  route I" << elem.first << "[" << elem.second.first << ", " << elem.second.second << "]: watermark = " << watermark << ";\n";
        }
        track.eb(nets);
        for (auto &elem: nets) intervalS.erase(elem);
        watermark = 0;
    }

    print_result(interval, track);
}