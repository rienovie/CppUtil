#include "util.hpp"

namespace util {

    float strToFloat ( std::string str ) {
        try {
            return std::stof(str);
        } catch (...) {
            qPrint("ERROR using stof! Attempted string:",str);
        }
        return -1.0f;
    }


    int strToInt(std::string str){
        try{
            return std::stoi(str);
        } catch (...){
            qPrint("ERROR using stoi! Attempted string:",str);
        }
        return -1;
    }

    void printMemUse(rusage& usageRef) {
        if(getrusage(RUSAGE_SELF, &usageRef) == 0){
            qPrint("Memory Usage:",usageRef.ru_maxrss,"kb");
        }
    }

    std::vector<std::string> splitStringOnChar ( std::string& sToSplit, char cSplit ) {
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

    bool hasPathPermission ( std::filesystem::path pPath, bool bPrintErrors ) {
        try {
            if(std::filesystem::is_directory(pPath)) {
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

    std::string vectorToSingleStr ( std::vector<std::string>& sFullVec, bool bAddNewLines ) {
        std::string sOutput = "";

        for(auto& s : sFullVec) {
            sOutput.append(s);
            if(bAddNewLines) { sOutput.push_back('\n'); }
        }

        return sOutput;
    }

    std::string vectorToSingleStr ( std::vector<std::string>& sFullVec, std::string sBetweenEach, bool bSkipLast ) {
        std::string sOutput = "";

        for(int i = 0, iLast = sFullVec.size() - 1; i <= iLast; i++) {
            sOutput.append(sFullVec[i]);
            if(i == iLast && bSkipLast) { continue; }
            else { sOutput.append(sBetweenEach); }
        }

        return sOutput;
    }

    int lerpInt ( int iStart, int iEnd, float fLerp ) {
        return iStart + std::round((float(iEnd) - float(iStart)) * fLerp);
    }

    void flip ( bool& toFlip ) {
        toFlip = !toFlip;
    }

    void toLowercase ( std::string& sToModify ) {
        for(char& c : sToModify) {
            c = std::tolower(c);
        }
    }

    std::string shorten ( std::string& sToShorten, char cEndOn ) {
        std::string sOutput = "";

        for(char& c : sToShorten) {
            if(c == cEndOn) { return sOutput; }
            else sOutput.push_back(c);
        }

        return sOutput;
    }

    std::string shorten ( std::string& sToShorten, int iLength ) {
        std::string sOutput = "";
        int iShortest = std::min(iLength,int(sToShorten.length()));

        for(int i = 0; i < iShortest; i++) {
            sOutput.push_back(sToShorten[i]);
        }

        return sOutput;
    }

    std::string shorten ( std::string& sToShorten, int iLength, char cEndOn ) {
        std::string sOutput = "";
        int iShortest = std::min(iLength,int(sToShorten.length()));

        for(int i = 0; i < iShortest; i++) {
            if(sToShorten[i] == cEndOn) { return sOutput; }
            sOutput.push_back(sToShorten[i]);
        }

        return sOutput;
    }

    std::string argvToString(char *argv) {
        std::string output;
        int currentIndex = 0;

        while(argv[currentIndex] != '\0') {
            output.push_back(argv[currentIndex]);
            currentIndex++;
        }

        return output;
    }

    void removeAllOfChar(std::string &sToModify, char cToRemove) {
        std::string sOutput;
        for(auto& c : sToModify) {
            if(c != cToRemove) sOutput.push_back(c);
        }
        sToModify = sOutput;
    }

    void removeAllOfChar(std::string& sToModify, std::string sMultiChars) {
        std::string sOutput;
        for(auto& c : sToModify) {
            if(sMultiChars.find(c) == sMultiChars.npos) sOutput.push_back(c);
        }
        sToModify = sOutput;
    }

    bool onlyContains(std::string &sSource, const char cToCheck) {
        for(auto& c : sSource) {
            if(c != cToCheck) return false;
        }
        return true;
    }

    bool endsWith(std::string &sSource, const std::string sEnd) {
        for(int i = 0; i < sEnd.length(); i++) {
            if(sSource.at(sSource.length()-1-i) != sEnd.at(sEnd.length()-1-i)) return false;
        }
        return true;
    }

    std::string getCurrentDateTime() {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }

}
