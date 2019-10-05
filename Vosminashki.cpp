#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using  namespace std;

struct State {
    string stat;
    string way;
    int posOfZero;
    explicit State (string& s, string w, int pOfZero);
    explicit State (State& prevStat, char destination);
    void Print ();
    bool isSolvable();
    void GetNextStates(vector<State*>& nextStates, State& state);
};

void State::Print() {
    cout << stat;
}

State::State(string &s, string w, int pOfZero) {
    stat = s;
    way = w;
    posOfZero = pOfZero;
}

State::State(State &prevStat, char destination) {
    if (destination == 'R') {
        stat = prevStat.stat;
        swap(stat[prevStat.posOfZero], stat[prevStat.posOfZero + 1]);
        way = prevStat.way + 'R';
        posOfZero = prevStat.posOfZero + 1;
    }
    if (destination == 'L') {
        stat = prevStat.stat;
        swap(stat[prevStat.posOfZero], stat[prevStat.posOfZero - 1]);
        way = prevStat.way + 'L';
        posOfZero = prevStat.posOfZero - 1;
    }
    if (destination == 'U') {
        stat = prevStat.stat;
        swap(stat[prevStat.posOfZero], stat[prevStat.posOfZero - 3]);
        way = prevStat.way + 'U';
        posOfZero = prevStat.posOfZero - 3;
    }
    if (destination == 'D') {
        stat = prevStat.stat;
        swap(stat[prevStat.posOfZero], stat[prevStat.posOfZero + 3]);
        way = prevStat.way + 'D';
        posOfZero = prevStat.posOfZero + 3;
    }
}

void State::GetNextStates(vector<State*> &nextStates, State& state) {
    if (posOfZero / 3 > 0) {
        State* next1 = new State (state, 'U');
        nextStates.push_back(next1);
    }
    if (posOfZero / 3 < 2) {
        State* next1 = new State (state, 'D');
        nextStates.push_back(next1);
    }
    if (posOfZero % 3 < 2) {
        State* next1 = new State (state, 'R');
        nextStates.push_back(next1);
    }
    if (posOfZero % 3 > 0) {
        State* next1 = new State (state, 'L');
        nextStates.push_back(next1);
    }
}

bool State::isSolvable() {
    int amount = 0;
    for (int i = 0; i < 9 ; ++i) {
        if (stat[i] != '0') {
            for (int j = i + 1; j < 9; ++j) {
                if (stat[j] != '0') {
                    if (stat[j] < stat[i]) {
                        ++amount;
                    }
                }
            }
        }
    }
    return amount % 2 == 0;
}

pair<int, string> FindSolution(State& firstState) { //ищет решение
    vector<State*> layer;
    vector<State*> nextlayer;
    vector<State*> nextStates;
    unordered_set<string> s;
    string finalStr = "123456780";
    int amountOfWays = 0;
    if (firstState.stat == finalStr) {
        return make_pair(amountOfWays, firstState.way);
    } else {
        if (!firstState.isSolvable()) {
            return make_pair(0, "-1");
        } else {
            s.insert(firstState.stat);
            layer.push_back(&firstState);
            while (layer.size() != 0) {
                ++amountOfWays;
                for (int i = 0; i < layer.size(); ++i) {
                    layer[i]->GetNextStates(nextStates, *layer[i]);
                    for (int j = 0; j < nextStates.size(); ++j) {
                        if (s.count(nextStates[j]->stat) == 0) {
                            if (nextStates[j]->stat == finalStr) {
                                return make_pair(amountOfWays, nextStates[j]->way);
                            } else {
                                nextlayer.push_back(nextStates[j]);
                                s.insert(nextStates[j]->stat);
                            }
                        }
                    }
                    nextStates.clear();
                }
                layer.clear();
                layer = nextlayer;
                nextlayer.clear();
            }
        }
    }
    return make_pair(0, "-1");
}

int main() {
    string firstStr;
    int posOfZero;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int el;
            cin >> el;
            if (el == 0) {
                posOfZero = i * 3 + j;
            }
            firstStr += (el + '0');
        }
    }
    State firstState(firstStr, "", posOfZero);
    vector<State*> next;
    pair<int, string> answer = FindSolution(firstState);
    if (answer.second == "-1") {
        cout << "-1";
    } else {
        cout << answer.first << endl;
        cout << answer.second;
    }
    return 0;
}
