#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Section {
    int maxSequence;
    int maxLeftSequence;
    int maxRightSequence;
    int sizeOfSection;
    Section (int mSequence, int mLeftSequence, int mRightSequence, int size);
};

Section::Section (int mSequence, int mLeftSequence, int mRightSequence, int size) {
    maxSequence = mSequence;
    maxLeftSequence = mLeftSequence;
    maxRightSequence = mRightSequence;
    sizeOfSection = size;
}

class SparseTable {
private:
    vector<vector<Section*>> table;
public:
    SparseTable(const int& size);
    void Fill(vector<int>& startArr);
    void Preprocessing(vector<pair<int, int>>& logarifmAndMaxLengthOfTwoPower);
    int RMQ(const int& posStart, const int& posEnd, vector<pair<int, int>>& logarifmAndMaxLengthOfTwoPower);
    pair<pair<int, int>, int>& CountMaxSequence (const int& posStart, const int& posEnd, vector<pair<int, int>> &logarifmAndMaxLengthOfTwoPower, pair<pair<int, int>, int>& trio, int& chosenPart, const int& size);
    void Print();
};

SparseTable::SparseTable(const int &size) {
    table.resize(size);
}

void SparseTable::Fill(vector<int> &startArr) {
    for (int i = 0; i < startArr.size(); ++i) {
        Section* el = new Section (startArr[i], startArr[i], startArr[i], 1);
        table[0].push_back(el);
    }
    int plus = 1;
    for (int i = 1; i < table.size(); ++i) {
        int j = 0;
        while (j + plus < table[i - 1].size()) {
            int mLeftSequence = table[i - 1][j]->maxLeftSequence;
            int mRightSequence = table[i - 1][j + plus]->maxRightSequence;
            int mSequence = max(table[i - 1][j]->maxLeftSequence, max(table[i - 1][j]->maxSequence, max(table[i - 1][j]->maxRightSequence + table[i - 1][j + plus]->maxLeftSequence, max(table[i - 1][j + plus]->maxSequence, table[i - 1][j + plus]->maxRightSequence))));
            if (table[i - 1][j]->maxLeftSequence == table[i - 1][j]->sizeOfSection) {
                mLeftSequence += table[i - 1][j + plus]->maxLeftSequence;
            }
            if (table[i - 1][j + plus]->maxRightSequence == table[i - 1][j + plus]->sizeOfSection) {
                mRightSequence += table[i - 1][j]->maxRightSequence;
            }
            Section* el = new Section (mSequence, mLeftSequence, mRightSequence, table[i - 1][j]->sizeOfSection + table[i - 1][j + plus]->sizeOfSection);
            table[i].push_back(el);
            ++j;
        }
        plus *= 2;
    }
}

void SparseTable::Preprocessing(vector<pair<int, int>>& logarifmAndSizeOfMaxSectTwoPower) {
    for (int i = 0; i <= logarifmAndSizeOfMaxSectTwoPower.size(); ++i) {
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

pair<pair<int, int>, int>& SparseTable::CountMaxSequence (const int& posStart, const int& posEnd, vector<pair<int, int>> &logarifmAndMaxLengthOfTwoPower, pair<pair<int, int>, int>& trio, int& chosenPart, const int& size) {
    int logarifm = logarifmAndMaxLengthOfTwoPower[posEnd - posStart + 1].second;
    int length = logarifmAndMaxLengthOfTwoPower[posEnd - posStart + 1].first;
    chosenPart += length;
    if (chosenPart == size) {
        trio.first.first = table[logarifm][posStart]->maxLeftSequence;
        trio.first.second = table[logarifm][posStart]->maxRightSequence;
        trio.second = table[logarifm][posStart]->maxSequence;
        return trio;
    } else {
        int mLeftSequence = table[logarifm][posStart]->maxLeftSequence;
        pair<pair<int, int>, int> pair = CountMaxSequence(posStart + length, posEnd, logarifmAndMaxLengthOfTwoPower, trio, chosenPart, size);
        int mRightSequence = pair.first.second;
        int mSequence = table[logarifm][posStart]->maxSequence;
        if (table[logarifm][posStart]->maxLeftSequence == table[logarifm][posStart]->sizeOfSection) {
            mLeftSequence += pair.first.first;
        }
        if (mRightSequence == posEnd - posStart - chosenPart + 1) {
            mRightSequence += table[logarifm][posStart]->maxRightSequence;
        }
        mSequence = max(table[logarifm][posStart]->maxLeftSequence, max(table[logarifm][posStart]->maxSequence, max(table[logarifm][posStart]->maxRightSequence + pair.first.first, max(pair.second, pair.first.second))));
        trio = make_pair(make_pair(mLeftSequence, mRightSequence), mSequence);
        return trio;
    }

}

int SparseTable::RMQ(const int &posStart, const int &posEnd, vector<pair<int, int>> &logarifmAndMaxLengthOfTwoPower) {
    int mSequence = 0;
    int mLeftSequence = 0;
    int mRightSequence = 0;
    int chosenPart = 0;
    pair<pair<int, int>, int> pair = make_pair(make_pair(mLeftSequence, mRightSequence), mSequence);
    pair = CountMaxSequence(posStart, posEnd, logarifmAndMaxLengthOfTwoPower, pair, chosenPart, posEnd - posStart + 1);
    mSequence = pair.second;
    return mSequence;
}

void SparseTable::Print() {
    for (auto i : table[1]) {
        cout << i->maxSequence <<i->maxLeftSequence <<i->maxRightSequence<<i->sizeOfSection <<'|';
    }
    cout << table[1].size();
}

int main() {
    int amount, numbOfDiapazones, numb, power;
    numb = 1;
    power = 0;
    cin >> amount >> numbOfDiapazones;
    while (numb < amount) {
        numb *= 2;
        if (numb < amount) {
            ++power;
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
        output[i] = table.RMQ(posStart, posEnd, preprocessing);
    }
    for (auto i : output) {
        cout << i << endl;
    }
    return 0;
}
