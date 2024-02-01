/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


#include "Matriz.h"


/*@ <answer>

NOTACIONES
    Cancion1i, Cancion2j: Canciones en la posición i de la lista de reproducción 1 y la posición j de la lista de reproducción 2, respectivamente.
    N, M: Número de canciones en la lista de reproducción 1 y 2, respectivamente.

RECURSIÓN
    longestPlaylist(i, j): Longitud de la subsecuencia común más larga entre las primeras i canciones de la lista de reproducción 1 y las primeras j canciones de la lista de reproducción 2, siguiendo las reglas de no repetición y mantenimiento del orden.

                                { 0,                                                              si i = 0 ó j = 0              Caso base
    longestPlaylist(i, j) =     {
                                { longestPlaylist(i - 1, j - 1) + 1,                              si Cancion1i = Cancion2j      Caso Recursivo
                                {
                                { max(longestPlaylist(i - 1, j), longestPlaylist(i, j - 1)),      de lo contrario

EXPLICACIÓN Y COSTE
    La solución se basa en programación dinámica ascendente para construir una tabla de tamaño N x M. La función recursiva longestPlaylist se usa para llenar esta tabla desde
    la esquina superior izquierda hasta la inferior derecha, siguiendo la definición de la función.

    Para cada par de canciones (i, j), comparamos Cancion1i y Cancion2j. Si son iguales, sumamos 1 a la longitud de la subsecuencia común más larga hasta i - 1, j - 1. Si no son iguales,
    tomamos el máximo entre longestPlaylist(i - 1, j) y longestPlaylist(i, j - 1), lo que nos da la longitud máxima de la subsecuencia común sin incluir la canción actual de una o ambas listas.

    El resultado del problema, es decir, la longitud de la lista de reproducción más larga posible, se encuentra en longestPlaylist(N, M).

    Coste en Tiempo: O(N * M), porque necesitamos recorrer toda la tabla, y para cada celda (i, j), las operaciones son de tiempo constante.
    Coste en Espacio: O(N * M), debido a la tabla de tamaño N x M utilizada para almacenar los resultados intermedios.

RECONSTRUCCION DEL VECTOR SOLUCION

    Si dp[i][j] es mayor que dp[i-1][j] y dp[i][j-1], y Cancion1i es igual a Cancion2j, significa que esta canción es parte de la subsecuencia común. La agregamos a nuestra secuencia y movemos los índices i y j a i-1 y j-1, respectivamente.
    Si no, movemos i a i-1 si dp[i-1][j] es mayor que dp[i][j-1], o movemos j a j-1 en caso contrario.
    Repetir Hasta Alcanzar el Inicio: Repetimos este proceso hasta que i o j llegue a 0.

    Invertir la Secuencia: La secuencia reconstruida está en orden inverso, ya que comenzamos desde el final. Por lo tanto, invertimos la secuencia para obtener el orden correcto.


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

vector<string> longestPlaylist(vector<string>& playlist1, vector<string>& playlist2) {
    int n = playlist1.size();
    int m = playlist2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    vector<vector<pair<int, int>>> path(n + 1, vector<pair<int, int>>(m + 1, { -1, -1 }));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (playlist1[i - 1] == playlist2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = { i - 1, j - 1 };
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                path[i][j] = { i - 1, j };
            }
            else {
                dp[i][j] = dp[i][j - 1];
                path[i][j] = { i, j - 1 };
            }
        }
    }

    vector<string> sequence;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (path[i][j] == make_pair(i - 1, j - 1)) {
            sequence.push_back(playlist1[i - 1]);
            i--;
            j--;
        }
        else {
            auto p = path[i][j];
            i = p.first;
            j = p.second;
        }
    }
    reverse(sequence.begin(), sequence.end());

    return sequence;
}

vector<string> readLineAsWords() {
    string line;
    getline(cin, line);

    istringstream iss(line);
    vector<string> words;
    string word;

    while (iss >> word) {
        words.push_back(word);
    }

    return words;

}


bool resuelveCaso() {

    vector<string> playlist1 = readLineAsWords();

    vector <string> playlist2 = readLineAsWords();
    if (!std::cin)  // fin de la entrada
        return false;

    vector<string> result = longestPlaylist(playlist1, playlist2);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << " ";
        }
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