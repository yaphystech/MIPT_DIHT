#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using  namespace std;

struct Solution {
    Solution(int amount, string str);
    int amountOfMoves;
    string direction;
};

Solution::Solution(int amount, string str) {
    amountOfMoves = amount;
    direction = str;
}

struct State {
    string stat;
    string way;
    int posOfZero;
    explicit State (string& s, string w, int pOfZero);
    explicit State (State& prevStat, char direction, int newPosOfZero);
    void Print ();
    bool isSolvable() const;
    void GetNextStates(vector<State>& nextStates, State& state);
};

void State::Print() {
    cout << stat;
}

State::State(string &s, string w, int pOfZero) {
    stat = s;
    way = w;
    posOfZero = pOfZero;
}

State::State(State &prevStat, char direction, int pOfZero) {
    stat = prevStat.stat;
    posOfZero = pOfZero;
    swap(stat[prevStat.posOfZero], stat[posOfZero]);
    way = prevStat.way + direction;
}

void State::GetNextStates(vector<State> &nextStates, State& state) {
    char destination = ' ';
    int pOfZero = 0;
    if (posOfZero / 3 > 0) {
        destination = 'U';
        pOfZero = state.posOfZero - 3;
        State next1(state, destination, pOfZero);
        nextStates.push_back(next1);
    }
    if (posOfZero / 3 < 2) {
        destination = 'D';
        pOfZero = state.posOfZero + 3;
        State next1(state, destination, pOfZero);
        nextStates.push_back(next1);
    }
    if (posOfZero % 3 < 2) {
        destination = 'R';
        pOfZero = state.posOfZero + 1;
        State next1(state, destination, pOfZero);
        nextStates.push_back(next1);
    }
    if (posOfZero % 3 > 0) {
        destination = 'L';
        pOfZero = state.posOfZero - 1;
        State next1(state, destination, pOfZero);
        nextStates.push_back(next1);
    }
}

bool State::isSolvable() const {
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

Solution FindSolution(const State& firstState) { //ищет решение
    vector<State> layer;
    vector<State> nextlayer;
    vector<State> nextStates;
    unordered_set<string> s;
    string finalStr = "123456780";
    int amountOfWays = 0;
    State fState = firstState;
    if (fState.stat == finalStr) {
        Solution sol (amountOfWays, fState.way);
        return sol;
    } else {
        if (!firstState.isSolvable()) {
            Solution sol (amountOfWays, "-1");
            return sol;
        } else {
            s.insert(fState.stat);
            layer.push_back(fState);
            while (layer.size() != 0) {
                ++amountOfWays;
                for (int i = 0; i < layer.size(); ++i) {
                    layer[i].GetNextStates(nextStates, layer[i]);
                    for (int j = 0; j < nextStates.size(); ++j) {
                        if (s.count(nextStates[j].stat) == 0) {
                            if (nextStates[j].stat == finalStr) {
                                Solution sol (amountOfWays, nextStates[j].way);
                                return sol;
                            } else {
                                nextlayer.push_back(nextStates[j]);
                                s.insert(nextStates[j].stat);
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
    Solution sol (amountOfWays, "-1");
    return sol;
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
    Solution answer = FindSolution(firstState);
    if (answer.direction == "-1") {
        cout << "-1";
    } else {
        cout << answer.amountOfMoves << endl;
        cout << answer.direction;
    }
    return 0;
}
