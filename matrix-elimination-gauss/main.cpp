#include <iostream>
#include "Eigen/Dense"
#include <gmpxx.h>

using Eigen::MatrixXd;
using namespace std;

int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;

  mpz_t result, base;
  mpz_init(result);
  mpz_init(base);
  mpz_set_str(base, "2", 10);
  mpz_pow_ui(result, base, 2);
  mpz_out_str(stdout, 10, result);
  return 0;
}
