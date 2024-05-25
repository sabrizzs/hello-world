#include <cmath>
#include <iostream>

class FormaGeometrica {
 private:
  char simbolo_;

 protected:
  FormaGeometrica(char simbolo);
  virtual ~FormaGeometrica() = default;

 public:
  void imprime();
  virtual float calculaArea() = 0;
};

FormaGeometrica::FormaGeometrica(char simbolo)
  : simbolo_(simbolo) {}

void FormaGeometrica::imprime() {
  std::cout << "Forma Geometrica "
            << simbolo_ << " " << calculaArea()
            << std::endl;
}

////////////////////////////////////////////////////////////////////////

class Quadrado : public FormaGeometrica {
 private:
  float lado_;

 public:
  Quadrado(float lado);
  virtual ~Quadrado() = default;

  float calculaArea() override;
};

Quadrado::Quadrado(float lado)
  : FormaGeometrica('q'), lado_(lado) {}

float Quadrado::calculaArea() {
  return lado_ * lado_;
}

////////////////////////////////////////////////////////////////////////

class Retangulo : public FormaGeometrica {
 private:
  float altura_;
  float largura_;

 public:
  Retangulo(float altura, float largura);
  virtual ~Retangulo() = default;

  float calculaArea() override;
};

Retangulo::Retangulo(float altura, float largura)
  : FormaGeometrica('r'), altura_(altura), largura_(largura) {}

float Retangulo::calculaArea() {
  return altura_ * largura_;
}

////////////////////////////////////////////////////////////////////////

class Circulo : public FormaGeometrica {
 private:
  float raio_;

 public:
  Circulo(float raio);
  virtual ~Circulo() = default;

  float calculaArea() override;
};

Circulo::Circulo(float raio)
  : FormaGeometrica('c'), raio_(raio) {}

float Circulo::calculaArea() {
  return M_PI * raio_ * raio_;
}

////////////////////////////////////////////////////////////////////////

class Triangulo : public FormaGeometrica {
 private:
  float altura_;
  float base_;

 public:
  Triangulo(float altura, float base);
  virtual ~Triangulo() = default;

  float calculaArea() override;
};

Triangulo::Triangulo(float altura, float base)
  : FormaGeometrica('t'), altura_(altura), base_(base) {}

float Triangulo::calculaArea() {
  return (altura_ * base_)/2;
}

////////////////////////////////////////////////////////////////////////

int main() {
  // Quadrado* q = new Quadrado(5.0);
  // q->imprime();
  // delete q;
  //
  // Retangulo* r = new Retangulo(4.0, 3.0);
  // r->imprime();
  // delete r;
  //
  // Circulo* c = new Circulo(1.0);
  // c->imprime();
  // delete c;
  // Triangulo* t = new Triangulo(5.0, 3.0);
  // t->imprime();
  // delete t;

  Quadrado q(5.0);
  q.imprime();
  // Quadrado::imprime(q);

  Retangulo r(4.0, 3.0);
  r.imprime();

  Circulo c(1.0);
  c.imprime();

  Triangulo t(5.0, 3.0);
  t.imprime();

  return 0;
}