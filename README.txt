Proyecto 4, Matematicas computacionales.
Daniel Monzalvo, A01021514
danielmonr@gmail.com
https://github.com/danielmonr/Chomsky-CYK

Manual de Usuario:
	Para compilar solo descarge el codigo, dirigase a la carpeta y en una terminal escriba el comando 'make'.
	Para correrlo utilize el comando './gramaticas'.

	Utilizar el programa:
		Para Introducir un GLC, empiece por la variable inicial S, las producciones deben de ir sin espacios y separadas por |.
		Solo pueden ser validas variables en mayusculas y terminales en minusculas.
		No ingrese numeros o simbolos.
		Para generar nuevas variables oprima s y la tecla Enter cuando se le pregunte.
		Una vez finalizado ingrese n y presione Enter para convertir su GLC en su forma normal de Chomsky.
		En pantalla apareceran las dos formas.
		Finalmente ingrese el string que quiere comprobar (sin espacios, ni numeros, ni simmbolos).
		Encaso de que pertenezca aparecera en pantalla verdadero, en caso contrario falso.
		
Forma Normal Utilizada:
	El programa utiliza la forma normal de Chomsky para poder utilizar el algoritmo de CYK.
	El programa hace la transformacion automaticamente a esta forma normal.
	El procedimiento es el que sigue:
		Chomsky
		paso 1: S no puede estar del lado derecho (añadir un nuevo start, en caso de que esto ocurra)
		paso 2: Quitar las producciones a nulos (en este caso no se permiten nulos)
		paso 3; quitar todas las reglas A->B, se transforma B en su(s) definicion(es);
		paso 4: Quitar todas las reglas con más de 2 variables, se agregan variables para asegurarlo
		paso 5: Modificar aB por AB A->a

CYK:
	CYK es un algoritmo de parseo utilizado para resolver el problema de la memresia.
	Este algoritmo necesita que la gramatica este en la forma normal de Chomsky.
	utiliza una tabla triangular que va llenando con substrings como sigue:
		para n = 4

		x1,4  -    -    -
		x1,3 x2,4  -    -
		x1,2 x2,3 x3,4  -
		x1,1 x2,2 x3,3 x4,4

	La Tabla se llena con las posibles variables que llevan a un substring desde otros dos más pequeños.
	Ejemplo: x2,4 -> x2,2 x3,4
	Para esto se llena la fila de abajo con las variables terminales, las iteraciones luego van de abajo hacia arriba y de izquierda a derecha.
	Si la celda de arriba se llena con alguna(s) variable(s), el string pertenece a la gramatica.

Codigo:
	Lenguaje utilizado: c++ version 11

Referencias:
	codigo propio.
	Explicacion Chomsky: Profesor Victor de la Cueva
	Eplicacion CYK: http://web.cs.ucdavis.edu/~rogaway/classes/120/winter12/CYK.pdf
