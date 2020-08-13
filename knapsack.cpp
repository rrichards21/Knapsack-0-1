#include <bits/stdc++.h>
using namespace std;

/* Definición algoritmo
Se tiene una mochila con capacidad W
Se tienen n objetos que se pueden agregar a la mochila
Cada objeto tiene un peso p[i] y un valor v[i]
Se desea encontrar el subconjunto de n objetos que se pueden agregar a la mochila,
que maximicen la capacidad que esta posee.

    
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

int main(){
    ifstream input;
    input.open("entradas.txt", ios_base::app);
    string linea;
    while(getline(input, linea)){
        vector<int> in;
        parse(linea," ",in);
        for(int i = 0; i < in.size(); i++){
            cout<<in[i]<<" ";
        }
        int n = in[0];
        int W = in[1];
    }
    return 0;
}