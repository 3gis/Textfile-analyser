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
bool Tikrinimas(const char & o);
bool Tikrinimasspace(const char & o);
string pasikartojimas(string map1,vector <string>& p);

int main()
{
    ifstream fd ("tekstas.txt");
    ofstream ff ("atsakymas.txt");
    map <string, int> Mappas;
    vector <string> p;
    stringstream ss;
    string k;
    if(fd.is_open()){
        ss << fd.rdbuf();
        fd.close();
    }
    string pasirinkimas;
    kl:
    cout << "(1) Zodziu pasikartojimai;\n";
    cout << "(2) URL adresu ieskojimas;\n";
    cout << "Pasirinkimas: ";
    cin >> pasirinkimas;
    if(pasirinkimas == "1"){
        fd.open("tekstas.txt", std::ifstream::in);
        while(!fd.eof()){
            getline(fd,k);
            //replace(k.begin(),k.end(),Tikrinimasspace,' ');
            k.erase(remove_if(k.begin(),k.end(),Tikrinimasspace),k.end());
            p.push_back(k);
        }
        fd.close();
        string t;
        while(ss >> t){
        t.erase(remove_if(t.begin(),t.end(),Tikrinimas),t.end());
        //cout << t << "\n";
        insert(Mappas, t);
        }
        char buffer[80];
        sprintf(buffer, "%-20s %-20s %-20s \n","Zodis", "Pasikartojimai", "Eilutes");
        cout << buffer;
        ff << buffer;
        for (int i = 0; i < 80; i++, cout << "-", ff << "-");
        cout << "\n";
        ff << "\n";
        for(auto it = Mappas.cbegin(); it != Mappas.cend(); ++it){
            if(it->second !=1 && it!=Mappas.cbegin()){

                //cout << it->first << " " << it->second << " | " << pasikartojimas(it->first,p,ff) << "\n";
                sprintf(buffer, "%-20s %-20i %-20s \n", it->first.c_str(), it->second, pasikartojimas(it->first,p).c_str());
                cout << buffer;
                ff << buffer;
            }
        }
    }
    else if(pasirinkimas == "2"){
        string t;
        set<string> Settas;
        while(ss>>t){
            if((t[0]=='h' && t[1]=='t' && t[2]=='t' && t[3]=='p') || (t[0]=='w' && t[1]=='w' && t[2]=='w'))
                Settas.insert(t);
        }
        char buffer[80];
        sprintf(buffer, "%-20s\n","Svetaines URL");
        cout << buffer;
        ff << buffer;
        for (int i = 0; i < 80; i++, cout << "-", ff << "-");
        cout << "\n";
        ff << "\n";
        for(auto i : Settas){
            sprintf(buffer, "%-20s\n",i.c_str());
            cout << buffer;
            ff << buffer;
            for (int i = 0; i < 80; i++, cout << "-", ff << "-");
            cout << "\n";
            ff << "\n";
        }
    }
    else{
        cout << "Tokio pasirinkimo nera..\n";
        goto kl;
    }
    return 0;
}
void insert(map <string, int>& map1, const string& word)
{
    ++map1[word];
}
bool Tikrinimas(const char & o)
{
    return !((o > 64 && o < 90) || (o >96 && o<123));
}
bool Tikrinimasspace(const char & o)
{
    return !((o > 64 && o < 90) || (o >96 && o<123) || o == 32);
}
string pasikartojimas(string map1, vector <string>& p){
    //vector <string> p;
    string t;
    string atsakymas;
    bool didIt=false;
    for(int i = 0; i<p.size();i++){
        didIt=false;
        for(auto j : p[i]){
            if(j!=' ' && j!='\n')
            t+=j;
            else{
                if(map1==t){
                    auto y = std::to_string(i+1);
                    atsakymas+= y + " ";
                    didIt=true;
                    break;
                }
                t="";
            }
        }
        if(map1==t && didIt==false){
            auto y = std::to_string(i+1);
            atsakymas+= y + " ";
            break;
        }
        t="";
    }

    return atsakymas;
}
