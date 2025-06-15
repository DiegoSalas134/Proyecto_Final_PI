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
    for (int i =0; i<4; i++)
    {
        string figura = cartaFiguras[i];
        for (int j=0;j<13;j++)
        {
            string valor= cartaValores[j];
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
            
            inicio++;
        }
        
    }
    return mazo;
}

//funcion para mezclar aleatoriamente
void mezclarMazo(Carta* mazo){
    for (int i = 0; i < TamMazo; i++)
    {
        int j= rand()%TamMazo;
        Carta momento = mazo[i];
        mazo[i]=mazo[j];//se mueve la carta entre posiciones
        mazo[j]=momento;//mezcla lo de i a j
    }
    
}


int main(){
    srand(time(NULL));
    Carta* mazo=CrearMazo();
    mezclarMazo(mazo);
    cout <<"\nLas cartas son: "<<endl;
    for (int i = 0; i < 5; i++)
    {
        cout << mazo[i].valor << " de " << mazo[i].figura << endl;
    }
    
    return 0;
}