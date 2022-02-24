import java.util.Arrays;

public class Solution {
    //二分法 o(nlogn)
    public static int[] twoSum(int[] numbers, int target) {
        for(int i = 0;i < numbers.length - 1;i++){
            int l = i + 1;
            int r = numbers.length - 1;
            while(l <= r){
                int mid = (l + r) >> 1;
                if(numbers[mid] == target - numbers[i]){
                    return new int[] {i+1,mid+1};
                }
                else if(numbers[mid] > target - numbers[i]){
                    r = mid - 1;
                }
                else{
                    l = mid + 1;
                }
            }
        }
        return null;
    }
    // 双指针最速缩小搜索范围 o(n)
    public static int[] twoSum1(int[] numbers, int target) {
        int l = 0;
        int r = numbers.length - 1;
        while(l < r){
            int sum = numbers[l] + numbers[r];
            if(sum == target)   return new int[] {l+1,r+1};
            else if(sum < target)    l++;
            else                r--;
        }
        return null;
    }

    public static void main(String[] args) {
        System.out.println(Arrays.toString(twoSum(new int[]{2,3,4}, 6)));
    }
}