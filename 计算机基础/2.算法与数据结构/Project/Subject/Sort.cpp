/**********
*����
*Sofice
*2020/7/15
*************/
#include<bits/stdc++.h>
using namespace std;
//1��������
//1.1ֱ�Ӳ�������
void InsertionSort(int *a, int n, int step=1) {//����n��Ԫ��
    for (int i = step; i < n; i++) {
        int v = a[i], j;
        for (j = i - step; j >= 0 && a[j] > v; j -= step)
            a[j + step] = a[j];
        a[j + step] = v;
    }
    return;
}
//1.2ϣ������
void ShellSort(int* a, int n) {
    int maxg;//���������
    for (maxg = 1; maxg < n; maxg = 3 * maxg + 1);//������㹫ʽ��g=3*g+1
    maxg = (maxg - 1) / 3;
    for (int g = maxg; g >= 1; g = (g - 1) / 3) {//����ݼ�
        InsertionSort(a, n, g);//ֱ�Ӳ�������
    }
    return;
}
//2��������
//2.1ð������
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
//2.2��������
int Partition(int* a, int low, int high) {//˫ָ��
    int pivotv = a[low];
    while (low < high) {
        while (low < high && a[high] >= pivotv) high--;//����������С�ĸ��Ƶ���ָ�봦
        a[low] = a[high];
        while (low < high && a[low] <= pivotv) low++;//���������Ҵ�ĸ��Ƶ���ָ�봦
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
//3ѡ������
//3.1��ѡ������
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
//3.2������
void HeapSort(int* a, int n) {

}
//4�鲢����
int b[1000];
void Merge(int* a, int low, int mid, int high) {//�ϲ�[low...mid]��[mid+1...high]��һ�������
    memcpy(b + low, a + low, sizeof(int) * (high - low + 1));
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (b[i] <= b[j])  a[k++] = b[i++];//ȡ��ߵ�
        else               a[k++] = b[j++];//ȡ�ұߵ�
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
//5��������
void LSDSort(int* a, int n) {

}
//6��������
void CountingSort(int* a, int n){
    const int k = 1000;//��������Ϊ[0...k-1]
    int c[k];//��������
    memset(c, 0, sizeof(c));
    for (int i = 0; i < n; i++)     c[a[i]]++;
    for (int i = 1; i < k; i++)     c[i] += c[i - 1];//c[i]��¼С�ڵ���i��Ԫ�س��ִ���
    int pre = 0;//ǰһ�� 
    int p = 0;//����ָ��
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