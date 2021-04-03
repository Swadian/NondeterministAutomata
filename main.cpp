#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
using namespace std;
struct tranzitie
{
  int destinatie;
  char litera;
};
struct parcurgere
{
    int stare;
    int depth;
};
int main()
{
    vector<tranzitie> l[1000];
    queue<parcurgere> st;//st de la stari, nu stiva
    string cuv;
    unordered_set<int> setF;
    ofstream fout("date.out");
    ifstream fin("date.in");
    int n;
    fin>>n;
    int dump;
    for(int i=0;i<n;i++)
        fin>>dump;//eliminam numerele starilor din fisier, nu ne trebuie
    int m;
    fin>>m;
    tranzitie trn;
    int x;
    for(int i=0;i<m;i++)
    {
        fin>>x>>trn.destinatie>>trn.litera;
        l[x].push_back(trn);
    }
    int s;fin>>s;
    int nrF;fin>>nrF;
    int state;
    for(int i=0;i<nrF;i++)
    {fin>>state; setF.insert(state);}
    int currentstate;
    int nrCuv;
    fin>>nrCuv;
    bool accepted;
    for(int i=0;i<nrCuv;i++)//procesarea pe cuvant
    {
        accepted=false;
        fin>>cuv;
        while(!st.empty())st.pop();//golesc coada
        parcurgere p;
        p.depth=0;
        p.stare=s;
        st.push(p);//adaug starea initiala
        for(int j=0;j<(int)cuv.size();j++)//procesarea pe litere
        {
            p.depth=j+1;
            while(st.front().depth==j)//cat timp in coada sunt stari de adancimea curenta
            {
                currentstate=st.front().stare;//scot starea curenta din coada
                for(int k=0;k<(int)l[currentstate].size();k++)//ii parcurg lista de adiacenta
                {
                    if(l[currentstate][k].litera==cuv[j])
                        {
                            p.stare=l[currentstate][k].destinatie;
                            st.push(p);
                        }//adaug starile in care poate ajunge
                }
                st.pop();//scor starea procesata din coada
            }
        }
        while(!st.empty())//procesarea cozii sa vad daca am ajuns la o stare finala
        {
            currentstate=st.front().stare;
            if(setF.count(currentstate)!=0)
            {
                fout<<"DA\n";
                accepted=true;
                break;
            }
            st.pop();
        }
        if(!accepted)fout<<"NU\n";
    }
    fin.close();
    fout.close();
    return 0;
}
