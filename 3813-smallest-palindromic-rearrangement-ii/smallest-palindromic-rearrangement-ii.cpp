#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Computes nCr (combinations) with a cap to prevent integer overflow
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (r > n / 2) r = n - r; // Optimization: C(n, r) == C(n, n - r)
        
        long long res = 1;
        for (int i = 1; i <= r; ++i) {
            res = res * (n - i + 1);
            res /= i;
            // Since max k is 10^6, we cap the result early to save computation 
            // and prevent exceeding long long bounds on massive strings.
            if (res > 1000000) return 1000001; 
        }
        return res;
    }

    // Computes the number of distinct permutations for a given set of character counts
    long long calcPermutations(const vector<int>& counts) {
        long long perms = 1;
        int total = 0;
        for (int c : counts) {
            total += c;
            if (c > 0) {
                // Number of ways to place 'c' identical items into 'total' slots
                perms = perms * nCr(total, c);
                if (perms > 1000000) return 1000001;
            }
        }
        return perms;
    }

public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        string mid = "";
        vector<int> half_counts(26, 0);
        int half_len = 0;
        
        for (int i = 0; i < 26; ++i) {
            if (freq[i] % 2 != 0) {
                mid += (char)('a' + i);
            }
            half_counts[i] = freq[i] / 2;
            half_len += half_counts[i];
        }
        
        // Base Check: If total possible palindromes are less than k, return ""
        if (calcPermutations(half_counts) < k) {
            return "";
        }
        
        string left_half = "";
        // Construct the left half string character by character
        for (int i = 0; i < half_len; ++i) {
            for (int c = 0; c < 26; ++c) {
                if (half_counts[c] > 0) {
                    // Try placing character 'c'
                    half_counts[c]--;
                    
                    long long P = calcPermutations(half_counts);
                    if (P >= k) {
                        // The k-th permutation falls within this sub-tree
                        left_half += (char)('a' + c);
                        break;
                    } else {
                        // The k-th permutation is further down, subtract skipped paths
                        k -= P;
                        half_counts[c]++; // Backtrack and try next character
                    }
                }
            }
        }
        
        // Construct the final full palindrome
        string right_half = left_half;
        reverse(right_half.begin(), right_half.end());
        return left_half + mid + right_half;
    }
};