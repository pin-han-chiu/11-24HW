#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
private:
    int* coefficients;
    int degree;        
public:
    Polynomial() : degree(0), coefficients(NULL) {}
    explicit Polynomial(int deg) : degree(deg) {
        coefficients = new int[degree + 1]{0};
    }
    ~Polynomial() {
        delete[] coefficients;
    }
    void setCoefficient(int power, int coeff) {
        if (power > degree) {
            int* newCoefficients = new int[power + 1]{0};
            for (int i = 0; i <= degree; ++i) {
                newCoefficients[i] = coefficients[i];
            }
            delete[] coefficients;
            coefficients = newCoefficients;
            degree = power;
        }
        coefficients[power] = coeff;
    }
    int getCoefficient(int power) const {
        if (power > degree) return 0;
        return coefficients[power];
    }
    int getDegree() const {
        return degree;
    }
    friend istream& operator>>(istream& in, Polynomial& poly) {
        cout << "請輸入多項式的最高次方數 :";
        in >> poly.degree;
        delete[] poly.coefficients;
        poly.coefficients = new int[poly.degree + 1]{0};
        cout << "請從最低到最高依次輸入係數（共 " << poly.degree + 1 << " 項):\n";
        for (int i = 0; i <= poly.degree; ++i) {
            cout << "x^" << i << " 的系數:";
            in >> poly.coefficients[i];
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        bool first = true;
        for (int i = poly.degree; i >= 0; --i) {
            if (poly.coefficients[i] != 0) {
                if (!first && poly.coefficients[i] > 0) out << " + ";
                if (poly.coefficients[i] < 0) out << " - ";
                if (abs(poly.coefficients[i]) != 1 || i == 0) out << abs(poly.coefficients[i]);
                if (i > 0) out << "x";
                if (i > 1) out << "^" << i;
                first = false;
            }
        }
        if (first) out << "0";
        return out;
    }
    //加法
    Polynomial operator+(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);
        for (int i = 0; i <= maxDegree; ++i) {
            result.setCoefficient(i, this->getCoefficient(i) + other.getCoefficient(i));
        }
        return result;
    }
    //減法
    Polynomial operator-(const Polynomial& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial result(maxDegree);
        for (int i = 0; i <= maxDegree; ++i) {
            result.setCoefficient(i, this->getCoefficient(i) - other.getCoefficient(i));
        }
        return result;
    }
    //乘法
    Polynomial operator*(const Polynomial& other) const {
        int resultDegree = this->degree + other.degree;
        Polynomial result(resultDegree);
        for (int i = 0; i <= this->degree; ++i) {
            for (int j = 0; j <= other.degree; ++j) {
                result.coefficients[i + j] += this->coefficients[i] * other.coefficients[j];
            }
        }
        return result;
    }
};
int main() {
    Polynomial p1, p2;
    cout << "請輸入第一個多項式 :" << endl;
    cin >> p1;
    cout << "請輸入第二個多項式 :" << endl;
    cin >> p2;
    Polynomial sum = p1 + p2;
    Polynomial diff = p1 - p2;
    Polynomial product = p1 * p2;
    cout << "和 :" << sum << endl;
    cout << "差 :" << diff << endl;
    cout << "積 :" << product << endl;
    return 0;
}
