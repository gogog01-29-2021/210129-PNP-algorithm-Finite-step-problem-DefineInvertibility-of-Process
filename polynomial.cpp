#include <cpg/cpg_std_extensions.hpp>
#include <cpg/cpg_polynomial.hpp>

namespace cpt = cpg::types;
namespace tpt = tpf::types;
namespace crn = cpg::rational_number;
namespace cpo = cpg::polynomial_operation;

void test_polynomial()
{
    using A = cpt::type_container<std::ratio<2, 3>, std::ratio<0, 1>, std::ratio<-1, 2>>;
    using B = cpt::type_container<std::ratio<2, 3>, std::ratio<0, 1>, std::ratio<-3, 2>>;

    auto C = cpo::subtract(A{}, B{});

    std::cout << "A = " << A{} << cpg::endl;
    std::cout << "B = " << B{} << cpg::endl;
    std::cout << "C = " << C << cpg::endl;

    auto P0 = cpo::build_legendre_polynomial<0>();
    auto P1 = cpo::build_legendre_polynomial<1>();

    std::cout <<"P0 = " << P0 << cpg::endl;
    std::cout <<"P1 = " << P1 << cpg::endl;

    constexpr auto P = cpo::build_legendre_polynomial<4>();
    
    std::cout <<"P = " << P << cpg::endl;

    auto D = cpo::derivative<0LL>(P);

    std::cout <<"D = " << D << cpg::endl;

    auto pl = cpo::create_legendre_polynomial<4>();

    std::cout <<"pl = " << pl(1.0) << cpg::endl;
}

int main()
{
    test_polynomial();
}