#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

const int MaxCartas = 10;
const int TamMazo= 52;

struct Carta
{
    string valor;
    string figura;
    int numValor;
};

struct Jugador
{
    string nom;
    int puntos;
    Carta mano[MaxCartas];
    int contCartas=0;
};

struct Partida
{
    string nomJugador;
    string result;
    string fecha;
};

//funcion para crear el mazo
Carta* CrearMazo(){
    Carta* mazo = new Carta[TamMazo];
    string cartaValores[]={"2","3","4","5","6","7","8",
    "9","10","J","Q","K","A"};
    string cartaFiguras[]={"Diamantes","Treboles",
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

//funcion para mezclar las cartas
void mezclarMazo(Carta* mazo){
    for (int i = 0; i < TamMazo; i++)
    {
        int j= rand()%TamMazo;
        Carta momento = mazo[i];
        mazo[i]=mazo[j];//se mueve la carta entre posiciones
        mazo[j]=momento;//mezcla lo de i a j
    }
}

//funcion para el conteo de puntos
int puntos(Jugador j){
    int tot=0;
    int ases=0;
    for (int i = 0; i < j.contCartas; i++)
    {
        tot+=j.mano[i].numValor;//suma los puntos
        if (j.mano[i].valor=="A")//casos de ases se suman
        {
            ases++;
        }
    }
    
    while (tot>21&&ases>0)
    {
        tot-=10;//se resta 10 para cambiar el valor a 1
        ases--;//se decrementa la cantidad de ases
    }
    return tot;
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
        cout <<"Quieres otra carta? (s/n): "<<endl;
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

//funcion de cuando le toca a la computadora
void turnoCompu(Jugador &c, Carta*mazo, int &inicioMazo){
    while (c.puntos<17)
    {
        repartir(c,mazo,inicioMazo);
        cout<< "La computadora tomo una carta"<<endl;
    }
    cout<<"Mano de la computadora: "<<endl;
    for (int i = 0; i < c.contCartas; i++)
    {
        cout << c.mano[i].valor << " de " << c.mano[i].figura <<endl;
    }
    cout << "Los puntos de la computadora son: " << c.puntos<<endl;
}

//funcion para ver quien gano
void ganador(Jugador j, Jugador c){
    if (j.puntos > 21)
    {
        cout << "Gano la computadora" << endl;
    }else if (c.puntos >21)
    {
        cout << "Ganaste" << endl;
    }else if (j.puntos>c.puntos)
    {
        cout << "Ganaste" << endl;
    }else
    {
        cout << "Gano la computadora" << endl;
    }   
}

//funcion para guardar en un archivo
void guardar(Partida p){
    fstream file;
    file.open("Historial.txt", ios::out|ios::trunc);
    if (!file)
    {
        cout  << "No se abrio"<< endl;
    }else
    {
        file << "Fecha: " << p.fecha << "\n";
        file << "Jugador: " << p.nomJugador<< "\n";
        file << "Resultado: " << p.result << "\n";
        file.close();
    }
}

int main(){
    srand(time(NULL));
    Carta* mazo = CrearMazo();
    mezclarMazo(mazo);
    
    Jugador j;
    Jugador c = {"Computadora", 0, {}, 0};
    int inicioMazo = TamMazo-1;//indice del mazo para saber que carta repartir
    //-1 porque los arrays empiezan en 0
    char op;
    
    do {
        j = {"", 0, {}, 0};//valores segun el struct
        c = {"Computadora", 0, {}, 0};//inician vacios
        
        cout << "--- BLACKJACK ---" << endl;
        cout << "Dame tu nombre: ";
        cin >> j.nom;
        
        repartir(j, mazo, inicioMazo);//se da carta numero 1
        repartir(j, mazo, inicioMazo);//carta 2
        repartir(c, mazo, inicioMazo);
        repartir(c, mazo, inicioMazo);
        cout << "\nCarta que tiene la computadora: " << endl;
        cout << c.mano[0].valor << " de " << c.mano[0].figura << endl;
        
        tuTurno(j, mazo, inicioMazo);
        
        if(j.puntos <= 21){
            turnoCompu(c, mazo, inicioMazo);
        }
        
        ganador(j, c);
        
        Partida actual;
        actual.nomJugador =j.nom;

        if (j.puntos <= 21 && (j.puntos > c.puntos || c.puntos > 21))
        {
            actual.result= "Gano";
        }else
        {
            actual.result="Perdio";
        }
        
        //fecha
        int dia=0,mes=0,anio=2025;
        int hora=0,min=0;
        cout << "\nDame la fecha y hora en que se jugo la partida"<< endl;
        cout << "El formato para la fecha sera DIA/MES/ANIO"<<endl;
        cout << "El formato para la hora sera HORA:MINUTOS"<<endl;
        do
        {
            cout << "Dame el dia: "<<endl;
            cin>>dia;
        } while (dia<1 || dia >31);
        do
        {
            cout << "Dame el mes: "<<endl;
            cin>>mes;
        } while (mes<1 || mes >12);

        do
        {
            cout << "Dame la hora (00/24): "<<endl;
            cin>>hora;
        } while (hora<0 || hora >24);

        do
        {
            cout << "Dame los minutos (00/60): "<<endl;
            cin>>min;
        } while (min<0 || min >60);
        
        actual.fecha = to_string(dia) + "/" + to_string(mes) + "/" + to_string(anio) + 
        "\nA las: " + to_string(hora) + ":" + to_string(min);
        guardar(actual);

        cout << actual.fecha << endl;
        
        cout << "\nQuieres jugar otra vez? (s/n): ";
        cin >> op;
        
        if(inicioMazo < 20){//cuando hya menos de 20 cartas el juego se vuelve a mezclar
            //esto evita que se acaben las cartas
            mezclarMazo(mazo);
            inicioMazo = TamMazo-1;
            cout << "Cartas nuevamente mezcladas" << endl;
        }
        
    } while (op=='s' || op=='S');
    
    delete[] mazo;
    cout << "Juego realizado por: " << endl;
    cout << "Ketzary" << endl;
    cout << "Sofia" << endl;
    cout << "Diego" << endl;
    return 0;
}