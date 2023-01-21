/*
   Alejandro Hidalgo Badillo _____ 
	Geometric search
	fecha de inicio: 5 de noviembre del 2022
	fecha de ultima modificacion: 4 de noviembre del 2022
*/
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;
int punto1[2];
int punto2[2];
float result;
int contador;

//generamos nuestra estructura de punto, la cual va a guardar nuestras entradas de X Y
struct Point
{
    int x, y;
};

 // FindX nos sirve para sortear nuestro arreglo de untos de acuardo a las X
int FindX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x != p2->x) ? (p1->x - p2->x) : (p1->y - p2->y);
		//tiene una complejidad de O(n) debido a que solo se realiza una comparacion
}
// FindY nos sirve para sortear nuestro arreglo de untos de acuardo a las Y
int FindY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->y != p2->y) ? (p1->y - p2->y) : (p1->x - p2->x);
	//tiene una complejidad de O(n) debido a que solo se realiza una comparacion
}
/* 
dist nos sirve para realizar la ecuacion de la distancia entre dos puntos, 
la cual es la raiz cuadrade de la suma de las restas entre las diferencias de los puntos al cuadrado 
*/
float dist(Point p1, Point p2)
{
    return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
	//tiene una complejidad de O(n) debido a que solo se realiza una operacion y se regresa el resultado
}

/* 
la funcion de bruteForce nos sirve para determinar la distancia mas corta 
de un arreglo de puntos de poca cantidad.

tiene una complejidad de O(logn) devido a que el arreglo ya se encuentra sorteado
*/
float bruteForce(Point P[], int n)
{
    float min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(P[i], P[j]) < min){
							if (contador==1){
								if (P[j].x-P[i].x <= punto1[0]-punto2[0]){
									if (P[j].y-P[i].y <= punto1[1]-punto2[1]){
												min = dist(P[i], P[j]);
												//cout<<"{"<<P[i].x<<", "<<P[i].y<<"} | {"<<P[j].x<<", "<<P[j].y<<"}\n";
												punto1[0]=P[i].x;
												punto1[1]=P[i].y;
					
												punto2[0]=P[j].x;
												punto2[1]=P[j].y;
									}
								}
							}else{
								if (contador !=1){
											min = dist(P[i], P[j]);
											//cout<<"{"<<P[i].x<<", "<<P[i].y<<"} | {"<<P[j].x<<", "<<P[j].y<<"}\n";
											punto1[0]=P[i].x;
											punto1[1]=P[i].y;
				
											punto2[0]=P[j].x;
											punto2[1]=P[j].y;
											contador =1;
								}
				
						}
					
							
						}
                
    return min;
}
 

float min(float x, float y)
{
    return (x < y)? x : y;
}
 
 
//esta funcion es la principal para encontrar los puntos con la distancia entre ellos mas cercana
float Shortestdist(Point P[], int size, float d)
{
    float min = d;  
 
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (P[j].y - P[i].y) < min; ++j)
           if (dist(P[i], P[j]) < min){
							min = dist(P[i], P[j]);
							//cout<<"{"<<P[i].x<<", "<<P[i].y<<"} | {"<<P[j].x<<", "<<P[j].y<<"}\n";
							punto1[0]=P[i].x;
							punto1[1]=P[i].y;

							punto2[0]=P[j].x;
							punto2[1]=P[j].y;
						}
                
 
    return min; //regresamos la distancia minima
}
 

float MainFunc(Point P1[], Point P2[], int n)
//MainFunc tiene una complejidad O(nlogn) debido a que tiene recusividad.
{
    //si hay 2 o tres 
    if (n <= 3){
			  return bruteForce(P1, n);
		}
      
 
   	//buscamos el punto medio que separara nuestros dos arreglos de entrada
    int mid_num = n/2;
		//cout<<"middle point: "<<mid<<"\n";
    Point media = P1[mid_num];
 
 
 //considerando la linea vertical imaginaria, calculamos la distancia mas corta de la izquierda del punto medio y en el lado derecho
    Point Pyl[mid_num];   
    Point Pyr[n-mid_num];  
    int li = 0, ri = 0; 
    for (int i = 0; i < n; i++)
    {
      if ((P2[i].x < media.x || (P2[i].x == media.x && P2[i].y < media.y)) && li<mid_num)
         Pyl[li++] = P2[i];
      else
         Pyr[ri++] = P2[i];
    }
 
//esta funcion trabaja de forma recursiva 

    float dl =  MainFunc(P1, Pyl, mid_num);
    float dr =  MainFunc(P1 + mid_num, Pyr, n-mid_num);
 

    float d = min(dl, dr);

    Point SortedPoint[n];
    int j = 0;
		//cout<<"listado de:\n";
    for (int i = 0; i < n; i++){
			    if (abs(P2[i].x - media.x) < d){
					SortedPoint[j] = P2[i],j++;
					//cout<<"{"<<strip[j-1].x<<", "<<strip[j-1].y<<"}\n";
					
					
				}
		}
    
            
 

    return Shortestdist(SortedPoint, j, d);
}
 
//se llama a la funcion con recursion, la cual no acaba hasta tener la distancia minima

float closest(Point P[], int n)
//tiene una complejidad de O(n) debido a 
{
    Point P1[n];
    Point P2[n];
    for (int i = 0; i < n; i++)
    {
        P1[i] = P[i];
        P2[i] = P[i];
    }
 		//se sortean nuestros arreglos de entrada
    qsort(P1, n, sizeof(Point), FindX);
    qsort(P2, n, sizeof(Point), FindY);
 
  
    return MainFunc(P1, P2, n); //regresamos el resultado de la distancia mas corta entre dos puntos
}


int main()
{
	//almacenamos los datos de entrada
	int n;
	cin>>n;
	int cont1,cont2;
	vector<vector<string>> puntos;
	string line;
	int cont = 0;
	//contq es el contador de lineas de entrada existentes
	int largo;
	getline(cin, line);
	 while (getline(cin, line)) {
		stringstream ss(line);
		puntos.push_back(vector<string>());
		while (ss.good()) {
        string substr;
        getline(ss, substr,' ');
        puntos[cont].push_back(substr);
    }
		 cont++;
  }//guardar matriz
	
	Point points[n];
	
	for(int i=0; i<cont;i++){
		//points[i].pos = puntos[i][0];
		points[i].x = stoi(puntos[i][1]);
		points[i].y = stoi(puntos[i][2]);	
		//cout<<points[i].x<<" "<<points[i].y<<"\n";
	}
	

	float result = closest(points, n);
	//cout << punto1[0]<<" "<<punto1[1]<<"\n";

	//se almacena la posicion en la cual encajan los valores resultantes con el arreglo de entrada
	for (int i = 0; i <n;i++){
		if (punto1[0]==points[i].x && punto1[1]==points[i].y){
			cont1=i+1;
		}
		if (punto2[0]==points[i].x && punto2[1]==points[i].y){
			cont2=i+1;
		}
	}
	//se utiliza fixed y setprecision 4 para determinar que solo se quieren imprimir los primeros 4 numeros despues del punto decimal
	cout << fixed;
	cout << setprecision(4);
	cout<<result<<" p"<<cont1<<" p"<<cont2;
	return 0;

/*
el programa tiene una complejidad O(n*n),
debido a que a pesar que trabaja con arreglos ya sorteados,
en el main se encuentran dos ciclos anidados while, que iteran cada valor entrante y lo almacenan en su respectiva variable posteriormente

	*/
}