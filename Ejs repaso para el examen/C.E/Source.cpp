
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

monedas(i,j) = numero minimo de monedas necesario para pagar la cantidad j pudiendo usar las monedas de la 1 a la i

               { monedas(i - 1, j)                                  si Mi > j 
monedas(i,j) = {
               { min(monedas(i - 1, j) , monedas(i, j - Mi) + 1)    si Mi <= j

Casos base:
    - monedas(i,0) = 0
    - monedas(0,j) = INF

Llamada inicial: monedas(N,C)

formas(i,j) = numero de formas distintas de conseguir una cantidad j pudiendo usar las monedas de la 1 a la i

              { formas(i - 1, j)                            si monedas(i - 1, j) < monedas(i, j - Mi) + 1
formas(i,j) = {
              { formas(i, j - Mi)                           si monedas(i - 1, j) > monedas(i, j - Mi) + 1
              {
              { formas(i - 1, j) +  formas(i, j - Mi)       si monedas(i - 1, j) == monedas(i, j - Mi) + 1

Casos base:
    - formas(i,0) = 1 
    - formas(0,j) = 0


Se utiliza programacion dinamica ascendente y se van rellenando ambas recurrencias y sus tablas de N + 1 filas y C + 1 columnas. Como ambas necesitan para calcular la fila i-esima
unicamente la fila i-1-iesima podemos reducir ambas tablas a dos vectores de tamaño C + 1. Esto dejara el coste en espacio adicional en O(2C) = O(C) aunque el coste en tiempo
seguira siendo de O(N*C) debido a que para ambas recurrencias vamos a realizar N*C subproblemas. La recurrencia de las monedas esta explicada en clase y la de formas toma sus valores
en funcion de la de monedas. La solucion queda almacenada en la posicion [N,C]

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
const int INF = 1000000000;

int resolver(const vector<int>& valores, const int N, const int C) {
    vector<int> monedas(C + 1, INF);
    vector<int> formas(C + 1, 0);
    monedas[0] = 0;
    formas[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        for (int j = valores[i-1]; j <= C; j++)
        {
            int v1 = monedas[j];
            int v2 = monedas[j - valores[i - 1]] + 1;

            monedas[j] = min(monedas[j], monedas[j - valores[i - 1]] + 1);

            if (v1 > v2) {
                formas[j] = formas[j - valores[i - 1]];
            }
            else if(v1 == v2) 
                formas[j] += formas[j - valores[i - 1]];
            
        }
    }
    return formas[C];
}

bool resuelveCaso() {

    int C, N;
    cin >> C >> N;
    if (!std::cin)
        return false;
    vector<int> valores(N);
    for (int& i : valores)
        cin >> i;

    cout << resolver(valores, N, C) << "\n";
    
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
