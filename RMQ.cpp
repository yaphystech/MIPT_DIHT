#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Section {
    int firstStat;
    int posOfFirstStat;
    int secondStat;
    int posOfSecondStat;
    Section (int fStat, int pOfFstat, int sStat, int pOfSstat);
};

Section::Section(int fStat, int pOfFstat, int sStat, int pOfSstat){
    firstStat = fStat;
    secondStat = sStat;
    posOfFirstStat = pOfFstat;
    posOfSecondStat = pOfSstat;
}

class SparseTable {
private:
    vector<vector<Section*>> table;
public:
    void Fill(vector<int>& startVec);
    int RMQ(const int& posStart, const int& posEnd, vector<pair<int, int>>& logarifmAndSizeOfMaxSectTwoPower);
    SparseTable(const int& size);
    void Preprocessing(vector<pair<int, int>>& logarifmAndSizeOfMaxSectTwoPower);
};

SparseTable::SparseTable(const int& size) {
    table.resize(size);
}

void SparseTable::Fill(vector<int> &startVec) {
    for (int i = 0; i < startVec.size(); ++i) {
        Section* el = new Section(startVec[i], i, startVec[i], i);
        table[0].push_back(el);
    }
    int plus = 1;
    for (int i = 1; i < table.size(); ++i) {
        if (i == 1) {
            int j = 0;
            while (j + plus < table[0].size()) {
                if (table[i - 1][j]->firstStat < table[i - 1][j + plus]->firstStat) {
                    Section* s = new Section (table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat, table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat);
                    table[1].push_back(s);
                } else {
                    Section* s = new Section (table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat, table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat);
                    table[1].push_back(s);
                }
                ++j;
            }
        } else {
            int j = 0;
            while (j + plus < table[i - 1].size()) {
                if (table[i - 1][j]->firstStat < table[i - 1][j + plus]->firstStat) {
                    pair<int, int> second = min(make_pair(table[i - 1][j]->secondStat, table[i - 1][j]->posOfSecondStat), make_pair(table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat));
                    int secondStat = second.first;
                    int posOfSecondStat = second.second;
                    Section* el = new Section (table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat, secondStat, posOfSecondStat);
                    table[i].push_back(el);
                } else {
                    pair<int, int> second = min(make_pair(table[i - 1][j + plus]->secondStat, table[i - 1][j + plus]->posOfSecondStat), make_pair(table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat));
                    int secondStat = second.first;
                    int posOfSecondStat = second.second;
                    Section* el = new Section (table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat, secondStat, posOfSecondStat);
                    table[i].push_back(el);
                }
                ++j;
            }
        }
        plus *= 2;
    }
}

void SparseTable::Preprocessing(vector<pair<int, int>>& logarifmAndSizeOfMaxSectTwoPower) {
    for (int i = 0; i < logarifmAndSizeOfMaxSectTwoPower.size(); ++i) {
        int len = 1;
        int logarifm = 0;
        while (len < i + 1)  {
            len *= 2;
            if (len < i + 1) {
                ++logarifm;
            } else {
                len = len /2;
                break;
            }
        }
        pair<int, int> el = make_pair(len, logarifm);
        logarifmAndSizeOfMaxSectTwoPower[i] = el;
    }
}

int SparseTable::RMQ (const int& posStart, const int& posEnd, vector<pair<int, int>>& logarifmAndSizeOfMaxSectTwoPower) {
    int logarifm = log2(posEnd - posStart);
    int power = 1;
    int secondStat = 0;
    for (int i = 0; i < logarifm; ++i) {
        power *= 2;
    }
    if (logarifm == 0) {
        secondStat = max(table[logarifm][posStart]->firstStat, table[logarifm][posEnd - power + 1]->firstStat);
    } else {
        if (table[logarifm][posStart]->posOfFirstStat == table[logarifm][posEnd - power + 1]->posOfFirstStat) {
            secondStat = min(table[logarifm][posStart]->secondStat, table[logarifm][posEnd - power + 1]->secondStat);
        } else {
            secondStat = min(max(table[logarifm][posStart]->firstStat, table[logarifm][posEnd - power + 1]->firstStat),
                             min(table[logarifm][posStart]->secondStat,
                                 table[logarifm][posEnd - power + 1]->secondStat));
        }
    }
    return  secondStat;
}

int main() {
    int amount, numbOfDiapazones, numb, power;
    numb = 1;
    power = 0;
    cin >> amount >> numbOfDiapazones;
    while (numb < amount) {
        numb *= 2;
        if (numb <= amount) {
            power += 1;
        }
    }
    SparseTable table(power + 1);
    vector<int> input(amount);
    vector<int> output(numbOfDiapazones);
    for (int i = 0; i < amount; ++i) {
        cin >> input[i];
    }
    table.Fill(input);
    vector<pair<int, int>> preprocessing(amount);
    table.Preprocessing(preprocessing);
    for (int i = 0; i < numbOfDiapazones; ++i) {
        int posStart, posEnd;
        cin >> posStart >> posEnd;
        output[i] = table.RMQ(posStart - 1, posEnd - 1, preprocessing);
    }
    for (int i = 0; i < output.size(); ++i) {
        cout << output[i] << endl;
    }
    return 0;
}
