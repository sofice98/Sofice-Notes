import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Solution {
    //**************************************
    //递归法
    //T(n*2^n),S(n*2^n)
    public static List<List<Integer>> subsets1(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        // 加入空集
        res.add(new ArrayList<Integer>());
        // 递归
        for (int num : nums) {
            List<List<Integer>> newSubsets = new ArrayList<>();
            for(List<Integer> subset:res){
                List<Integer> newSubset = new ArrayList<Integer>(subset);//复制结果中已经存在的子集
                newSubset.add(num); // 将数字加入
                newSubsets.add(newSubset); // 加入输出结果
            }
            res.addAll(newSubsets);
        }
        return res;
    }
    //**************************************
    //回溯法
    //T(n*2^n),S(n*2^n)
    List<List<Integer>> res = new ArrayList<List<Integer>>();
    List<Integer> tmp = new ArrayList<Integer>();

    public List<List<Integer>> subsets2(int[] nums) {
        dfs(0, nums);
        return res;
    }
    //cur:当前位置
    public void dfs(int cur, int[] nums) {
        if (cur == nums.length) {
            res.add(new ArrayList<Integer>(tmp));
            return;
        }
        // 考虑选择当前位置
        tmp.add(nums[cur]);
        dfs(cur + 1, nums);
        tmp.remove(tmp.size() - 1);
        // 考虑不选择当前位置
        dfs(cur + 1, nums);
    }
    //**************************************
    //二进制编码法
    //T(n*2^n),S(n*2^n)
    public static List<List<Integer>> subsets3(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        int n = nums.length;

        // (1)直接生成二进制编码
        /*for (int i = (int)Math.pow(2,n); i < (int)Math.pow(2,n+1); i++){
            String bitmask = Integer.toBinaryString(i).substring(1);

            List<Integer> cur = new ArrayList<>();
            for (int j = 0; j < n; j++){
                if(bitmask.charAt(j) == '1') cur.add(nums[j]);
            }
            res.add(cur);
        }*/
        // (2)不生成二进制编码，使用掩码
        for (int mask = 0; mask < (1<<n); mask++){
            List<Integer> tmp = new ArrayList<Integer>();
            for (int i = 0; i < n; i++){
                if((mask & (1<<i)) != 0)  tmp.add(nums[i]);
            }
            res.add(tmp);
        }
        return res;
    }


    public static void main(String[] args) {
        int[] nums = {1,2,3};
        System.out.println(subsets1(nums));
    }
}

