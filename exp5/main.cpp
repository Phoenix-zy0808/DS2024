#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

std::vector<int> generate_array(const std::string& type, int size) {
    std::vector<int> arr(size);
    if (type == "sorted") {
        std::iota(arr.begin(), arr.end(), 1);
    } else if (type == "reverse") {
        std::iota(arr.begin(), arr.end(), 1);
        std::reverse(arr.begin(), arr.end());
    } else if (type == "random") {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, size);
        for (int& val : arr) {
            val = dis(gen);
        }
    }
    return arr;
}
void bubble_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void insertion_sort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void selection_sort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[i], arr[min_idx]);
    }
}
void merge(std::vector<int>& arr, int l, int m, int r) {
    std::vector<int> L(arr.begin() + l, arr.begin() + m + 1);
    std::vector<int> R(arr.begin() + m + 1, arr.begin() + r + 1);
    size_t i = 0, j = 0, k = static_cast<size_t>(l);
    while (i < L.size() && j < R.size()) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < L.size()) {
        arr[k++] = L[i++];
    }
    while (j < R.size()) {
        arr[k++] = R[j++];
    }
}

void merge_sort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}
void quick_sort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // 这里不需要引用符号
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[i] < arr[l]) {
        largest = l;
    }
    if (r < n && arr[largest] < arr[r]) {
        largest = r;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
void test_sorting_algorithms(const std::string& type, int size) {
    std::vector<int> arr = generate_array(type, size);

    std::cout << "Testing Bubble Sort on " << type << " array:" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    bubble_sort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    arr = generate_array(type, size);

    std::cout << "Testing Insertion Sort on " << type << " array:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    insertion_sort(arr);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    arr = generate_array(type, size);

    std::cout << "Testing Selection Sort on " << type << " array:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    selection_sort(arr);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    arr = generate_array(type, size);

    std::cout << "Testing Merge Sort on " << type << " array:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    merge_sort(arr, 0, arr.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    arr = generate_array(type, size);

    std::cout << "Testing Quick Sort on " << type << " array:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    quick_sort(arr, 0, arr.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    arr = generate_array(type, size);

    std::cout << "Testing Heap Sort on " << type << " array:" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    heap_sort(arr);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

int main() {
    int size = 10000;
    std::cout << "Testing on sorted array:" << std::endl;
    test_sorting_algorithms("sorted", size);
    std::cout << "\nTesting on reverse array:" << std::endl;
    test_sorting_algorithms("reverse", size);
    std::cout << "\nTesting on random array:" << std::endl;
    test_sorting_algorithms("random", size);
    return 0;
}
