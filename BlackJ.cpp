#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

//Estructuras de datos

//Estructura de carta
struct Card
{
    string value;
    string figure;
    int numValue;
};

//Estructura de Jugador
struct Player
{
    string name;
    int points;
    int money;
    vector<Card> cards; //vector de la mano del jugador
};

//Estructura de la partida en curso (historial)
struct Match
{
    string nameOFplayer;
    string result;
    string date;
};

//Creamos el mazo de cartas y lo mezclamos
vector<Card> createDeck(){
    
}