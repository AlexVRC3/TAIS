
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;



/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */
struct Pelicula {
    int inicio;
    int fin;
    int duracion;

    Pelicula(int comienzo, int duracion) : inicio(comienzo), duracion(duracion), fin(comienzo + duracion) { }
};

bool operator<(Pelicula const& a, Pelicula const& b) {
    return a.fin < b.fin;
}

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int n; 
    cin >> n;

    if (n == 0) return false;

    vector<Pelicula> peliculas;

    int horas, minutos, duracion;
    char aux;
    for (int i = 0; i < n; i++) {
        cin >> horas >> aux >> minutos >> duracion;
        horas *= 60;
        peliculas.push_back({ horas + minutos, duracion + 10 });
    }

    sort(peliculas.begin(), peliculas.end()); // Se ordenan por hora de finalización

    int numPeliculas = 0;
    int tiempo = 0;

    for (Pelicula p : peliculas) {
        if (tiempo > p.inicio) {
            numPeliculas++;
            tiempo = p.fin;
        }
    }

    cout << numPeliculas << "\n";
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
