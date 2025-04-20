#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int INF = 1e9;

void optimalBST(const vector<double>& p, int n) {
    vector<vector<double>> cost(n + 2, vector<double>(n + 1, 0));
    vector<vector<double>> weight(n + 2, vector<double>(n + 1, 0));
    vector<vector<int>> root(n + 2, vector<int>(n + 1, 0));

    for (int i = 1; i <= n + 1; i++) {
        cost[i][i - 1] = 0;
        weight[i][i - 1] = 0;
    }

    for (int i = 1; i <= n; i++) {
        weight[i][i] = p[i];
        cost[i][i] = p[i];
        root[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            cost[i][j] = INF;
            weight[i][j] = weight[i][j - 1] + p[j];

            for (int r = i; r <= j; r++) {
                double c = 0;
                if (r > i)
                    c += cost[i][r - 1];
                if (r < j)
                    c += cost[r + 1][j];
                c += weight[i][j];

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "\nMinimum expected search cost: " << cost[1][n] << endl;

    cout << "\nRoot Table (Subtree roots):\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            cout << "Root of keys[" << i << "..." << j << "] = k" << root[i][j] << endl;
        }
    }
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<double> p(n + 1);
    cout << "Enter the search probabilities for keys k1 to k" << n << ":\n";
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }

    optimalBST(p, n);

    return 0;
}