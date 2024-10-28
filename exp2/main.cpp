#include <iostream>
#include <cmath>
#include <stdexcept>
#include"Stack.cpp"
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

// 定义运算符的优先级
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}


double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : throw runtime_error("Division by zero");
        case '^': return pow(a, b);
        case 's': return sin(b);
        case 'c': return cos(b);
        case 't': return tan(b);
        case 'l': return log(b);
        default: throw runtime_error("Invalid operator");
    }
}


using namespace std;



double parseAndCalculate(const string &expression, Stack<double>& operands, Stack<char>& operators) {
    for (size_t i = 0; i < expression.length(); i++) { // 使用 size_t 类型的变量
        char c = expression[i];

        if (isspace(c)) continue;

        if (isdigit(c) || c == '.') {
            string num;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                num += expression[i++];
            }
            i--;
            operands.push(stod(num));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.is_empty() && operators.top() != '(') {
                double b = operands.pop();
                double a = operands.pop();
                char op = operators.pop();
                operands.push(applyOp(a, b, op));
            }
            operators.pop(); // Remove '('
        } else {
            while (!operators.is_empty() && precedence(operators.top()) >= precedence(c)) {
                double b = operands.pop();
                double a = operands.pop();
                char op = operators.pop();
                operands.push(applyOp(a, b, op));
            }
            operators.push(c);
        }
    }

    while (!operators.is_empty()) {
        double b = operands.pop();
        double a = operands.pop();
        char op = operators.pop();
        operands.push(applyOp(a, b, op));
    }

    // 返回最终结果
    return operands.pop();
}

double sin(const string &expression) {
    size_t start = expression.find('(');
    size_t end = expression.find(')');
    if (start == string::npos || end == string::npos || start > end) {
        throw runtime_error("Invalid trigonometric expression");
    }
    double angle = stod(expression.substr(start + 1, end - start - 1));
    return sin(angle * M_PI / 180.0); // 将角度转换为弧度
}
double cos(const string &expression) {
    size_t start = expression.find('(');
    size_t end = expression.find(')');
    if (start == string::npos || end == string::npos || start > end) {
        throw runtime_error("Invalid trigonometric expression");
    }
    double angle = stod(expression.substr(start + 1, end - start - 1));
    return cos(angle * M_PI / 180.0);
}


int RectangleArea(const vector<int> &heights)

{

    Stack<int> st;

    int maxArea = 0;

    int n = heights.size();

    for (int i = 0; i < n; i++)

    {

        while (!st.empty() && heights[st.top()] > heights[i])

        {

            int h = heights[st.top()]; st.pop();

            int width = st.empty() ? i : i - st.top() - 1;

            maxArea =max(maxArea, h * width);

        } st.push(i);

    }

    while (!st.empty())

    {

        int h = heights[st.top()];

        st.pop();

        int width = st.empty() ? n : n - st.top() - 1;

        maxArea = max(maxArea, h * width);

    }

    return maxArea;

}

void RandomData(int numTests) {

    srand(time(0)); 

    for (int i = 0; i < numTests; ++i) {

        int length = rand() % 105 + 1;

        vector<int> heights(length);

        cout << "Test " << i + 1 << ": [ ";

        for (int j = 0; j < length; ++j) {

            heights[j] = rand() % 104;

            cout << heights[j] << " ";

        }

        cout << "]\nMax Area: " << RectangleArea(heights) << endl << endl;

    }

}

int main() {
    try {
        Stack<double> operands;
        Stack<char> operators;
        string S1 = {"2 + 5 * 3 - 6 / 2 + 4.5",};
        string S2 = {"( 6 + 4 ) * 7 -17",};
        string S3 = {"(3 + 5) * 4",};
        cout << "Result: " << parseAndCalculate(S1, operands, operators) << endl;
        cout << "Result: " << parseAndCalculate(S2, operands, operators) << endl;
        cout << "Result: " << parseAndCalculate(S3, operands, operators) << endl;
        cout << "Result: " << sin(45) + cos(60)<< endl;
        vector<int> B1 = {2, 1, 5, 6, 2, 3};
        vector<int> B2 = {2, 4};
        cout << "IN: " << "[2, 1, 5, 6, 2, 3]" << endl;
        cout << "OUT: " << RectangleArea(B1) << endl;
        cout << "IN: " << "[2, 4]" << endl;
        cout << "OUT: " << RectangleArea(B2) << endl;
        RandomData(10);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
