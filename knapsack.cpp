#include <bits/stdc++.h>
using namespace std;
#define MAX 99999

/* Definición algoritmo
Se tiene una mochila con capacidad W
Se tienen n objetos que se pueden agregar a la mochila
Cada objeto tiene un peso p[i] y un valor v[i]
Se desea encontrar el subconjunto de n objetos que se pueden agregar a la mochila dada su capacidad,
tal que ese subconjuno sea el de mayor valor, es decir que maximizan el valor total de los objetos
dada la capacidad de la mochila.

    
    a) Describa y proporcione una solución usando programación dinámica y establezca su
    complejidad asintótica del tiempo de ejecución.
*/
typedef struct nodo{
    int valor;
    nodo *cosa;
}nodo;
void parse(const string& str, const string& delimiters,vector<int>& p){
	vector<string> tokens;
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos     = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos){
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	for(vector<string>::iterator i = tokens.begin(); i != tokens.end(); ++i){
		stringstream ss(*i);
		int num;
		ss >> num;
		p.push_back(num);
    }
}

void knapsack(vector<int> &values, vector<int> &weights, int C, vector<int> &x){
    vector<int> aux(C+1);
    vector<vector<int> > memo(values.size()+1,aux);
    for(int elementosTotales = 0; elementosTotales <= values.size(); elementosTotales++){
        for(int capacidad = 0; capacidad <= C; capacidad++){
            int elementoAct = elementosTotales - 1;     //Elemento actual
            if (elementosTotales == 0 || capacidad == 0) {
            memo[elementosTotales][capacidad] = 0;
            } 
            else if (weights[elementoAct] > capacidad) {
                memo[elementosTotales][capacidad] = memo[elementosTotales - 1][capacidad];
            } 
            else {
                int seleccionar = values[elementoAct] + memo[elementosTotales - 1][capacidad - weights[elementoAct]];
                int noSeleccionar = memo[elementosTotales - 1][capacidad];
                memo[elementosTotales][capacidad] = max(seleccionar, noSeleccionar);
            }
        }
    }
    int res = memo[values.size()][C];     
    printf("%d ", res); 
      
    int c = C; 
    for(int i = values.size(); i > 0 && res > 0; i--) {
        if (res == memo[i - 1][c])  
            continue;         
        else {
            x[i-1] = 1;
            res = res - values[i - 1]; 
            c = c - weights[i - 1]; 
        } 
    }
}

/*
    float e: margen de error
*/
int knapsack_approx(float e, vector<int> &values, vector<int> &weights, int C, vector<int> &x){
    
    int V = 0;
    int n = values.size();
    for (int i = 0; i < n; i++)
        V += values.at(i);
    int X = (1-e)*V/n;

    for (int i = 0; i < n; i++) 
        values[i] = values[i] / X;

    return 1;
}

int knapsackV(vector<int> &values, vector<int> &weights, int C, vector<int> &x) {
    int V = 0;
    int n = values.size();
    for (int i = 0; i < n; i++)
        V += values[i];
    vector<int> aux(V+1,MAX);
    vector<vector<int> > memo(values.size()+1, aux);
    /*for(int i = 0; i < n + 1; i++){
        for(int j = 0; j < V + 1; j++){
            if (i == 0 || j == 0) {
                memo[i][j] = MAX;
            } 
        }
    }*/
    stack<int> prevRow;
    for (int e = 1; e < n + 1; e++){
        for (int v = 1; v < V + 1; v++) {
            if (values[e-1] >= v) {

                //Ver valor de celda de arriba
                if(memo[e-1][v] > weights[e-1] && memo[e-1][v] != MAX){
                    memo[e][v] = memo[e-1][v];
                    prevRow.push(memo[e][v]);
                }
                //Insertar peso de elemento actual si casilla de arriba es menor
                else if(weights[e-1] > memo[e-1][v]){
                    memo[e][v] = weights[e-1];
                    prevRow.push(memo[e][v]);
                }
                //Agregar elemento actual a los elementos que permiten generar la capacidad
                //de la mochila
                else{
                    int sum = weights[e-1];
                    while(!prevRow.empty()){
                        act = prevRow.top();
                        //aqui se está haciendo una suma con los pesos, se debe ver
                        //que el valor del elemento actual sumado a algun/os elemento/os de la
                        //fila anterior generen el valor actual (v)
                        if(sum + act <= v){
                            sum += act;
                        }
                        act.pop();
                    }
                    /*for(int i = v; i > 0; i--){
                        if(sum+memo[e-1][i] <= v && memo[e-1][i] != MAX){
                            sum += memo[e-1][i];
                        }
                    }*/
                    if(v >= values[e-1]){ memo[e][v] = sum;cout<<"soy mayor\n";}
                    else{cout<<"soy menor"<<endl;}
                }
            }
            else {
                memo[e][v] = memo[e-1][v];
            }
        }        
    }

    return memo[values.size()][V];
}

int main(){
    ifstream input;
    input.open("udacity.txt", ios_base::app);
    string linea;
    while(getline(input, linea)){
        vector<int> in;
        parse(linea," ",in);
        int n = in[0];
        int C = in[1];
        int j = 0, k = 0;
        vector<int> w(n),v(n),x(n,0);
        for(int i = 2; i < in.size(); i++){
            if(i%2 == 0){ 
                w[j] = in[i];
                j++;
            }
            else{
                v[k] = in[i];
                k++;
            }
        }
        vector<int> aux(C,-1);
        vector<vector<int> > tabla(C,aux);
        cout<<n<<" ";
        knapsackV(v,w,C,x); //Working
        for(int i = 0; i < x.size(); i++){
            cout<<x[i]<<" ";
        }
        cout<<endl;
    }    
    return 0;
}