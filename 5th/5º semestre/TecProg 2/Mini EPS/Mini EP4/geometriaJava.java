abstract class FormaGeometrica {
  char simbolo;

  protected FormaGeometrica(char simbolo) {
    this.simbolo = simbolo;
  }

  public void imprime() {
    System.out.println(String.format(
        "Forma Geométrica %c %f", simbolo, calculaArea()
    ));
  }

  public abstract double calculaArea();
}

class Quadrado extends FormaGeometrica {
  private double lado;

  public Quadrado(double lado) {
    super('q');
    this.lado = lado;
  }

  @Override
  public double calculaArea() {
    return lado * lado;
  }
}

class Retangulo extends FormaGeometrica {
  private double altura;
  private double largura;

  public Retangulo(double altura, double largura) {
    super('r');
    this.altura = altura;
    this.largura = largura;
  }

  @Override
  public double calculaArea() {
    return altura * largura;
  }
}

class Circulo extends FormaGeometrica {
  private double raio;

  public Circulo(double raio) {
    super('c');
    this.raio = raio;
  }

  @Override
  public double calculaArea() {
    return Math.PI * raio * raio;
  }
}

class Triangulo extends FormaGeometrica {
  private double altura;
  private double base;

  public Triangulo(double altura, double base) {
    super('t');
    this.altura = altura;
    this.base = base;
  }

  @Override
  public double calculaArea() {
    return (altura * base)/2;
  }
}

public class Geometria {
  public static void main(String args[]) {
    Quadrado q = new Quadrado(5.0);
    q.imprime();
    // Quadrado::imprime(q);

    Retangulo r = new Retangulo(4.0, 3.0);
    r.imprime();

    Circulo c = new Circulo(1.0);
    c.imprime();

    Triangulo t = new Triangulo(5.0, 3.0);
    t.imprime();
  }
}