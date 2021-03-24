#include <bits/stdc++.h>
using namespace std;
#include <armadillo>
#include <limits>

typedef std::numeric_limits< double > dbl;
// g++ zdt6.cpp -larmadillo -g -o zdt6 && ./zdt6


std::tuple<double, double> pagmo(arma::vec point)
{
    double pi = arma::datum::pi;
    double g = 0.;
    double f1 = point[0];
    auto N = point.size();

    f1 = 1 - std::exp(-4 * point[0]) * std::pow(std::sin(6 * pi * point[0]), 6);
    for (decltype(N) i = 1; i < N; ++i) {
        g += point[i];
    }
    g = 1 + 9 * std::pow((g / static_cast<double>(N - 1u)), 0.25);
    double f2 = g * (1 - (f1 / g) * (f1/ g));

    return make_tuple(f1, f2);
}

std::tuple<double, double> ensmallen(arma::vec point)
{
      double pi = arma::datum::pi;
      size_t numVariables = point.size();
      double f1 = 1. - std::exp(-4 * point[0]) *
          std::pow(std::sin(6 * pi * point[0]), 6);
      double sum = std::pow(
          arma::accu(point(arma::span(1, numVariables - 1), 0)) / 9, 0.25);
      double g = 1. + 9. * sum;
      double objectiveRatio = f1 / g;
      double f2 = g * (1. - std::pow(objectiveRatio, 2));

      return make_tuple(f1, f2);
}

int main()
{
  size_t numVar = 10;
  size_t numObj = 2;

  arma::vec point(numVar, arma::fill::randu);

  std::cout << "Pagmo result: " << std::get<0>(pagmo(point)) << " " << std::get<1>(pagmo(point))<< std::endl;
  std::cout << "Ensmallen result: " << std::get<0>(ensmallen(point)) <<  " " <<std::get<1>(ensmallen(point))  << std::endl;

}
