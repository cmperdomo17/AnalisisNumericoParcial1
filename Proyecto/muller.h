#ifndef MULLER_H
#define MULLER_H

#include "expression.h"
#include "solucion.h"
#include <cmath>

using std::string;
using raices::solucion;
using raices::calcular_erp;
using raices::es_cero;

namespace raices {
	/**
	* @brief Implementacion del metodo de Muller
	*/
	class muller{
	public:
		/**
		* @brief Construye una nueva instancia de Muller
		* @param strFunc Texto de la funcion
		*/
		muller(string strFunc):f(strFunc){
		}
		
		/**
		* @brief Calcula raiz de la funcion a partir de x0, x1, y x2
		* @param x0 Primera aproximacion dada
		* @param x1 Segunda aproximacion dada
		* @param x2 Tercera aproximacion dada
		* @param tol Tolerancia (Error relativo porcentual)
		* @param n Numero maximo de iteraciones
		* @return Solucion encontrada. La raiz es NAN si no se encuentra
		*/
		solucion calcular(double x0, double x1, double x2, double tol, int n){
			solucion sol;
			
            
            
			//Paso 1
			double h1 = x1 - x0;
			double h2 = x2 - x1;
			double delta1 = (f(x1) - f(x0))/h1;
			double delta2 = (f(x2) - f(x1))/h2;
			double a = (delta2 - delta1)/(h2 - h1);
			double b;
			int & i = sol.iteraciones = 2;
            
			
			if(fabs(f(x0))< DBL_EPSILON){
				sol.raiz=x0;
				return sol;
			}else if(fabs(f(x1))< DBL_EPSILON){
				sol.raiz=x1;
				return sol;
			}else if(fabs(f(x2))< DBL_EPSILON){
				sol.raiz=x2;
				return sol;
			}
			//Paso 2
			while(i<=n){
				//Paso 3
				b=delta2 + (h2 * a);
				double D = sqrt(pow(b,2) - (4*f(x2)*a));
				double E;
				
				//Paso 4
				if(fabs(b - D) < fabs(b + D)){
					E = b + D;
				}else{
					E = b - D;
				}
				
				//Paso 5
				double h = (-2*f(x2))/E;
				double p = x2 + h;
				
				//Paso 6
				double erp = calcular_erp(p,x2);
				sol.adicionar({x2,p,erp});
				
				if(erp < tol){
					sol.raiz=p;
					return sol;
				}
				
				//Paso 7
				x0=x1;
				x1=x2;
				x2=p;
				h1=x1-x0;
				h2=x2-x1;
				delta1 = (f(x1)-f(x0))/h1;
				delta2 = (f(x2)-f(x1))/h2;
				a = (delta2-delta1)/(h2+h1);
				i++;
				
			}
			
			return sol;
		}
	private:
		Expression f; /*!< Evaluador de la funcion */
	};
};

#endif