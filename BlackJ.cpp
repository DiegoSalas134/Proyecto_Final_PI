#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Estructuras de datos

const int MaxCartas = 10;
const int TamMazo= 52;

//Estructura de carta
struct Carta
{
    string valor;
    string figura;
    int numValor;
};

//Estructura de Jugador
struct Jugador
{
    string nom;
    int puntos;
    int dinero;
    Carta mano[MaxCartas];
    int contCartas=0;
};

//Estructura de la partida en curso (historial)
struct Match
{
    string nomJugador;
    string result;
    string fecha;
};

//funcion para crear mazo

Carta* CrearMazo(){
    Carta* mazo = new Carta[TamMazo];
    string cartaValores[]={"2","3","4","5","6","7","8"
    "9","10","J","K","Q","A"};
    string cartaFiguras[]={"Diamantes","Treboles"
    "Corazones","Picas"};
    
    int inicio=0;
    for (string figura: cartaFiguras)
    {
        for (string valor: cartaValores)
        {
            mazo[inicio].valor = valor;
            mazo[inicio].figura= figura;

            if (valor == "A")
            {
                mazo[inicio].numValor=11;
            }
            else if (valor=="J" || valor=="Q" || valor =="K")
            {
                mazo[inicio].numValor = 10;
            }
            else
            {
                mazo[inicio].numValor=stoi(valor);
                //basicamente los valores que estan entre comillas
                //ejemplo "2" lo convierte de string a int siendo ahora 2
            }
            
            
        }
        
    }
    
}

int main(){
    srand(time(NULL));
    return 0;
}