#include <cmath>
#include <iostream>

// -----------------------------------------------
// Kod z instrukcji
// -----------------------------------------------

// funkcja liczy wartosc wielomianu interpolacyjnego Lagrange'a
// tablice *x i *y zawieraja wspolrzedne wezlow interpolacji
// n liczba wezlow interpolacji
// xx wartosc dla ktorej liczy sie wielomian
double lagrange(const double *x, const double *y, int n, double xx) {
  int i, j;
  double yint, ylag;

  yint = 0.0;
  for (i = 0; i < n; i++) {
    ylag = 1.0;
    for (j = 0; j < n; j++) {
      if (i == j)
        continue;

      ylag *= (xx - x[j]) / (x[i] - x[j]);
    }

    yint += y[i] * ylag;
  }

  return yint;
}

// oblicza calke metoda simpsona
double simpson(double a, double b, double (*pf)(double), int n) {
  double x = a;
  double h = (b - a) / (2 * n);
  double h2 = h * 2;
  double x1 = a + h;

  double suma = pf(a) + 4. * pf(x1) + pf(b);

  for (int i = 0; i < n - 1; i += 1) {
    x += h2;
    suma += 2. * pf(x) + 4. * pf(x + h);
  }
  return suma * h / 3.;
}

// Szuka rozwiazania rownania pf(x)=0 w przedziale (xa,xb) z dokladnoscia eps i
// wpisuje liczbę koniecznych iteracji do zmiennej, na która wskazuje i_iter xa
// i xb muszą spełniać pf(xa)*pf(xb)<0
double bisec(double xa, double xb, double (*pf)(double), double eps,
             int *i_iter) {
  int i;
  double fa, fb, xc, fc;

  fa = pf(xa);
  fb = pf(xb);

  if (fa * fb > 0.0) {
    *i_iter = -1;
    return 0;
  }

  for (i = 1; i <= 10000; i++) {
    xc = (xa + xb) / 2.;
    fc = pf(xc);

    if (fa * fc < 0.) {
      xb = xc;
      fb = fc;
    } else {
      xa = xc;
      fa = fc;
    }

    if (fabs(fc) < eps && fabs(xb - xa) < eps)
      break;
  }

  *i_iter = i;
  return xc;
}
// -----------------------------------------------

const double x1 = -.3;
const double x2 = 1.4;
const double E1[] = {.8,  .81, .85, .9, .94,
                     .91, .9,  .86, .8}; // Wartosci E1 w punktach pomiarowych
const double E2[] = {
    .04,     .14, .12, .1, .11,
    .112568, .15, .16, .1}; // Wartosci E2 w punktach pomiarowych
const double xpom[] = {
    -2., -1.5, -1., -.5, 0.,
    .5,  1.,   1.5, 2.}; // Wartosci x, w ktorych zmierzono E1 i E2
const int n = 9;         // Liczba punktow pomiarowych

double rozwiazanie() { return 0.; }

int main() {
  const double y_mean = rozwiazanie();
  printf("Srednia wartosc y: %lf\n", y_mean);
}
