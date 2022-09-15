//laboratorio #3 recursividad hecho por Carlos D Barrientos -1040121
#include "pch.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

//codigo del menu utlizado del ejemplo de recursividad del portal
//opciones del menu para ingresar
const int multiplication_option = 1;
const int palindromasCheck_option = 2;
const int baseConvertor_option = 3;
const int exit_option = 0;

//EJERCICIO 1
//este es el metodo del primer ejercicio
int multiplicacionDosNumeros(int numero1, int numero2, int contador) {
	if (contador == numero1) {
		return numero2;
	}
	else {
		contador++;
		return (numero2 + multiplicacionDosNumeros(numero1, numero2, contador));
	}

}

//EJERCICIO 2
//Metodo recursivo para invertir las palabras y mostrar el resultado por pantalla
void verificacionPalindromas(string palabra, string palabraInvertida, int posicion, int posicionInvertida) {
	if (posicionInvertida==-1) //se iguala a -1 porque el parametro "posicionInvertida" cuando llega al 0 ya no cuenta el valor de la posicion 0 y lo tiene que contar
	{
		if (palabraInvertida == palabra) {
			cout << "la palabra " << palabra << " es palindroma, aqui te muestro su inversión: "<<palabraInvertida << endl;
		}
		else {
			cout << "la palabra " << palabra << " no es palindroma, aqui te muestro su inversión: " << palabraInvertida << endl;
		}
	}
	else {
		palabraInvertida += palabra[posicionInvertida];//se añade desde la utlima posicion hasta la primera
		verificacionPalindromas(palabra, palabraInvertida, posicion, (posicionInvertida - 1));
	}
}

//metodo para leer los datos del archivo CSV que se encuentra en la carpeta solucion del proyecto, devuelve un vector 
//creditos:Luis Cabrera Benito -Youtube
vector<string> leerDatosCSV() {
	ifstream infile("palindromas.csv");
	string line = "";
	vector<string> datos_csv;
	while (getline(infile, line)) {
		stringstream strstr(line);
		string word = "";
		while (getline(strstr, word, ',')) {
			datos_csv.push_back(word);
		}
	}
	return datos_csv;
}
//este metodo sirve para traer solamente la palabra que vamos a comprobar del vector.
void separacionDePalindromas() {
	string palabraContadora="";
	int posicion=0;
	int posicionPalabraNormal = 0;
	int lengthLeerDatosCSV = leerDatosCSV().size();
	for (int i = 0; i < lengthLeerDatosCSV; i++)
	{
		posicion = (leerDatosCSV().at(i).size()-1);
		verificacionPalindromas(leerDatosCSV().at(i), palabraContadora, posicionPalabraNormal, posicion);
	}
}

//EJERCICIO 3

//metodo recursivo para convertir bases a decimal

int convertidorADecimal(int numeroSinConvertir, int baseOrigen, int numeroConvertido, int contadorPotencias) {
	if (numeroSinConvertir<=0) {
		return numeroConvertido;
	}
	else {
		numeroConvertido += (numeroSinConvertir % 10 * pow(baseOrigen, contadorPotencias));//Codigo referenciado de Programming Art -Octal a Decimal
		numeroSinConvertir = numeroSinConvertir / 10;
		contadorPotencias ++;
		return(convertidorADecimal(numeroSinConvertir, baseOrigen, numeroConvertido, contadorPotencias));
	}
}

//metodo para convertir de decimal a base M
void convertidorABaseM(int baseDestino, int numeroDecimal) { //codigo utilizado en base a StackOverflow

	
	int numeroDecimalCopia, resultado=0, contador = 0;
	numeroDecimalCopia = numeroDecimal;

	do {
		numeroDecimalCopia = numeroDecimalCopia / baseDestino;
		contador++;
	} while (numeroDecimalCopia != 0);
	numeroDecimalCopia = numeroDecimal;

	int result[25];

	if (baseDestino > 1 && baseDestino < 10) {
		for (int i = contador - 1; i >= 0; --i) {
			resultado = (int)numeroDecimalCopia % (int)baseDestino;

			result[i] = resultado;

			numeroDecimalCopia = numeroDecimalCopia / baseDestino;
		}
		for (int i = 0; i < contador; ++i) {
			cout <<result[i];
		}
		cout << " en base (" << baseDestino << ") es la conversion de la operacion solicitada" << endl;
	}
	else if (baseDestino > 9 && baseDestino < 17) { //esta validacion es para que incluya las letras en la conversion
		for (int i = contador - 1; i >= 0; --i) {
			resultado = numeroDecimalCopia % baseDestino;
			switch (resultado) {
			case 10: 
				resultado = 'A'; 
				break;
			case 11: 
				resultado = 'B'; 
				break;
			case 12: 
				resultado = 'C'; 
				break;
			case 13: 
				resultado = 'D';
				break;
			case 14: 
				resultado = 'E'; 
				break;
			case 15: 
				resultado = 'F'; 
				break;
			}
			result[i] = resultado;
			numeroDecimalCopia = numeroDecimalCopia / baseDestino;
		}
		for (int i = 0; i < contador; ++i) {//validacion para imprimir los datos
			cout << result[i];
		}
		cout << "(" << baseDestino << ")" << endl;
	}
	if (baseDestino < 0 && baseDestino > 17) {
		cout << "No se trabaja con ese tipo de datos en este programa"<<endl;;
	}

}


