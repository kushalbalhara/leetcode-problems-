class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
      
        // Arrays to store the maximum height to the left and right of each position
        vector<int> leftMax(n), rightMax(n);
      
        // Initialize the first and last elements
        leftMax[0] = height[0];
        rightMax[n - 1] = height[n - 1];
      
        // Build the maximum height arrays
        // leftMax[i] = maximum height from index 0 to i
        // rightMax[i] = maximum height from index i to n-1
        for (int i = 1; i < n; ++i) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
            rightMax[n - i - 1] = max(rightMax[n - i], height[n - i - 1]);
        }
      
        // Calculate the total trapped water
        int totalWater = 0;
        for (int i = 0; i < n; ++i) {
            // Water level at position i is determined by the minimum of
            // the maximum heights on both sides
            // Trapped water = water level - ground height
            totalWater += min(leftMax[i], rightMax[i]) - height[i];
        }
      
        return totalWater;
    }
};
