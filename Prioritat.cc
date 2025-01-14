/** @file Prioritat.cc
    @brief Implementació de la classe Prioritat
*/

#include "Prioritat.hh"
using namespace std;

Prioritat::Prioritat()
{
    ide="";
    pacceptat=0;
    prefusat=0;
}

Prioritat::Prioritat(const string& id)
{
    ide=id;
    pacceptat=0;
    prefusat=0;
}

string Prioritat::consultar_ide()const
{
    return ide;
}

int Prioritat::consultar_pacceptat()const
{
    return pacceptat;
}

int Prioritat::consultar_prefusat()const
{
    return prefusat;
}

bool Prioritat::baixa_la_prioritat()const
{
    return cua.empty();
}

void Prioritat::enviar(int& n, Cluster& clu)
{
    int mida=cua.size();
    int i=0;
    while(i<mida and n>0){
        Proces p=*(cua.begin());
        cua.erase(cua.begin());
        bool passa=false;
        clu.passa_cluster(p,passa);
        if(passa){
            int nom=p.consulta_nom();
            pr.erase(nom);
            ++pacceptat;
            --n;
        }
        else{
            cua.insert(cua.end(),p);
            ++prefusat;
        }
        ++i;
    }
}


void Prioritat::afegeix(const Proces& pro)
{
    int nom=pro.consulta_nom();
    set<int>::iterator it=pr.find(nom);
    if (it!=pr.end()){
        cout << "error: ya existe proceso" << endl;
    }
    else {
        cua.insert(cua.end(),pro);
        pr.insert(nom);
    }
}

void Prioritat::escriu_prioritat()const
{
    list<Proces>::const_iterator it=cua.begin();
    while (it!=cua.end()){
        cout << it->consulta_nom() << " " << it->consultar_memoc() << " " << it->consultar_temps() << '\n';
        ++it;
    }
    cout << pacceptat << " " << prefusat << '\n';
}
