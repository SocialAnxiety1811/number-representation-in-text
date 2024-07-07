#include <iostream>
#include <array>
#include <string>
#include <iterator>
#include <cmath>
#include <cassert>

const std::array<std::string, 10> trifle { "", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
const std::array<std::string, 10> teens {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
const std::array<std::string, 10> tens { "", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто" };
const std::array<std::string, 10> hundreds { "", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот" };
const std::array<std::string, 10> thousTrifle {"", "одна", "две"};
//
const std::array<std::string, 3> millions {"миллион","миллиона","миллионов"};
const std::array<std::string, 3> thousands {"тысяча","тысячи","тысяч"};
const std::array<std::string, 3> rubles {"рубль","рубля","рублей"};
//
const std::vector<std::array<std::string, 10>> ranks {trifle, tens};
const std::vector<std::array<std::string, 10>> otherRanks {thousTrifle, teens};
const std::vector<std::vector<std::array<std::string, 10>>> allRanks {ranks, otherRanks};
//


std::array<int, 3> numberIntoAVectorOfTriplets(int number) {
    std::array<int, 3> numberInTriplets;
    for (int i = 2; i >= 0; --i) {
        numberInTriplets[i] = number % 1000;
        number /= 1000;
    }
    return numberInTriplets;
}


std::array<std::string, 3> tripletsVectorToStringVector (const std::array<int, 3>& numberInTriplets) {
    std::array<std::string, 3> stringArray;
    for (size_t tripletIndex{0}; tripletIndex<3; ++tripletIndex)
    {
        int triplet{numberInTriplets[tripletIndex]};
        if (triplet==0) continue;
    
        for (int i{2}; i>=0; --i) 
        {
            int num { (triplet / static_cast<int>(pow(10, i))) % 10 };
            switch (i) 
            {
                case 2: stringArray[tripletIndex] += (num>0)? hundreds[num] + " " : ""; break;
                case 1: stringArray[tripletIndex] += (triplet>9)? allRanks[(num==1)?1:0][1][(num==1)?triplet%10:num] + " " : ""; break;
                case 0: (triplet%100>19 || triplet%100<10)? stringArray[tripletIndex] += allRanks[(tripletIndex==1&&num<=2)?1:0][0][num] + " " : "";
            }
        }
    }
    return stringArray;
}


void appendEndings(std::array<std::string, 3>& stringArray, std::array<int, 3> numberInTriplets)
{
    std::vector<std::array<std::string, 3>> pars {millions, thousands, rubles};
    for (int i{2}; i>=0; --i) {
        
        int digit{ numberInTriplets[i] % 10 };
        int triplet { numberInTriplets[i] };
        
        if (triplet > 0 && (triplet%100<10 || triplet%100>19) ) 
        {
            switch (digit) 
            {
                case 1: stringArray[i] += pars[i][0]; break;
                case 2 ... 4: stringArray[i] += pars[i][1]; break;
                case 0:
                case 5 ... 9: stringArray[i] += pars[i][2]; break;
            }
        } 
        else if (numberInTriplets[i] > 0) stringArray[i] += pars[i][2];
    }
    if (numberInTriplets[3] == 0) {
        stringArray[3] = "рублей";
    }
}

std::string toConvert(int number) 
{
    assert((number >= 0 && number <= 1000000000) && "invalid number entered");
    
    if (number==0) {
        std::cout << "ноль рублей\n";
        return 0;
    } else if (number==1000000000) {
        std::cout << "миллиард рублей\n";
        return 0;
    }
    
    std::array<int, 3> intA {numberIntoAVectorOfTriplets(number)};
    std::array<std::string, 3> strA {tripletsVectorToStringVector(intA)};
    appendEndings(strA,intA);
    
    std::string stringValue;
    
    for (std::string& i: strA) 
    {
        stringValue += i + ' ';
    }
    
    return stringValue;
}


int main() {
    setlocale(LC_ALL, "rus");
    std::cout << "Введите число от 0 до миллиарда: ";
    int number{};
    std::cin >> number;
    
    std::cout << "Представление числа в прописи:\n" << toConvert(number) << '\n';
    
    return 0;
}
