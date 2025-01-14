/** @file program.cc
    @brief Programa principal
*/

#include "AreaDeEspera.hh"
#include "Cluster.hh"


#ifndef NO_DIAGRAM
#include "Prioritat.hh"
#include "Proces.hh"
#include "Processador.hh"
#include <iostream>
#include <vector>
#include <string>
#endif

using namespace std;

int main(){
    string prio; //identificador de prioritat
    string pro;  //identificador de processador
    Proces p;
    Cluster clu;
    clu.configurar_cluster();
    int n;
    cin >> n;
    AreaDeEspera area;
    area.llegeix_AreaDeEspera(n);
    string comando;
    cin >> comando;
    while (comando != "fin") {
        if (comando == "cc" or comando=="configurar_cluster"){
            cout << "#" << comando << '\n';
            clu.configurar_cluster();
        }
        else if (comando == "mc" or comando=="modificar_cluster"){
            cin >> pro;
            cout << "#" << comando << " " << pro << '\n';
            Cluster c;
            c.llegeix_cluster();
            clu.modificar_cluster(pro,c);
        }
        else if (comando == "ap" or comando=="alta_prioridad"){
            cin >> prio;
            cout << "#" << comando << " " << prio << '\n';
            area.alta_prioridad(prio);
        }
        else if (comando == "bp" or comando=="baja_prioridad"){
            cin >> prio;
            cout << "#" << comando << " " << prio << '\n';
            area.baja_prioridad(prio);
        }
        else if (comando == "ape" or comando=="alta_proceso_espera"){
            cin >> prio;
            p.llegeix_proces();
            cout << "#" << comando << " " << prio << " " << p.consulta_nom() << '\n';
            area.alta_proceso_espera(prio,p);
        }
        else if (comando == "app" or comando=="alta_proceso_procesador"){
            cin >> pro;
            p.llegeix_proces();
            cout << "#" << comando << " " << pro << " " << p.consulta_nom() << '\n';
            clu.alta_proceso_procesador(pro,p);
        }
        else if (comando == "bpp" or comando=="baja_proceso_procesador"){
            cin >> pro;
            int f;
            cin >> f;
            cout << "#" << comando << " " << pro << " " << f << '\n';
            clu.baja_proceso_procesador(pro,f);
        }
         else if (comando == "epc" or comando=="enviar_procesos_cluster"){
             int e;
             cin >> e;
             cout << "#" << comando << " " << e << '\n';
             area.enviar_procesos_cluster(e,clu);
        }
         else if (comando == "at" or comando=="avanzar_tiempo"){
             int t;
             cin >> t;
             cout << "#" << comando << " " << t << '\n';
             clu.avanzar_tiempo(t);
        }
         else if (comando == "ipri" or comando=="imprimir_prioridad"){
             cin >> prio;
             cout << "#" << comando << " " << prio << '\n';
             area.imprimir_prioridad(prio);
        }
         else if (comando == "iae" or comando=="imprimir_area_espera"){
             cout << "#" << comando << endl;
             area.imprimir_area_espera();
        }
         else if (comando == "ipro" or comando=="imprimir_procesador"){
             cin >> pro;
             cout << "#" << comando << " " << pro << '\n';
             clu.imprimir_procesador(pro);
        }
         else if (comando == "ipc" or comando=="imprimir_procesadores_cluster"){
             cout << "#" << comando << '\n';
             clu.imprimir_procesadores_cluster();
        }
         else if (comando == "iec" or comando=="imprimir_estructura_cluster"){
             cout << "#" << comando << '\n';
             clu.imprimir_estructura_cluster();
             cout << endl;
        }
         else if (comando == "cmp" or comando=="compactar_memoria_procesador"){
             cin >> pro;
             cout << "#" << comando << " " << pro << '\n';
             clu.compactar_memoria_procesador(pro);
        }
         else if (comando == "cmc" or comando=="compactar_memoria_cluster"){
             cout << "#" << comando << '\n';
             clu.compactar_memoria_cluster();
        }
        cin >> comando;
    }
}
