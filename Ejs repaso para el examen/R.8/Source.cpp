
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"

/*@ <answer>

coste_minimo(i,j) = coste minimo de ir del pueblo i al j

                    
coste_minimo(i,j) = Pt k: i < k <= j : min(coste_min(i,j), Aik + coste_min(k,j)      (Aik es lo que cuesta el alquiler si vas con una canoa del pueblo i al k)

CASOS BASE:
    - coste_minimo(i,i) = 0 porque no nos movemos a ningun pueblo

Utilizo programacion dinamica ascendente y se va rellenando la matriz por diagonales. La matriz es de tamaño NxN y la diagonal d = 0 o la principal es la que se rellena
en los casos base. Las posiciones por debajo de la diagonal no estan consideradas en este problema. La solucion al problema queda guardada en las posiciones de la matriz que hemos
ido rellenando las cuales vienen a ser todas las diagonales por encima de la principal. El coste en tiempo es del orden de O(N^3) debido a que utilizamos 3 bucles for 2 para recorrer
las diagonales y uno para el coste minimo. El coste en espacio adicional es O(1) ya que la matriz que se utiliza dentro del metodo de programacion dinamica es la que utilizamos para imprimir la solucion.

                    
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int Infinito = 1000000000;

Matriz<int> coste_min(const Matriz<int>& alquileres) {
    int N = alquileres.numfils();
    Matriz<int> coste_min(N, N, Infinito);

    //Inicializo la diagonal con los casos basicos
    for (int i = 0; i < N; i++)
    {
        coste_min[i][i] = 0; 
    }

    for (int d = 1; d < N; d++) // Recorre diagonales
    {
        for (int i = 0; i < N - d; i++) // Recorre elementos de la diagonal
        {
            int j = i + d;
            for (int k = i + 1; k <= j; k++) 
            {
                coste_min[i][j] = min(coste_min[i][j], alquileres[i][k] + coste_min[k][j]);
            }
        }
    }
    return coste_min;
}


bool resuelveCaso() {

    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> alquileres(N, N);
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            cin >> alquileres[i][j];
        }
    }

    Matriz<int> sol = coste_min(alquileres);
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i+1; j < N; j++)
        {
            cout << sol[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

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
