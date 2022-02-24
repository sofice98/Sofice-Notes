

public class Solution {
    // 双指针最速搜索 o(n)
    public static int maxArea(int[] height) {
        int max = -1;
        int l = 0;
        int r = height.length - 1;
        while (l < r){
            int la = height[l];
            int ra = height[r];
            int area = (r - l) * (la < ra? la : ra);
            max = area < max? max : area;
            // 优化如果移动后的指针比之前小就继续移动
            if(la <= ra){
                while (l < r && height[++l] <= la);
            }
            else{
                while (l < r && height[--r] <= ra);
            }
        }
        return max;
    }

    public static void main(String[] args) {
        System.out.println(maxArea(new int[]{1,2,4,3}));
    }
}