/** @file Cluster.cc
    @brief Implementació de la classe Cluster
*/

#include "Cluster.hh"
using namespace std;

void Cluster::passa(bool& passat, const BinTree<string>& clu, string& pr, int alcada, int& alcaux, const Proces& pro)
{
//     si no estem a una fulla buida
    if(not clu.empty()){
        map<string,Processador>::iterator it=mapa.find(clu.value());
//         encara no hem trobat cap processador on puguem afegir el proces
        if(not passat){
//              mirem si cap el processador
            if(it->second.cabe_proceso(pro)){
//              canviem a true perque hem trobat un proces al que cap i passem el nom d'aquest proces i l'alçada a pr i alcaux respectivament
                passat=true;
                pr=it->first;
                alcaux=alcada;
            }
        }
//         si ja habiem trobat un processador candidat
        else{
//             comencem amb els desempats per veure quin processador es més adient per afegir el proces, si el trobem, canviem pr pel nou i alcaux per l'alçada del processador en qüestió
            if(it->second.cabe_proceso(pro)){
                if(mapa[pr].hueco_ajustado(pro)>it->second.hueco_ajustado(pro)){
                    pr=it->first;
                    alcaux=alcada;
                }
                else if(mapa[pr].hueco_ajustado(pro)==it->second.hueco_ajustado(pro)){
                    if(mapa[pr].consultar_memlliure()<it->second.consultar_memlliure()){
                        pr=it->first;
                        alcaux=alcada;
                    }
                    else if(mapa[pr].consultar_memlliure()==it->second.consultar_memlliure()){
                        if(alcada<alcaux){
                            pr=it->first;
                            alcaux=alcada;
                        }
                    }
                }
            }
        }
//         repetim el proces amb tots els processadors del cluster
        passa(passat,clu.left(),pr,alcada+1,alcaux,pro);
        passa(passat,clu.right(),pr,alcada+1,alcaux,pro);
    }
}

void Cluster::estructura(const BinTree<string>& clu)
{
    if(clu.empty())cout << " ";
    else {
        cout << "(" << clu.value();
        estructura(clu.left());
        estructura(clu.right());
        cout << ")";
    }
}

void Cluster::modificar(const string& p, const Cluster& nou, BinTree<string>& a)
{
//     busquem el processador i mirem si el podem modificar o no
    if(not a.empty()){
        if (a.value()==p){
            if(a.left().empty() and a.right().empty()){
                a=nou.clu;
                mapa.erase(p);
                mapa.insert(nou.mapa.begin(),nou.mapa.end());
            }
            else cout << "error: procesador con auxiliares" << '\n';
        }
        else{
            BinTree<string>left=a.left();
            modificar(p,nou,left);
            BinTree<string>right=a.right();
            modificar(p,nou,right);
            a=BinTree<string>(a.value(),left,right);
        }
    }

}

void Cluster::leer_cluster(BinTree<string>& a)
{
    string pr;
    cin >> pr;
    if(pr!= "*"){
        int m;
        cin >> m;
        Processador pro(pr,m);
        mapa[pr]=pro;
        BinTree<string> left;
        leer_cluster(left);
        BinTree<string> right;
        leer_cluster(right);
        a = BinTree<string> (pr, left, right);
    }
}

Cluster::Cluster()
{}

void Cluster::passa_cluster(const Proces& pro,bool& passat)
{
//     inicialitzem els parametres que passem per referencia
    string pr="";
    int alcaux=0;
    passa(passat,clu,pr,0,alcaux,pro);
    if (passat){
        map<string,Processador>::iterator it=mapa.find(pr);
        it->second.afegeix_proces(pro);
    }
}

void Cluster::modificar_cluster(const string& p, const Cluster& nou)
{
    map<string,Processador>::const_iterator it=mapa.find(p);
    if(it==mapa.end())cout << "error: no existe procesador" << '\n';
    else{
        if(it->second.te_processos())cout << "error: procesador con procesos" << '\n';
        else{
            modificar(p,nou,clu);
        }
    }
}


void Cluster::alta_proceso_procesador(const string& id,const Proces& p)
{
    map<string,Processador>::iterator it=mapa.find(id);
    if (it==mapa.end())cout << "error: no existe procesador" << '\n';
    else {
        int nom=p.consulta_nom();
        if(it->second.existeix_proces(nom))cout << "error: ya existe proceso" << '\n';
        else it->second.afegeix_proces(p);
    }
}

void Cluster::baja_proceso_procesador(const string& p, int& f)
 {
     map<string,Processador>::iterator it=mapa.find(p);
     if (it==mapa.end())cout << "error: no existe procesador" << '\n';
     else {
         if(not it->second.existeix_proces(f))cout << "error: no existe proceso" << '\n';
         else it->second.elimina_proces(f);
    }
}

void Cluster::avanzar_tiempo(int& t)
{
    map<string,Processador>::iterator it=mapa.begin();
    while (it!=mapa.end()){
        it->second.actualitza(t);
        ++it;
    }
}

void Cluster::compactar_memoria_procesador(const string& id)
{
    map<string,Processador>::iterator it=mapa.find(id);
    if(it==mapa.end())cout << "error: no existe procesador" << '\n';
    else it->second.comprimeix();
}

void Cluster::compactar_memoria_cluster()
{
    map<string,Processador>::iterator it=mapa.begin();
    while(it!=mapa.end()){
        it->second.comprimeix();
        ++it;
    }
}

void Cluster::llegeix_cluster()
{
    leer_cluster(clu);
}

void Cluster::configurar_cluster()
{
    mapa.clear();
    leer_cluster(clu);
}

void Cluster::imprimir_procesador(const string& id)const
{
     map<string,Processador>::const_iterator it=mapa.find(id);
     if (it==mapa.end())cout << "error: no existe procesador" << '\n';
     else {
         it->second.escriu_processador();
    }
}

void Cluster::imprimir_procesadores_cluster()const
{
    map<string,Processador>::const_iterator it=mapa.begin();
    while(it!=mapa.end()){
        cout << it->second.consulta_id() << '\n';
        bool fes=it->second.te_processos();
        if (fes)it->second.escriu_processador();
        ++it;
    }
}

void Cluster::imprimir_estructura_cluster()
{
    estructura(clu);
}









