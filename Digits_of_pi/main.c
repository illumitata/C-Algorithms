#include <stdio.h>
#include <gmp.h>
#include <assert.h>

#define STEP 10 //number of taken steps in sum

//factorial function with gmp
void factorial(mpf_t fact, const mpf_t n){
  unsigned long int i, j;
  mpf_t p;

  j = mpf_get_si(n);

  mpf_init_set_ui(p,1); /* p = 1 */

  for (i=1; i <= j ; ++i){
    mpf_mul_ui(p,p,i); /* p = p * i */
  }

  printf("silnia: \n");
  mpf_set(fact, p);
  mpf_clear(p);

  return;
}

int main(){

  mpf_t k1, k2, k3, k4, k5, k6;
  mpf_t n, sum;
  mpf_t tmp, one, up1, up2, down1, down2, down3; //części składowe równania

  //Maybe change the precision for k1...k6 and n to 1 or 2 'cause they don't need that much
  //And stay with 80000 or more for sum and tmp
  //mpz can convert into mpf using mpf_set_z
  mpf_set_default_prec(80000);

  //(...,...,10) for the system used in describing number
  mpf_init_set_str(k1, "545140134e0", 10);
  mpf_init_set_str(k2, "13591409e0", 10);
  mpf_init_set_str(k3, "640320e0", 10);
  mpf_init_set_str(k4, "100100025e0", 10);
  mpf_init_set_str(k5, "327843840e0", 10);
  mpf_init_set_str(k6, "53360e0", 10);

  //if ...e0  k6 returns 53360.0000
  //if ...e3  k6 returns 5336000.0000 (shift dot to the right)
  //if ...e-5 k6 returns 0.533600 (shifts dot to the left)

  mpf_init_set_ui(n, 0);    //  mpz_set_ui(n, 0);
  mpf_init_set_ui(sum, 0);  //  mpz_set_ui(sum, 0);

  mpf_init_set_ui(one, 1);  // init for -1
  mpf_neg(one, one);

  mpf_init_set_ui(tmp, 0);
  mpf_init_set_ui(up1, 0);
  mpf_init_set_ui(up2, 0);
  mpf_init_set_ui(down1, 0);
  mpf_init_set_ui(down2, 0);
  mpf_init_set_ui(down3, 0);

  printf("\n");

  /*
  mpf_out_str(stdout, 10, 0, k6);
  double test = mpf_get_d(k6);
  printf("\n%lf\n", test);
  */

  /*
  mpf_t test, result;
  mpf_init_set_ui(result, 0);
  mpf_init_set_ui(test, 10);
  factorial(result, test);
  mpf_out_str(stdout, 10, 0, result);
  */

//  for(int k=0; k<=STEP; k++){
//    mpf_mul(up1, )

//  }

  mpf_clear(k1);
  mpf_clear(k2);
  mpf_clear(k3);
  mpf_clear(k4);
  mpf_clear(k5);
  mpf_clear(k6);
  mpf_clear(n);
  mpf_clear(sum);
  mpf_clear(one);
  mpf_clear(tmp);
  mpf_clear(up1);
  mpf_clear(up2);
  mpf_clear(down1);
  mpf_clear(down2);
  mpf_clear(down3);

  printf("\n");

  return 0;
}
