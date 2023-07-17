#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Symbol {
    char symbol;
    double probability;
    string code;
};

bool sortByProbability(const Symbol& a, const Symbol& b) {
    return a.probability > b.probability;
}

void shannonFano(vector<Symbol>& symbols, int startIndex, int endIndex) {
    if (startIndex == endIndex) {
        return;
    }

    double sumProb = 0.0;
    for (int i = startIndex; i <= endIndex; i++) {
        sumProb += symbols[i].probability;
    }

    double halfProb = 0.0;
    int partitionIndex = -1;
    for (int i = startIndex; i <= endIndex; i++) {
        halfProb += symbols[i].probability;
        if (halfProb >= sumProb / 2) {
            partitionIndex = i;
            break;
        }
    }

    for (int i = startIndex; i <= partitionIndex; i++) {
        symbols[i].code += '0';
    }

    for (int i = partitionIndex + 1; i <= endIndex; i++) {
        symbols[i].code += '1';
    }

    shannonFano(symbols, startIndex, partitionIndex);
    shannonFano(symbols, partitionIndex + 1, endIndex);
}

int main() {
    int n;
    cout << "Enter the number of symbols: ";
    cin >> n;

    vector<Symbol> symbols(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter symbol " << i+1 << ": ";
        cin >> symbols[i].symbol;
        cout << "Enter probability of " << symbols[i].symbol << ": ";
        cin >> symbols[i].probability;
    }

    sort(symbols.begin(), symbols.end(), sortByProbability);

    shannonFano(symbols, 0, n-1);

    cout << "\nSymbol\tProbability\tCode\n";
    for (int i = 0; i < n; i++) {
        cout << symbols[i].symbol << "\t" << symbols[i].probability << "\t\t" << symbols[i].code << endl;
    }

    return 0;
}
