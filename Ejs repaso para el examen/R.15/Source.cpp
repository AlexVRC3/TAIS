
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

veces(i,j) = numero minimo de veces que hay que realizar la llamada a trim para borrar por completo una palabra que va de la i a la j.
                
             { veces(i + desp_I, j - desp_J) + 1                si palabra[i] = palabra[j]
veces(i,j) = {
             { min(veces(i + desp_I,j) , veces(i,j - desp_J)    si palabra[i] != palabra[j]

      desp_I = # c: i <= c < j: palabra[c] = palabra[i]
      desp_J = # c: i < c <= j : palabra[c] = palabra[j]

Casos base:
    veces(i,i) = 1
    veces(i,j) con i > j es 0

Llamada inicial: veces(i,j)

Se utiliza programacion dinamica descendente y se da solucion a los subproblemas que no esten resueltos para no repetir calculos innecesarios. La matriz es de tamaño N * N y los casos
que nos importan estan en la parte superior de la matriz si la miramos una vez partida por su diagonal principal. Los casos basicos son la diagonal principal que toman todos valor 1
porque habria que hacer minimo 1 llamada para borrar un unico caracter. El resto de casos de la parte inferior son 0 y son casos no considerados. La solucion quedará almacenada
en la posicion arriba a la derecha de la matriz [0][N-1]. El coste en tiempo es del orden de O(N*N) ya que se resuelven N*N subproblemas y cada uno de ellos solo genera trabajo 1 vez
debido a que el resultado ya estará guardado. El coste en espacio adicional es del orden de O(N*N) debido a la matriz donde almacenamos los resultados del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int desp_I(const string& palabra, int i, int j) {
    int desp = 0;
    while (i + desp < j && palabra[ i + desp] == palabra[i])
        desp++;
    return desp;
}

int desp_J(const string& palabra, int i, int j) {
    int desp = 0;
    while (j - desp > i && palabra[j - desp] == palabra[j])
        desp++;
    return desp;
}

int veces(const string& palabra, int i, int j, Matriz<int>& m) {
    
    int& res = m[i][j];
    if (res == -1) {
        if (i > j) res = 0;
        else if (i == j) res = 1;
        else if (palabra[i] == palabra[j]) {
                res = veces(palabra, i + desp_I(palabra,i,j), j - desp_J(palabra,i,j), m) + 1;
        }
        else {
                res = min(veces(palabra,  i + desp_I(palabra, i, j), j, m) , veces(palabra, i, j - desp_J(palabra, i, j), m)) + 1;
        }
    }
    
    return res;
}


bool resuelveCaso() {

    string palabra;
    cin >> palabra;

    if (!std::cin)  // fin de la entrada
        return false;
    int N = palabra.size();
    Matriz<int> m(N, N, -1);
    cout << veces(palabra, 0, N - 1, m) << endl;
    
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
