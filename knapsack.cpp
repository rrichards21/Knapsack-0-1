#include <bits/stdc++.h>
using namespace std;

/* Definición algoritmo
Se tiene una mochila con capacidad W
Se tienen n objetos que se pueden agregar a la mochila
Cada objeto tiene un peso p[i] y un valor v[i]
<<<<<<< HEAD
Se desea encontrar el subconjunto de n objetos que se pueden agregar a la mochila dada su capacidad,
tal que ese subconjuno sea el de mayor valor, es decir que maximizan el valor total de los objetos
dada la capacidad de la mochila.
=======
Se desea encontrar el subconjunto de n objetos que se pueden agregar a la mochila,
que maximicen la capacidad que esta posee.
>>>>>>> 6d4451c925c6fc1324fcaccbdffc195352427f46

    
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

<<<<<<< HEAD
int knapsack(vector<int> &values, vector<int> &weights, int C, vector<int> &x){
    vector<int> aux(C+1);
    vector<vector<int> > cache(values.size()+1,aux);
    for(int totalItems = 0; totalItems <= values.size(); totalItems++){
        for(int maxWeight = 0; maxWeight <= C; maxWeight++){
            int currentItem = totalItems - 1;
            if (totalItems == 0 || maxWeight == 0) {
            cache[totalItems][maxWeight] = 0;
            } 
            else if (weights[currentItem] > maxWeight) {
                cache[totalItems][maxWeight] = cache[totalItems - 1][maxWeight];
            } 
            else {
                int withItem = values[currentItem] + cache[totalItems - 1][maxWeight - weights[currentItem]];
                int withoutItem = cache[totalItems - 1][maxWeight];
                if(withItem > withoutItem) x[currentItem] = 1;
                cache[totalItems][maxWeight] = max(withItem, withoutItem);
            }
        }
    }
    return cache[values.size()][C];
}

int main(){
    ifstream input;
    input.open("test.txt", ios_base::app);
=======
int main(){
    ifstream input;
    input.open("entradas.txt", ios_base::app);
>>>>>>> 6d4451c925c6fc1324fcaccbdffc195352427f46
    string linea;
    while(getline(input, linea)){
        vector<int> in;
        parse(linea," ",in);
<<<<<<< HEAD
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
    
=======
        for(int i = 0; i < in.size(); i++){
            cout<<in[i]<<" ";
        }
        int n = in[0];
        int W = in[1];
    }
>>>>>>> 6d4451c925c6fc1324fcaccbdffc195352427f46
    return 0;
}