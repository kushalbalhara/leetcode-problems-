class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {

        vector<int> ans;

        if (s.empty() || words.empty())
            return ans;

        int wordLen = words[0].length();
        int wordCount = words.size();
        int totalLen = wordLen * wordCount;

        if (s.length() < totalLen)
            return ans;

        unordered_map<string, int> required;

        for (string word : words) {
            required[word]++;
        }

        // We need to try every possible offset
        for (int offset = 0; offset < wordLen; offset++) {

            int left = offset;
            int right = offset;

            unordered_map<string, int> window;

            int usedWords = 0;

            while (right + wordLen <= s.length()) {

                // Take the next word
                string word = s.substr(right, wordLen);
                right += wordLen;

                // Word doesn't exist in words
                if (required.find(word) == required.end()) {

                    window.clear();
                    usedWords = 0;
                    left = right;

                    continue;
                }

                // Add word to current window
                window[word]++;
                usedWords++;

                // Too many copies of this word
                while (window[word] > required[word]) {

                    string leftWord = s.substr(left, wordLen);
                    window[leftWord]--;

                    left += wordLen;
                    usedWords--;
                }

                // We have exactly all required words
                if (usedWords == wordCount) {
                    ans.push_back(left);

                    // Move window forward
                    string leftWord = s.substr(left, wordLen);
                    window[leftWord]--;

                    left += wordLen;
                    usedWords--;
                }
            }
        }

        return ans;
    }
};