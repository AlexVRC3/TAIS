
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 * Gabriel Torres Mart�n TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;



/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

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
// Escribe el c�digo completo de tu soluci�n aqu� debajo
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

    sort(peliculas.begin(), peliculas.end()); // Se ordenan por hora de finalizaci�n

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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
