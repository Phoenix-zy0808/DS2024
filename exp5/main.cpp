#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

// 起泡排序
void BubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 选择排序
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

// 归并排序
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 快速排序
int partition(vector<int>& arr, int low, int high); // 添加函数声明

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// 堆排序
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 测试函数
void testBubbleSort(vector<int>& arr, string name) {
    auto start = high_resolution_clock::now();
    BubbleSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Bubble Sort " << name << " took " << duration.count() << " microseconds." << endl;
}

void testSorting(vector<int>& arr, string name) {
    auto start = high_resolution_clock::now();
    BubbleSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Bubble Sort " << name << " took " << duration.count() << " microseconds." << endl;
}

// 测试函数
void testInsertionSort(vector<int>& arr, string name) {
    auto start = high_resolution_clock::now();
    insertionSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion Sort " << name << " took " << duration.count() << " microseconds." << endl;
}

// 测试函数
void testSelectionSort(vector<int>& arr, string name) {
    auto start = high_resolution_clock::now();
    selectionSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Selection Sort " << name << " took " << duration.count() << " microseconds." << endl;
}

// 测试函数
void testMergeSort(vector<int>& arr, string name) {
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Merge Sort " << name << " took " << duration.count() << " microseconds." << endl;
}

// 测试函数
void testQuickSort(vector<int>& arr, string name) {
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Quick Sort " << name << " took " << duration.count() << " microseconds." << endl;
}

// 测试函数
void testHeapSort(vector<int>& arr, string name) {
    auto start = high_resolution_clock::now();
    heapSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Heap Sort " << name << " took " << duration.count() << " microseconds." << endl;
}

int main() {
    int n = 10000; // 测试数据大小
    vector<int> arr1, arr2, arr3;

    // 生成顺序序列
    for (int i = 0; i < n; i++) {
        arr1.push_back(i);
    }

    // 生成逆序序列
    for (int i = n - 1; i >= 0; i--) {
        arr2.push_back(i);
    }

    // 生成随机序列
    vector<int> arr4 = arr1;
    random_shuffle(arr4.begin(), arr4.end());
    arr3 = arr4;

    // 测试顺序序列
    cout << "Testing on sorted array:" << endl;
    testBubbleSort(arr1, "Sorted");
    testInsertionSort(arr1, "Sorted");
    testSelectionSort(arr1, "Sorted");
    testMergeSort(arr1, "Sorted");
    testQuickSort(arr1, "Sorted");
    testHeapSort(arr1, "Sorted");
    cout << "\n";

    // 测试逆序序列
    cout << "Testing on reverse sorted array:" << endl;
    testBubbleSort(arr2, "Reverse Sorted");
    testInsertionSort(arr2, "Reverse Sorted");
    testSelectionSort(arr2, "Reverse Sorted");
    testMergeSort(arr2, "Reverse Sorted");
    testQuickSort(arr2, "Reverse Sorted");
    testHeapSort(arr2, "Reverse Sorted");
    cout << "\n";
    
    // 测试随机序列
    cout << "Testing on random array:" << endl;
    testBubbleSort(arr3, "Random");
    testInsertionSort(arr3, "Random");
    testSelectionSort(arr3, "Random");
    testMergeSort(arr3, "Random");
    testQuickSort(arr3, "Random");
    testHeapSort(arr3, "Random");

    return 0;
}
