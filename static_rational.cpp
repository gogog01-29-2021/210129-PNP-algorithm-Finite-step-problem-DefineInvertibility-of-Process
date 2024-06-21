#include <cpg/cpg_std_extensions.hpp>
#include <cpg/cpg_rational.hpp>
#include <cpg/cpg_prime_numbers.hpp>

namespace crn = cpg::rational_number;
namespace cpr = cpg::prime_numbers;

void test_integer()
{
    constexpr auto min = std::numeric_limits<unsigned int>::min();

    std::cout <<"min= " << min << cpg::endl;

    unsigned a = -5;
    unsigned b = 3;

    signed int c = a + b;

    std::cout <<"c = " << c << cpg::endl;

    using r1 = crn::create_ratio_t<6*6, 9*9>;
    using r2 = crn::create_ratio_t<5>;

    constexpr auto r_a = crn::ratio_add<r1, r2>();
    constexpr auto r_b = crn::ratio_multiply<r1, r_a>();

    std::cout << r_a <<" == " << r_b <<" ? " 
        << crn::ratio_not_equal<r_a, r1>();

    constexpr auto sr = crn::sqrt<r1>();

    std::cout << ", r1 = " << r1{} << cpg::endl;
    std::cout << ", sr = " << sr << cpg::endl;

    using r3 = crn::create_ratio_t<-5>;

    std::cout << r3{} <<" is negative ? " 
        << crn::ratio_is_positive<r3>() << cpg::endl;

    std::cout << r1{} << " as double = " 
        << crn::ratio_cast<float>(r_a) << cpg::endl;

    auto r_r = crn::create_rational(r_b);

    std::cout <<"r_r = " >> r_r << cpg::endl;

    auto srr = std::sin((double)r_r);

    auto rs1 = crn::create_rational(5);

}

int main()
{
    std::cout << std::boolalpha << cpg::endl;

    test_integer();
}
