#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

bool isStrictlyDecreasing(int n, int a[]) {
    for (int i = 1; i < n; ++i) {
        if (a[i] >= a[i - 1]) {
            return false;
        }
    }
    return true;
}

int f(int idx, int prev_idx, int n, int a[], vector<vector<int> >& dp) {
    if (idx == n) {
        return 0;
    }

    if (dp[idx][prev_idx + 1] != -1) {
        return dp[idx][prev_idx + 1];
    }

    int notTake = 0 + f(idx + 1, prev_idx, n, a, dp);
    int take = INT_MIN;
    if (prev_idx == -1 || a[idx] > a[prev_idx]) {
        take = 1 + f(idx + 1, idx, n, a, dp);
    }

    return dp[idx][prev_idx + 1] = max(take, notTake);
}

int longestSubsequence(int n, int a[]) {
    if (isStrictlyDecreasing(n, a)) {
        return 0; // Return 0 directly for strictly decreasing array
    }

    vector<vector<int> > dp(n + 1, vector<int>(n + 1, -1));
    int lisLength = f(0, -1, n, a, dp);
    return lisLength;
}

int main() {
    ifstream inputFile("input1.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    int numTestCases;
    inputFile >> numTestCases;

    for (int t = 0; t < numTestCases; ++t) {
        int n;
        inputFile >> n;
        int a[n];
        for (int i = 0; i < n; ++i) {
            inputFile >> a[i];
        }

        int lisLength = longestSubsequence(n, a);
        cout << "Test Case " << t + 1 << ": Length of the Longest Increasing Subsequence is " << lisLength << endl;
    }

    inputFile.close();
    return 0;
}
