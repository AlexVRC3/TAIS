/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"

/*@ <answer>
* 
* Ahora creo que si que está bien definida la recurrencia ya que ayer al buscar otra forma de expresar la solución me confundi.

NOTACIONES
----------
 C = Cantidad a pagar con las monedas
 N = Numero de monedas distintas (tipos)
 Vi = Valor de la moneda i

 RECURSION
 ---------

 monedas(i,j) = minimo numero de monedas que hacen falta para pagar la cantidad j pudiendo utilizando monedas desde 1 hasta la i

                { monedas(i - 1, j)                                 si Vi > j
 monedas(i,j) = {
                { min(monedas(i - 1, j) , monedas(i, j - Vi) + 1)   si Vi <= j

 Casos base:

 monedas(i,0) = 0
 monedas(0,j) = Infinito


 formas(i,j) = numero de formas de pagar la cantidad j usando el minimo numero de monedas pudiendo utilizar monedas desde la 1 hasta la i

               { formas(i, j - Vi)                          si monedas(i,j - Vi) + 1 < monedas(i - 1, j)    
               {                     
 formas(i,j) = { formas(i - 1, j)                           si monedas(i,j - Vi) + 1 > monedas(i - 1, j)    
               { 
               { formas(i - 1, j) + formas(i, j - Vi)       si monedas(i, j - Vi) + 1 == monedas(i - 1,j) 
              
              

Casos base:

 formas(0,j) = 0
 formas(i,0) = 1

 EXPLICACION Y COSTE
 -------------------

 Utilizamos programación dinamica ascendente. Debido a que solo necesitamos posiciones de la fila superior y de la misma fila podemos reducir el espacio
 de dos matrices a utilizar dos vectores y asi respetamos la restriccion de O(C) en espacio adicional. Al rellenar de izquierda a derecha los vectores tendremos
 en la parte izquierda del vector los datos de la fila i y a la derecha los de la fila i - 1 previamente calculados. La solución quedará almacenada
 en la ultima posicion del vector [C].

 El coste en espacio adicional es O(2 * C) = O(C) debido al uso de los 2 vectores para las 2 recurrencias.
 El coste en tiempo es O(N * C) por el recorrido de las dos matrices.

 @ </answer> */



 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int resolver(int C, const vector<int>& valores) {
    int N = valores.size();

    vector<EntInf> monedas(C + 1, Infinito);
    vector<int> formas(C + 1, 0);

    formas[0] = 1;
    monedas[0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = valores[i - 1]; j <= C; ++j) {
            if (monedas[j] == monedas[j - valores[i - 1]] + 1) {
                formas[j] += formas[j - valores[i - 1]];
            }
            else if (monedas[j - valores[i - 1]] + 1 < monedas[j]) {
                formas[j] = formas[j - valores[i - 1]];
                monedas[j] = monedas[j - valores[i - 1]] + 1;
            }

        }
    }
    return formas[C];
}



bool resuelveCaso() {

    int N, C;
    cin >> C;

    if (!std::cin)  // fin de la entrada
        return false;
    cin >> N;
    vector<int> monedas(N);
    for (int i = 0; i < N; i++)
    {
        cin >> monedas[i];
    }

    cout << resolver(C, monedas) << endl;
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