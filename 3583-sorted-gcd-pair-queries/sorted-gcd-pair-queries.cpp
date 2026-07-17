class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<int> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        vector<long long> divisible(mx + 1, 0);

        // Count numbers divisible by each i
        for (int i = 1; i <= mx; i++) {
            for (int j = i; j <= mx; j += i) {
                divisible[i] += freq[j];
            }
        }

        // exact[g] = number of pairs whose gcd is exactly g
        vector<long long> exact(mx + 1, 0);

        for (int g = mx; g >= 1; g--) {
            long long c = divisible[g];
            exact[g] = c * (c - 1) / 2;

            for (int m = g + g; m <= mx; m += g) {
                exact[g] -= exact[m];
            }
        }

        // Prefix counts in sorted gcdPairs
        vector<long long> prefix(mx + 1, 0);
        for (int i = 1; i <= mx; i++) {
            prefix[i] = prefix[i - 1] + exact[i];
        }

        vector<int> ans;
        for (long long q : queries) {
            int g = lower_bound(prefix.begin() + 1, prefix.end(), q + 1) - prefix.begin();
            ans.push_back(g);
        }

        return ans;
    }
};