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
public:
    SparseTable(const int& size, const int& amount);
    ~SparseTable();
    void Fill(const vector<int>& startVec);
    int RMQ(const int& posStart, const int& posEnd);
    void Preprocessing(int amount);
private:
    vector<vector<Section*>> table;
    vector<pair<int, int>> logarifmAndSizeOfMaxSectTwoPower;
};

SparseTable::SparseTable(const int& size, const int& amount) {
    table.resize(size);
    logarifmAndSizeOfMaxSectTwoPower.resize(amount);
}

SparseTable::~SparseTable() {
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table.size(); ++j) {
            delete(table[i][j]);
        }
    }
}

void SparseTable::Fill(const vector<int> &startVec) {
    for (int i = 0; i < startVec.size(); ++i) { //заполняем нулевой уровень
        Section* el = new Section(startVec[i], i, startVec[i], i);
        table[0].push_back(el);
    }
    int plus = 1;
    for (int i = 1; i < table.size(); ++i) { //заполняем остальные уровни
        if (i == 1) { //отдельно обрабатываем заполнение первого уровня
            int j = 0; //нужен для прохода по предыдущему уровню
            while (j + plus < table[0].size()) { //пока не вышли за границы уровня
                if (table[i - 1][j]->firstStat < table[i - 1][j + plus]->firstStat) { //если первая статистика левого отрезка меньше первой статистики правого
                    Section* s = new Section (table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat, table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat);
                    table[1].push_back(s); //тогда они и есть первые две статистики нового отрезка(т.к. уровень первый)
                } else {
                    Section* s = new Section (table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat, table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat);
                    table[1].push_back(s); //иначе наоборот
                }
                ++j; //идём дальше по предыдущему слою
            }
        } else { //заполнение абсолютно любого уровня
            int j = 0; //идём по предыдущему
            while (j + plus < table[i - 1].size()) { //пока не вышли за границы
                if (table[i - 1][j]->firstStat < table[i - 1][j + plus]->firstStat) { //если первая статистика левого отрезка меньше первой статистики правого
                    pair<int, int> second = min(make_pair(table[i - 1][j]->secondStat, table[i - 1][j]->posOfSecondStat), make_pair(table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat));
                    int secondStat = second.first; //тогда вторая статистика нового отрезка - это минимум из второй статистики левого и первой статистики правого
                    int posOfSecondStat = second.second;
                    Section* el = new Section (table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat, secondStat, posOfSecondStat);
                    table[i].push_back(el);
                } else { //иначе вторая статистика нового отрезка - это минимум из второй статистики левого отрезка и первой статистики правого отрезка
                    pair<int, int> second = min(make_pair(table[i - 1][j + plus]->secondStat, table[i - 1][j + plus]->posOfSecondStat), make_pair(table[i - 1][j]->firstStat, table[i - 1][j]->posOfFirstStat));
                    int secondStat = second.first;
                    int posOfSecondStat = second.second;
                    Section* el = new Section (table[i - 1][j + plus]->firstStat, table[i - 1][j + plus]->posOfFirstStat, secondStat, posOfSecondStat);
                    table[i].push_back(el);
                }
                ++j;
            }
        }
        plus *= 2; //увеличиваем в два раза, т.к. конструируем отрезки в два раза большей длины
    }
}

void SparseTable::Preprocessing(int amount) {
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

int SparseTable::RMQ (const int& posStart, const int& posEnd) {
    int logarifm = logarifmAndSizeOfMaxSectTwoPower[posEnd - posStart].second;
    int power = logarifmAndSizeOfMaxSectTwoPower[posEnd - posStart].first;
    int secondStat = 0;
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
    SparseTable table(power + 1, amount);
    vector<int> input(amount);
    vector<int> output(numbOfDiapazones);
    for (int i = 0; i < amount; ++i) {
        cin >> input[i];
    }
    table.Fill(input);
    table.Preprocessing(amount);
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
