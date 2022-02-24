

public class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        int m = matrix.length;
        if(m == 0)  return false;
        int n = matrix[0].length;
        int i = 0;
        int j = n - 1;
        while(i < m && j >= 0){
            if(matrix[i][j] == target) return true;
            else if(matrix[i][j] > target){
                while(j >= 0 && matrix[i][j] > target) --j;
            }
            else{
                while(i < m && matrix[i][j] < target) ++i;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        System.out.println(searchMatrix(new int[]{1,2,4,3}));
    }
}