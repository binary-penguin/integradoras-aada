#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <fstream>
#include <iterator>
#include <bits/stdc++.h>

using namespace std;


ofstream MyFile_("output.txt");

vector<vector<int>> PRIM( vector<vector<int>> adjL, int n, int m) {
    typedef vector<int> vec;
    priority_queue<vec,vector<vec>, greater<vec> > pq;

    vector<int> visited(n);
    fill(visited.begin(), visited.end(), 0);
    visited[0] = 1;
    int index=0;

    vector<vector<int>> mst;
   
    do {
        for(int i=0; i<m; i++) {
            if(adjL[i][1] == index && visited[adjL[i][2]] != 1) {
                pq.push(adjL[i]);
            }
        }
           
        if(visited[pq.top()[2]] != 1) {
            index = pq.top()[2];
            visited[index]=1;
            mst.push_back(pq.top());
        }

        pq.pop();

    } while(!pq.empty());
  
    return(mst);
}

int TSP(vector<vector<int>> graph, int s, int n,vector<string> cities) {   
    for(int i=0; i<n; i++){
        graph[i][i] = 0;
    }
    
    vector<int> vertex, path, aux_path;
    for (int i = 0; i < n; i++)
        if (i != s)
            vertex.push_back(i);
 
    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    do {
 
        // store current Path weight(cost)
        int current_pathweight = 0;
 
        // compute current path weight
        int k = s;
        
        aux_path.clear();
        aux_path.push_back(k);
        for (int i = 0; i < vertex.size(); i++) {

            if(graph[k][vertex[i]] != -1 ){
          
                current_pathweight += graph[k][vertex[i]];
                k = vertex[i];
                aux_path.push_back(k);
            }
            
    
            
        }
        if(graph[k][s] != -1){
            current_pathweight += graph[k][s];

            if (current_pathweight < min_path && aux_path.size() == n) {
                min_path = current_pathweight;
                path = aux_path;
                path.push_back(s);
            }
        }
        
 
    } while (
        next_permutation(vertex.begin(), vertex.end()));
    
    MyFile_ << "2 – La ruta óptima es: "<<   endl;
    for(int i = path.size()-1; i>0; i--){
        MyFile_ << cities[path[i]] +" - ";
        
    } 
    MyFile_ <<cities[path[0]] << "\n\n";
    MyFile_ << "Costo Total = " << min_path << endl<< endl;
    return min_path;
}

vector<vector<int>> Dijkstra(int source, vector<vector<int>> adjM, int n) {
    typedef vector<int> vec;
    priority_queue<vec,vector<vec>, greater<vec> > pq;

    vector<vector<int>> key(n, vector<int> (3,0));
    vector<int> r;

    for(int i=0; i<n; i++){
        key[i][0]= INT_MAX;
        key[i][2]= 0;
    }
    key[source][0]= 0;
    key[source][2]= 1;
    int actual= source;

    int pathC=0; // path cost
    do{
        for(int i=0; i<n; i++){
            if( adjM[actual][i] != 0 && adjM[actual][i] != -1 && key[i][2] != 1 ){

                pathC += adjM[actual][i];
                pq.push({pathC,actual,i});
                pathC -= adjM[actual][i];

            }
        }

        if(!pq.empty()){

            if(key[pq.top()[2]][2] != 1){
                key[pq.top()[2]][0]=pq.top()[1]; //tag
                key[pq.top()[2]][1]=pq.top()[0]; //cost
                key[pq.top()[2]][2]=1;           //boolean flag
                pathC=pq.top()[0];               //path cost

            }
            actual = pq.top()[2]; 
            pq.pop();
        }
    }while(!pq.empty());
    
        
    
    

    return key;
}

void EuclideanDistance(vector<int> centrales, vector<vector<int>> newLocations, vector<vector<int>> locations, vector<string> cities, vector<string> newCities, int q, int n) {

    MyFile_ << "4 – Conexión de nuevas colonias" << endl;

    int central = 0;
    double minDist = 0.0;

    for(int i=0; i<q; i++){
        minDist = INT_MAX;

        for(int j=0; j<n; j++ ){
        
            if (centrales[j] == 1){
                double distance = sqrt( pow(locations[j][0] - newLocations[i][0],2) + pow(locations[j][1] - newLocations[i][1],2) );
                if(distance < minDist){
                    minDist= distance;
                    central = j;
                } 
            }
        }
        MyFile_ << newCities[i] << " debe conectarse con " << cities[central] << endl;
    
    }
}


void ShortestPathBtwCentrals(vector<int> centrales, vector<string> cities, vector<vector<int>> matriz, int n) {

    MyFile_ << "3 – Caminos más cortos entre centrales" << endl;

    vector<vector<int>> dijkstra;
    int tag = 0;

    for(int i=0; i<n; i++){
        if(centrales[i] == 1){
            dijkstra = Dijkstra(i, matriz, n);

            for(int j=0; j<n; j++){
                if(dijkstra[j][1] != 0 && centrales[j] == 1 && j<i) {
                    tag= j;

                    while(tag != i) {
                        MyFile_<< cities[tag] << " - ";
                        tag = dijkstra[tag][0];
                    }
                    MyFile_ << cities[tag] << " = " << dijkstra[j][1] << endl << endl;
                }
            }
        }
    }

}

int search(string city, vector<string> vec){
    vector<string>::iterator it;
    it = find(vec.begin(),vec.end(),city);
    
    int pos = distance(vec.begin(), it);

    if(it!=vec.end()){
        return pos;
    }
    return INT_MAX;
}

void showMST(vector<string> cities, vector<vector<int>> mst) {
    MyFile_ << "1 – Cableado óptimo de nueva conexión." << endl;
    int costoCableado = 0;

    for(int i=0; i<mst.size(); i++){
        MyFile_ <<  cities[mst[i][1]] << " - " << cities[mst[i][2]] << " " <<mst[i][0] << endl;
        costoCableado +=  mst[i][0];
    }
    MyFile_ << endl <<"Costo Total = " <<  costoCableado << "\n\n";
}