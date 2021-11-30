#include <bits/stdc++.h>
#include "helper.h"

using namespace std;

int main() {

    /** A. Declaramos variables necesarias **/
    vector<vector<int>> mst, adjL, locations, newLocations;
    vector<string> cities, newCities;
    string city, cityO, cityE;
    int n, m, q, cost, central, x, y;
    vector<int> centrales;

    /** B. Leemos de stdin n, m y q **/
    cin >> n >> m >> q;
    
    /** C. Rellenamos cities con el nombre de la ciudad,
           Rellenamos centrales con valores binarios 0/1,
           Rellenamos locations con las coordenadas (x, y) **/
    for(int i = 0; i < n; i++) {
        cin >> city >> x >> y >> central;
        cities.push_back(city);
        centrales.push_back(central);
        locations.push_back({x, y});
    }
    /** D. Creamos una Lista de Adyacencia con los pesos de las aristas a cada vértice */
    for(int i = 0; i < m; i++) {
        cin >> cityO >> cityE >> cost;
        adjL.push_back({cost,search(cityO,cities),search(cityE,cities)});
        adjL.push_back({cost,search(cityE,cities),search(cityO,cities)});
    }

    /** E. Rellenamos newLocations con las coordenadas de las nuevas colonias,
     *     Rellenamos a newCities con los nombres de las nuevas colonias**/
    for(int i = 0; i < q; i++) {
        cin >> city >> x >> y;
        newLocations.push_back({x,y});
        newCities.push_back(city);
    }

    /** F. Obtenemos el MST usando el algoritmo de prim y con nuestra lista de adyacencia **/
    mst = PRIM(adjL, n, m*2);


    /** G. Mostramos de forma amigable al usuario el MST **/
    showMST(cities, mst);

    /** H. Creamos una matriz basada en la Lista de Adyacencia **/
    vector<vector<int>> matriz(n, vector<int> (n,- 1));

    for(int i = 0; i < adjL.size(); i++){
        int a = adjL[i][1];
        int b = adjL[i][2];
        matriz[a][b] = adjL[i][0];
    }

    /** I. Calculamos el Ciclo Hamiltoniano con menor costo**/
    TSP(matriz, 1, 5,cities);


    /** J. Calculamos la distancia más corta entre centrales **/
    ShortestPathBtwCentrals(centrales, cities, matriz, n);

    /** K. Obtenemos la distancia euclideana que optimiza el cableado entre nuevas colonias y centrales **/
    EuclideanDistance(centrales, newLocations, locations, cities, newCities, q, n);

    return(0);
}
