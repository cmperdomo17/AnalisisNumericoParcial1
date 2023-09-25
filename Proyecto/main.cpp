
/**
 * @file main.cpp
 * Numerical Methods to find roots of functions
 * Methods implemented: Bisection, Regula Falsi, Secant, Newton-Raphson, Generalized Newton-Raphson, Muller
 * @authors Carlos Mario Perdomo Ramos <cmperdomo@unicauca.edu.co> - Daniel Fernando Solarte Ortega <dfsolarte@unicauca.edu.co>
*/

#include <cmath>
#include <iostream>
#include "solucion.h"
#include "biseccion.h"
#include "reglafalsa.h"
#include "newton_raphson.h"
#include "newton_generalizado.h"
#include "muller.h"
#include "secante.h"
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::isnan;
using std::make_pair;
using std::pair;
using std::string;
using std::to_string;

using raices::aproximacion;
using raices::biseccion;
using raices::muller;
using raices::newton_generalizado;
using raices::newton_raphson;
using raices::reglafalsa;
using raices::secante;
using raices::solucion;

void ejercicio_2();
void ejercicio_1();
void mostrar_aproximaciones(vector<pair<string, solucion>> soluciones, string funcstr);
void metodo_biseccion(string fstr);
void metodo_reglaFalsa(string fstr);
void metodo_secante(string fstr);

/**
 * @brief Main function
 * @details Main function to run the program
 * @return 0 
*/
int main()
{
    int opcion;
    do
    {
        cout << "\n==============================================================\n" << endl;
        cout << "Ingrese que ejercicio desea evaluar: \n\n";
        cout << "\n[1]. Ejercicio 1 \n";
        cout << "\n[2]. Ejercicio 2 \n";
        cout << "\n[3]. Salir \n";
        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            ejercicio_1();
            break;
        case 2:
            ejercicio_2();
            break;
        case 3:
            cout << "\nSaliendo..." << endl;
            exit(0);
            break;
        default:
            cout << "\nOpcion invalida" << endl;
        }

    } while (opcion != 3);

    return 0;
}

/**
 * @brief Ejercicio 1
 * @return void
*/
void ejercicio_1()
{
    int metodo;
	
	string constante = "(sqrt(5)/sqrt(2))";
	string numerador = "((x*(10+x))^5)^(1.0/3.0)";
	string denominador = "((10 + 2*x*sqrt(2))^2)^(1.0/3.0)";
    string fstr = constante+"*(("+numerador+")/("+denominador+")) - 101.08";
	
    cout << "\n1. Ejercicio 1" << endl;
    cout << "\nFuncion: " << fstr << endl;
    cout << "\nIngrese por que metodo desea hallar la raiz: \n\n";
    cout << "[1]. Metodo de Biseccion \n";
    cout << "[2]. Metodo de Regla Falsa \n";
    cout << "[3]. Metodo de la Secante \n";
    cout << "[4]. Regresar al menu principal \n";

    cout << "\nIngrese una opcion: ";
    cin >> metodo;

    switch (metodo)
    {
    case 1:
        metodo_biseccion(fstr);
        break;
    case 2:
        metodo_reglaFalsa(fstr);
        break;
    case 3:
        metodo_secante(fstr);
        break;
    case 4:
        // Regresar al menú principal
        return;
    default:
        cout << "\nOpcion invalida" << endl;
    }
}

