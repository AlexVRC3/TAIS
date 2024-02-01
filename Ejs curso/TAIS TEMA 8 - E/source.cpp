/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;


/*@ <answer>

    // Para resolver el problema la estrategia óptima es elegir los numeros entre 1 y 10^7 (restricción de valor de N) mas pequeños en los que no haya dos que sumados den S. De esta
    // manera minimizamos el coste de la suma ya que cada ohmio costará un céntimo. Lo que proponemos es ir almacenando los números que cumplen la restricción dada en un vector e ir
    // comprobando si el siguiente número es combinable con alguno de los añadidos para sumar S. En caso de que lo sea lo saltamos y en caso de que no lo sea lo añadimos a la solución
    // que siempre tendra tamaño N como máximo.

    // Como tenemos un bucle externo que se ejecuta N veces aproximadamente (omitimos algunos números) y otro bucle interno que en el peor caso ejecuta N iteraciones, el coste en el caso
    // peor sería de O(N^2) para el algoritmo completo, ya que para cada una de las N resistencias podríamos estar comprobando contra M resistencias previamente 
    // seleccionadas para asegurarnos de que no sumen S con la resistencia actual que estamos considerando.

    // En terminos de espacio adicional tenemos O(N) debido al vector de la solución.


    // Como solución aunque fuera de tiempo proponemos una solución utilizando un solo bucle y por tanto dandonos un coste lineal O(N)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int calcularCostoMinimo(int N, int S) { // Aunque fuera de tiempo enviamos tambíen la solucion en coste lineal en la cual diferenciamos entre dos casos para aumentar el contador
    int costoTotal = 0, contAnadidos = 0, i = 1;
    while (contAnadidos < N) {
        if (S - i <= 0) { // Si el numero a añadir es mayor o igual que S
            contAnadidos++;
            costoTotal += i;
        }
        else if (S - i >= i)  { // Si el número a añadir es menor o igual a la mitad de S
            contAnadidos++;
            costoTotal += i;
        }
        
        i++;
    }
    return costoTotal;
}


bool resuelveCaso() {
    int N, S;
    cin >> N >> S;

    if (!std::cin) return false; // Fin de la entrada

    long long int resultado = (N * (N - 1)) / 2;
    cout << resultado << "\n";
    //cout << calcularCostoMinimo(N, S) << endl;

    return true;
}

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