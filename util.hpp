#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <sys/resource.h>
#include <filesystem>
#include <math.h>
#include <ctime>
#include <map>

#define MACRO_ReadFileByLine(fileToOpen,sLine,code_block) { \
    std::ifstream file; \
    file.open(fileToOpen); \
    if(file.is_open()) { \
        while(getline(file,sLine)) { \
            code_block; \
        } \
        file.close(); \
    } else { \
        util::qPrint("Error opening file \"",fileToOpen,"\""); \
    } \
}

#define MACRO_WriteToFile(fileToWrite,fileFlags,code_block) { \
    std::ofstream file; \
    file.open(fileToWrite,fileFlags); \
    if(file.is_open()) { \
        code_block; \
        file.close(); \
    } else { \
        util::qPrint("Error openning file \"",fileToWrite,"\""); \
    } \
}

namespace util {

    struct int2d {
        int x, y;

        int2d(int _x, int _y) : x(_x), y(_y) {};
        int2d() : x(0), y(0) {};
    };

    //quick print
    template <typename T>
    void qPrint(T output) {
        std::cout << output << "\n";
    }
    template <typename T, typename... Args>
    void qPrint(T output, Args... args){
        std::cout << output << " ";
        qPrint(args...);
    }

    //if bReturnIndex = false will return 0 if not found
    //if bReturnIndex = true will return -1 if not found
    template <typename T>
    int searchVector(std::vector<T>& inputVector, T toFind, bool bReturnIndex = false) {
        int iSize = inputVector.size();
        for(int i = 0; i < iSize; i++) {
            if(inputVector[i] == toFind) {
                return (i + (!bReturnIndex));
                //need to return at least 1 if found at index 0 when bReturnIndex is false
            }
        }
        return (0 - (bReturnIndex));
    }

    // Will return NULL if not found
    template <typename A, typename B>
    A findKey(std::map<A,B>& mSource, B toFind) {
        for(auto& i : mSource) {
            if(i.second == toFind) {
                return i.first;
            }
        }
        return NULL;
    }

    template <typename T>
    void removeFirst(std::vector<T>& inputVector, T toRemove) {
        for(int i = 0, last = inputVector.size() - 1; i <= last; i++) {
            if(inputVector[i] == toRemove) {
                inputVector.erase(inputVector.begin() + i);
                return;
            }
        }
        qPrint("Value",toRemove,"was not found in vector!");
    }

    template <typename T>
    bool contains(std::unordered_set<T>& inputUSet, T toCheck) {
        return (inputUSet.find(toCheck) != inputUSet.end());
    }

    template <typename T>
    bool contains(std::string& sSource, T toFind) {
        return (sSource.find(toFind) != sSource.npos);
    }

    template <typename T>
    bool contains(std::vector<T>& sSource, T toFind) {
        for(auto& i : sSource) {
            if(i == toFind) return true;
        }
        return false;
    }

    template <typename A, typename B>
    bool containsValue(std::map<A,B>& mSource, B toFind) {
        for(auto& i : mSource) {
            if(i.second == toFind) {
                return true;
            }
        }
        return false;
    }

    int
        strToInt(std::string str),
        lerpInt(int iStart, int iEnd, float fLerp);

    float strToFloat(std::string str);
    std::vector<std::string> splitStringOnChar(std::string& sToSplit,char cSplit);

    bool
        endsWith(std::string& sSource, const std::string sEnd),
        hasPathPermission(std::filesystem::path pPath, bool bPrintErrors = false),
        onlyContains(std::string& sSource, const char cToCheck),
        charFilter(char& input, const char* filter, const bool bAlpha = false, const bool bNumbers = false),
        containsChar(const char* input, const char cToCheck);

    std::string
        vectorToSingleStr(std::vector<std::string>& sFullVec,bool bAddNewLines = true),
        vectorToSingleStr(std::vector<std::string>& sFullVec,std::string sBetweenEach,bool bSkipLast = true),
        shorten(std::string& sToShorten, int iLength, char cEndOn),
        shorten(std::string& sToShorten, int iLength),
        shorten(std::string& sToShorten, char cEndOn),
        argvToString(char* argv),
        getCurrentDateTime();

    void
        printMemUse(rusage& usageRef),
        flip(bool& toFlip),
        toLowercase(std::string& sToModify),
        removeAllOfChar(std::string& sToModify, char cToRemove),
        removeAllOfChar(std::string &sToModify, std::string sMultiChars),
        reverseString(std::string& sInput);
}
