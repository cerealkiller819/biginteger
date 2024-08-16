#include <iostream>
#include <string>
#include <algorithm>

class BigInteger {
private:
    std::string name;
public:
    BigInteger(const std::string& name) : name(name) {
        
    }
    BigInteger operator+(const BigInteger& SecondInt) const {
        int len1 = name.length() ;
        int len2 = (SecondInt.name).length() ;
        std::string num1 = name;
        std::string num2 = SecondInt.name;
        if (len1 > len2) {
             num2.insert(0, len1  - len2, '0');
        }
        else {
            num1.insert(0, len2  - len1, '0');
        }
        std::string result1 = "" ;
        int next = 0;
        for (int i = (len1 -1) ; i >= 0; i--){
            int digit1 = num1[i] - '0';//char类型是int
            int digit2 = num2[i] - '0';
            int sum = digit1 + digit2 + next;
            if ( sum >= 10 ){
                result1 += std::to_string(sum - 10) ;
                next = 1 ;
            }
            else {
                result1 += std::to_string(sum) ;
                next = 0 ;
            }
        }
         if (next) {
            result1 += '1';
        }
        std::reverse(result1.begin(), result1.end());
        return BigInteger(result1);
    }

    BigInteger operator-(const BigInteger& SecondInt) const {
        int len1 = name.length();
        int len2 = SecondInt.name.length();

        std::string num1, num2, result2 = "";


        if (len1 > len2) {
            num1 = name;
            num2 = SecondInt.name;
        } else if (len2 > len1) {
            num1 = SecondInt.name;
            num2 = name;
            result2 = "-";
        } else {
            for (int j = 0; j < len1; j++) {
                if (name[j] > SecondInt.name[j]) {
                    num1 = name;
                    num2 = SecondInt.name;
                    break;
                } else if (name[j] < SecondInt.name[j]) {
                    num1 = SecondInt.name;
                    num2 = name;
                    result2 = "-";
                    break;
                }
            }
        }

        if (len1 > len2) {
            num2.insert(0, len1 - len2, '0');
        } else if (len2 > len1) {
            num1.insert(0, len2 - len1, '0');
        }

        int next = 0;
        for (int i = num1.length() - 1; i >= 0; i--) {
            int digit1 = num1[i] - '0';
            int digit2 = num2[i] - '0';
            int sum = digit1 - digit2 + next;

            if (sum < 0) {
                sum += 10;
                next = -1;
            } else {
                next = 0;
            }

            result2 += std::to_string(sum);
        }

        while (result2.length() > 1 && result2.back() == '0') {
            result2.pop_back();
        }

        std::reverse(result2.begin()+1, result2.end());


        return BigInteger(result2);
    }



    BigInteger operator*(const BigInteger& SecondInt) const {
        int len1 = name.length();
        int len2 = SecondInt.name.length();
        int result_length = len1 + len2;
        std::string result(result_length, '0');

        for (int i = len1 - 1; i >= 0; i--) {
            int digit1 = name[i] - '0';
            int carry = 0;

            for (int j = len2 - 1; j >= 0; j--) {
                int digit2 = SecondInt.name[j] - '0';
                int product = digit1 * digit2 + carry + (result[i + j + 1] - '0');
                carry = product / 10;
                result[i + j + 1] = (product % 10) + '0';
            }

            result[i + len2] += carry;
        }

        auto start = result.find_first_not_of('0');
        if (start == std::string::npos) {
            return BigInteger("0");
        }

        return BigInteger(result.substr(start));
    }

        
    void print() const {
        std::cout << name<< std::endl ;
    }
};



int main() {
    BigInteger num1("100000000000000000000000000000");
    BigInteger num2("900000000000000000000000000000");
    BigInteger sum = num1 + num2;
    BigInteger diff = num1 - num2;
    BigInteger product = num1 * num2;
    sum.print(); 
    diff.print();
    product.print();
    return 0;
}