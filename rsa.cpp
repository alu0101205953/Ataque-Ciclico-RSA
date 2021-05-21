#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define RESET   "\033[0m"

std::vector<int> euclides(int a, int b) {
  std::vector<int> z = {0, 1};
  std::vector<int> x = {a, b};
  int tmpx, tmpz;
  while((x[0] % x[1]) != 0) {
    tmpx = x[0] % x[1];
    tmpz = (-1 * (x[0] / x[1]) * z[1]) + z[0];
    while(tmpz < 0) tmpz += a;
    x[0] = x[1];
    x[1] = tmpx;
    z[0] = z[1];
    z[1] = tmpz;
  }
  std::vector<int> result;
  result.push_back(z[1]);
  result.push_back(x[1]);
  return result;
}

int exponenciacion(int a, int b, int m) {
  int x = 1;
  int y = a % m;
  while((b > 0) && (y > 1)) {
    if ((b % 2) != 0) {
      x = (x*y) % m;
      b = b - 1;
    }
    else {
      y = (y * y) % m;
      b = b / 2;
    }
  }
  return x;
}

bool primality(int p) {
  if ((p == 0) || (p == 1)) {
    return false;
  } else if((p == 2) || (p == 3) || (p == 5) || (p == 7) || (p == 11)) { //Comprobar que no es un primo pequeño
    return true;
  } else if((p % 2 != 0) || (p % 3 != 0) || (p % 5 != 0) || (p % 7 != 0) || (p % 11 != 0)) { //Comprobar que no es divisible por nigún primo pequeño
    std::vector<int> random;
    for(int i = 0; i < p / 2; i++) {
      random.push_back(2 + (std::rand() % (p - 3))); //Elegir enteros aleatorios entre 2 y p-1
    }
    std::vector<int> result;
    for(int i = 0; i < random.size(); i++) {
      result.push_back(exponenciacion(random[i], ((p-1) / 2), p));
    }
    bool negative = false;
    for (int i = 0; i < result.size(); i++) { //Si para todo resultado existe alguno distinto dde 1 y -1, p es compuesto
      if((result[i] != 1) && (result[i] != (p - 1))) {
        return false;
      } else if (result[i] == (p-1)) { //Si todos los resultados = 1, p es compuesto
        negative = true;  //Si existe i tal que el resultado es -1, p puede ser compuesto
      }
    }
    if(negative) return true;
    else return false;
  }
}

int logbase(int a, int base) {
   return (int)(log(a) / log(base));
}

int cyclicalAttack(int C, int e, int n) {
  std::vector<int> result = {};
  result.push_back(exponenciacion(C, e, n));
  while(result[result.size() - 1] != C) {
    result.push_back(exponenciacion(result[result.size() - 1], e, n));
    if(result[result.size() - 1] == C) {
      return result[result.size() - 2];
    }
  }
}

/*void RSA(int p, int q, int d, int C) {
  if(primality(p) && primality(q)) {  //Se cumprueba si p y q son primos con el tests Lehmann-Peralta
    int phi = (p - 1) * (q - 1); //Se calcula phi
    std::vector<int> result = euclides(phi, d); //Se comprueba que d y phi son primos (mcd = 1) y se calcula el inverso de d
    if(result[1] == 1) {
      int e = result[0]; // e = inverso de d
      int n = p * q; //Se calcula n
      int cypher = exponenciacion(C, e, n); //Se calcula el criptograma cifrado
      int attack = cyclicalAttack(C, e, n);
      std::cout << BOLDRED << "Se ha capturado el criptograma y realizado un ataque por cifrado cíclico. La clave enmascarada es: " << RESET << attack << std::endl; 
    } else {
      std::cout << "Los enteros " << d << " y " << phi << " no son primos" << std::endl;
    }
  } else {
    std::cout << "Los enteros " << p << " y " << q << " no son primos" << std::endl; 
  }
}*/


int main(void) {
  int n, e, C;
  std::cout << "ATAQUE POR CIFRADO CÍCLICO A RSA\n";
  std::cout << "Introduzca la clave pública:\nn:  ";
  std::cin >> n;
  std::cout << "\ne: ";
  std::cin >> e;
  std::cout << "\nIntroduzca el criptograma capturado: ";
  std::cin >> C;
  std::cout << std::endl; 
  int attack = cyclicalAttack(C, e, n);
  std::cout << BOLDRED << "Se ha capturado el criptograma y realizado un ataque por cifrado cíclico. La clave enmascarada es: " << RESET << attack << std::endl; 

  return 0; 
}