#include <bits/stdc++.h>
using namespace std;
#include <armadillo>
#include <limits>

typedef std::numeric_limits< double > dbl;
// g++ zdt4.cpp -larmadillo -g -o zdt4 && ./zdt4


std::tuple<double, double> pagmo(arma::vec point)
{
    double pi = arma::datum::pi;
    double g = 0.;
    auto N = point.size();

    g = 1 + 10 * static_cast<double>(N - 1u);
    double f1 = point[0];
    for (decltype(N) i = 1u; i < N; ++i) {
        g += point[i] * point[i] - 10. * std::cos(4. * pi * point[i]);
    }
    double f2 = g * (1. - std::sqrt(f1 / g));

    return make_tuple(f1, f2);
}

std::tuple<double, double> ensmallen(arma::vec point)
{
      double pi = arma::datum::pi;
      double f1 = point[0];
      size_t numVariables = point.size();
      arma::vec truncatedCoords = point(arma::span(1, numVariables - 1));
      double sum = arma::accu(arma::square(truncatedCoords) -
          10. * arma::cos(4 * pi * truncatedCoords));
      double g = 1. + 10. * static_cast<double>(numVariables - 1) + sum;
      double objectiveRatio = f1/ g;
	  double f2 = g * (1. - std::sqrt(objectiveRatio));

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
