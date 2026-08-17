class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();

        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }

        vector<vector<int>> dp(n, vector<int>(n, -1));

        function<int(int, int)> dfs = [&](int left, int right) -> int {
            if (left >= right)
                return 0;

            if (dp[left][right] != -1)
                return dp[left][right];

            int ans = 0;

            int leftSum = 0;
            int rightSum = prefix[right + 1] - prefix[left];

            for (int k = left; k < right; k++) {

                leftSum += stoneValue[k];
                rightSum -= stoneValue[k];

                if (leftSum < rightSum) {

                    // This split cannot beat current answer
                    if (ans >= 2 * leftSum)
                        continue;

                    ans = max(ans,
                             leftSum + dfs(left, k));

                }
                else if (leftSum > rightSum) {

                    // Future rightSum will only become smaller,
                    // so if this can't improve ans, stop completely.
                    if (ans >= 2 * rightSum)
                        break;

                    ans = max(ans,
                             rightSum + dfs(k + 1, right));

                }
                else {

                    // Equal sums: Alice can choose either side
                    ans = max(ans,
                             max(leftSum + dfs(left, k),
                                 rightSum + dfs(k + 1, right)));
                }
            }

            return dp[left][right] = ans;
        };

        return dfs(0, n - 1);
    }
};