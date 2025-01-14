/** @file Processador.hh
    @brief Especificació de la classe Processador
*/

#ifndef PROCESSADOR_HH
#define PROCESSADOR_HH

#include "Proces.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#endif

using namespace std;

/** @class Processador
    @brief Representa un processador
*/

class Processador {

private:

    string id;
    int capacitat;
    int memlliure;
    map<int,Proces>pos_proces;
    map<int,int>id_pos;
    map<int,set<int>>espais;

public:

    //Creadors

    /** @brief creadora per defecte
     * \pre cert
     * \post crea un processador buit
    */
    Processador();

    /** @brief creadora amb un identificador
     * \pre ide es l'identificador d'un processador
     * \post crea un processador buit amb identificador ide
    */
    Processador(const string& ide);

     /** @brief creadora amb un identificador i memoria
     * \pre ide es l'identificador d'un processador i me la memoria que te
     * \post crea un processador buit amb identificador ide i memoria me
    */
    Processador(const string& ide, int& me);

    //Consultors

     /** @brief retorna la memoria que te lliure el processador
    \pre cert
    \post retorna la memoria que queda lliure del p. i.
    */
    int consultar_memlliure()const;

     /** @brief retorna l'espai mes ajustat al que cap el proces
    \pre cert
    \post retorna l'espai mes ajustat al que cap el proces del p. i.
    */
    int hueco_ajustado(const Proces& pro)const;

    /** @brief retorna true si el proces cap, false altrament
    \pre cert
    \post retorna true si el proces cap, false altrament
    */
    bool cabe_proceso(const Proces& pro)const;

    /** @brief retorna l'dentificador
    \pre cert
    \post retorna l'id del p. i.
    */
    string consulta_id()const;

    /** @brief retorna la memòria del processador
    \pre cert
    \post retorna memoria del p. i.
    */
    int consulta_capacitat()const;

    /** @brief retorna true si el processador conte processos, else altrament
    \pre cert
    \post retorna true si el p. i. conte processos, else altrament
    */
    bool te_processos()const;

     /** @brief retorna true si el processador conte el proces pro, else altrament
    \pre cert
    \post retorna true si el p. i. conte el proces pro, else altrament
    */
    bool existeix_proces(const int& nom)const;

    //Modificadors

    /** @brief actualitza els temps dels processadors i elimina els processos finalitzats
    \pre t es el temps transcorregut
    \post a tots els processos del p. i. se'ls hi ha actualitzat el temps i s'han eliminat els processos finalitzats
    */
    void actualitza(int& t);

    /** @brief comprimeix la memòroia del processador
    \pre el p. i. te espais buits a la memoria entre processos
    \post el p. i. ja no te espais buits entre els processos
    */
    void comprimeix();

    /** @brief afegeix un proces al processador
    \pre pro es un proces
    \post pro s'ha afegit a aquest processador a la posicio mes petita que cap
    */
    void afegeix_proces(const Proces& pro);

    /** @brief elimina un proces del processador
    \pre f es un identificador d'un proces
    \post pro s'elimina del p. i.
    */
    void elimina_proces(int& f);

    //Lectura i escriptura

    /** @brief operació de lectura
    \pre cert
    \post el p. i. passa a tenir tots els atributs
    */
    void llegeix_processador();

    /** @brief operació d'escriptura
    \pre cert
    \post s'han escrit els atributs del p. i. al parametre de sortida
    */
    void escriu_processador()const;

};


#endif
