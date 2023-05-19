#include <iomanip>	// for right, setw
#include <iostream>
#include <map>
#include <string>

using namespace std;

template <typename T>
class BarGraph {
  public:
    void operator+=(const T &datum) {
        data[datum]++;
    }
    const map<T, unsigned> &getMap() const {
        return data;
    }
  private:
    map<T, unsigned> data;
};

// For BarGraph<T>
template <typename T>
ostream &operator <<(ostream &os, const BarGraph<T> &rhs) {
    auto data = rhs.getMap();
    for (const auto &val : data) {
        os << right << setw(10) << val.first << ' '
             << string(val.second, '*') << '\n';
    }
    return os;
}

template <>
class BarGraph<bool> {
    unsigned false_count = 0, true_count = 0;
  public:
    void operator+=(bool datum) {
	datum ? true_count++ : false_count++;
    }
    unsigned getFalse() const {
        return false_count;
    }
    unsigned getTrue() const {
        return true_count;
    }
};

// For BarGraph<bool>
ostream &operator <<(ostream &os, const BarGraph<bool> &rhs) {
    auto false_count = rhs.getFalse();
    auto true_count = rhs.getTrue();
    os << "     false " << string(false_count, '*') << "\n"
            "      true " << string(true_count,  '*') << "\n";
    return os;
}

template<>
class BarGraph<char> {
  public:
    void operator+=(int datum) {
        ++data[datum]; 
    }
    void operator+=(const string &str) {
        for (const char c : str) {
            *this+=c;
        }
    } 
    const int *getData() const {
        return data;
    }
  private:
    int data[128] {0};
};

// For BarGraph<char>
ostream &operator <<(ostream &os, const BarGraph<char> &rhs) {
    auto data = rhs.getData();
    for (int i = 0; i < 128; ++i) {
        if (data[i] != 0) {
            char c = static_cast<char> (i);
            os << right << setw(10) << c << ' '
                 << string(data[i], '*') << '\n';
        }
    }
    return os;
}


int main() {
    BarGraph<int> alpha;
    alpha += 12;
    alpha += 6;
    alpha += 4;
    alpha += 6;
    cout << alpha << '\n';

    BarGraph<double> beta;
    beta += 3.14;
    beta += 2.71828;
    beta += 6.023e23;
    beta += 2.71828;
    cout << beta << '\n';

    BarGraph<bool> gamma;
    gamma += false;
    gamma += true;
    gamma += false;
    gamma += true;
    gamma += true;
    cout << gamma << '\n';

    BarGraph<char> delta;
    /*
    delta += 'G';
    delta += 'e';
    delta += 'o';
    delta += 'f';
    delta += 'f';
    */
    delta += "Colorado";
    cout << delta << '\n';

    return 0;
}