//Validador de entrada de solo 0s y 1s, referenciado de Tutos Edgard y StackOverflow
bool EsUnNumero(char texto[100])
{
	int valor=0, contador=0;
	string suplente=texto;
	int comparacion = suplente.length();
	char letra;
	int ini = 48;//codigo ASCII
	int fin = 49;
	for (int i = 0; i <=comparacion; i++)
	{
		letra = texto[i];
		valor = letra;
		for (int j = ini; j <=fin; j++)
		{
			if (valor==j)
			{
				contador++;
			}
		}
	}
	if (comparacion==contador)
	{
		return true;
	}
	else {
		return false;
	}
}
//menu para inicializar las operaciones
void opcionesMenuBases() {
	//variables para el convertidor de bases
	int baseOrigen=0,baseDestino=0, numeroAConvertir=0;
	char numeroBinario[100];
	//varaibles de prueba para convertir a decimal
	int contador = 0;
	int contadorExponentes = 0;
	do
	{
		cout << "Bienvenido al convertidor de bases" << endl << "Cual es la base origen del numero" << endl;
		try
		{
			cin >> baseOrigen;
		}
		catch (const std::exception&)
		{
			cout << "no se puede usar esa base de origen";
		}
	} while (baseOrigen==0);
	
	if (baseOrigen == 2) {
		cout << "Escriba el numero binario que desea convertir" << endl;
		cin >> numeroBinario;
		if (EsUnNumero(numeroBinario)) {
			int numeroBinarioInt;
			cout << "Escriba la base destino a la que desea convertir el numero" << endl;
			try
			{
				cin >> baseDestino;
			}
			catch (const std::exception&)
			{
				cout << "no se puede trabajar con ese dato";
			}
			numeroBinarioInt = atof(numeroBinario);
			int numeroEnDecimalBinario= convertidorADecimal(numeroBinarioInt, 2, contador, contadorExponentes);
			convertidorABaseM(baseDestino, numeroEnDecimalBinario);
		}
		else {
			cout << "no escribiste bien";
		}
	}
	else {
		cout << "Escriba el numero que desea convertir" << endl;
		try
		{
			cin >> numeroAConvertir;
		}
		catch (const std::exception&)
		{
			cout << "no se puede trabajar con ese dato";
		}
		cout << "Escriba la base destino a la que desea convertir el numero" << endl;
		try
		{
			cin >> baseDestino;
		}
		catch (const std::exception&)
		{
			cout << "no se puede trabajar con ese dato";
		}

		//salida de datos decimal
		int numeroenDecimal = convertidorADecimal(numeroAConvertir, baseOrigen, contador, contadorExponentes);
		//salida de datos a base m 
		convertidorABaseM(baseDestino, numeroenDecimal);
	}
}




//seleccion de menu
int menu() {
	cout << "\n1.Calcular la mutliplicacion de dos números" << endl;
	cout << "\n2.Comprobacion de palabras palindromas por csv " << endl;
	cout << "\n3.Conversion de base M a base N " << endl;
	cout << "\n4.Salir" << endl;
	cout << "\nIngrese la opcion que desee realizar" << endl;

	int option;
	cin >> option;
	return option;
}

//envio a funciones responsables del menu
int handleOption(int option) {
	//variables de la multiplicacion de dos numeros
	int numero1 = 0, numero2 = 0, contador = 1;
	switch (option)
	{
	case multiplication_option:
		cout << "EJERCICIO 1: MULTIPLICACIÓN DE 2 NÚMEROS" << endl;

		do
		{
			try
			{
				do
				{
					cout << "Por favor escriba el primer numero " << endl;
					cin >> numero1;
				} while (numero1 <= 0 || numero1 > 10000);
				do
				{
					cout << "Por favor escriba el segundo numero " << endl;
					cin >> numero2;
				} while (numero2 <= 0 || numero2 > 10000);
				cout << "El resultado de la multiplicacion es "<< multiplicacionDosNumeros(numero1, numero2, contador);
			}
			catch (const std::exception&)
			{
				cout << "No se puede trabajar con ese tipo de datos" << endl;
			}
		} while (numero1==0 &&numero2==0);
		
		break;
	case palindromasCheck_option:
		cout << "EJERCICIO 2: COMPROBACIÓN DE PALABRAS PALINDROMAS" <<endl;
		separacionDePalindromas();
		break;
	case baseConvertor_option:
		cout << "EJERCICIO 3: CONVERSIÓN DE BASES M A N" << endl;
		opcionesMenuBases();
		break;
	case exit_option:
		cout << "Adios" << endl;
		break;
	default:
		cout << "Opcion no válida" << endl;
		return int::MaxValue;
	}
	return option;
}

//codigo del main
int main()
{
	int option;
	do
	{
		option = menu();
		option = handleOption(option);
	} while (option > 0);

}
