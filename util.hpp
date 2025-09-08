#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <filesystem>
#include <math.h>
#include <map>
#include <fstream> // this is for the macros

// Avoid this macro. It works but doesn't work with a debugger
// fileToOpen is ifstream
// sLine is string you must create
// code_block is code to be executed
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

namespace util {

    // defined in cpp file
    extern std::map<std::string,std::string> mColors;

    // Switch between two variables by global switch
    // Use instance util::alt instead of this class directly
    class alternativeVariables {
        public:
            bool getAlt();
            void setAlt(const bool value);

            //contructor
            alternativeVariables(const bool value);

        private:
            bool altValue;
    };
    // Switch between two variables by global switch
    // Value defaults to false
    extern alternativeVariables alt;
    // Switch between two variables by global switch
    // Value defaults to false
    template<typename T>
    T switchOnAlt(const T& a, const T& b) {
        return (alt.getAlt()) ? a : b;
    }

    // Logic gate by unique string as ID but will overwrite if ID already exists
    // Use instance util::gate instead of this class directly
    class class_gate {
        public:
            void
                open(const std::string ID),
                close(const std::string ID),
                toggle(const std::string ID),

                // Uses string for unique ID but will overwrite if ID already exists
                create(const std::string ID, const bool bStartOpen = true);
            bool
                exists(const std::string ID),
                state(const std::string ID);

        private:
            std::map<std::string,bool> mGates;
    };
    // Logic gate by unique string as ID but will overwrite if ID already exists
    extern class_gate gate;

    // Use instance util::timer instead of this class directly
    class class_timer {
        public:
            void
                start(),
                end();

            // Returns miliseconds with "ms" appended
            std::string getStr();

            // Returns miliseconds value
            int get();

            ~class_timer();
        private:
            bool finished = true;
            std::chrono::high_resolution_clock::time_point
                startTime,
                endTime;
    };
    extern class_timer timer;

    struct int2d {
        int x, y;

        int2d(const int _x, const int _y) : x(_x), y(_y) {};
        int2d() : x(0), y(0) {};
        int2d(const std::pair<int,int> _input) : x(_input.first), y(_input.second) {};
    };

    void qPrint(const bool output);
    void cPrint(const std::string sColor, const bool output);

    // need to list these first or else fails to compile
    template <typename T, typename U>
    void qPrint(const std::map<T,U>& output) {
        for(auto& i : output) {
            std::cout << i.first << ":" << i.second << "\n";
        }
    }
    template <typename T>
    void qPrint(const std::vector<T>& output) {
        for(int i = 0, size = output.size(); i < size; i++) {
            std::cout << i << ":" << output[i] << "\n";
        }
    }
    template <typename T, typename U>
    void qPrint(const std::unordered_map<T,U>& output) {
        for(auto& i : output) {
            std::cout << i.first << ":" << i.second << "\n";
        }
    }
    template <typename T>
    void qPrint(const std::set<T>& output) {
        for(auto& i : output) {
            std::cout << i << "\n";
        }
    }
    template <typename T>
    void qPrint(const std::unordered_set<T>& output) {
        for(auto& i : output) {
            std::cout << i << "\n";
        }
    }

    //quick print
    template <typename T>
    void qPrint(const T output) {
        std::cout << output << "\n";
    }
    template <typename T, typename... Args>
    void qPrint(const T output, const Args... args){
        std::cout << output << " ";
        qPrint(args...);
    }
    template <typename... Args>
    void qPrint(const bool output, const Args... args) {
        std::cout << (output ? "True" : "False") << " ";
        qPrint(args...);
    }

    // Color print with predefined colors found on util.cpp beginning of file
    template <typename T>
    void cPrint(const std::string sColor, const T output) {
        if(mColors.find(sColor) == mColors.end()) {
            std::cout << mColors.at("red") << "Color '" << sColor << "' is not defined. Using qPrint..." << "\033[0m\n";
            qPrint(output);
            return;
        }
        std::cout << mColors.at(sColor) << output << "\033[0m\n";
    }
    // Color print with predefined colors found on util.cpp beginning of file
    template <typename T, typename... Args>
    void cPrint(const std::string sColor, const T output, const Args... args) {
        if(mColors.find(sColor) == mColors.end()) {
            std::cout << mColors.at("red") << "Color '" << sColor << "' is not defined. Using qPrint..." << "\033[0m\n";
            qPrint(output,args...);
            return;
        }
        std::cout << mColors.at(sColor) << output << " \033[0m";
        cPrint(sColor,args...);
    }
    // Color print with predefined colors found on util.cpp beginning of file
    template <typename... Args>
    void cPrint(const std::string sColor, const bool output, const Args... args) {
        if(mColors.find(sColor) == mColors.end()) {
            std::cout << mColors.at("red") << "Color '" << sColor << "' is not defined. Using qPrint..." << "\033[0m\n";
            qPrint(output,args...);
            return;
        }
        std::cout << mColors.at(sColor) << (output ? "True" : "False") << " \033[0m";
        cPrint(sColor,args...);
    }

    // Universal clear template
    // Works with vectors, strings, maps, etc
    template <typename T>
    void clear(T& toClear) {
        toClear.clear();
    }

