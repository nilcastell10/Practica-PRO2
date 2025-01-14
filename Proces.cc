/** @file Proces.cc
    @brief Implementació de la classe Proces
*/

#include "Proces.hh"
using namespace std;

Proces::Proces()
{
    nom=0;
    memoc=0;
    temps=0;
    restant=0;
}

int Proces::consulta_nom()const
{
    return nom;
}

int Proces::consultar_memoc()const
{
    return memoc;
}

int Proces::consultar_temps()const
{
    return temps;
}

int Proces::consultar_restant()const
{
    return restant;
}

void Proces::treure_temps(int& t)
{
    if (t<=restant){
        restant=restant-t;
    }
    else restant=0;
}

void Proces::llegeix_proces()
{
    cin >> nom >> memoc >> temps;
    restant=temps;
}

void Proces::escriu_proces()const
{
    cout << nom << " " << memoc << " " << restant << '\n';
}
