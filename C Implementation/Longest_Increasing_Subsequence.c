#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool isStrictlyDecreasing(int n, int a[]) {
    for (int i = 1; i < n; ++i) {
        if (a[i] >= a[i - 1]) {
            return false;
        }
    }
    return true;
}

int f(int idx, int prev_idx, int n, int a[], int **dp) {
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

    return dp[idx][prev_idx + 1] = (take > notTake) ? take : notTake;
}

int longestSubsequence(int n, int a[]) {
    if (isStrictlyDecreasing(n, a)) {
        return 0; // Return 0 directly for strictly decreasing array
    }

    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; ++i) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = -1;
        }
    }

    int lisLength = f(0, -1, n, a, dp);

    for (int i = 0; i <= n; ++i) {
        free(dp[i]);
    }
    free(dp);

    return lisLength;
}

int main() {
    FILE *inputFile = fopen("input1.txt", "r");
    if (!inputFile) {
        perror("Error: Unable to open input file.");
        return 1;
    }

    int numTestCases;
    if (fscanf(inputFile, "%d", &numTestCases) != 1) {
        fprintf(stderr, "Error: Unable to read the number of test cases.\n");
        fclose(inputFile);
        return 1;
    }

    for (int t = 0; t < numTestCases; ++t) {
        int n;
        if (fscanf(inputFile, "%d", &n) != 1) {
            fprintf(stderr, "Error: Unable to read the size of the array for Test Case %d.\n", t + 1);
            fclose(inputFile);
            return 1;
        }

        int *a = (int *)malloc(n * sizeof(int));
        if (!a) {
            fprintf(stderr, "Error: Memory allocation failed for array in Test Case %d.\n", t + 1);
            fclose(inputFile);
            return 1;
        }
        for (int i = 0; i < n; ++i) {
            if (fscanf(inputFile, "%d", &a[i]) != 1) {
                fprintf(stderr, "Error: Unable to read the array elements for Test Case %d.\n", t + 1);
                fclose(inputFile);
                free(a);
                return 1;
            }
        }
        int lisLength = longestSubsequence(n, a);
        printf("Test Case %d: Length of the Longest Increasing Subsequence is %d\n", t + 1, lisLength);

        free(a);
    }

    fclose(inputFile);
    return 0;
}
