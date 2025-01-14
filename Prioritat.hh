/** @file Prioritat.hh
    @brief Especificació de la classe Prioritat
*/

#ifndef PRIORITAT_HH
#define PRIORITAT_HH

#include "Proces.hh"

#ifndef NO_DIAGRAM
#include "Cluster.hh"
#include <string>
#include <list>
#include <iostream>
#include <set>
#endif

using namespace std;

/** @class Prioritat
    @brief Representa una prioritat
*/

class Prioritat {

private:

    string ide;
    list <Proces>cua;
    set<int> pr;
    int pacceptat;
    int prefusat;

public:

    //Constructors

    /** @brief creador per defecte
     * \pre cert
     * \post crea una prioritat buida
    */
    Prioritat();

    /** @brief creadora amb un identificador
    \pre id es l'identificador d'una prioritat
    \post crea una prioritat buida amb l'identificador id
    */
    Prioritat(const string& id);

    //Consultors

    /** @brief retorna l'identificador de la prioritat
    \pre cert
    \post retorna l'identificador de la prioritat
    */
    string consultar_ide()const;

    /** @brief retorna el nombre de processos acceptats
    \pre cert
    \post retorna el numero de processos acceptats
    */
    int consultar_pacceptat()const;

    /** @brief retorna el nombre de processos refusats
    \pre cert
    \post retorna el numero de processos refusats
    */
    int consultar_prefusat()const;

    /** @brief retorna true si la prioritat esta lliure de processos, fals altrament
    \pre cert
    \post retorna true si la prioritat esta lliure de processos , fals altrament
    */
    bool baixa_la_prioritat()const;

    //Modificadors

     /** @brief envia com a maxim els processos restants(res) de la prioritat al cluster i retorna el numero de processos enviats
    \pre restant són els processos màxims que ha d'enviar i clu es el cluster destinatari
    \post s'han enviat a clu els maxims processos del p. i.
    */
    void enviar(int& n, Cluster& clu);

    /** @brief afegeix un proces a la prioritat
    \pre pro es un proces
    \post pro s'afegeix a la prioritat
    */
    void afegeix(const Proces& pro);


    //Lectura i escriptura

    /** @brief operació de lectura
    \pre cert
    \post omple els atributs de la prioritat del p. i.
    */
    void llegeix_prioritat();

    /** @brief operació d'escriptura
    \pre el p. i. no es buit
    \post escriu en el canal de sortida els atributs del p. i.
    */
    void escriu_prioritat()const;


};


#endif
