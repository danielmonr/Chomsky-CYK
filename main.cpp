/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Proyecto Mates Computacionales n°4, Gramaticas
 *
 *        Version:  1.0
 *        Created:  06/12/15 20:35:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Daniel Monzalvo
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <list>

using namespace std;


// Declaracion de estructuras
class variable{

public:
	char S;
	vector<string> producciones;
	variable(){

	}
};

class glc{
private:
	char nombre;
public:
	variable* start;
	vector<variable*> variables;
	glc(){}
	void setNombre(char c){
		nombre = c;
	}

	variable* reemplazar(char c){
		for (auto item:variables){
			if(item->S == c){
				return item;
			}
		}

		return nullptr;
	}

	void Normalizar(){

		//Chomsky
		//paso 1: S no puede estar del lado derecho (añadir un nuevo start)
		//paso 2: Quitar las producciones a nulos
		//paso 3; quitar todas las reglas A->B
		//paso 4: Quitar todas las reglas con más de 2 variables
		//paso 5: Modificar aB por AB A->a


		/* Paso 1 - inicio */
		bool SDerecho = false;
		for (auto item:variables){
			for (auto j:item->producciones){
				if(j.find(start->S) != string::npos){
					SDerecho = true;
					break;
				}
			}
		}

		if (SDerecho){
			variable* S0 = new variable;
			S0->S = '0';
			string t = "" + start->S;
			S0->producciones.push_back(t);
			start = S0;
			variables.push_back(S0);
		}
		//cout <<"S nuevo: " << start->S << endl; 		//Descomentar esta linea para debuggear S del chomskya
		/* Paso 1 - fin */

		/* Paso 2 - inicio */
		// No se permiten nulos
		/* Paso 2 - fin */

		/* Paso 3 - inicio */
		for (vector<variable*>::iterator item = variables.begin(); item != variables.end(); ++item){
			for(vector<string>::iterator it = (*item)->producciones.begin(); it != (*item)->producciones.end(); ++it){
				if((*it).length() == 1 && (*it)[0] > 64 && (*it)[0] < 91){
					variable* temp = reemplazar((*it)[0]);
					(*item)->producciones.erase(it);
					item--;
					if (temp != nullptr)
						for(auto k:temp->producciones){
							(*item)->producciones.push_back(k);
						}
					else{
						cout << "Error en la sintaxis" << endl;
						exit(0);
					}
					break;
				}
			}
		}

		/* Paso 3 - fin */

		/* Paso 4 - inicio */
		for(auto item:variables){
			for(auto it:item->producciones){
				if(it.length() > 2){
					string stepm = it.substr(1);
					it = "" + it[0];
					it += nombre;
					variable* vtemp = new variable;
					vtemp->S = nombre;
					vtemp->producciones.push_back(stepm);
					variables.push_back(vtemp);
					nombre++;
				}
			}
		}
		/* Paso 4 - fin */

		/* Paso 5 - inicio */
		for (auto item:variables){
			for (auto it:item->producciones){
				if (it.length() > 1){
					for(int i = 0; i < it.length(); ++i){
						if(it[i] < 123 && it[i] > 96){
							string ts = "" +  it[i];
							it[i] = nombre;
							variable* tvar = new variable;
							tvar->S = nombre;
							tvar->producciones.push_back(ts);
							variables.push_back(tvar);
							nombre++;
						}
					}
				}
			}
		}
		/* Paso 5 - fin */
	}

	// Funcion para buscar alguna produccion
	vector<char> buscar(string s){
		// cout << "Buscando: " << s << endl;
		vector<char> R;
		for (auto i:variables){
			for(auto j:i->producciones){
				if(s == j){
					R.push_back(i->S);
					break;
				}
			}
		}
		return R;
	}

	// funcion para impimir el GLC
	friend ostream& operator << (ostream &os, glc &g){
		for (auto item:g.variables){
			os << item->S << "->";
			for (auto item2:item->producciones){
				cout << item2 << "|";
			}
			os << endl;
		}
		return os;
	}

};




// Declaracion de variables globales
char nombre = 'A';

// Declaracion de funciones
glc* IngresarGLC(glc*);
bool Preguntar(string pregunta);
variable* PedirVariable(char);
bool membresia(glc*, string);

