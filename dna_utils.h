#ifndef DNA_UTILS_H
#define DNA_UTILS_H

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Compute Hamming Distance (only works if lengths are equal)
int hammingDistance(const string &a, const string &b) {
    int diff = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i] != b[i]) diff++;
    }
    return diff;
}

// Compute Edit Distance (Levenshtein)
int editDistance(const string &a, const string &b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1];
            else {
                dp[i][j] = 1 + min({ dp[i-1][j], dp[i][j-1], dp[i-1][j-1] });
            }
        }
    }
    return dp[n][m];
}

#endif
