#include <iostream>
#include <vector>
using namespace std;

struct TestCase {
    int power;
    int skips;
    int recharge;
    vector<int> powerOfEnemies;
    string expectedOutcome;
};

bool solve(vector<int>& powerOfEnemies, int initialPower, int enemyNo, int currPower, int skips, int recharge) {
    if (enemyNo >= powerOfEnemies.size()) {
        return true;
    }
    if (currPower >= powerOfEnemies[enemyNo]) {
        // fight
        bool ans1 = solve(powerOfEnemies, initialPower, enemyNo + 1, currPower - powerOfEnemies[enemyNo], skips, recharge);
        bool ans2 = false;
        if (skips > 0)
            ans2 = solve(powerOfEnemies, initialPower, enemyNo + 1, currPower, skips - 1, recharge);
        return ans1 || ans2;
    } else if (initialPower > powerOfEnemies[enemyNo]) {
        bool ans1 = false, ans2 = false;
        if (recharge > 0)
            // recharge and fight
            ans1 = solve(powerOfEnemies, initialPower, enemyNo + 1, initialPower - powerOfEnemies[enemyNo], skips, recharge - 1);
        if (skips > 0)
            // skip
            ans2 = solve(powerOfEnemies, initialPower, enemyNo + 1, currPower, skips - 1, recharge);
        return ans1 || ans2;
    } else {
        if (skips > 0)
            // skip
            return solve(powerOfEnemies, initialPower, enemyNo + 1, currPower, skips - 1, recharge);
        else
            return false;
    }
}

bool chakravyuh(vector<int>& powerOfEnemies, int initialPower, int skips, int recharge) {
    if (skips >= powerOfEnemies.size()) {
        // abhimanyu can skip all the enemies
        return true;
    }
    powerOfEnemies[3] += powerOfEnemies[2] / 2;
    powerOfEnemies[7] += powerOfEnemies[6] / 2;

    return solve(powerOfEnemies, initialPower, 0, initialPower, skips, recharge);
}

int main() {
    vector<TestCase> testCases = {
        {50, 2, 3, {20, 30, 40, 15, 25, 35, 45, 10, 20, 30, 40}, "no"},
        {30, 1, 2, {20, 30, 15, 10, 25, 35, 50, 20, 30, 10, 20}, "no"},
        {10, 6, 2, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 1}, "yes"},
        {5, 5, 3, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 7}, "no"},
        {16, 1, 2, {10, 14, 2, 3, 3, 3, 2, 3, 3, 3, 3}, "yes"},
        {8, 3, 1, {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, "no"},
        {25, 4, 2, {15, 20, 10, 30, 25, 5, 12, 18, 22, 15, 9}, "yes"},
        {12, 2, 3, {20, 22, 25, 30, 28, 18, 17, 15, 14, 13, 11}, "no"},
        {10, 6, 2, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 1}, "yes"},
        {5, 5, 3, {0, 10, 2, 3, 9, 5, 6, 7, 8, 4, 7}, "no"}
    };

    for (auto& testCase : testCases) {
        bool result = chakravyuh(testCase.powerOfEnemies, testCase.power, testCase.skips, testCase.recharge);
        cout << (result ? "Yes" : "No") << " (Expected: " << testCase.expectedOutcome << ")" << endl;
    }

    return 0;
}
