/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 * Gabriel Torres Mart�n TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;


/*@ <answer>

    // Para resolver el problema la estrategia �ptima es elegir los numeros entre 1 y 10^7 (restricci�n de valor de N) mas peque�os en los que no haya dos que sumados den S. De esta
    // manera minimizamos el coste de la suma ya que cada ohmio costar� un c�ntimo. Lo que proponemos es ir almacenando los n�meros que cumplen la restricci�n dada en un vector e ir
    // comprobando si el siguiente n�mero es combinable con alguno de los a�adidos para sumar S. En caso de que lo sea lo saltamos y en caso de que no lo sea lo a�adimos a la soluci�n
    // que siempre tendra tama�o N como m�ximo.

    // Como tenemos un bucle externo que se ejecuta N veces aproximadamente (omitimos algunos n�meros) y otro bucle interno que en el peor caso ejecuta N iteraciones, el coste en el caso
    // peor ser�a de O(N^2) para el algoritmo completo, ya que para cada una de las N resistencias podr�amos estar comprobando contra M resistencias previamente 
    // seleccionadas para asegurarnos de que no sumen S con la resistencia actual que estamos considerando.

    // En terminos de espacio adicional tenemos O(N) debido al vector de la soluci�n.


    // Como soluci�n aunque fuera de tiempo proponemos una soluci�n utilizando un solo bucle y por tanto dandonos un coste lineal O(N)

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>


int calcularCostoMinimo(int N, int S) { // Aunque fuera de tiempo enviamos tamb�en la solucion en coste lineal en la cual diferenciamos entre dos casos para aumentar el contador
    int costoTotal = 0, contAnadidos = 0, i = 1;
    while (contAnadidos < N) {
        if (S - i <= 0) { // Si el numero a a�adir es mayor o igual que S
            contAnadidos++;
            costoTotal += i;
        }
        else if (S - i >= i)  { // Si el n�mero a a�adir es menor o igual a la mitad de S
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