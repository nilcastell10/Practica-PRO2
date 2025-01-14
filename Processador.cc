/** @file Processador.cc
    @brief Implementació de la classe Processador
*/

#include "Processador.hh"
using namespace std;

Processador::Processador()
{
    id="";
    capacitat=0;
    espais[capacitat].insert(0);
    memlliure=0;
}

Processador::Processador(const string& ide)
{
    id=ide;
    capacitat=0;
    espais[capacitat].insert(0);
    memlliure=0;
}

Processador::Processador(const string& ide, int& me)
{
    id=ide;
    capacitat=me;
    espais[capacitat].insert(0);
    memlliure=me;
}

int Processador::hueco_ajustado(const Proces& pro)const
{
    int oc=pro.consultar_memoc();
    map<int,set<int>>::const_iterator it=espais.lower_bound(oc);
    return it->first;
}

bool Processador::cabe_proceso(const Proces& pro)const
{
    int oc=pro.consultar_memoc();
    map<int,set<int>>::const_iterator it=espais.lower_bound(oc);
    int nom=pro.consulta_nom();
    map<int,int>::const_iterator it1=id_pos.find(nom);
    if(it!=espais.end() and it1==id_pos.end())return true;
    else return false;
}

int Processador::consultar_memlliure()const
{
    return memlliure;
}

string Processador::consulta_id()const
{
    return id;
}

int Processador::consulta_capacitat()const
{
    return capacitat;
}

bool Processador::te_processos()const
{
    return not pos_proces.empty();
}

bool Processador::existeix_proces(const int& nom)const
{
    map<int,int>::const_iterator it=id_pos.find(nom);
    if(it==id_pos.end())return false;
    else return true;
}

void Processador::actualitza(int& t)
{
    map<int,Proces>aux=pos_proces;
    map<int,Proces>::const_iterator it1=aux.begin();
    while (it1!=aux.end()){
        pos_proces[it1->first].treure_temps(t);
        if (pos_proces[it1->first].consultar_restant()==0){
            int nom=it1->second.consulta_nom();
            elimina_proces(nom);
        }
        ++it1;
    }
}

void Processador::comprimeix()
{
    espais.clear();
    map<int,Proces>::iterator it=pos_proces.begin();
    map<int,int>::iterator it1;
    int pos=0;
    while(it!=pos_proces.end()){
        int oc=it->second.consultar_memoc();
//         si la posicio en la que es troba el proces coincideix amb la posicio en la que acaba el proces anterior no cal fer res
        if(it->first!=pos){
            Proces p=it->second;
            int nom=it->second.consulta_nom();
            it1=id_pos.find(nom);
            id_pos.erase(it1);
            id_pos[nom]=pos;
            it=pos_proces.erase(it);
            pos_proces[pos]=p;
        }
        else ++it;
        pos=pos+oc;
    }
    if(memlliure!=0){
        espais[memlliure].insert(pos);
    }
}

void Processador::afegeix_proces(const Proces& pro)
{
    int nom=pro.consulta_nom();
    int oc=pro.consultar_memoc();
//     primer mirem si l'espai lliure de memoria es superior o igual al proces
    if(oc<=memlliure){
//         busquem si hi ha un espai on capigue el proces, i alhora el més ajustat
        map<int,set<int>>::iterator it1=espais.lower_bound(oc);
        if (it1!=espais.end()){
            int pos=*(it1->second.begin());
            int espai=it1->first;
            it1->second.erase(pos);
            if(it1->second.empty()){
                espais.erase(it1);
            }
            pos_proces[pos]=pro;
            id_pos[nom]=pos;
            espai=espai-oc;
            pos=pos+oc;
            if(espai!=0){
                espais[espai].insert(pos);
            }
            memlliure=memlliure-oc;
        }
        else cout << "error: no cabe proceso" << '\n';
    }
    else cout << "error: no cabe proceso" << '\n';
}

