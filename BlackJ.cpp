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
    int puntos=0;
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

int puntos(Jugador j){
    int totalpuntos=0;
    int ases=0;
 for (int i = 0; i < j.contCartas; i++)
    {
        totalpuntos+=j.mano[i].numValor;//suma los puntos
        if (j.mano[i].valor=="A")//casos de ases se suman
        {
            ases++;
        }
    }
    
    while (totalpuntos>21&&ases>0)
    {
        totalpuntos-=10;//se resta 10 para cambiar el valor a 1
        ases--;//se decrementa la cantidad de ases
    }
    return totalpuntos;
}

//funcion para repartir cartas
void repartir(Jugador &j, Carta* mazo, int &inicioMazo){
    if (inicioMazo >=0 && j.contCartas <MaxCartas)
    {
        j.mano[j.contCartas]=mazo[inicioMazo];
        j.contCartas++;
    }

   j.puntos=puntos(j);//se actualizan los puntos
    inicioMazo--;//se elimina la carta
}

//funcion de cuando le toca al jugador
void tuTurno(Jugador &j, Carta*mazo, int &inicioMazo){
    char op;
    do
    {
        cout <<"Tu mano, " << j.nom <<": "<<endl;
        for (int i = 0; i < j.contCartas; i++)
        {
            cout << j.mano[i].valor << " de " << j.mano[i].figura <<endl;
        }
        cout << "Tus puntos son: " << j.puntos<<endl;
        cout <<"¿Quieres otra carta? (s/n): "<<endl;
        cin>>op;
        if (op=='S' || op=='s')
        {
            repartir(j,mazo,inicioMazo);
            if (j.puntos>21)
            {
                cout << "Te pasaste de 21"<<endl;
                cout <<"Pierdes esta ronda"<<endl;
                cout <<"Con un total de: " << j.puntos << " Puntos"<<endl;
                break;
            }
        }
    } while (op=='S' || op=='s');
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
    Jugador j;
    int inicioMazo = TamMazo-1;//indice del mazo para saber que carta repartir
    //-1 porque los arrays empiezan en 0
    char op;
    
    do {
        j = {"", 0, {}, 0};//valores segun el struct
        cout << "--- BLACKJACK ---" << endl;
        cout << "Dame tu nombre: ";
        cin >> j.nom;
        
        repartir(j, mazo, inicioMazo);//se da carta numero 1
        repartir(j, mazo, inicioMazo);//carta 2
        
        tuTurno(j, mazo, inicioMazo);
        cout << "\nQuieres jugar otra vez? (s/n): ";
        cin >> op;
    } while(op=='S'||op== 's');
        
     
        cout << "Juego realizado por: " << endl;
        cout << "Ketzary" << endl;
        cout << "Sofia" << endl;
        cout << "Diego" << endl;

    
    return 0;
}