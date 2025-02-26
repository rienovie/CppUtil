#include "util.hpp"
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <string>
#include <thread>
#include <utility>
#include <unistd.h>

// Put variables in this namespace section
namespace util {
    std::map<std::string,std::string> mColors {
        {"red","\033[31m"},
        {"green","\033[32m"},
        {"yellow","\033[33m"},
        {"blue","\033[34m"},
        {"magenta","\033[35m"},
        {"cyan","\033[36m"}
    };

    alternativeVariables alt(false);
    class_gate gate;
    class_timer timer;
}

util::alternativeVariables::alternativeVariables(const bool value) {
    altValue = value;
}

void util::alternativeVariables::setAlt(const bool value) {
    altValue = value;
    cPrint("magenta","Util::AlternativeValue is set to " + std::to_string(value));
}

bool util::alternativeVariables::getAlt() {
    return altValue;
}

void util::class_timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void util::class_timer::end() {
    endTime = std::chrono::high_resolution_clock::now();
    finished = true;
}

int util::class_timer::get() {
    if(!finished) {
        util::cPrint("red","Timer get called but has not finished!");
        return 0;
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

std::string util::class_timer::getStr() {
    if(!finished) {
        util::cPrint("red","Timer get called but has not finished!");
        return "Timer not Started.";
    }
    return std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()) + "ms";
}

bool util::class_gate::exists(const std::string ID) {
    return mGates.find(ID) != mGates.end();
}

bool util::class_gate::state(const std::string ID) {
    if(exists(ID)) {
        return mGates.at(ID);
    } else {
        cPrint("red","Gate with ID '",ID,"' does not exist / Function will always return",false);
        return false;
    }
}

void util::class_gate::create(const std::string ID, const bool bStartOpen) {
    mGates[ID] = bStartOpen;
}

void util::class_gate::open(const std::string ID) {
    if(exists(ID)) {
        mGates.at(ID) = true;
    } else {
        cPrint("red","Gate with ID '",ID,"' does not exist / Unable to open gate");
    }
}

void util::class_gate::close(const std::string ID) {
    if(exists(ID)) {
        mGates.at(ID) = false;
    } else {
        cPrint("red","Gate with ID '",ID,"' does not exist / Unable to close gate");
    }
}

void util::class_gate::toggle(const std::string ID) {
    if(exists(ID)) {
        flip(mGates.at(ID));
    } else {
        cPrint("red","Gate with ID '",ID,"' does not exist / Unable to toggle gate");
    }
}

float util::strToFloat ( const std::string str ) {
    try {
        return std::stof(str);
    } catch (...) {
        qPrint("ERROR using stof! Attempted string:",str);
    }
    return -1.0f;
}

int util::strToInt(const std::string str){
    try{
        return std::stoi(str);
    } catch (...){
        qPrint("ERROR using stoi! Attempted string:",str);
    }
    return -1;
}

std::vector<std::string> util::splitStringOnChar ( const std::string& sToSplit, const char cSplit ) {
    std::vector<std::string> vOutput;
    std::string sBuild = "";
    int iStrLength = sToSplit.length();

    for(int i = 0; i < iStrLength; i++) {
        if(sToSplit[i] == cSplit) {
            if(sBuild.length() == 0) { continue; } //if is blank don't add
            vOutput.push_back(sBuild);
            sBuild.clear();
        } else { sBuild.push_back(sToSplit[i]); }
    }
    if(sBuild.length() != 0) { vOutput.push_back(sBuild); }

    return vOutput;
}

bool util::hasPathPermission ( const std::filesystem::path pPath, const bool bPrintErrors ) {
    try {
        if(std::filesystem::is_directory(pPath)) {
            // NOLINTNEXTLINE(bugprone-unused-raii)
            std::filesystem::directory_iterator{pPath}; //should fail if not accessable
            return true;
        } else if(std::filesystem::is_regular_file(pPath)) {
            return true;
        } else {
            if(bPrintErrors) {
                util::qPrint("Error in hasPathPermission! Path:",pPath.c_str(),"is not a directory or regular file!");
            }
            return false;
        }

    } catch (const std::filesystem::filesystem_error& error){
        if(bPrintErrors) {
            util::qPrint("Filesystem error:",error.what());
        }
        return false;
    } catch (...) {
        if(bPrintErrors) {
            util::qPrint("Unknown Error in hasPathPermission!");
        }
        return false;
    }

}

std::string util::vectorToSingleStr(const std::vector<std::string>& sFullVec, const bool bAddNewLines ) {
    std::string sOutput = "";

    for(auto& s : sFullVec) {
        sOutput.append(s);
        if(bAddNewLines) { sOutput.push_back('\n'); }
    }

    return sOutput;
}

std::string util::vectorToSingleStr(const std::vector<std::string>& sFullVec, const std::string sBetweenEach, const bool bSkipLast ) {
    std::string sOutput = "";

    for(int i = 0, iLast = sFullVec.size() - 1; i <= iLast; i++) {
        sOutput.append(sFullVec[i]);
        if(i == iLast && bSkipLast) { continue; }
        else { sOutput.append(sBetweenEach); }
    }

    return sOutput;
}

int util::lerpInt ( const int iStart, const int iEnd, const float fLerp ) {
    return iStart + std::round((float(iEnd) - float(iStart)) * fLerp);
}

bool util::flip ( bool& toFlip ) {
    return (toFlip = !toFlip);
}

void util::toLowercase ( std::string& sToModify ) {
    for(char& c : sToModify) {
        c = std::tolower(c);
    }
}

std::string util::shorten (const std::string& sToShorten, const char cEndOn ) {
    std::string sOutput = "";

    for(const char& c : sToShorten) {
        if(c == cEndOn) { return sOutput; }
        else sOutput.push_back(c);
    }

    return sOutput;
}

std::string util::shorten (const std::string& sToShorten, const int iLength ) {
    std::string sOutput = "";
    int iShortest = std::min(iLength,int(sToShorten.length()));

    for(int i = 0; i < iShortest; i++) {
        sOutput.push_back(sToShorten[i]);
    }

    return sOutput;
}

std::string util::shorten (const std::string& sToShorten, const int iLength, const char cEndOn ) {
    std::string sOutput = "";
    int iShortest = std::min(iLength,int(sToShorten.length()));

    for(int i = 0; i < iShortest; i++) {
        if(sToShorten[i] == cEndOn) { return sOutput; }
        sOutput.push_back(sToShorten[i]);
    }

    return sOutput;
}

std::string util::argvToString(const char *argv) {
    std::string output;
    int currentIndex = 0;

    while(argv[currentIndex] != '\0') {
        output.push_back(argv[currentIndex]);
        currentIndex++;
    }

    return output;
}

void util::removeAllOfChar(std::string &sToModify, const char cToRemove) {
    std::string sOutput;
    for(auto& c : sToModify) {
        if(c != cToRemove) sOutput.push_back(c);
    }
    sToModify = sOutput;
}

void util::removeAllOfChar(std::string& sToModify, const std::string sMultiChars) {
    std::string sOutput;
    for(auto& c : sToModify) {
        if(sMultiChars.find(c) == sMultiChars.npos) sOutput.push_back(c);
    }
    sToModify = sOutput;
}

bool util::onlyContains(const std::string &sSource, const char cToCheck) {
    for(auto& c : sSource) {
        if(c != cToCheck) return false;
    }
    return true;
}

bool util::endsWith(const std::string &sSource, const std::string sEnd) {
    return (sSource.substr(sSource.length() - sEnd.length()) == sEnd);
}

std::string util::getCurrentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M-%S", &tstruct);

    return buf;
}

