#include <iostream>
#include <vector>
#include <cmath>

using std::vector, std::pair, std::make_pair, std::min, std::endl, std::max, std::cin, std::cout;

class SparseTable{
private:
    vector<vector<pair<pair<int, int>, pair<int, int>>>> table;
public:
    SparseTable (const int& size);
    void Fill(vector<int>& startArr);
    int RMQ(const int& posStart, const int& posEnd);
    int Out(const int& start, const int& end);
};

SparseTable::SparseTable(const int& size) {
    table.resize(size);
}

void SparseTable::Fill(vector<int>& startArr) {
    table[0].resize(startArr.size());
    for (int i = 0; i < startArr.size(); ++i){
        table[0][i] = make_pair(make_pair(startArr[i], i), make_pair(startArr[i], i));
    }
    int plus = 1;

    for (int i = 1; i < table.size(); ++i) {
        if (i == 1) {
            table[1].resize(table[0].size() - plus);
            for (int j = 0; j < table[1].size(); ++j) {
                if (table[i - 1][j].first.first < table[i - 1][j + plus].first.first) {
                    table[i][j].first = table[i - 1][j].first;
                    table[i][j].second = table[i - 1][j + plus].first;
                } else {
                    table[i][j].first = table[i - 1][j + plus].first;
                    table[i][j].second = table[i - 1][j].first;
                }
            }

        } else{
            table[i].resize(table[i - 1].size() - plus);
            for (int j = 0; j < table[i].size(); ++j) {
                if (table[i - 1][j].first.first < table[i - 1][j + plus].first.first) {
                    table[i][j].first = table[i - 1][j].first;
                    table[i][j].second = min(table[i - 1][j].second, table[i - 1][j + plus].first);
                } else {
                    table[i][j].first = table[i - 1][j + plus].first;
                    table[i][j].second = min(table[i - 1][j + plus].second, table[i - 1][j].first);
                }
            }
        }
        plus *= 2;
    }
}

int SparseTable::RMQ(const int &posStart, const int &posEnd) {
    int logarifm = log2(posEnd - posStart);
    int secondStat = 0;
    int power = 1;
    for (int i = 0; i < logarifm; ++i) {
        power *= 2;
    }
    if (logarifm == 0) {
        secondStat = max(table[logarifm][posStart].first.first, table[logarifm][posEnd - power + 1].first.first);
    } else {
        if (table[logarifm][posStart].first.second == table[logarifm][posEnd - power + 1].first.second) {
            secondStat = min(table[logarifm][posStart].second.first, table[logarifm][posEnd - power + 1].second.first);
        } else {
            secondStat = min(max(table[logarifm][posStart].first.first, table[logarifm][posEnd - power + 1].first.first),
                             min(table[logarifm][posStart].second.first, table[logarifm][posEnd - power + 1].second.first));
        }
    }
    return secondStat;
}

int SparseTable::Out(const int &start, const int &end) {
    return table[start][end].second.first;
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
    for (int i = 0; i < numbOfDiapazones; ++i) {
        int posStart, posEnd;
        cin >> posStart >> posEnd;
        output[i] = table.RMQ(posStart - 1, posEnd - 1);
    }
    for (int i = 0; i < output.size(); ++i) {
        cout << output[i] << endl;
    }
    return 0;
}
