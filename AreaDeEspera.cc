/** @file AreaDeEspera.cc
    @brief Implementació de la classe AreaDeEspera
*/

#include "AreaDeEspera.hh"
using namespace std;

AreaDeEspera::AreaDeEspera()
{}

//En aquesta recorro totes les prioritats que siguin necessaries per tal d'arribar als processos necessaris
void AreaDeEspera::enviar_procesos_cluster(int n, Cluster& clu)
{
    map<string,Prioritat>::iterator it=espera.begin();
    while(it!=espera.end() and n>0){
        it->second.enviar(n, clu);
        ++it;
    }
}

// Primer busco la prioritat a l'area d'espera, si existeix s'imprimeix el missatge d'error, sinó s'afegeig una prioritat buida amb l'identificador p
void AreaDeEspera::alta_prioridad(const string& p)
{
    map<string,Prioritat>::iterator it=espera.find(p);
    if (it!=espera.end())cout << "error: ya existe prioridad" << '\n';
    else {
        Prioritat pr(p);
        espera[p]=pr;
    }
}

// Primer busco la prioritat a l'area d'espera, si no existeix s'imprimeix el missatge d'error, sinó, es mira si no té processos pendents, llavors s'elimina la prioritat amb identificador p
void AreaDeEspera::baja_prioridad(const string& p)
{
    map<string,Prioritat>::iterator it=espera.find(p);
    if (it==espera.end())cout << "error: no existe prioridad" << '\n';
    else {
        bool bp=it->second.baixa_la_prioritat();
        if(not bp)cout << "error: prioridad con procesos" << '\n';
        else espera.erase(it);
    }
}

// Busco si existeix la prioritat, llavors li afegeixo el proces pro
void AreaDeEspera::alta_proceso_espera(const string& p, const Proces& pro)
{
   map<string,Prioritat>::iterator it=espera.find(p);
   if (it==espera.end())cout << "error: no existe prioridad" << '\n';
   else {
       it->second.afegeix(pro);
   }
}

// Creo n prioritats buides i les afegeixo a l'area d'espera
void AreaDeEspera::llegeix_AreaDeEspera(int& n)
{
    string p;
    for (int i=1; i<=n; ++i){
       cin >> p;
       Prioritat pr(p);
       espera[p]=pr;
    }
}

// Busco si existeix la prioritat, llavors la imprimeixo
void AreaDeEspera::imprimir_prioridad(const string& p)const
{
    map<string,Prioritat>::const_iterator it=espera.find(p);
    if (it==espera.end())cout << "error: no existe prioridad" << '\n';
    else {
        it->second.escriu_prioritat();
    }
}

// Recorro tota l'area d'espera i vaig imprimint les prioritats
void AreaDeEspera::imprimir_area_espera()const
{
    map<string,Prioritat>::const_iterator it=espera.begin();
    while(it!=espera.end()){
        cout << it->second.consultar_ide() << endl;
        bool bp=it->second.baixa_la_prioritat();
        if (not bp){
            it->second.escriu_prioritat();
        }
        else cout << it->second.consultar_pacceptat() << " " << it->second.consultar_prefusat() << '\n';
        ++it;
    }
}




