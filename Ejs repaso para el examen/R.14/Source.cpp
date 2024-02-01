/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>

luces(i,j) = coste minimo que cuesta la instalacion pudiendo usar las bombillas de la 1 a la i y necesitando una potencia j.

             {  luces(i-1,j)                                  si Pi > j
luces(i,j) = {                                                                      Siendo Pi la pot de la bombilla i e Ci su coste
             {  min(luces(i-1,j) , luces(i, j - Pi) + Ci)     si Pi <= j

 Casos base:
    - luces(0,j) = Infinito
    - luces(i,0) = 0

Llamada inicial luces(N,Pmax) que va a generar la solucion en la ultima fila de la matriz y será el minimo valor de esa fila y su indice. 
Se utiliza programacion dinamica ascendente y se va rellenando desde los casos basicos la matriz de tamaño N + 1, Pmax + 1. Se puede reducir el espacio adicional a un vector si nos
damos cuenta de que solo es necesaria la fila actual y la anterior. De esta manera en el calculo de la solucion podemos rellenar la matriz de arriba a abajo y de izquierda a 
derecha hasta tener la solución almacenada en la posicion [N][Pmax]. El coste en tiempo es del orden de O(N * Pmax) y a pesar de tener que recorrer la ultima fila de la matriz de
soluciones esto no aumentara el coste. El coste en espacio es del orden de O(N * Pmax) si utilizamos la matriz y O(Pmax) si solo utilizamos un vector.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tSol {
    EntInf coste;
    int pot;
};

//tSol resolver(const vector<int>& potencias, const vector<int>& costes, const int N, const int Pmin, const int Pmax) {
//    EntInf costeMin = Infinito;
//    int pot = -1;
//    vector<EntInf> luces(Pmax + 1, Infinito);
//    luces[0] = 0;
//    for (int i = 1; i <= N; i++)
//    {
//        for (int j = potencias[i-1]; j <= Pmax ; j++)
//        {
//           luces[j] = min(luces[j], luces[j - potencias[i - 1]] + costes[i - 1]);
//        }
//    }
//    
//    for (int j = Pmin; j <= Pmax; j++)
//    {
//        if (costeMin > luces[j]) {
//            costeMin = luces[j];
//            pot = j;
//        }
//    }
//    return { costeMin, pot };
//}

tSol resolver(const vector<int>& potencias, const vector<int>& costes, const int N, const int Pmin, const int Pmax) {
    EntInf costeMin = Infinito;
    int pot = -1;
    Matriz<EntInf> luces(N+1,Pmax + 1, Infinito);
    luces[0][0] = 0;
    for (int i = 1; i <= N; i++)
    {
        luces[i][0] = 0;
        for (int j = 1; j <= Pmax; j++)
        {
            if (potencias[i - 1] > j)
                luces[i][j] = luces[i - 1][j];
            else
                luces[i][j] = min(luces[i - 1][j], luces[i][j - potencias[i - 1]] + costes[i - 1]);
           
        }
    }
  
    for (int j = Pmin; j <= Pmax; j++)
    {
        if (luces[N][j] < costeMin) {
            costeMin = luces[N][j];
            pot = j;
        }
            
    }
    return { costeMin, pot };
}

bool resuelveCaso() {

    // leer los datos de la entrada

    int N, Pmax, Pmin;
    cin >> N >> Pmax >> Pmin;

    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> potencias(N);
    vector<int> costes(N);
    for (int i = 0; i < N; i++)
    {
        cin >> potencias[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> costes[i];
    }
    tSol sol = resolver(potencias, costes, N, Pmin, Pmax);
    if (sol.coste != Infinito)
        cout << sol.coste << " " << sol.pot << "\n";
    else
        cout << "IMPOSIBLE\n";
   

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
