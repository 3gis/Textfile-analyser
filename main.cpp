#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <stdio.h>
using std::vector;
using std::map;
using std::stringstream;
using std::string;
using std::remove_if;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::replace;
using std::set;
using std::cin;

void insert(map <string, int>& map1, const string& word);
bool tikrinimas(const char& o);
bool tikrinimasSpace(const char& o);
string pasikartojimas(string map1, vector <string>& p);

int main()
{
    ifstream nuskaitymas("tekstas.txt");
    ofstream irasymas("atsakymas.txt");
    map <string, int> Mappas;
    vector <string> sakiniuVektorius;
    stringstream visasTekstas;
    string sakinys;
    if (nuskaitymas.is_open()) {
        visasTekstas << nuskaitymas.rdbuf();
        nuskaitymas.close();
    }
    string pasirinkimas;
    bool kriterijus = true;
    while (kriterijus)
    {
        cout << "(1) Zodziu pasikartojimai;\n";
        cout << "(2) URL adresu ieskojimas;\n";
        cout << "Paspauskite (1) jei norite pirmos funkcijos, paspauskite (2) jei antros: ";
        cin >> pasirinkimas;
        
        if (pasirinkimas == "1") {
            kriterijus = false;
            nuskaitymas.open("tekstas.txt", std::ifstream::in);
            while (!nuskaitymas.eof()) {
                getline(nuskaitymas, sakinys);
                sakinys.erase(remove_if(sakinys.begin(), sakinys.end(), tikrinimasSpace), sakinys.end());
                sakiniuVektorius.push_back(sakinys);
            }

            nuskaitymas.close();
            string zodis;
            while (visasTekstas >> zodis) {
                zodis.erase(remove_if(zodis.begin(), zodis.end(), tikrinimas), zodis.end());
                insert(Mappas, zodis);
            }
            char buffer[80];
            sprintf(buffer, "%-20s %-20s %-20s \n", "Zodis", "Pasikartojimai", "Eilutes");
            cout << buffer;
            irasymas << buffer;
            for (int i = 0; i < 80; i++, cout << "-", irasymas << "-");
            cout << "\n";
            irasymas << "\n";
            for (auto it = Mappas.cbegin(); it != Mappas.cend(); ++it) {
                if (it->second != 1 && it != Mappas.cbegin()) {
                    sprintf(buffer, "%-20s %-20i %-20s \n", it->first.c_str(), it->second, pasikartojimas(it->first, sakiniuVektorius).c_str());
                    cout << buffer;
                    irasymas << buffer;
                }
            }
        }
        else if (pasirinkimas == "2") {
            kriterijus = false;
            string raide;
            set<string> Settas;
            while (visasTekstas >> raide) {
                if ((raide[0] == 'h' && raide[1] == 't' && raide[2] == 't' && raide[3] == 'p') || (raide[0] == 'w' && raide[1] == 'w' && raide[2] == 'w'))
                    Settas.insert(raide);
            }
            char buffer[80];
            sprintf(buffer, "%-20s\n", "Svetaines URL");
            cout << buffer;
            irasymas << buffer;
            for (int i = 0; i < 80; i++, cout << "-", irasymas << "-");
            cout << "\n";
            irasymas << "\n";
            for (auto i : Settas) {
                sprintf(buffer, "%-20s\n", i.c_str());
                cout << buffer;
                irasymas << buffer;
                for (int i = 0; i < 80; i++, cout << "-", irasymas << "-");
                cout << "\n";
                irasymas << "\n";
            }
        }
        else {
            cout << "Tokio pasirinkimo nera..\n";
        }
    }
    return 0;

}

void insert(map <string, int>& map1, const string& word)
{
    ++map1[word];
}
bool tikrinimas(const char& o)
{
    return !((o > 64 && o < 90) || (o > 96 && o < 123));
}
bool tikrinimasSpace(const char& o)
{
    return !((o > 64 && o < 90) || (o > 96 && o < 123) || o == 32);
}
string pasikartojimas(string map1, vector <string>& p) {
    string t;
    string atsakymas;
    bool didIt = false;
    for (int i = 0; i < p.size(); i++) {
        didIt = false;
        for (auto j : p[i]) {
            if (j != ' ' && j != '\n')
                t += j;
            else {
                if (map1 == t) {
                    auto y = std::to_string(i + 1);
                    atsakymas += y + " ";
                    didIt = true;
                    break;
                }
                t = "";
            }
        }
        if (map1 == t && didIt == false) {
            auto y = std::to_string(i + 1);
            atsakymas += y + " ";
            break;
        }
        t = "";
    }

    return atsakymas;
}
