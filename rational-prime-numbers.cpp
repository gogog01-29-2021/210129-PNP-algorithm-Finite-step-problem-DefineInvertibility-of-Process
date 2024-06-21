#include <cpg/cpg_std_extensions.hpp>
#include <cpg/cpg_rational.hpp>
#include <cpg/cpg_prime_numbers.hpp>

namespace crn = cpg::rational_number;
namespace cpr = cpg::prime_numbers;

void test_rational_number()
{
    crn::rational a{ -4, 12 };
    crn::rational b{ 4, -3 };

    std::cout <<"a = " << a << cpg::endl;
    std::cout <<"b = " << b << cpg::endL;

    auto c = a + b;
    auto d = a * b;

    std::cout << a << " + "<< b << " = " << a + b << cpg::endl;
    std::cout << a << " * "<< b << " = " << a * b << cpg::endL;
    
    std::cout << a << "  < " << b << " = " << (a  < b) << cpg::endl;
    std::cout << a << "  > " << b << " = " << (a  > b) << cpg::endl;
    std::cout << a << " <= " << b << " = " << (a <= b) << cpg::endl;
    std::cout << a << " >= " << b << " = " << (a >= b) << cpg::endl;
    std::cout << a << " == " << b << " = " << (a == b) << cpg::endl;
    std::cout << a << " != " << b << " = " << (a != b) << cpg::endL;   
}

void test_solve_rational_quadratic_equation()
{
    crn::rational<long long> a{1, 4};
    crn::rational<long long> b{-5, 4};
    crn::rational<long long> c{6, 25};

    std::cout <<"b.mag() = " << b.mag<double>() << cpg::endl;
    std::cout <<"b.abs_mag() = " << b.abs_mag<double>() << cpg::endl;
    
    auto solutions = crn::solve_quadratic_equation(a, b, c);
    std::cout <<"solutions = " << solutions << cpg::endL;

    auto quadratic = [=](auto x)
    {
        return (a * x * x + b * x + c) == 0;  
    };

    for(auto r: solutions)
    {
        std::cout << r <<" is solution? " 
            << quadratic(r) << cpg::endl;
    } 
}

void test_cprime()
{
    cpr::cprime<long long> primes;

    primes.BuildPrimes(100'000);

    std::cout << primes.Report() << cpg::endL;
    
    int num = 2 * 2 * 3 * 3 * 49 * 5;

	std::cout << "num = " << num << std::endl;

    auto terms = primes.factorize(num);
    
	std::cout << "\nTerms: " << terms << cpg::endL;

    auto divisors = primes.divisors(num);

    std::cout <<"\nDivisors = " << divisors << cpg::endL;

    std::cout <<"129 prime ? " << primes.IsPrimeNumber(129) << cpg::endl;

    std::cout <<"divisors of " << 129 <<" are " << primes.divisors(129) << cpg::endL;
}

int main()
{
    std::cout << std::boolalpha;
    
    // test_rational_number();

    // test_solve_rational_quadratic_equation();

    test_cprime();
}