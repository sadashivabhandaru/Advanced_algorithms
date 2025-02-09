#include <iostream>
#include <vector>
using namespace std;

string findLongestCommonSubstring(const string& str1, const string& str2) {
    int n = str1.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    int maxLength = 0, endIdx = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIdx = i;
                }
            }
        }
    }

    cout << "\nDynamic Programming Table:\n";
    for (const auto& row : dp) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return str1.substr(endIdx - maxLength, maxLength);
}

int main() {
    string str1, str2;

    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    if (str1.length() != str2.length()) {
        cout << "Error: Strings must have the same length.\n";
        return 1;
    }

    string lcs = findLongestCommonSubstring(str1, str2);
    cout << "\nLongest Common Substring: " << lcs << " (Length: " << lcs.length() << ")\n";

    return 0;
}
