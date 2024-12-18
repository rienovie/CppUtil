#include "playground.hpp"
#include "../util.hpp"
#include <string>
#include <vector>

int main() {
    util::qPrint("Util Playground Hello.");

    util::qPrint(util::fileToString("/home/vince/Repos/CppUtil/playground/playground.hpp"));

    std::vector<std::string> vFile = util::fileToVector("/home/vince/Repos/CppUtil/playground/playground.cpp");

    for(auto& l : vFile) {
        util::qPrint("~|",l);
    }

    util::gate.create("gate1");
    util::qPrint(util::gate.state("gate1"));
    util::qPrint(util::gate.state("nogate"));
    util::gate.toggle("gate1");
    util::qPrint(util::gate.state("gate1"));
    util::qPrint(util::gate.exists("nogate"));
    util::gate.close("nogate");
    util::gate.open("nogate");
    util::gate.toggle("gate1");
    util::qPrint(util::gate.state("gate1"));

}
