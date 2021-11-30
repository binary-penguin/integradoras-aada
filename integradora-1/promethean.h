#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <utility>
/**
 * @file promethean.h
 *
 * @brief Este header file sirve como apoyo a la realización de la actividad integradora conteniendo algunas rutinas frecuentemente usadas
 *
 * @author Jorge Flores A01769059
 * @author Ruben Ruiz A01366792
 * @author Jemuel Flores A01367182
 * @author V. de la Cueva
 *
 */
   
void Preprocesamiento(const char* pat, int M, int* pre_array) {
    // COMPLEJIDAD: O(M)

    // 0. Inicializamos el array con 0 en 0
    pre_array[0] = 0;
    // 1. i representa el actual elemento y j significa 
    //    j representa la suma que llevamos de strings que conicidieron
    int j = 0;
    int i = 1;


    while (i < M) {
        // 2. Si son iguales incrementamos i, j y agregamos j al pre_array
        if (pat[i] == pat[j]) {
            j++;
            pre_array[i] = j;
            i++;
        }
        else
        {
            // 2.0 Sino llevamos nada en j, recorrer al siguiente elemento del patron
            if (j == 0) {
                pre_array[i] = 0;
                i++;
                
            }
            // 2.1 Si ya llevamos algo en j, no volvemos hasta 0 sino que vamos un caracter anterior
            else 
            {
                j = pre_array[j - 1];
                
            }
        }
    }
}

void KMP(const char* pat, const char* txt, std::vector<std::string> &result) {
    // COMPLEJIDAD: O(N)
    int M = strlen(pat);
    int N = strlen(txt);
    int pre_array[M];

    // 1. Hacemos el procesamiento del patron usando pre_array
    Preprocesamiento(pat, M, pre_array);
  
    int i = 0;
    int j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
  
        if (j == M) {
            // 2. Agregamos al vector la posicion (index = 1) y un espacio
            result.push_back(std::to_string(i - j + 1));
            result.push_back(" ");
            j = pre_array[j - 1];
        }

        else if (i < N && pat[j] != txt[i]) {
            // 3. Volvemos uno sino es igual a 0
            if (j != 0)
                j = pre_array[j - 1];
            // 4. Sino simplemente agregamos 1
            else
                i = i + 1;
        }
    }
}
  
void findPattern(std::string pat, std::string txt, std::vector<std::string> &result) {
    KMP(pat.c_str(), txt.c_str(), result);
    if (!result.empty()) {
        std::cout << "true ";
        for (std::vector<std::string>::iterator t = result.begin(); t!=result.end(); ++t) {
        std::cout << *t;
        }
        std::cout << "\n";
    }
    else {
        std::cout << "false";
        std::cout << "\n";
    }
}

std::string getFileContent(std::string filename) {

    std::ifstream in(filename);
    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return content;
}


std::string aumenta(std::string S){
  std::string s = "";
  for (char c:S){
    s = s+"|"+c;
  }
  return s+"|";
}

std::pair<int,int> MANACHER(std::string S){
    // COMPLEJIDAD: O(N)
  std::pair<int,int> res(0,0); // resultado (inicio, longitud)
  if (S.length() == 0) // S es nulo
    return res;
  std::string T = aumenta(S);  // llamar a funci�n
  int N = T.length();
  // longitud y centro del m�ximo pal�ndromo encontrado
  int maxLong=1, maxCentro=1; // Hasta ahora posici�n 1
  int L[N];
  int C = 1;
  int Li = 0, Ri = 0;
  bool expansion = false; // true si requiera expansi�n

  L[0]=0; L[1]=1;
  for (Ri=2; Ri<N; Ri++){
    expansion = false;
    Li = C - (Ri-C);
    if ((C+L[C])-Ri >= 0){
      if(L[Li] < (C+L[C])-Ri) // Caso 1
				L[Ri] = L[Li];
			else if(L[Li] == (C+L[C])-Ri && (C+L[C]) == N-1) // Caso 2
				L[Ri] = L[Li];
			else if(L[Li] == (C+L[C])-Ri && (C+L[C]) < N-1){ // Caso 3
					L[Ri] = L[Li];
					expansion = true; // requiere expansi�n
			}
			else if(L[Li] > (C+L[C])-Ri){ // Case 4
				L[Ri] = (C+L[C])-Ri;
				expansion = true; // requiere expansi�n
			}
    }
    else{
      L[Ri] = 0;
      expansion = true;  // requiere expansi�n
    }
    if (expansion) // hacer la expansi�n hasta donde se pueda
      while ((Ri + L[Ri]) < N && (Ri - L[Ri]) > 0
             && T[Ri+L[Ri]+1] == T[Ri-L[Ri]-1])
        L[Ri]++;
    if (Ri + L[Ri] > (C + L[C]))
      // si el nuevo pal�ndromo se expande m�s all� de C
			C = Ri;
    if(L[Ri] > maxLong){
      // Guardar longitud y centro del pal�ndromo m�s grande,
      // hasta ahora
			maxLong = L[Ri];
			maxCentro = Ri;
		}
  }
  // obtener inicio y longitud del m�ximo pal�ndromo encontrado
  // recordando que la longitud de T es el doble de la de S
  res.first = ((maxCentro - maxLong)/2) + 1; // inicio en S
  res.second = maxLong; // longitud en S
  return res;
}


std::pair<int,int> LCS(std::string string1, std::string string2) {
    // COMPLEJIDAD: O(M*N)
    const char* s1 = string1.c_str();
    const char* s2 = string2.c_str();
    int m = strlen(s1);
    int n = strlen(s2);

    // 0. Crear matriz de estados
    int matrix[m + 1][n + 1];
    int longest = 0;

    // 1. Crear par que contendrá las posiciones
    std::pair<int,int> end(0,0); 
    std::pair<int,int> start(0,0); 
    


    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {

            // 2. Crear primera fila de 0s
            if (i == 0 || j == 0)
                matrix[i][j] = 0;
 
            else if (s1[i - 1] == s2[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;

                if (matrix[i][j] > longest) {
                    longest = matrix[i][j];
                    end.first = i;
                    end.second = j;
                } 

            }
            else
                matrix[i][j] = 0;
        }
    }

    // Get starting point

    int i = end.first;
    int j = end.second;

    while (matrix[i][j] != 0) {
        i = i - 1;
        j = j - 1;
    }

    start.first = i + 1;
    start.second = j + 1;

    std::pair<int,int> res(start.first,end.first);
    return res;
}