class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> st;
        int left = 0, right = 0;
        int ans = 0;

        while (right < s.size()) {

            while (st.count(s[right])) {
                st.erase(s[left]);
                left++;
            }

            st.insert(s[right]);
            ans = max(ans, right - left + 1);
            right++;
        }

        return ans;
    }
};