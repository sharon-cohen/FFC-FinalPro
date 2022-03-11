#pragma once
#include <windows.h>
#include <string>
#include <vector>
class Preser {        // The class
private:
    bool valid;
    BYTE* packet;
    std::vector <int> intPackge;
    int len;
    int lenCounter;
    int Counter;
    int checkSum;
    long unsigned int  bytesRead;
    HANDLE _hComPort;
    int attention;
    int ByteReadNumber;


public:
    Preser() {};
    Preser(HANDLE hComPort);
    ~Preser() { free(packet); }
    bool vlidation_package();
    void read_Lenght_package();
    void read_data_byte();
    void read_checkSum();
    int get_len() { return len; }
    // DEBUG methods
    void printPackage();
    bool check_attention_byte();
    int get_attention() { return attention; }
};







