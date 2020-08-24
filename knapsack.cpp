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

int knapsackV1(vector<int> &values, vector<int> &weights, int C, vector<int> &x) {
    int V = 0;
    int n = values.size();
    for (int i = 0; i < n; i++)
        V += values[i];
    vector<int> aux(V+1, 0);
    vector<vector<int> > memo(values.size() + 1, aux);
    for (int e = 1; e < n + 1; e++){        
        for (int v = 1; v < V + 1; v++) {
            int opcion1 = MAX;
            int opcion2 = MAX;
            int valorRestante = v - values[e - 1]; //1
            if (memo[e - 1][v] > 0)
                opcion1 = memo[e - 1][v];
            if (valorRestante >= 0) {
                if (valorRestante == 0) 
                    opcion2 = weights[e - 1];
                else if (memo[e - 1][valorRestante] != 0)
                    opcion2 = weights[e - 1] + memo[e - 1][valorRestante];
            }
            int seleccionado = min(opcion1, opcion2);
            if (seleccionado != MAX) 
                memo[e][v] = seleccionado;                                        
        }
    }
    return memo[values.size()][V];
}

int knapsackV(vector<int> &values, vector<int> &weights, int C, vector<int> &x) {
    int V = 0;
    int n = values.size();
    for (int i = 0; i < n; i++)
        V += values[i];
    vector<int> aux(V+1, 0);
    vector<vector<int> > memo(values.size() + 1, aux);  
    memo[0][0] = C + 1;      
    pair<int, int> max_weight = make_pair(0,0);        
    for (int e = 1; e < n + 1; e++){        
        for (int v = 1; v < V + 1; v++) {
            int opcion1 = MAX;
            int opcion2 = MAX;
            int valorRestante = v - values[e - 1]; //1
            if (memo[e - 1][v] > 0)
                opcion1 = memo[e - 1][v];
            if (valorRestante >= 0) {
                if (valorRestante == 0) 
                    opcion2 = weights[e - 1];
                else if (memo[e - 1][valorRestante] != 0)
                    opcion2 = weights[e - 1] + memo[e - 1][valorRestante];
            }
            int seleccionado = min(opcion1, opcion2);
            if (seleccionado != MAX) {
                memo[e][v] = seleccionado;
                if (seleccionado <= C && max_weight.second <= v) {
                    if (max_weight.second < v || memo[max_weight.first][max_weight.second] > seleccionado) {
                        max_weight.first = e;
                        max_weight.second = v;   
                    }
                }
            }
        }
    }

    int v = max_weight.second;
    for (int e = max_weight.first; e > 0; e--) {
        if (v == 0) 
            break;
        if (memo[e][v] != memo[e - 1][v]) {
            x[e - 1] = 1;
            v = v - values[e - 1];            
        }
    }
    return memo[values.size()][V];
}


int main(){
    ifstream input;
    input.open("test3.txt", ios_base::app);
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