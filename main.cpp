#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <map>
#include <sstream>
#include <fstream>


using std::cin;
using std::cout;
using std::endl;
using std::setw;
using std::setprecision;
using std::vector;
using std::string;
//using std::sort;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::getline;
using std::to_string;
using std::exception;
using std::map;
using std::left;
//using std::partition;
class zodis{
    public:
    vector<int> line;
    int ocurence=1;
    //string name;

};
void stand(string &A){
    for(int i=0; i<A.size(); i++){
    

    std::transform(A.begin(), A.end(), A.begin(),
    [](unsigned char c){ return std::tolower(c); });
      A.erase (std::remove_if (A.begin (), A.end (), ispunct), A.end());
      A.erase (std::remove_if (A.begin (), A.end (), isdigit), A.end());
        
       /*if(A.empty()){
           A.clear();
       }*/
    }
    
    
}
void addw(string word, map<string, zodis> &A, int linec){
     if(!word.empty()){
        auto iter=A.find(word);
        zodis B;
        B.line.push_back(linec);

        if(iter==A.end()){
            A.insert({word, B});
        }
        else{
           if(linec != iter->second.line.back()){
                iter->second.line.push_back(linec);
           }
        }
        iter->second.ocurence++;
     }
    
}
void skaitymas( vector<string> &links, map<string, zodis> &A, int &linec){
    ifstream open_f;
    string n;
    cout << "iveskite failo pav" << endl;
    cin >> n;
    string filename=n+".txt";
     try
    {

        open_f.open(filename);
        if (!open_f)
            throw std::runtime_error("failas neatsidare");
    }
    catch (std::exception &ex)
    {
        cout << "programa neveike, nes: " << ex.what() << endl;
    }
    stringstream buffer;
    string eil;
     linec=1;
     buffer << open_f.rdbuf();
    
   // cout << "pog1" << endl;
     while (getline(buffer, eil)){
         
         stringstream ss(eil);
         string word;
         
         while (ss >> word){
            if(word.substr(0, 8)=="https://" || word.substr(0, 4)=="www."){
                links.push_back(word);
            }
            else{
                stand(word);
                addw(word, A, linec);
            }
             
         }
         linec++;
     }
     open_f.close();
}


int tarpskaic(int prev, int eil){
    int sum=0;
        for(int i=prev; i<eil; i++){
        int n=to_string(i).length();
        sum+=n+1;
        }
        return sum;
}
int main(){
    

    map <string, zodis> A;
    vector<string> links;
    int linec;
    skaitymas(links, A, linec);
    //atrinklinks(A, links);
    //stand(A);
   // skaic(A);
    ofstream out_fcounter("counter.txt");
    //cout << "zodziai"<< endl;
    for(auto zodis : A){
        if(zodis.second.ocurence>1){
            out_fcounter<< zodis.first << " ";
            out_fcounter << zodis.second.ocurence ;
           /* for(auto line : zodis.second.line){
            cout << line << " ";
        }*/
        out_fcounter << endl;
       }
        
    }
    ofstream out_flinks("links.txt");
  //  cout << "nuorodos"<< endl;
    for(int i=0; i<links.size(); i++){
        out_flinks<< links[i] << endl;
    }


    ofstream out_ftable("table.txt");
    out_ftable <<setw(15) << left <<"zodis"  ;
    for(int i=0; i<linec; i++){
        out_ftable <<  i+1 <<  " ";
    }
    out_ftable << endl;
    out_ftable << endl;
    int atimti;
    int prev;


    
     for(auto zodis: A){
         if(zodis.second.ocurence>1){
        out_ftable <<setw(15)<< left <<zodis.first ;
        int i=0;
        for(auto eil : zodis.second.line){
                if(i==0){
                    atimti=1;
                    out_ftable <<  string(tarpskaic(atimti, eil), ' ') <<"*";
                }
                else{
                    atimti=prev;
                    out_ftable <<  string(tarpskaic(atimti, eil)-1, ' ') <<"*";
                }
           
                prev=eil;
                i++;
        }
        out_ftable << endl;}
    }

    out_ftable << endl;
  
    
}