void Processador::elimina_proces(int& t)
{
    map<int,int>::iterator it=id_pos.find(t);
    int pos=it->second;
    map<int,Proces>::iterator it1=pos_proces.find(pos);
    int oc=it1->second.consultar_memoc();
    map<int,set<int>>::iterator it2;
    if(it1==pos_proces.begin()){ //el proces es el primer situat, llavors hi ha dos casos
        if(pos==0){ //si es troba a la primera posició, nomes pot tenir espai per la seva dreta
            ++it1;
            if(it1!=pos_proces.end()){ //mirem si aquest proces es l'unic o en te mes a la dreta
                int po=it1->first;
                int espai=po-oc;
                if(espai!=0){ //com que l'espai entre processos es >0, hem de modificar el mapa d'espais
                    it2=espais.find(espai);
                    if(it2!=espais.end()){
                        it2->second.erase(it2->second.begin());
                        if(it2->second.empty())it2=espais.erase(it2);
                    }
                    //l'espai que es deixa es l'anterior sumat amb l'ocupació del proces
                    espai=espai+oc;
                    espais[espai].insert(0);
                }
                else{ //si l'espai entre processos es =0, l'espai final sera igual a l'ocupació del propi proces
                    espais[oc].insert(0);
                }
            }
            else{   //si el proces es l'unic que hi ha, l'espai sera la capacitat de la memoria
                if(not espais.empty()){
                    espais.erase(espais.begin());
                }
                espais[capacitat].insert(0);
            }
            --it1;
        }
        else{ //si es troba a una posició que no es l'inicial, te espai a l'esquerra i en pot tenir a la dreta
            it2=espais.find(pos);
            if(it2!=espais.end()){
                it2->second.erase(it2->second.begin());
                if(it2->second.empty())espais.erase(it2);
            }
            ++it1;
            if(it1!=pos_proces.end()){//repetim el procediment de mirar si conte processos a la dreta o es l'unic
                int po=it1->first;
                int espai=po-oc-pos;
                if(espai!=0){
                    it2=espais.find(espai);
                    if(it2!=espais.end()){
                        it2->second.erase(it2->second.begin());
                        if(it2->second.empty())it2=espais.erase(it2);
                    }
                    espai=espai+oc+pos;
                    it2=espais.find(espai);
                    if(it2!=espais.end())it2->second.insert(0);
                    else {
                        espais[espai].insert(0);
                    }
                }
            }
            else{
                if(not espais.empty()){
                    espais.erase(espais.begin());
                }
                espais[capacitat].insert(0);
            }
            --it1;
        }
    }
    else{   //el proces te processos per davant seu, llavors pot haver-hi espai a les dues bandes
        --it1;
        int posaux=it1->first;
        int ocaux=it1->second.consultar_memoc();
        int nou=posaux+ocaux;
        int espai=pos-nou;
        if(espai!=0){ //comprovem si disposa d'espai a la seva esquerra
            it2=espais.find(espai);
            if(it2!=espais.end()){
                it2->second.erase(it2->second.find(nou));
                if(it2->second.empty())espais.erase(it2);
            }
        }
        espai=espai+oc;
        ++it1;
        ++it1;  //comprovem quin es l'espai de la seva dreta
        int espaux;
        if(it1!=pos_proces.end())posaux=it1->first;
        else posaux=capacitat;
        nou=pos+oc;
        espaux=posaux-nou;
        if(espaux!=0){
            it2=espais.find(espaux);
            if(it2!=espais.end()){
                it2->second.erase(it2->second.find(nou));
                if(it2->second.empty())espais.erase(it2);
            }
        }
        espai=espai+espaux;
        posaux=posaux-espai;
        it2=espais.find(espai);
        if(it2!=espais.end())it2->second.insert(posaux);
        else{
            espais[espai].insert(posaux);
        }
        --it1;
    }
    id_pos.erase(it);
    pos_proces.erase(it1);
    memlliure=memlliure+oc;
}

void Processador::llegeix_processador()
{
    cin >> id >> capacitat;
    espais[capacitat].insert(0);
    memlliure=capacitat;
}

void Processador::escriu_processador()const
{
    for (map<int,Proces>::const_iterator it=pos_proces.begin(); it!=pos_proces.end(); ++it){
        cout << it->first << " ";
        it->second.escriu_proces();
    }
}
