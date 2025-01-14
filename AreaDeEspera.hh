/** @file AreaDeEspera.hh
    @brief Especificació de la classe AreaDeEspera
*/

#ifndef AREADEESPERA_HH
#define AREADEESPERA_HH

#include "Cluster.hh"
#include "Proces.hh"
#include "Prioritat.hh"


#ifndef NO_DIAGRAM
#include <map>
#include <iostream>
#include <string>
#endif
using namespace std;

/** @class AreaDeEspera
    @brief Representa una Area d'Espera
*/

class AreaDeEspera {

private:

    map <string, Prioritat> espera;

public:

    //Creadors

    /** @brief creadora per defecte
     * \pre cert
     * \post crea una area d'espera buida
    */
    AreaDeEspera();

    //Modificadors

    /** @brief envia un nombre de processos al cluster
    \pre n es un enter>0 i clu es el cluster al que s'envien els processos
    \post s'intenten enviar n processos pendents al cluster per ordre de prioritats, no s'atura fins que s'hagin enviat els n processos, o fins que no quedin més processos pendents o fins que tots els que quedin pendents ja s'hagin intentat col.locar sense exit. Si un proces no s'ha pogut col.locar, es torna a enviar a l'area d'espera com si fos nou, amb la mateixa prioritat. Si un procés es pot col·locar a més d'un processador, es tria el que disposi un buit més ajustat respecte a aquest procés. En cas d'empat entre diversos processadors, es designa el que quedi amb més memòria lliure. Si l'empat persisteix, s'escull el més proper a l'arrel de l'arbre de processadors i si encara és necessari desempatar, el de més a l'esquerra
    */
    void enviar_procesos_cluster(int n, Cluster& clu);

    /** @brief afegeix una nova prioritat
    \pre p es un identificador de prioritat
    \post si p existeix al p. i. s'envia un missatge d'error, d'altra banda, s'afegeix aquesta prioritat sense processos pendents
    */
    void alta_prioridad(const string& p);

    /** @brief s'elimina una prioritat
    \pre p es un identificador de prioritat
    \post si p no existeix al p. i. o si te processos pendents s'envia un missatge d'error, sino, s'elimina la prioritat
    */
    void baja_prioridad(const string& p);

    /** @brief afegeix un proces a una prioritat
    \pre p es un identificador de prioritat i pro un proces
    \post llegeix les dades d'un proces, si p no existeix al p. i. o si ja hi ha un proces amb el mateix identificador a aquesta prioritat, s'envia un missatge d'error, sino, s'afegeix el proces a la prioritat d'identificador p
    */
    void alta_proceso_espera(const string& p, const Proces& pro);

    //Lectura i escriptura

    /** @brief operació de lectura
    \pre n enter>0
    \post llegeix una area d'espera amb n prioritats
    */
    void llegeix_AreaDeEspera(int& n);

    /** @brief escriu una prioritat
    \pre p es un identificador de prioritat
    \post si no hi ha una prioritat amb el mateix identificador a l'àrea d'espera, s'imprimeix un missatge d'error. En cas contrari, s'escriuen els processos pendents d'aquesta prioritat per ordre decreixent d'antiguitat, des de la darrera alta. A més, escriu el nombre de processos de la prioritat col·locats al clúster per l'operació enviar_procesos_cluster i el nombre de rebutjos (un mateix procés compte tantes vegades com rebutjos hagi patit)
    */
    void imprimir_prioridad(const string& p)const;

    /** @brief operació d'escriptura
    \pre cert
    \post escriu els processos pendents de totes les prioritats de l'àrea d'espera per l'ordre creixent de prioritat. Per a cada prioritat s'escriu el mateix que en la funcionalitat imprimir_prioridad
    */
    void imprimir_area_espera()const;
};
#endif
