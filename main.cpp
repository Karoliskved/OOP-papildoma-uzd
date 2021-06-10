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

/*oid atrinklinks(vector<zodis> &A, vector<string> &links){
    for(int i=0; i<A.size(); i++){
       // cout<< A[i].name.substr(0, 4)<< endl;
        if(A[i].name.substr(0, 8)=="https://" || A[i].name.substr(0, 4)=="www."){
            links.push_back(A[i].name);
            A.erase(A.begin()+i);
            i--;
        }
    }    
}*/

/*void skaic(vector<zodis> &A){
    for(int i=0; i<A.size(); i++){
        for(int j=i+1; j<A.size(); j++){
            if(A[i].name==A[j].name){
                A[i].line.push_back(A[j].line[0]);
                A[i].ocurence++;
                A.erase(A.begin()+j);
                j--;
            }
        }
        if(A[i].ocurence<=1){
            A.erase(A.begin()+i);
            i--;
        }
    }
}*/
int distance(int prev, int eil){
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
    
    cout << "zodziai"<< endl;
    for(auto zodis : A){
        if(zodis.second.ocurence>1){
            cout<< zodis.first << " ";
            cout << zodis.second.ocurence << " ";
           /* for(auto line : zodis.second.line){
            cout << line << " ";
        }*/
        cout << endl;
       }
        
    }
    cout << "nuorodos"<< endl;
    for(int i=0; i<links.size(); i++){
        cout << links[i] << endl;
    }
    cout <<setw(15) << left <<"zodis"  ;
    for(int i=0; i<linec; i++){
        cout <<  i+1 <<  " ";
    }
    cout << endl;
    cout << endl;
    int atimti;
    int prev;


    
     for(auto zodis: A){
         if(zodis.second.ocurence>1){
        cout <<setw(15)<< left <<zodis.first ;
        int i=0;
        for(auto eil : zodis.second.line){
                if(i==0){
                    atimti=1;
                    cout <<  string(distance(atimti, eil), ' ') <<"*";
                }
                else{
                    atimti=prev;
                    cout <<  string(distance(atimti, eil)-1, ' ') <<"*";
                }
           
                prev=eil;
                i++;
        }
        cout << endl;}
    }

    cout << endl;
  
    
}