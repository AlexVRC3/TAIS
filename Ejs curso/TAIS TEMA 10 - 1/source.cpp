
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

Li = longitud del cordel i, i € {1,.....N}
N = numero de cordeles
L = longitud de la cuerda deseada


RECURSION MATEMATICO
--------------------

maneras (i,j) = minimo número maneras posibles de formar una cuerda de longitud j pudiendo usar los cordeles del 1 al i

                {    maneras(i - 1, j)                                si Li > j
maneras (i,j) = {
                {    maneras(i - 1, j) + maneras(i - 1, j - Li)       si Li <= j


CASOS BASE:
    - maneras(0,j) = 0
    - maneras(i,0) = 1
    - maneras(0,0) = 1

Se utiliza programación dinamica ascendente. Se va generando la tabla con N + 1 filas y L + 1 columnas (longitudes de cordel de 0 a L). La posicion [0][0] será 1 y la primera fila 
exceptuando la primera posición sera valor 0 y la primera columna se rellena con unos.

A partir de ahi se recorre la tabla de arriba a abajo y de izquierda a derecha de forma que la solución queda almacenada en la ultima posicion de la tabla. Aunque se puede almacenar la tabla en una matriz
realmente para generar una fila solo necesitamos el valor superior por lo que si recorremos la matriz de arriba a abajo y de derecha a izquierda, cada vez que movamos una posicion a la izquierda dejaremos
de necesitar el valor que tenia la posicion superior por lo que podemos mantener un unico vector en el que se va cambiando la posicion correspondiente a la j por la que vamos.

El coste en tiempo de resolver el problema esta en el orden de O(N * L) porque recorremos toda la matriz y sobre cada elemento realizamos operaciones constantes.
El coste en espacio esta en el orden de O(L) por el vector donde almacenamos la fila por la que vamos.




RECURSION INGENIERO
--------------------

cordelesMinimos (i,j) = minimo número de cordeles para formar una cuerda de longitud j pudiendo usar los cordeles del 1 al i

                        {    cordelesMinimos(i - 1, j)                                               si Li > j
cordelesMinimos (i,j) = {
                        {    min(cordelesMinimos(i - 1, j), cordelesMinimos(i - 1, j - Li) + 1       si Li <= j


CASOS BASE:
    - cordelesMinimos(0,j) = Infinito
    - cordelesMinimos(i,0) = 0
    - cordelesMinimos(0,0) = 0

La explicación y el coste es la misma que en el problema del matematico cambiando los valores de los casos base


RECURSION ECONOMISTA
--------------------

costeMinimo (i,j) = minimo coste para formar una cuerda de longitud j pudiendo usar los cordeles del 1 al j

                        {    costeMinimo(i - 1, j)                                                         si Li > j
costeMinimo (i,j) =     {
                        {    min(cordelesMinimos(i - 1, j), cordelesMinimos(i - 1, j - Li) + coste[i]      si Li <= j


CASOS BASE:
    - costeMinimo(0,j) = Infinito
    - costeMinimo(i,0) = 0
    - costeMinimo(0,0) = 0

La explicación y el coste es la misma que en el problema del matematico/ingeniero cambiando los valores de los casos base

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cordel {
    int longitud;
    int coste;
};

struct tSol {
    long long int nManeras;
    EntInf minCordeles;
    EntInf minCoste;
};

long long int maneras(const vector<Cordel>& C, int L) {
    int N = C.size();
    vector<long long int> maneras(L + 1, 0);
    maneras[0] = 1;
    for (int i = 1; i <= N ; i++)
    {
        for (int j = L; j >= C[i - 1].longitud; j--)
        {
            maneras[j] = maneras[j] + maneras[j - C[i - 1].longitud];
        }

    }
    return maneras[L];
}

EntInf minimosCordeles(const vector<Cordel>& C, int L) {
    int N = C.size();
    vector<EntInf> cordelesMinimos(L + 1, Infinito);
    cordelesMinimos[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = L; j >= C[i - 1].longitud; j--)
        {
            cordelesMinimos[j] = min(cordelesMinimos[j], cordelesMinimos[j - C[i - 1].longitud] + 1);
        }
    }
    return cordelesMinimos[L];
}

EntInf costeMinimo(const vector<Cordel>& C, int L) {
    int N = C.size();
    vector<EntInf> costesMinimos(L + 1, Infinito);
    costesMinimos[0] = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = L; j >= C[i - 1].longitud; j--)
        {
            costesMinimos[j] = min(costesMinimos[j], costesMinimos[j - C[i - 1].longitud] + C[i-1].coste);
        }
    }
    return costesMinimos[L];
}

tSol resolver(const vector<Cordel> &C, int L) {
    long long int nManeras = maneras(C, L);
    EntInf minCordeles = -1, minCoste = -1;
    if (nManeras != 0) {
        minCordeles = minimosCordeles(C, L);
        minCoste = costeMinimo(C, L);
    }
    return { nManeras,minCordeles,minCoste };
}


bool resuelveCaso() {

    int N, L;

    cin >> N >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<Cordel> cordeles(N);
    for (int i = 0; i < N; i++)
    {
        cin >> cordeles[i].longitud >> cordeles[i].coste;
    }

    tSol sol = resolver(cordeles, L);

    if (sol.nManeras != 0) cout << "SI " << sol.nManeras << " " << sol.minCordeles << " " << sol.minCoste;
    else cout << "NO";
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