bool util::containsChar(const char *input, const char cToCheck) {
    for(int i = 0; input[i] != '\0'; i++) {
        if(input[i] == cToCheck) return true;
    }
    return false;
}

bool util::charFilter(const char& input, const char* filter, const bool bAlpha, const bool bNumbers) {
    return
    (( bNumbers && (input > 47 && input < 58))
    || ( bAlpha && ((input > 64 && input < 91) || (input > 96 && input < 123)))
    || ( containsChar(filter, input)));
}

void util::reverseString(std::string &sInput) {
    for(int i = sInput.length() - 1; i > round(sInput.length() / 2); i--) {
        std::swap(sInput[i],sInput[sInput.length() - 1 - i]);
    }
}

std::string util::fileToString(const std::string file) {
    std::string sOutput = "";
    std::ifstream fileStream;

    fileStream.open(file);
    if(fileStream.is_open()) {
        std::string sCurLine;
        while(getline(fileStream, sCurLine)) {
            sOutput.append(sCurLine);
            sOutput.push_back('\n');
        }
        fileStream.close();
    } else {
        util::cPrint("red","File ", file, "was not opened!");
        return "";
    }

    return sOutput;
}

std::vector<std::string> util::fileToVector(const std::string file) {
    std::vector<std::string> vOutput;
    std::ifstream fileStream;

    fileStream.open(file);
    if(fileStream.is_open()) {
        std::string sCurLine;
        while(getline(fileStream, sCurLine)) {
            vOutput.push_back(sCurLine);
        }
        fileStream.close();
    } else {
        util::cPrint("red","File ", file, "was not opened!");
    }

    return vOutput;
}

void util::qPrint(const bool output) {
    std::cout << (output ? "True" : "False") << "\n";
}

void util::cPrint(const std::string sColor, const bool output) {
    if(mColors.find(sColor) == mColors.end()) {
        std::cout << mColors.at("red") << "Color '" << sColor << "' is not defined. Using qPrint..." << "\033[0m\n";
        qPrint(output);
        return;
    }
    std::cout << mColors.at(sColor) << (output ? "True" : "False") << "\033[0m\n";
}

bool util::containsAny(const std::string &sSource, const char *chars) {
    for (auto& c : sSource) {
        if(charFilter(c, chars)) {
            return true;
        }
    }

    return false;
}

bool util::onlyContains(const std::string& sSource, const char* filter, const bool bAlpha, const bool bNumbers) {
    for(auto& c : sSource) {
        if(!charFilter(c,filter,bAlpha,bNumbers)) {
            return false;
        }
    }
    return true;
}

void util::sleep(const float fSeconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(int(fSeconds * 1000)));
}

std::string util::switchOnAlt(const char* a, const char* b) {
    return std::string(alt.getAlt() ? a : b);
}

