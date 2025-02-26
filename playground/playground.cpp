#include "playground.hpp"
#include "../util.hpp"
#include <ctime>
#include <string>
#include <vector>

int main() {
    util::qPrint("Util Playground Hello.");
    util::qPrint("");

    util::qPrint(util::fileToString("/home/vince/Repos/CppUtil/playground/playground.hpp"));
    util::qPrint("");

    std::vector<std::string> vFile = util::fileToVector("/home/vince/Repos/CppUtil/playground/playground.cpp");

    std::vector<std::string> vToMerge = {"This is to be appended to the end of the vector!"};

    util::appendVectors(vFile, vToMerge);

    for(auto& l : vFile) {
        util::qPrint("~|",l);
    }
    util::qPrint("");

    std::string sTrue = "Value is true!", sFalse = "Value is false!";
    util::cPrint("magenta",util::switchOnAlt(sTrue, sFalse));
    util::alt.setAlt(true);
    util::cPrint("magenta",util::switchOnAlt(sTrue, sFalse));
    util::qPrint("");

    util::gate.create("gate1");
    util::qPrint("gate1 created with state",util::gate.state("gate1"));
    util::qPrint("nogate has state",util::gate.state("nogate"));
    util::gate.toggle("gate1");
    util::qPrint("gate1 toggled with state",util::gate.state("gate1"));
    util::gate.close("nogate");
    util::qPrint("nogate attempted close with exist state",util::gate.exists("nogate"));
    util::gate.open("nogate");
    util::qPrint("nogate atttempted open with exist state",util::gate.exists("nogate"));
    util::gate.toggle("gate1");
    util::qPrint("gate1 toggled with state",util::gate.state("gate1"));
    util::qPrint("");

    std::string sTest = "Hello thIs is 8 test.";
    std::vector<const char*> charFilters = {
        "2c8h","h","gby","T","t","I",".,"
    };
    util::qPrint("CheckPhrase:\n" + sTest);
    for(auto& filter : charFilters) {
        util::qPrint("Filter '" + std::string(filter) + "' / value:",util::containsAny(sTest, filter));
    }
    util::qPrint("");

    std::unordered_map<std::string,int> mTestIncrementer = {
        { "First" , 2 },
        { "Second" , 8 },
        { "Third" , 12 },
        { "Fourth" , 3 }
    };

    util::unordered_mapIncrement(mTestIncrementer, std::string("Third"));
    util::unordered_mapIncrement(mTestIncrementer, std::string("Five"));

    for(auto& i : mTestIncrementer) {
        util::cPrint("cyan",i.first,i.second);
    }
    util::qPrint("");

    bool bTestFlipReturn = false;
    for(int i = 0; i < 5; ++i) {
        util::cPrint("green",util::flip(bTestFlipReturn));
        util::qPrint(bTestFlipReturn);
    }
    util::qPrint("");

    std::string sAN = "abced827", sNAN = "abs.w2f", sNNN = "28ab,", sND = "3829.3", sN = "512421", sA = "asljdb";
    util::qPrint("Alpha=False Number=True");
    util::qPrint(sA,util::onlyContains(sA,"",false,true));
    util::qPrint(sAN,util::onlyContains(sAN,"",false,true));
    util::qPrint(sNAN,util::onlyContains(sNAN,"",false,true));
    util::qPrint(sNNN,util::onlyContains(sNNN,"",false,true));
    util::qPrint(sND,util::onlyContains(sND,"",false,true));
    util::qPrint(sN,util::onlyContains(sN,"",false,true));
    util::qPrint("");

    util::qPrint("Alpha=True Number=True");
    util::qPrint(sA,util::onlyContains(sA,"",true,true));
    util::qPrint(sAN,util::onlyContains(sAN,"",true,true));
    util::qPrint(sNAN,util::onlyContains(sNAN,"",true,true));
    util::qPrint(sNNN,util::onlyContains(sNNN,"",true,true));
    util::qPrint(sND,util::onlyContains(sND,"",true,true));
    util::qPrint(sN,util::onlyContains(sN,"",true,true));
    util::qPrint("");

    util::qPrint("Alpha=True Number=False");
    util::qPrint(sA,util::onlyContains(sA,"",true,false));
    util::qPrint(sAN,util::onlyContains(sAN,"",true,false));
    util::qPrint(sNAN,util::onlyContains(sNAN,"",true,false));
    util::qPrint(sNNN,util::onlyContains(sNNN,"",true,false));
    util::qPrint(sND,util::onlyContains(sND,"",true,false));
    util::qPrint(sN,util::onlyContains(sN,"",true,false));
    util::qPrint("");

    util::qPrint("Alpha=False Number=False");
    util::qPrint(sA,util::onlyContains(sA,"",false,false));
    util::qPrint(sAN,util::onlyContains(sAN,"",false,false));
    util::qPrint(sNAN,util::onlyContains(sNAN,"",false,false));
    util::qPrint(sNNN,util::onlyContains(sNNN,"",false,false));
    util::qPrint(sND,util::onlyContains(sND,"",false,false));
    util::qPrint(sN,util::onlyContains(sN,"",false,false));
    util::qPrint("");


    float fTestSleep = 1.25;
    util::qPrint("Sleeping",fTestSleep,"seconds.");
    util::timer.start();
    util::sleep(fTestSleep);
    util::timer.end();
    util::qPrint("Sleeping finished :",util::timer.get(),util::timer.getStr());

}
