/** @file Proces.hh
    @brief Especificació de la classe Proces
*/

#ifndef PROCES_HH
#define PROCES_HH


#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;

/** @class Proces
    @brief Representa un proces
*/

class Proces {

private:
   int nom; //identificador
   int memoc; //memòria que ocupa el procés
   int temps;  //temps que triga en executar el procés
   int restant; //temps que li queda al proces per finalitzar

public:

    //Creadors

    /** @brief creadora per defecte
     * \pre cert
     * \post crea un proces buit
    */
    Proces();

    //Consultors

    /** @brief retorna l'identificador
    \pre cert
    \post retorna l'identificador del p. i.
    */
    int consulta_nom()const;

    /** @brief retorna la memoria que ocupa
    \pre cert
    \post retorna la memoria que ocupa el p. i.
    */
    int consultar_memoc()const;

    /** @brief retorna el temps que triga
    \pre cert
    \post retorna el temps que triga el p. i.
    */
    int consultar_temps()const;

    /** @brief retorna el temps restant que li queda per finalitzar el proces
    \pre cert
    \post retorna el temps que li queda al p. i.
    */
    int consultar_restant()const;

    //Modificadors

    /** @brief modifica el temps restant
    \pre t es el temps transcorregut
    \post temps passa a valer el temps que li falta per acabar d'executar el proces
    */
    void treure_temps(int& t);

    //Lectura i escriptura

    /** @brief operació de lectura
    \pre cert
    \post el p. i. passa a tenir tots els atributs
    */
    void llegeix_proces();

    /** @brief operació d'escriptura
    \pre cert
    \post s'han escrit els atributs del p. i. al parametre de sortida
    */
    void escriu_proces()const;


};



#endif
