#include <iostream>
#include "vector.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Complex {
public:
    double real;
    double imag;
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator>(const Complex& other) const {
        return modulus() > other.modulus();
    }

    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    double real_part() const {
        return real;
    }

    double imag_part() const {
        return imag;
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator<(const Complex& other) const {
        if (modulus() == other.modulus()) {
            return real < other.real;
        }
        return modulus() < other.modulus();
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

bool compare(const Complex& a, const Complex& b) {
	if(a.modulus() == b.modulus()) {
		return a.real < b.real;
	}
	return a.modulus() < b.modulus();
}

void merge(Vector<Complex>& v, Vector<Complex>& left, Vector<Complex>& right) {
	int i = 0, j = 0, k = 0;
	while (i < left.size() && j < right.size()) {
		if (compare(left[i], right[j])) {
			v[k++] = left[i++];
		} else {
			v[k++] = right[j++];
		}
	}
	while (i < left.size()) {
		v[k++] = left[i++];
	}
	while (j < right.size()) {
		v[k++] = right[j++];
	}
}

void mergeSort(Vector<Complex>& v) {
	if (v.size() <= 1) {
		return;
	}
	Vector<Complex> left, right;
	for (int i = 0; i < v.size() / 2; i++) {
		left.insert(i, v[i]);
	}
	for (int i = v.size() / 2; i < v.size(); i++) {
		right.insert(i - v.size() / 2, v[i]);
	}
	mergeSort(left);
	mergeSort(right);
	merge(v, left, right);
}

int main() {
    // 创建一个复数向量
    Vector<Complex> complex_vector;
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        complex_vector.insert(complex_vector.size(), Complex(rand() % 100, rand() % 100));
    }

    // 测试置乱
    permute(complex_vector);
    std::cout << "Shuffled vector:" << std::endl;
    complex_vector.traverse([](Complex& c) { std::cout << c << " "; });
    std::cout << std::endl;

    // 测试查找
    Complex target(25, 25);
    Rank pos = complex_vector.find(target);
    if (pos != -1) {
        std::cout << "Found " << target << " at position " << pos << std::endl;
    } else {
        std::cout << "Not found " << target << std::endl;
    }

    // 测试插入
    complex_vector.insert(3, Complex(1, 3));
    std::cout << "After insert:" << std::endl;
    complex_vector.traverse([](Complex& c) { std::cout << c << " "; });
    std::cout << std::endl;

    // 测试删除
    complex_vector.remove(2);
    std::cout << "After remove:" << std::endl;
    complex_vector.traverse([](Complex& c) { std::cout << c << " "; });
    std::cout << std::endl;

    // 测试唯一化
    complex_vector.deduplicate();
    std::cout << "After deduplicate:" << std::endl;
    complex_vector.traverse([](Complex& c) { std::cout << c << " "; });
    std::cout << std::endl;

    // 测试排序
    clock_t start = clock();
    complex_vector.bubbleSort(0, complex_vector.size() - 1);
    clock_t end = clock();
    double bubble_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Bubble sorted vector:" << std::endl;
    complex_vector.traverse([](Complex& c) { std::cout << c << " "; });
    std::cout << std::endl;
    std::cout << "Bubble sort time: " << bubble_time << " seconds" << std::endl;

    // 测试归并排序
    start = clock();
    mergeSort(complex_vector);
    end = clock();

    double merge_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Merge sorted vector:" << std::endl;
    complex_vector.traverse([](Complex& c) { std::cout << c << " "; });
    std::cout << std::endl;
    std::cout << "Merge sort time: " << merge_time << " seconds" << std::endl;

    // 测试区间查找
    Vector<Complex> result = complex_vector.find(Complex(5, 0));
    std::cout << "Range search result:" << std::endl;
    result.traverse([](Complex& c) { std::cout << c << " "; });
    std::cout << std::endl;

    return 0;
}

template <typename T>
Vector<T> searchRange(Vector<T> const &vector, T const &low, T const &high) {
    Vector<T> result;
    for (Rank i = 0; i < vector.size(); ++i) {
        if (vector[i] >= low && vector[i] < high) {
            result.push_back(vector[i]);
        }
    }
    return result;
}
