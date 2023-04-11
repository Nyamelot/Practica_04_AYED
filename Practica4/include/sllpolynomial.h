// AUTOR: José Ángel Portillo García
// FECHA: 07/04/2023
// EMAIL: alu0101568232@ull.edu.es
// VERSION: 2.0
// ASIGNATURA: Algoritmos y Estructuras de Datos
// PRÁCTICA Nº: 4
// ESTILO: Google C++ Style Guide
// COMENTARIOS:

#ifndef SLLPOLYNOMIAL_H_
#define SLLPOLYNOMIAL_H_

#include <iostream>
#include <math.h>  // fabs, pow

#include "pair_t.h"
#include "sll_t.h"
#include "vector_t.h"

#define EPS 1.0e-6

typedef pair_t<double> pair_double_t;  // Campo data_ de SllPolynomial
typedef sll_node_t<pair_double_t> SllPolyNode;  // Nodos de SllPolynomial

// Clase para polinomios basados en listas simples de pares
class SllPolynomial : public sll_t<pair_double_t> {
 public:
  // constructores
  SllPolynomial(void) : sll_t() {};
  SllPolynomial(const vector_t<double>&, const double = EPS);

  // destructor
  ~SllPolynomial() {};

  // E/S
  void Write(std::ostream& = std::cout) const;
  
  // operaciones
  double Eval(const double) const;
  bool IsEqual(const SllPolynomial&, const double = EPS) const;
  void Sum(const SllPolynomial&, SllPolynomial&, const double = EPS);
};


bool IsNotZero(const double val, const double eps = EPS) {
  return fabs(val) > eps;
}

// FASE II
// constructor
SllPolynomial::SllPolynomial(const vector_t<double>& v, const double eps) {
  for (int i = v.get_size() - 1; i >= 0; i--) {
    pair_double_t data(v.at(i), i);
    SllPolyNode* nodo = new SllPolyNode;
    nodo -> set_data(data);
    if ((fabs(v.at(i)) > eps)) {
      push_front(nodo);
    }
  }
}

// E/S
void SllPolynomial::Write(std::ostream& os) const {
  os << "[ ";
  bool first{true};
  SllPolyNode* aux{get_head()};
  while (aux != NULL) {
    int inx{aux->get_data().get_inx()};
    double val{aux->get_data().get_val()};
    if (val > 0)
      os << (!first ? " + " : "") << val;
    else
      os << (!first ? " - " : "-") << fabs(val);
    os << (inx > 1 ? " x^" : (inx == 1) ? " x" : "");
    if (inx > 1)
      os << inx;
    first = false;
    aux = aux->get_next();
  }
  os << " ]" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const SllPolynomial& p) {
  p.Write(os);
  return os;
}


// Operaciones con polinomios

// FASE III
// Evaluación de un polinomio representado por lista simple
double SllPolynomial::Eval(const double x) const {
  double result{0.0};
  SllPolyNode* aux = get_head();
  while (aux != NULL) {
    result = result + (aux -> get_data().get_val() * pow(x, aux -> get_data().get_inx()));
    aux = aux -> get_next();
  }
  return result;
}

// Comparación si son iguales dos polinomios representados por listas simples
bool SllPolynomial::IsEqual(const SllPolynomial& sllpol,
			    const double eps) const {
  bool differents = false;
  SllPolyNode* aux1 = get_head();
  SllPolyNode* aux2 = sllpol.get_head();
  while (aux1 != NULL && aux2) {
    if (fabs(aux1 -> get_data().get_val() - aux2 -> get_data().get_val()) > eps) {
      return differents;
    }
    aux1 = aux1 -> get_next();
    aux2 = aux2 -> get_next();
  }
  return !differents;
}

// FASE IV
// Generar nuevo polinomio suma del polinomio invocante mas otro polinomio
void SllPolynomial::Sum(const SllPolynomial& sllpol,
			SllPolynomial& sllpolsum,
			const double eps) {
  SllPolyNode *aux1 = get_head();
  SllPolyNode *aux2 = sllpol.get_head();
  SllPolynomial aux_sum_poly;
  while (aux1 != NULL && aux2 != NULL) {
    if (aux1->get_data().get_inx() == aux2->get_data().get_inx()) {
      pair_double_t data(aux1->get_data().get_val() + aux2->get_data().get_val(), aux1->get_data().get_inx());
      SllPolyNode *nodo = new SllPolyNode(data);
      nodo->set_data(data);
      if (fabs(data.get_val()) > eps) {
        aux_sum_poly.push_front(nodo);
      }
      aux1 = aux1->get_next();
      aux2 = aux2->get_next();
    } else if (aux1->get_data().get_inx() < aux2->get_data().get_inx()) {
      pair_double_t data(aux1->get_data().get_val(), aux1->get_data().get_inx());
      SllPolyNode *nodo = new SllPolyNode(data);
      nodo->set_data(data);
      aux_sum_poly.push_front(nodo);
      aux1 = aux1->get_next();
    } else {
      pair_double_t data(aux2->get_data().get_val(), aux2->get_data().get_inx());
      SllPolyNode *nodo = new SllPolyNode(data);
      nodo->set_data(data);
      aux_sum_poly.push_front(nodo);
      aux2 = aux2->get_next();
    }
    if (aux1 == NULL && aux2 != NULL) {
      while (aux2 != NULL) {
        pair_double_t data(aux2->get_data().get_val(), aux2->get_data().get_inx());
        SllPolyNode *nodo = new SllPolyNode(data);
        nodo->set_data(data);
        aux_sum_poly.push_front(nodo);
        aux2 = aux2->get_next();
      }
    } else if (aux2 == NULL && aux1 != NULL) {
      while (aux1 != NULL) {
        pair_double_t data(aux1->get_data().get_val(), aux1->get_data().get_inx());
        SllPolyNode *nodo = new SllPolyNode(data);
        nodo->set_data(data);
        aux_sum_poly.push_front(nodo);
        aux1 = aux1->get_next();
      }
    }
  }
  SllPolyNode *aux3 = aux_sum_poly.get_head();
  while (aux3 != NULL) {
    pair_double_t data(aux3 -> get_data().get_val(), aux3 -> get_data().get_inx());
    SllPolyNode *nodo = new SllPolyNode(data);
    aux3 ->set_data(data);
    sllpolsum.push_front(nodo);
    aux3 = aux3->get_next();
  }
}

#endif  // SLLPOLYNOMIAL_H_
