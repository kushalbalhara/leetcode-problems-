class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Frequency of characters available from s
        int cnt[26] = {};

        for (char ch : s) {
            cnt[ch - 'a']++;
        }

        // Try to match target from left to right
        int i = 0;

        while (i < n && cnt[target[i] - 'a'] > 0) {
            cnt[target[i] - 'a']--;
            i++;
        }

        // Now move backwards and try to make the string
        // just slightly greater than target
        while (true) {

            // If we have not reached the end,
            // try to put the smallest character > target[i]
            if (i < n) {

                for (int c = target[i] - 'a' + 1; c < 26; c++) {

                    if (cnt[c] == 0)
                        continue;

                    string ans = target.substr(0, i);

                    // Put the smallest possible greater character
                    ans.push_back('a' + c);

                    cnt[c]--;

                    // Fill remaining characters in ascending order
                    for (int x = 0; x < 26; x++) {
                        ans.append(cnt[x], 'a' + x);
                    }

                    return ans;
                }
            }

            // Couldn't make target greater at this position.
            // Move one position back.
            if (i == 0)
                break;

            i--;

            // Restore the character we had used for target[i]
            cnt[target[i] - 'a']++;
        }

        // No permutation is greater than target
        return "";
    }
};