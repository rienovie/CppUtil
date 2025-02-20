#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <sys/resource.h>
#include <filesystem>
#include <math.h>
#include <ctime>
#include <map>
#include <fstream> // this is for the macros

// Avoid these macros. They work but don't work with a debugger
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

// Avoid these macros. They work but don't work with a debugger
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

    extern std::map<std::string,std::string> mColors;

    // Use instance util::alt instead of this class directly
    class alternativeVariables {
        public:
            bool getAlt();
            void setAlt(bool value);

            //contructor
            alternativeVariables(bool value);

        private:
            bool altValue;
    };
    extern alternativeVariables alt;
    template<typename T>
    T switchOnAlt(T a, T b) {
        return (alt.getAlt()) ? a : b;
    }

    // Use instance util::gate instead of this class directly
    class class_gate {
        public:
            void
                open(std::string ID),
                close(std::string ID),
                toggle(std::string ID),

                // Will overwrite if ID already exists
                create(std::string ID, bool bStartOpen = true);
            bool
                exists(std::string ID),
                state(std::string ID);

        private:
            std::map<std::string,bool> mGates;
    };
    extern class_gate gate;

    // Use instance util::timer instead of this class directly
    class class_timer {
        public:
            void
                start(),
                end();

            // Returns miliseconds with "ms" appended
            std::string getStr();

            // Returns miliseconds
            int get();
        private:
            bool finished = false;
            std::chrono::high_resolution_clock::time_point
                startTime,
                endTime;
    };
    extern class_timer timer;

    struct int2d {
        int x, y;

        int2d(int _x, int _y) : x(_x), y(_y) {};
        int2d() : x(0), y(0) {};
        int2d(std::pair<int,int> _input) : x(_input.first), y(_input.second) {};
    };

    void qPrint(bool output);
    void cPrint(const std::string sColor, bool output);

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
    template <typename... Args>
    void qPrint(bool output,Args... args) {
        std::cout << (output ? "True" : "False") << " ";
        qPrint(args...);
    }

    //Color print
    template <typename T>
    void cPrint(const std::string sColor,T output) {
        if(mColors.find(sColor) == mColors.end()) {
            std::cout << mColors.at("red") << "Color '" << sColor << "' is not defined. Using qPrint..." << "\033[0m\n";
            qPrint(output);
            return;
        }
        std::cout << mColors.at(sColor) << output << "\033[0m\n";
    }
    template <typename T, typename... Args>
    void cPrint(const std::string sColor,T output, Args... args) {
        if(mColors.find(sColor) == mColors.end()) {
            std::cout << mColors.at("red") << "Color '" << sColor << "' is not defined. Using qPrint..." << "\033[0m\n";
            qPrint(output,args...);
            return;
        }
        std::cout << mColors.at(sColor) << output << " \033[0m";
        cPrint(sColor,args...);
    }
    template <typename... Args>
    void cPrint(const std::string sColor, bool output, Args... args) {
        if(mColors.find(sColor) == mColors.end()) {
            std::cout << mColors.at("red") << "Color '" << sColor << "' is not defined. Using qPrint..." << "\033[0m\n";
            qPrint(output,args...);
            return;
        }
        std::cout << mColors.at(sColor) << (output ? "True" : "False") << " \033[0m";
        cPrint(sColor,args...);
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

    template <typename T>
    void appendVectors(std::vector<T>& appendTarget,std::vector<T>& toBeAppended) {
        appendTarget.insert(appendTarget.end(),toBeAppended.begin(),toBeAppended.end());
    }

    // Will increment a maped value that exists
    // or will add key and initialize to 0 + incrementAmount
    template <typename T>
    int& mapIncrement(std::map<T,int>& sourceMap, T incrementKey, int incrementAmount = 1) {
        if(sourceMap.find(incrementKey) == sourceMap.end()) {
            sourceMap[incrementKey] = 0 + incrementAmount;
            return sourceMap.at(incrementKey);
        } else {
            sourceMap[incrementKey] += incrementAmount;
            return sourceMap.at(incrementKey);
        }
    }

    // Will increment a maped value that exists
    // or will add key and initialize to 0 + incrementAmount
    template <typename T>
    int& unordered_mapIncrement(std::unordered_map<T,int>& sourceMap, T incrementKey, int incrementAmount = 1) {
        if(sourceMap.find(incrementKey) == sourceMap.end()) {
            sourceMap[incrementKey] = 0 + incrementAmount;
            return sourceMap.at(incrementKey);
        } else {
            sourceMap[incrementKey] += incrementAmount;
            return sourceMap.at(incrementKey);
        }
    }

    int
        strToInt(std::string str),
        lerpInt(int iStart, int iEnd, float fLerp);

    float strToFloat(std::string str);
    std::vector<std::string> splitStringOnChar(std::string& sToSplit,char cSplit);

    bool
        endsWith(std::string& sSource, const std::string sEnd),
        hasPathPermission(std::filesystem::path pPath, bool bPrintErrors = false),
        onlyContains(std::string& sSource, const char* filter,const bool bAlpha = false, const bool bNumbers = false),
        onlyContains(std::string& sSource, const char cToCheck),
        charFilter(char& input, const char* filter, const bool bAlpha = false, const bool bNumbers = false),
        containsChar(const char* input, const char cToCheck),
        flip(bool& toFlip),
        containsAny(std::string& sSource, const char* chars);

    std::vector<std::string> fileToVector(std::string file);

    std::string
        vectorToSingleStr(std::vector<std::string>& sFullVec,bool bAddNewLines = true),
        vectorToSingleStr(std::vector<std::string>& sFullVec,std::string sBetweenEach,bool bSkipLast = true),
        shorten(std::string& sToShorten, int iLength, char cEndOn),
        shorten(std::string& sToShorten, int iLength),
        shorten(std::string& sToShorten, char cEndOn),
        argvToString(char* argv),
        getCurrentDateTime(),
        fileToString(std::string file);

    void
        printMemUse(rusage& usageRef),
        sleep(float fSeconds),
        toLowercase(std::string& sToModify),
        removeAllOfChar(std::string& sToModify, char cToRemove),
        removeAllOfChar(std::string &sToModify, std::string sMultiChars),
        reverseString(std::string& sInput);
}