    // Search vector for first value that matches
    // bReturnIndex defaults to false
    // if bReturnIndex = false will return 0 if not found
    // if bReturnIndex = true will return -1 if not found
    template <typename T>
    int searchVector(const std::vector<T>& inputVector, const T toFind, const bool bReturnIndex = false) {
        int iSize = inputVector.size();
        for(int i = 0; i < iSize; i++) {
            if(inputVector[i] == toFind) {
                return (i + (!bReturnIndex));
                //need to return at least 1 if found at index 0 when bReturnIndex is false
            }
        }
        return (0 - (bReturnIndex));
    }

    // Searches thru map by value and returns key
    // Will return nullptr if not found
    template <typename A, typename B>
    A findKey(const std::map<A,B>& mSource, const B toFind) {
        for(auto& i : mSource) {
            if(i.second == toFind) {
                return i.first;
            }
        }
        return nullptr;
    }

    template <typename T>
    void removeFirst(std::vector<T>& inputVector, const T toRemove) {
        for(int i = 0, last = inputVector.size() - 1; i <= last; i++) {
            if(inputVector[i] == toRemove) {
                inputVector.erase(inputVector.begin() + i);
                return;
            }
        }
        qPrint("Value",toRemove,"was not found in vector!");
    }

    template <typename T>
    bool contains(const std::unordered_set<T>& inputUSet, const T toCheck) {
        return (inputUSet.find(toCheck) != inputUSet.end());
    }

    template <typename T>
    bool contains(const std::string& sSource, const T toFind) {
        return (sSource.find(toFind) != sSource.npos);
    }

    template <typename T>
    bool contains(const std::vector<T>& sSource, const T toFind) {
        for(auto& i : sSource) {
            if(i == toFind) return true;
        }
        return false;
    }

    template <typename A, typename B>
    bool containsValue(const std::map<A,B>& mSource, const B toFind) {
        for(auto& i : mSource) {
            if(i.second == toFind) {
                return true;
            }
        }
        return false;
    }

    template <typename T>
    void appendVectors(std::vector<T>& appendTarget, const std::vector<T>& toBeAppended) {
        appendTarget.insert(appendTarget.end(),toBeAppended.begin(),toBeAppended.end());
    }

    // Will increment a maped value that exists
    // or will add key and initialize to 0 + incrementAmount
    template <typename T>
    int& mapIncrement(std::map<T,int>& sourceMap, const T incrementKey, const int incrementAmount = 1) {
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
    int& unordered_mapIncrement(std::unordered_map<T,int>& sourceMap, const T incrementKey, const int incrementAmount = 1) {
        if(sourceMap.find(incrementKey) == sourceMap.end()) {
            sourceMap[incrementKey] = 0 + incrementAmount;
            return sourceMap.at(incrementKey);
        } else {
            sourceMap[incrementKey] += incrementAmount;
            return sourceMap.at(incrementKey);
        }
    }

    // Will assume to the end unless specified
    // iEnd is inclusive
    template <typename T>
    std::vector<T> subVector(const std::vector<T>& inputVector, const int iStart, const int iEnd = -1) {
        if (iStart < 0 || iEnd > inputVector.size() - 1) {
            util::cPrint("yellow","inputVector for subVector function is not within bounds of specified values.");
            return std::vector<T>();
        }
        return std::vector<T>(inputVector.begin() + iStart, inputVector.begin() + (iEnd < 0 ? inputVector.size() : iEnd + 1));
    }

    int
        strToInt(const std::string str),
        lerpInt(const int iStart, const int iEnd, const float fLerp);

    float strToFloat(const std::string str);
    std::vector<std::string> splitStringOnChar(const std::string& sToSplit, const char cSplit);

    bool
        endsWith(const std::string& sSource, const std::string sEnd),
        hasPathPermission(const std::filesystem::path pPath, const bool bPrintErrors = false),
        onlyContains(const std::string& sSource, const char* filter, const bool bAlpha = false, const bool bNumbers = false),
        onlyContains(const std::string& sSource, const char cToCheck),

        // Will return true if char is caught by filter
        charFilter(const char& input, const char* filter, const bool bAlpha = false, const bool bNumbers = false),
        containsChar(const char* input, const char cToCheck),
        flip(bool& toFlip),

        // Each char is checked individually
        containsAny(const std::string& sSource, const char* chars);

    std::vector<std::string> fileToVector(const std::string file);

    std::string
        switchOnAlt(const char* a, const char* b),
        vectorToSingleStr(const std::vector<std::string>& sFullVec, const bool bAddNewLines = true),
        vectorToSingleStr(const std::vector<std::string>& sFullVec, const std::string sBetweenEach, const bool bSkipLast = true),
        shorten(const std::string& sToShorten, const int iLength, const char cEndOn),
        shorten(const std::string& sToShorten, const int iLength),
        shorten(const std::string& sToShorten, const char cEndOn),
        argvToString(const char* argv),
        getCurrentDateTime(),
        fileToString(const std::string file);

    void
        qPrint(),
        sleep(const float fSeconds),
        toLowercase(std::string& sToModify),
        removeAllOfChar(std::string& sToModify, const char cToRemove),
        removeAllOfChar(std::string &sToModify, const std::string sMultiChars),
        reverseString(std::string& sInput);
}
