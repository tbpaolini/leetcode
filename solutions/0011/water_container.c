// Problem 11 - Container With Most Water
// https://leetcode.com/problems/container-with-most-water/

int maxArea(int* height, int heightSize){
    int left = 0;
    int right = heightSize - 1;
    int max_area = 0;

    while (left < right)
    {
        const int left_height  = height[left];
        const int right_height = height[right];
        int area;
        
        if (left_height > right_height)
        {
            area = right_height * (right - left);
            right--;
        }
        else
        {
            area = left_height * (right - left);
            left++;
        }

        if (area > max_area) max_area = area;
    }
    
    return max_area;
}