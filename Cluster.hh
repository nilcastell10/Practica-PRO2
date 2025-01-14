/** @file Cluster.hh
    @brief Especificació de la classe Cluster
*/

#ifndef CLUSTER_HH
#define CLUSTER_HH

#include "Processador.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <map>
#include <iostream>
#include <list>
#include <queue>
#endif

using namespace std;

/** @class Cluster
    @brief Representa un cluster
*/

class Cluster {

private:

    BinTree<string>clu;
    map<string,Processador>mapa;

    /** @brief Envia un processador al cluster per trobar un processador que tingui les millors caracteristiques per poder-lo afegir
     * \pre passat false, pr es un identificador de processador buit, alcada es 0, alcaux es 0 i pro el proces que volem afegir
     * \post passat sera true si s'ha aconseguit trobar el processador indicat al cluster, fals altrament
     */
    void passa(bool& passat, const BinTree<string>& clu, string& pr,int alcada, int& alcaux, const Proces& pro);

     /** @brief si es compleixen les condicions, aquesta funció modifica el processador amb identificador p i el canvia pel cluster nou
     * \pre el processador amb identificador id existeix al cluster i no té processos executant-se i nou es el cluster que volem afegir
     * \post si el processador amb identificador p no té processadors auxiliars, es modifica l'arbre
     */
    void modificar(const string& p, const Cluster& nou, BinTree<string>& a);

     /** @brief imprimeix l'estructura del cluster
     * \pre cert
     * \post imprimeix l'estructura del cluster
     */
    void estructura(const BinTree<string>& clu);

     /** @brief llegeix un cluster nou
     * \pre cert
     * \post llegeix un cluster nou
     */
    void leer_cluster(BinTree<string>& a);

public:

    //Creadors

    /** @brief creadora per defecte
     * \pre cert
     * \post crea un cluster buit
    */
    Cluster();

    //Modificadors

    /** @brief retorna true si el proces s'ha pogut afegir al cluster i fals altrament
    \pre p es un proces
    \post s'ha intentat afegir el proces al cluster i es retorna true si s'ha aconseguit i fals altrament
    */
    void passa_cluster(const Proces& p,bool& passat);

    /** @brief afegeix al cluster un cluster nou
    \pre p es un identificador d'un proces i nou un cluster abans llegit
    \post si p no existeix al p. i. o te processos en execució o te processadors auxiliars envia un missatge d'error, d'altra banda, afegeix el cluster nou al original amb l'arrel del nou cluster p
    */
    void modificar_cluster(const string& p, const Cluster& nou);

    /** @brief s'afegeix el proces al processador
    \pre id es l'identificador d'un processador i p un proces
    \post si no existeix el processador al clúster o ja conté un procés amb el mateix identificador o el procés no es pot col·locar al processador, s'imprimeix un missatge derror. En cas contrari, el procés passa a executar-se a aquest processador i la memòria que utilitza passa a estar ocupada. El procés es col·loca en la posició més petita que deixi el buit més ajustat
    */
    void alta_proceso_procesador(const string& id,const Proces& p);

    /** @brief elimina el proces d'un processador
    \pre p es l'identificador d'un processador i f el d'un proces
    \post si el processador no existeix o el procés no és al processador, s'imprimeix un missatge derror. En cas contrari, s'elimina el procés del processador
    */
    void baja_proceso_procesador(const string& p, int& f);

    /** @brief avança el temps
    \pre t es un enter positiu
    \post s'avança el temps t unitats, s'eliminen els processos que hagin acabat i els que no han acabat han avançat t unitats de temps
    */
    void avanzar_tiempo(int& t);

    /** @brief compacta la memòria d'un processador
    \pre id es l'identificador d'un processador
    \post si no existeix un processador amb el mateix identificador en el clúster s'imprimeix un missatge d'error. En cas contrari, se mouen tots els processos cap al principi de la memòria del processador, sense deixar espais, sense solapar-se i respectant l'ordre inicial
    */
    void compactar_memoria_procesador(const string& id);

    /** @brief compacta la memòria de tots els processadors del cluster
    \pre existeixen espais de memoria buits entre els ocupats pels processos
    \post en cada processador, se mouen tots els processos cap el principi de la memòria, sense deixar espais, sense solapar-se i respectant l'ordre inicial
    */
    void compactar_memoria_cluster();

    //Lectura i escriptura

    /** @brief operació de lectura
    \pre cert
    \post llegeix un nou cluster
    */
    void llegeix_cluster();

    /** @brief lectura d'un nou cluster i elimina els anteriors
    \pre n es un enter>0
    \post llegeix un nou cluster i elimina els anteriors
    */
    void configurar_cluster();

    /** @brief operació d'escriptura  d'un processador
    \pre id es l'identificador d'un processador
    \post si no existeix un processador amb el mateix identificador en el clúster se imprime un missatge de error. En cas contrari, s'escriuen els processos del processador per ordre creciente de primera posició de memòria, incloent dicha posició i el resto de dades de cada procés. El temps que escriu és el temps que falta per a que el procés acabe, no el temps inicial d'execució
    */
    void imprimir_procesador(const string& id)const;

    /** @brief operació d'escriptura de tots els processadors del cluster
    \pre cert
    \post escriu tots els processadors del clúster per orden creciente d'identificador. Per cada processador escriu el mateix que en la funcionalitat imprimir_procesador
    */
    void imprimir_procesadores_cluster()const;

    /** @brief operació d'escriptura de l'estructura dels processadors del cluster
    \pre cert
    \post escriu la estructura de processadors del cluster
    */
    void imprimir_estructura_cluster();



};

#endif