/**
 * @brief Ejercicio 2
 * @return void
*/
void ejercicio_2()
{
	string fstr("x^8 - x^7 + 35x^5 + 426x^4 - 170x^3 - 1827x^2 - 255x"); // Funcion
	string dfstr("8x^7 - 7x^6 + 175x^4 + 1704x^3 - 510x^2 - 3654x - 255"); // Derivada
	string d2fstr("56x^6 - 42x^5 + 700x^3 + 5112x^2 - 1020x - 3654"); // Segunda derivada

	double erp = 1e-8f;
	double n;
	n = 10;

	// Puntos iniciales para cada método

	// Método de Newton Raphson

	// Raíz 1 = -1.90012
	double nrP0 = -1.9f;  
	// Raíz 2 = -0.1421
	double nrP1 = 0.14f;   
	// Raíz 3 = 2.1249
	double nrP2 = 2.1252f;    
	// Raíz 4 = 0
	double nrP3 = 0.0f;

	// Método de Newton Generalizado

	// Raíz 1 = -1.900
	double nrgP0 = -1.9f;  
	// Raíz 2 = -0.1421
	double nrgP1 = -0.14f;  
	// Raíz 3 = 2.1249
	double nrgP2 = 2.1252f;  
	// Raíz 4 = 0
	double nrgP3 = 0.0f;

	// Método de Muller

	// Raíz 1 = -1.900
	double m1_x0 = -1.89;     // Punto más cercano a la raíz
	double m1_x1 = -1.90;     // Punto medio
	double m1_x2 = -1.91;     // Punto más alejado

	// Raíz 2 = -0.1421
	double m2_x0 = -0.13;   // Punto más cercano a la raíz
	double m2_x1 = -0.14;   // Punto medio
	double m2_x2 = -0.143;   // Punto más alejado

	// Raíz 3 = 2.1249
	double m3_x0 = 2.1;    // Punto más cercano a la raíz
	double m3_x1 = 2.1252;  // Punto medio
	double m3_x2 = 2.13;   // Punto más alejado

	// Raíz 4 = 0
	double m4_x0 = 0.1;     // Punto más cercano a la raíz
	double m4_x1 = 0.0;     // Punto medio
	double m4_x2 = -0.1;    // Punto más alejado

	// Vector de soluciones para cada método
	vector<pair<string, solucion>> soluciones = {
		{make_pair("\nNewton-Raphson desde p0= " + to_string(nrP0), newton_raphson(fstr, dfstr).calcular(nrP0, erp, n))},
		{make_pair("\nNewton-Raphson desde p0= " + to_string(nrP1), newton_raphson(fstr, dfstr).calcular(nrP1, erp, n))},
		{make_pair("\nNewton-Raphson desde p0= " + to_string(nrP2), newton_raphson(fstr, dfstr).calcular(nrP2, erp, n))},
		{make_pair("\nNewton-Raphson desde p0= " + to_string(nrP3), newton_raphson(fstr, dfstr).calcular(nrP3, erp, n))},

		{make_pair("\nNewton-Raphson generalizado desde p0= " + to_string(nrgP0), newton_generalizado(fstr, dfstr, d2fstr).calcular(nrgP0, erp, n))},
		{make_pair("\nNewton-Raphson generalizado desde p0= " + to_string(nrgP1), newton_generalizado(fstr, dfstr, d2fstr).calcular(nrgP1, erp, n))},
		{make_pair("\nNewton-Raphson generalizado desde p0= " + to_string(nrgP2), newton_generalizado(fstr, dfstr, d2fstr).calcular(nrgP2, erp, n))},
		{make_pair("\nNewton-Raphson generalizado desde p0= " + to_string(nrgP3), newton_generalizado(fstr, dfstr, d2fstr).calcular(nrgP3, erp, n))},

		{make_pair("\nMuller con p0= " + to_string(m1_x0) + ", p1=" + to_string(m1_x1) + ", p2=" + to_string(m1_x2), muller(fstr).calcular(m1_x0, m1_x1, m1_x2, erp, n))},
		{make_pair("\nMuller con p0= " + to_string(m2_x0) + ", p1=" + to_string(m2_x1) + ", p2=" + to_string(m2_x2), muller(fstr).calcular(m2_x0, m2_x1, m2_x2, erp, n))},
		{make_pair("\nMuller con p0= " + to_string(m3_x0) + ", p1=" + to_string(m3_x1) + ", p2=" + to_string(m3_x2), muller(fstr).calcular(m3_x0, m3_x1, m3_x2, erp, n))},
		{make_pair("\nMuller con p0= " + to_string(m4_x0) + ", p1=" + to_string(m4_x1) + ", p2=" + to_string(m4_x2), muller(fstr).calcular(m4_x0, m4_x1, m4_x2, erp, n))},
	};
	// Muestra las aproximaciones de cada método
	mostrar_aproximaciones(soluciones, fstr);
}

/**
 * @brief Impresión de las aproximaciones de cada método
 * @param soluciones Vector de soluciones
 * @param funcstr Función
 * @return void
*/
void mostrar_aproximaciones(vector<pair<string, solucion>> soluciones, string funcstr)
{
	cout << "\nAproximaciones para la funcion: " << funcstr << endl;

	// Recorre el vector de soluciones e imprime cada una
	for (auto &sol : soluciones)
	{
		cout << "\nRaiz de: " << funcstr << " \nMetodo utilizado: " << sol.first << endl;
		sol.second.imprimir();

		cout << "\n-------------------------------------------------------------------" << endl;
	}
}

/**
 * @brief Método de Bisección
 * @param fstr Función
 * @return void
*/
void metodo_biseccion(string fstr) {
	
	double xa, xb;
	int n;
	
	cout << "\nFuncion a evaluar: " << fstr << endl;
	cout << "\nIngrese el valor inferior del intervalo: ";
	cin >> xa;
	cout << "\nIngrese el valor superior del intervalo: ";
	cin >> xb;
	/*
	cout << "\nIngrese la tolerancia (en porcentaje): ";
	cin >> tol;
	*/
	cout << "\nIngrese el maximo numero de iteraciones: ";
	cin >> n;
	//Crear una instancia de biseccion pasando 
	//la funcion como parametro
	
	biseccion bis(fstr);
	
	solucion sol = bis.calcular(xa, xb,1e-6, n);
	
	sol.imprimir();
}

/**
 * @brief Método de Regla Falsa
 * @param fstr Función
 * @return void
*/
void metodo_reglaFalsa(string fstr) {
	
	double xi, xs;
	int n;
	
	cout << "\nFuncion a evaluar: " << fstr << endl;
	cout << "\nIngrese el valor inferior del intervalo: ";
	cin >> xi;
	cout << "\nIngrese el valor superior del intervalo: ";
	cin >> xs;
	/*
	cout << "\nIngrese la tolerancia (en porcentaje): ";
	cin >> tol;
	*/
	cout << "\nIngrese el maximo numero de iteraciones: ";
	cin >> n;
	//Crear una instancia de regla falsa pasando 
	//la funcion como parametro
	
	reglafalsa rf(fstr);
	
	solucion sol = rf.calcular(xi,xs,1e-6,n);
	
	sol.imprimir();
	
}

/**
 * @brief Método de la Secante
 * @param fstr Función
 * @return void
*/
void metodo_secante(string fstr){
	double x0, x1;
	int n;

	cout << "\nIngrese el valor de x0: ";
	cin >> x0;
	cout << "\nIngrese el valor de x1: ";
	cin >> x1;
	/*
	cout << "\nIngrese la tolerancia (en porcentaje): ";
	cin >> tol;
	*/
	cout << "\nIngrese el maximo numero de iteraciones: ";
	cin >> n;
	//Crear una instancia de secante pasando 
	//la funcion como parametro
	
	secante sec(fstr);
	
	solucion sol = sec.calcular(x0,x1,1e-6,n);
	
	sol.imprimir();
}
