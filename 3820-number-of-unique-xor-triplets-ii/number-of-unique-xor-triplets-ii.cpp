class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int x : nums) {
            // Update in increasing order because the same index
            // can be chosen multiple times (i <= j <= k).
            for (int cnt = 0; cnt < 3; cnt++) {
                for (int xr = 0; xr < MAXX; xr++) {
                    if (dp[cnt][xr]) {
                        dp[cnt + 1][xr ^ x] = true;
                    }
                }
            }
        }

        int ans = 0;
        for (bool ok : dp[3])
            if (ok) ans++;

        return ans;
    }
};