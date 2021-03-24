#include <bits/stdc++.h>
using namespace std;
#include <armadillo>
#include <limits>

typedef std::numeric_limits< double > dbl;
// g++ zdt1.cpp -larmadillo -g -o zdt1 && ./zdt1

std::tuple<double, double> pagmo(arma::vec point)
{
    double g = 0.;
    double f1 = point[0];
    auto N = point.size();

    for (decltype(N) i = 1u; i < N; ++i) {
        g += point[i];
    }
    g = 1. + (9. * g) / static_cast<double>(N - 1u);
    double f2 = g * (1. - std::sqrt(f1 / g));

    return make_tuple(f1, f2);
}

std::tuple<double, double> ensmallen(arma::vec point)
{
      double f1 = point[0];
      size_t numVariables = point.size();
      double sum = arma::accu(point(arma::span(1, numVariables - 1), 0));
      double g = 1. + 9. * sum / (static_cast<double>(numVariables) - 1.);
      double objectiveRatio = f1 / g;
      double f2 = g * (1. - std::sqrt(objectiveRatio));

      return make_tuple(f1, f2);
}

int main()
{
  size_t numVar = 30;
  size_t numObj = 2;

  arma::vec point(numVar, arma::fill::randu);

  std::cout << "Pagmo result: " << std::get<0>(pagmo(point)) << " " <<  std::get<1>(pagmo(point))<< std::endl;
  std::cout << "Ensmallen result: " << std::get<0>(ensmallen(point)) << " " << std::get<1>(ensmallen(point))  << std::endl;

}
