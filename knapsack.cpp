#include <bits/stdc++.h>
using namespace std;


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

int knapsack(vector<int> &values, vector<int> &weights, int C, vector<int> &x){
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
                if(seleccionar > noSeleccionar) x[elementoAct] = 1;
                memo[elementosTotales][capacidad] = max(seleccionar, noSeleccionar);
            }
        }
    }
    return memo[values.size()][C];
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

    return knapsackV();
}

int main(){
    ifstream input;
    input.open("test.txt", ios_base::app);
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
        cout<<knapsack(v,w,C,x)<<" "; //Working
        for(int i = 0; i < x.size(); i++){
            cout<<x[i]<<" ";
        }
        cout<<endl;
    }    
    return 0;
}