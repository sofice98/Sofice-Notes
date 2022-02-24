/**********
*排序
*Sofice
*2020/7/15
*************/
#include<bits/stdc++.h>
using namespace std;
//1插入排序
//1.1直接插入排序
void InsertionSort(int *a, int n, int step=1) {//包含n个元素
    for (int i = step; i < n; i++) {
        int v = a[i], j;
        for (j = i - step; j >= 0 && a[j] > v; j -= step)
            a[j + step] = a[j];
        a[j + step] = v;
    }
    return;
}
//1.2希尔排序
void ShellSort(int* a, int n) {
    int maxg;//计算最大间隔
    for (maxg = 1; maxg < n; maxg = 3 * maxg + 1);//间隔计算公式：g=3*g+1
    maxg = (maxg - 1) / 3;
    for (int g = maxg; g >= 1; g = (g - 1) / 3) {//间隔递减
        InsertionSort(a, n, g);//直接插入排序
    }
    return;
}
//2交换排序
//2.1冒泡排序
void BubbleSort(int* a, int n) {
    bool flag = true;
    for (int i = 0; flag; i++) {
        flag = false;
        for (int j = n - 1; j >= i + 1; j--) {
            if (a[j] < a[j - 1]) {
                swap(a[j], a[j - 1]);
                flag = true;
            }
        }
    }
    return;
}
//2.2快速排序
int Partition(int* a, int low, int high) {//双指针
    int pivotv = a[low];
    while (low < high) {
        while (low < high && a[high] >= pivotv) high--;//从右向左找小的复制到低指针处
        a[low] = a[high];
        while (low < high && a[low] <= pivotv) low++;//从左向右找大的复制到高指针处
        a[high] = a[low];
    }
    a[low] = pivotv;//low=high
    return low;
}
void QuickSort(int* a, int low, int high) {
    if (low < high) {
        int pivot = Partition(a, low, high);
        QuickSort(a, low, pivot - 1);
        QuickSort(a, pivot + 1, high);
    }
    return;
}
//3选择排序
//3.1简单选择排序
void SelectionSort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minj = i;
        for (int j = i; j < n; j++) {
            if (a[j] < a[minj])    minj = j;
        }
        swap(a[i], a[minj]);
    }
    return;
}
//3.2堆排序
void HeapSort(int* a, int n) {

}
//4归并排序
int b[1000];
void Merge(int* a, int low, int mid, int high) {//合并[low...mid]和[mid+1...high]成一个有序表
    memcpy(b + low, a + low, sizeof(int) * (high - low + 1));
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (b[i] <= b[j])  a[k++] = b[i++];//取左边的
        else               a[k++] = b[j++];//取右边的
    }
    while (i <= mid)   a[k++] = b[i++];
    while (j <= high)   a[k++] = b[j++];
    return;
}
void MergeSort(int* a, int low, int high) {
    if (low < high) {
        int mid = (low + high) >> 1;
        MergeSort(a, low, mid);
        MergeSort(a, mid+1, high);
        Merge(a, low, mid, high);
    }
    return;
}
//5基数排序
void LSDSort(int* a, int n) {

}
//6计数排序
void CountingSort(int* a, int n){
    const int k = 1000;//排序数字为[0...k-1]
    int c[k];//计数数组
    memset(c, 0, sizeof(c));
    for (int i = 0; i < n; i++)     c[a[i]]++;
    for (int i = 1; i < k; i++)     c[i] += c[i - 1];//c[i]记录小于等于i的元素出现次数
    int pre = 0;//前一个 
    int p = 0;//更新指针
    for (int i = 0; i < k; i++) {
        if (c[i] != pre) {
            for (int j = pre; j < c[i]; j++)   a[p++] = i;
            pre = c[i];
        }
    }
    return;
}

int main() {
    int a[10] = { 4,3,7,5,2,1,6,5,3,1 };
    //InsertionSort(a, 10);
    //ShellSort(a, 10);
    //BubbleSort(a, 10);
    //QuickSort(a, 0, 9);
    //SelectionSort(a, 10);
    //MergeSort(a, 0, 9);
    CountingSort(a, 10);

    for (int c : a)    printf("%d ", c);

    system("pause");
    return 0;
}