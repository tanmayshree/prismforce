#include <bits/stdc++.h>
using namespace std;

struct TestCase {
    int power;
    int skips;
    int recharge;
    vector<int> powerOfEnemies;
    string expectedOutcome;
};

bool canDefeatAllEnemies(vector<int>& powerOfEnemies, int initialPower, int maxSkips, int maxRecharge) {

    vector<int> enemies = powerOfEnemies;
    enemies[3] += enemies[2] / 2;
    enemies[7] += enemies[6] / 2;

    queue<tuple<int, int, int, int>> q;
    q.push(make_tuple(0, initialPower, maxSkips, maxRecharge));

    while (!q.empty()) {
        auto [enemyIndex, currPower, skipsLeft, rechargeLeft] = q.front();
        q.pop();

        if (enemyIndex >= enemies.size()) {
            return true;
        }

        if (currPower >= enemies[enemyIndex]) {
            q.push(make_tuple(enemyIndex + 1, currPower - enemies[enemyIndex], skipsLeft, rechargeLeft));
        }

        if (skipsLeft > 0) {
            q.push(make_tuple(enemyIndex + 1, currPower, skipsLeft - 1, rechargeLeft));
        }

        if (rechargeLeft > 0 && currPower < enemies[enemyIndex]) {
            q.push(make_tuple(enemyIndex + 1, initialPower - enemies[enemyIndex], skipsLeft, rechargeLeft - 1));
        }
    }

    return false;
}

int main() {
    vector<TestCase> testCases = {
        {50, 2, 3, {20, 30, 40, 15, 25, 35, 45, 10, 20, 30, 40}, "no"},
        {30, 1, 2, {20, 30, 15, 10, 25, 35, 50, 20, 30, 10, 20}, "no"},
        {10, 6, 2, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 1}, "yes"},
        {5, 5, 3, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 7}, "no"},
        {16, 1, 2, {10, 14, 2, 3, 3, 3, 2, 3, 3, 3, 3}, "yes"},
        {8, 3, 1, {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, "no"},
        {25, 4, 2, {15, 20, 10, 30, 25, 5, 12, 18, 22, 15, 9}, "no"},
        {12, 2, 3, {20, 22, 25, 30, 28, 18, 17, 15, 14, 13, 11}, "no"},
        {10, 6, 2, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 1}, "yes"},
        {5, 5, 3, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 7}, "no"}
    };

    for (auto& testCase : testCases) {
        bool result = canDefeatAllEnemies(testCase.powerOfEnemies, testCase.power, testCase.skips, testCase.recharge);
        cout << (result ? "Yes" : "No") << " (Expected: " << testCase.expectedOutcome << ")" << endl;
    }

    return 0;
}
