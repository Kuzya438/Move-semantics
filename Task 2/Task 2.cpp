#include <iostream>
#include <cstdlib>
#include <string>

class big_integer {
private:
    std::string num__;

public:
    big_integer(const std::string& num) : num__(num) {}
    big_integer(big_integer&& other) noexcept : num__(std::move(other.num__)) {}

    big_integer& operator=(big_integer&& other) noexcept {
        num__ = std::move(other.num__);
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        std::string res;
        int i{ static_cast<int>(num__.size()) - 1 };
        int j{ static_cast<int>(other.num__.size()) - 1 };
        int c{};

        while (i >= 0 || j >= 0 || c) {
            int sum{ c };
            if (i >= 0) { sum += num__[i--] - '0'; }
            if (j >= 0) { sum += other.num__[j--] - '0'; }
            res.push_back(static_cast<char>('0' + sum % 10));
            c = sum / 10;
        }
        std::reverse(res.begin(), res.end());
        return big_integer(std::move(res));
    }

    big_integer operator*(int num) const {
        if (num == 0 || num__ == "0") { return big_integer("0"); }

        std::string res;
        int c{};

        for (int i{ static_cast<int>(num__.size()) - 1 }; i >= 0; --i) {
            int prod{ (num__[i] - '0') * num + c };
            res.push_back(static_cast<char>('0' + prod % 10));
            c = prod / 10;
        }
        while (c) {
            res.push_back(static_cast<char>('0' + c % 10));
            c /= 10;
        }

        std::reverse(res.begin(), res.end());
        return big_integer(std::move(res));
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& bi) { return os << bi.num__; }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result; // 193099

    return EXIT_SUCCESS;
}