// Funcion principal
int main(){


	// Introduccion e instrucciones
	cout << "################################################################################" << endl;
	cout << " -- Desarrollado por Daniel Monzalvo -- " << " -- 

	glc* g = new glc;

	IngresarGLC(g);
	cout << *g;
	g->Normalizar();
	cout << *g;

	cout << "String: ";
	string compara;
	cin >> compara;
	string respuesta = "falso";
	if (membresia(g,compara)){
		respuesta = "verdaero" ;
	}

	cout << "Membresia: " << respuesta << endl;
	return  0;
}


// Inicializacion de un GLC
glc* IngresarGLC(glc* g){
	string produccion;
	string temp;
	variable* var = new variable;
	var->S = 'S';
	cout << "Ingrese su GLC: " << endl;

	var = PedirVariable('S');
	g->start = var;
	g->variables.push_back(var);


	while (Preguntar("Ingresar nueva variable?")){
		var = PedirVariable(nombre);
		g->variables.push_back(var);
		nombre++;
	}
	g->setNombre(nombre);
	return g;
}

// funcion auxiliar para pedir una nueva variable al usuario
variable* PedirVariable(char S){
	string produccion;
	string temp;
	int last = 0;
	variable* var = new variable;
	var->S = S;
	cout << S << "->" << endl;
	cin >> produccion;
	while(produccion.length() == 0){
		cout << "Por favor ingrese la(s) produccion(es)"<<endl;
		cin >>produccion;
	}
	for (int i = 0; i < produccion.length(); i++){
		if ((produccion[i] < 65 || produccion[i] > 90) && (produccion[i] < 97 || produccion[i] > 122) && produccion[i] != '|'){
			cout << "Entrada invalida" << endl;
			exit(0);
		}
		else if(produccion[i] == '|'){
			if (i == produccion.length()-1){
				cout << "Entrada invalida" << endl;
				exit(0);
			}
			temp = produccion.substr(last, i-last);
			var->producciones.push_back(temp);
			//cout << temp;			// Para debuggear la variable temp descomente esta linea
			last = i+1;
		}
	}
	temp = produccion.substr(last);
	var->producciones.push_back(temp);
	return var;
}

// Funcion para preguntar Si o No
bool Preguntar(string pregunta){
	cout << pregunta << "(S/N)" << endl;
	char r;
	cin >> r;
	if (r == 'S' || r == 's')
		return true;
	else if (r == 'n' || 'N')
		return false;
	else{
		cout << "Entrada invalida" << endl;
		return Preguntar(pregunta);
	}
}


// Funcion para comprobar la membresia de un string en algun GLC
// EL GLC debe estar en la forma normal de Chomsky
// Algoritmo CYK
bool membresia(glc* g, string s){
	// Variables iniciales
	int n = s.length(); // Longitud del string
	vector<char> tabla[n][n]; // tabla de CYK
	vector<char> temp; // Vector auxiliar
	string util = ""; // string auxiliar

	// Inicializar la tabla CYK con los valores de la primera fila
	for(int i = 0; i < n; ++i){
		for (auto v:g->variables){
			for (auto p:v->producciones){
				if(p.length() == 1 && p[0] == s[i]){
					tabla[0][i].push_back(v->S);
				}
			}
		}
	}

	// Si algun valor inicial no se encontró entonces el string no pertenece a la gramatica
	for (int i = 0; i < n; ++i){
		if (tabla[0][i].empty()){
			return false;
		}
	}



	// Comprobar todas las iteraciones, y los substrings de acuerdo a CYK
	for (int i = 1; i < n ; ++i){
		for (int j = 0; j < n-i; ++j){
			for (int k = 0; k <i; ++k){
				for (auto item:tabla[k][j]){
					for (auto item2:tabla[i-k-1][j+k+1]){
						util += (char)item;
						util += (char)item2;
						temp = g->buscar(util);
						util = "";
						if (!temp.empty()){
							for(auto it:temp){
								tabla[i][j].push_back(it);
							}
						}

					}
				}
			}
		}
	}

	// Imprimir tabla CYK
	/* Descomentar para implementar */
	/* 
	for (int i = 0;i < n; ++i){
		for (int j = 0; j <n-i;++j){
			cout << "(";
			for(auto item:tabla[i][j]){
				cout << item << ",";
			}
			cout << ")";
		}
		cout << endl;
	}*/

	// Si se obtuvo alguna variable para obtener el string entonces pertenece a la gramatica, en caso contrario no
	if (tabla[n-1][0].empty()){
		return false;
	}
	return true;
}

