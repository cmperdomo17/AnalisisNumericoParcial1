#ifndef NEWTON_GENERALIZADO_H
#define NEWTON_GENERALIZADO_H

#include <string>
#include <cmath>
#include "Expression.h"
#include "solucion.h"

using std::string;
using raices::solucion;
using raices::calcular_erp;
using raices::es_cero;

namespace raices {
	/**
	 * @brief Implementacion del metodo de Newton Raphson generalizado
	*/
	class newton_generalizado { //El nombre del constructor DEBE ser igual al nombre de la clase
	public:
		/**
		* @brief Construye una nueva instancia de Newton Raphson
		* @param strFunc Texto de la funcion
		* @param strdFun Texto de la derivada de la funcion
        * @param strd2Fun Segunda derivada, para usar la version generalizada
		*/
		newton_generalizado(string strFunc, string strdFunc, string strd2Func):f(strFunc), df(strdFunc), d2f(strd2Func) { //Se inicializaron las instancias de la funcion y derivada

			// Verificar si el usuario desea usar Newton Raphson generalizado
			if (strd2Func.length() > 0) {
				usar_generalizado = true;
			}
	
    	}
		
		/**
		* @brief Calcula la raiz de la funcion a partir de p0
		* @param p0 Aproximacion inicial
		* @param tol Tolerancia (error relativo porcentual)
		* @param n Numero maximo de iteraciones
		* @return Solucion encontrada. La raiz es NAN si no se encuentra la solucion.
		*/
		solucion calcular(double p0, double tol, int n) {
				solucion sol;
				
				//Paso 1
				int & i = sol.iteraciones = 1;
				//Paso 2
				
				//Validar si el usuario especificifico una raiz
				if ( es_cero(f(p0)) ) {
					//Guardar la raiz
					sol.raiz = p0;
					// TODO sol.iteraciones = i;
					return sol;
				}
				
				//Paso 2

				while (i < n) {	
					//Paso 3 
					double num = f(p0)*df(p0);
                    double den = pow(df(p0),2) - f(p0)*d2f(p0);
                    double p = p0 - (num/den);

					//Paso 4
					//Calcular el error relativo porcentual
					double erp = calcular_erp(p, p0);
					
					//Adicionar la aproximacion
					sol.adicionar({p0, p, erp});
					
					if (es_cero(f(p))) {
						//Guardar la raiz
						sol.raiz = p;
						//TODO sol.iteraciones = i;
						return sol;
					}
					//Paso 5
					i++;
					
					//Paso6
					p0 = p;
				}
				
				
				return sol;
		}
	private:
		Expression f; /*!< Evaluador de la funcion */
		Expression df; /*!< Evaluador de la derivada de la funcion */
        Expression d2f; /*!< Evaluador de la segunda derivada de la funcion */
        bool usar_generalizado = false; /*!< Indica si se debe usar la version generalizada */  
	};
}

#endif
