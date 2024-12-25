#include "playground.hpp"
#include "../util.hpp"
#include <string>
#include <vector>

int main() {
    util::qPrint("Util Playground Hello.");

    util::qPrint(util::fileToString("/home/vince/Repos/CppUtil/playground/playground.hpp"));

    std::vector<std::string> vFile = util::fileToVector("/home/vince/Repos/CppUtil/playground/playground.cpp");

    std::vector<std::string> vToMerge = {"This is to be appended to the end of the vector!"};

    util::appendVectors(vFile, vToMerge);

    for(auto& l : vFile) {
        util::qPrint("~|",l);
    }

    util::gate.create("gate1");
    util::qPrint(util::gate.state("gate1"));
    util::qPrint(util::gate.state("nogate"));
    util::gate.toggle("gate1");
    util::qPrint(util::gate.state("gate1"));
    util::gate.close("nogate");
    util::qPrint(util::gate.exists("nogate"));
    util::gate.open("nogate");
    util::gate.toggle("gate1");
    util::qPrint(util::gate.state("gate1"));

    std::string sTest = "Hello thIs is 8 test.";
    std::vector<const char*> charFilters = {
        "2c8h","h","gby","T","t","I",".,"
    };
    util::qPrint("CheckPhrase:\n" + sTest);
    for(auto& filter : charFilters) {
        util::qPrint("Filter '" + std::string(filter) + "' / value:",util::containsAny(sTest, filter));
    }

}
