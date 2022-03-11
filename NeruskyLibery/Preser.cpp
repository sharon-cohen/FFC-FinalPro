#include "Preser.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>



std::string  upper_string(std::string str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')   //checking for lowercase characters
            str[i] = str[i] - 32;        //converting lowercase to uppercase  
    }

    return str;
}
int hexadecimalToDecimal(std::string hexVal)
{
    int len = hexVal.size();

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last
    // character
    for (int i = len - 1; i >= 0; i--) {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            dec_val += (int(hexVal[i]) - 48) * base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            dec_val += (int(hexVal[i]) - 55) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}
Preser::Preser(HANDLE hComPort) {
    _hComPort = hComPort;

    ByteReadNumber = 0;
    bytesRead = 0;
    len = 0;
    lenCounter = 0;
    Counter = 0;
    checkSum = 0;
    valid = false;
    packet = NULL;
    attention = 0;
    //for (int i = 1; i <= 15; i++)
        //intPackge.push_back(0);
}
bool Preser::vlidation_package() {

    BYTE b;
    if (ReadFile(_hComPort, &b, sizeof(b), &bytesRead, NULL)) {
        if (b == 0xaa) {
            intPackge.push_back(170);
            return true;
        }
        else
            return false;
    }
    else
        return false;
    //DEBUG
    printf("%x ", b & 0x0ff);
}

void Preser::read_checkSum() {
    BYTE b;
    if (ReadFile(_hComPort, &b, sizeof(b), &bytesRead, NULL)) {
        b = b & 0xff;
        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        for (int i(0); i < 1; ++i)
            ss << std::setw(2) << std::setfill('0') << static_cast<int>(b);


        std::string stringHex = ss.str();
        stringHex = upper_string(stringHex);
        checkSum = hexadecimalToDecimal(stringHex);
        intPackge.push_back(checkSum);

    }
    //DEBUG
    //printf("%x", b & 0x0ff);
}
void Preser::read_data_byte() {
    BYTE b;
    if (ReadFile(_hComPort, &b, sizeof(b), &bytesRead, NULL)) {
        b = b & 0xff;
        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        for (int i(0); i < 1; ++i)
            ss << std::setw(2) << std::setfill('0') << static_cast<int>(b);


        std::string stringHex = ss.str();
        stringHex = upper_string(stringHex);
        int data = hexadecimalToDecimal(stringHex);
        intPackge.push_back(data);
        ///std::cout << stringHex

    }
    //DEBUG
    //printf("%x", b & 0x0ff);
}
void Preser::read_Lenght_package() {

    BYTE b;
    if (ReadFile(_hComPort, &b, sizeof(b), &bytesRead, NULL)) {
        b = b & 0xff;
        std::stringstream ss;
        ss << std::hex << std::setfill('0');

        for (int i(0); i < 1; ++i)
            ss << std::setw(2) << std::setfill('0') << static_cast<int>(b);


        std::string stringHex = ss.str();
        stringHex = upper_string(stringHex);
        len = hexadecimalToDecimal(stringHex);
        intPackge.push_back(len);

    }
    else {
        std::cout << "error";
    }
    //DEBUG
    //printf("%x", b & 0x0ff);
}
// DEBUG
void Preser::printPackage() {

    for (auto i = intPackge.begin(); i != intPackge.end(); ++i)
        std::cout << *i << ", ";
    printf("\n");
}
bool Preser::check_attention_byte() {

    if (intPackge[31] == 4 && intPackge[33] == 5) {

        attention = intPackge[32];
        return true;
    }
    else {
        return false;
    }

}

