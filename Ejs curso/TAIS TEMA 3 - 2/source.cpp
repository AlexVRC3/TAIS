#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "PriorityQueue.h"
using namespace std;


//se equilibra los 2 monticulos
void equilibrar(PriorityQueue<int, greater<int>>& max, PriorityQueue<int>& min) {
	int d = min.size() - max.size();
	if (d < 1) {//si max es mayor
		int aux = max.top(); max.pop();//log(N)
		min.push(aux);//log(N)
	}
	else if (d > 1) {//si min es mayor
		int aux = min.top(); min.pop();
		max.push(aux);//log(N)
	}
}


//El coste es O(P(LogN + 2LogN)) , donde P es el numero de parejas de pajaros y N es la edad del pajaro
//En cada iteracion, hay otra iteracion de insertar(push) las edades de las parejas, y eso tiene un coste total de 2LogN,
//luego hay que sumarle el coste de equilibrar los 2 monticulos de insertar (push) y eliminar(pop),
// si necesita equilibrarse tiene un coste LogN,el coste total sera O(P(LogN + 2LogN))
bool resuelveCaso() {
	int e, p;
	cin >> e >> p;
	if (e == 0 && p == 0) return false;
	PriorityQueue<int, greater<int>> max;//cola de maximos
	PriorityQueue<int> min;
	min.push(e);//inserta en la cola de minimos el primer pajaro
	for (int i = 0; i < p; i++) {//Numero de parejas,  O(P(LogN + 2LogN))
		for (int j = 0; j < 2; j++) {//lee cada par  //coste O(2log(N))
			cin >> e;
			if (e > min.top())//se va construyendo los 2 monticulos
				min.push(e);//cola minimos
			else
				max.push(e);//cola maximos
		}
		equilibrar(max, min);//O(logN)
		cout << min.top() << " ";
	}
	cout << "\n";
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