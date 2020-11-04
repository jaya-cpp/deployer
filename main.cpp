#include <iostream>
#include <utility>
#include <ctime>
#include <iomanip>
#include <sys/stat.h>
#include <nlohmann/json.hpp>
#include <cstdlib>


using namespace std;


namespace deployer {
    class Split : public std::vector<std::string> {
    public:
        Split(std::string s, char delimiter){
            auto paux = s.c_str();
            std::string accstring{};
            for(;*paux; ++paux){
                if (*paux == delimiter){
                    this->push_back(accstring);
                    accstring = std::string{};
                } else {
                    accstring += *paux;
                }
            }
            if (!accstring.empty()) this->push_back(accstring);
        }
    };
    class DateTimeString : public std::string {
    public:
        DateTimeString() {
            auto now = time(0);
            auto ltm = localtime(&now);
            std::ostringstream strstr;
            strstr << 1900 + ltm->tm_year << setfill('0') << setw(2) << ltm->tm_mon + 1;
            strstr << setfill('0') << setw(2) << ltm->tm_mday;
            strstr << setfill('0') << setw(2) << ltm->tm_hour;
            strstr << setfill('0') << setw(2) << ltm->tm_min;
            *this += strstr.str();
        }
    };

    class DirectoryExists {
        bool mExists {false};
    public:
        DirectoryExists(const std::string pathname){
            struct stat info;
            if (stat(pathname.c_str(), &info)) return;
            else if (!(info.st_mode & S_IFDIR)) return;
            mExists = true;
        }
        const bool& operator()(){
            return mExists;
        }
    };

    class Environ : public std::map<std::string, std::string> {

    public:
        explicit Environ(char **envp) {
            auto index = 0;
            for (auto auxenvp = envp; *auxenvp != 0x00; ++auxenvp){
                auto split = deployer::Split(*auxenvp,'=');
                this->insert(make_pair(split[0], split[1]));
            }
        }
    };
}





int main(int argc, char** argv, char **envp) {
    cout << "==============================" << endl;
    auto env = deployer::Environ(envp);
    auto deploydate = deployer::DateTimeString();
    std::cout << deploydate << endl;

    for (auto kv : env){
        std::cout << kv.first << " = " << kv.second << endl;
    }
    cout << "==============================" << endl;

    return 0;
}
