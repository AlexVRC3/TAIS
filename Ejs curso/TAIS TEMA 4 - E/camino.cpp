#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

#include "Grafo.h" // propios o los de las estructuras de datos de clase
/*

using Camino = std::deque<int>;
int vOrigen = 0;


bool hayCamino(int v) const {
	return visit[v];
}
Camino camino(int v) const {
	if (!hayCamino(v))
		throw std::domain_error("No existe camino");
	Camino cam;
	for (int x = v; x != vOrigen; x = ant[x])
	{
		cam.push_front(x);
	}
	cam.push_front(vOrigen);
	return cam;
}*/