// dpcpp -Qstd=c++20 /EHsc derivatives.cpp -o d.exe
// g++ -std=c++20 derivatives.cpp -ltbb12 -o g.exe
// clang++ -std=c++20 derivatives.cpp -ltbb12 -o c.exe
// cl /EHsc /std:c++20 derivatives.cpp /Fe: m.exe

#define CPG_INCLUDE_SYCL

#include <cpg/cpg_std_extensions.hpp>
#include <cpg/calculus.hpp>

namespace cna = cpg::numerical_analysis;
namespace cpt = cpg::types;

void test_calculus_single_variable_tbb()
{
    std::cout<<"1. Single Variable Derivatives with TBB" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto f = [](auto x)
    {
        return std::sin(x);
    };

    auto fx = [](auto x)
    {
        return std::cos(x);
    };

    auto fxx = [](auto x)
    {
        return -std::sin(x);
    };

    auto fxxx = [](auto x)
    {
        return -std::cos(x);
    };

    auto fxxxx = [](auto x)
    {
        return std::sin(x);
    };

    auto pi_2 = std::numbers::pi_v<double> * 2.0;
    auto bound = std::array{0.0, pi_2};

    auto nr_1 = cna::differentiate(dx_1, f, 5, bound);
    auto ar_1 = cna::evaluate(fx, 5, bound);

    std::cout <<"nr_1 = " << nr_1 << cpg::endl;
    std::cout <<"ar_1 = " << ar_1 << cpg::endL;
    
    auto nr_2 = cna::differentiate(dx_2, f, 5, bound);
    auto ar_2 = cna::evaluate(fxx, 5, bound);

    std::cout <<"nr_2 = " << nr_2 << cpg::endl;
    std::cout <<"ar_2 = " << ar_2 << cpg::endL;

    auto nr_3 = cna::differentiate(dx_3, f, 5, bound);
    auto ar_3 = cna::evaluate(fxxx, 5, bound);

    std::cout <<"nr_3 = " << nr_3 << cpg::endl;
    std::cout <<"ar_3 = " << ar_3 << cpg::endL;

    auto nr_4 = cna::differentiate(dx_4, f, 5, bound);
    auto ar_4 = cna::evaluate(fxxxx, 5, bound);

    std::cout <<"nr_4 = " << nr_4 << cpg::endl;
    std::cout <<"ar_4 = " << ar_4 << cpg::endL;
}

void test_calculus_multivariabl_tbb()
{
    std::cout<<"2. Multivariable Derivatives with TBB" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;
    
    auto pi_2 = std::numbers::pi_v<double> * 2.0;
    auto bound = std::array{0.0, pi_2};

    auto f =[](auto x, auto y)
    {
        return std::sin(x) * std::cos(y);
    };

    auto fx =[](auto x, auto y)
    {
        return std::cos(x) * std::cos(y);
    };

    auto fxy =[](auto x, auto y)
    {
        return -std::cos(x) * std::sin(y);
    };

    auto fxxy =[](auto x, auto y)
    {
        return std::sin(x) * std::sin(y);
    };

    auto cmd_dx = cna::create_command(dx_1);
    
    auto nr_dx_1 = cna::differentiate<0>(cmd_dx, f, 5, bound, 1.0, 1.0);
    auto ar_dx_1 = cna::evaluate<0>(fx, 5, bound, 1.0, 1.0);

    std::cout <<"nr_dx_1 = " << nr_dx_1 << cpg::endl;
    std::cout <<"ar_dx_1 = " << ar_dx_1 << cpg::endL;

    auto cmd_dxdy = cna::create_command(dx_1, dy_1);

    auto nr_dxdy_1 = cna::differentiate<0>(cmd_dxdy, f, 5, bound, 1.0, 1.0);
    auto ar_dxdy_1 = cna::evaluate<0>(fxy, 5, bound, 1.0, 1.0);

    std::cout <<"nr_dxdy_1 = " << nr_dxdy_1 << cpg::endl;
    std::cout <<"ar_dxdy_1 = " << ar_dxdy_1 << cpg::endL;

    auto cmd_dxdxdy = cna::create_command(dx_2, dy_1);
    auto cmd_dxdydx = cna::create_command(dx_1, dy_1, dx_1);

    auto nr_dxdxdy_1 = cna::differentiate<0>(cmd_dxdxdy, f, 5, bound, 1.0, 1.0);
    auto nr_dxdydx_1 = cna::differentiate<0>(cmd_dxdydx, f, 5, bound, 1.0, 1.0);
    auto ar_dxdxdy_1 = cna::evaluate<0>(fxxy, 5, bound, 1.0, 1.0);

    std::cout <<"nr_dxdxdy_1 = " << nr_dxdxdy_1 << cpg::endl;
    std::cout <<"nr_dxdydx_1 = " << nr_dxdydx_1 << cpg::endl;
    std::cout <<"ar_dxdxdy_1 = " << ar_dxdxdy_1 << cpg::endL;
}

void test_calculus_single_variable_gpu()
{
    std::cout<<"3. Single Variable Derivatives with SYCL" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto f = [](auto x)
    {
        return std::sin(x);
    };

    auto fx = [](auto x)
    {
        return std::cos(x);
    };

    auto fxx = [](auto x)
    {
        return -std::sin(x);
    };

    auto fxxx = [](auto x)
    {
        return -std::cos(x);
    };

    auto fxxxx = [](auto x)
    {
        return std::sin(x);
    };

    sycl::queue queue;

    auto pi_2 = std::numbers::pi_v<double> * 2.0;
    auto bound = std::array{0.0, pi_2};

    auto nr_1 = cna::differentiate(queue, dx_1, f, 5, bound);
    auto ar_1 = cna::evaluate(queue, fx, 5, bound);

    std::cout <<"nr_1 = " << nr_1 << cpg::endl;
    std::cout <<"ar_1 = " << ar_1 << cpg::endL;
    
    auto nr_2 = cna::differentiate(queue, dx_2, f, 5, bound);
    auto ar_2 = cna::evaluate(queue, fxx, 5, bound);

    std::cout <<"nr_2 = " << nr_2 << cpg::endl;
    std::cout <<"ar_2 = " << ar_2 << cpg::endL;

    auto nr_3 = cna::differentiate(queue, dx_3, f, 5, bound);
    auto ar_3 = cna::evaluate(queue, fxxx, 5, bound);

    std::cout <<"nr_3 = " << nr_3 << cpg::endl;
    std::cout <<"ar_3 = " << ar_3 << cpg::endL;

    auto nr_4 = cna::differentiate(queue, dx_4, f, 5, bound);
    auto ar_4 = cna::evaluate(queue, fxxxx, 5, bound);

    std::cout <<"nr_4 = " << nr_4 << cpg::endl;
    std::cout <<"ar_4 = " << ar_4 << cpg::endL;
}

void test_calculus_multivariabl_gpu()
{
    std::cout<<"4. Multivariable Derivatives with SYCL" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;
    
    sycl::queue queue;

    auto pi_2 = std::numbers::pi_v<double> * 2.0;
    auto bound = std::array{0.0, pi_2};

    auto f =[](auto x, auto y)
    {
        return std::sin(x) * std::cos(y);
    };

    auto fx =[](auto x, auto y)
    {
        return std::cos(x) * std::cos(y);
    };

    auto fxy =[](auto x, auto y)
    {
        return -std::cos(x) * std::sin(y);
    };

    auto fxxy =[](auto x, auto y)
    {
        return std::sin(x) * std::sin(y);
    };

    auto cmd_dx = cna::create_command(dx_1);
    
    auto nr_dx_1 = cna::differentiate<0>(queue, cmd_dx, f, 5, bound, 1.0, 1.0);
    auto ar_dx_1 = cna::evaluate<0>(queue, fx, 5, bound, 1.0, 1.0);

    std::cout <<"nr_dx_1 = " << nr_dx_1 << cpg::endl;
    std::cout <<"ar_dx_1 = " << ar_dx_1 << cpg::endL;

    auto cmd_dxdy = cna::create_command(dx_1, dy_1);

    auto nr_dxdy_1 = cna::differentiate<0>(queue, cmd_dxdy, f, 5, bound, 1.0, 1.0);
    auto ar_dxdy_1 = cna::evaluate<0>(queue, fxy, 5, bound, 1.0, 1.0);

    std::cout <<"nr_dxdy_1 = " << nr_dxdy_1 << cpg::endl;
    std::cout <<"ar_dxdy_1 = " << ar_dxdy_1 << cpg::endL;

    auto cmd_dxdxdy = cna::create_command(dx_2, dy_1);
    auto cmd_dxdydx = cna::create_command(dx_1, dy_1, dx_1);

    auto nr_dxdxdy_1 = cna::differentiate<0>(queue, cmd_dxdxdy, f, 5, bound, 1.0, 1.0);
    auto nr_dxdydx_1 = cna::differentiate<0>(queue, cmd_dxdydx, f, 5, bound, 1.0, 1.0);
    auto ar_dxdxdy_1 = cna::evaluate<0>(queue, fxxy, 5, bound, 1.0, 1.0);

    std::cout <<"nr_dxdxdy_1 = " << nr_dxdxdy_1 << cpg::endl;
    std::cout <<"nr_dxdydx_1 = " << nr_dxdydx_1 << cpg::endl;
    std::cout <<"ar_dxdxdy_1 = " << ar_dxdxdy_1 << cpg::endL;

}

int main()
{
    // std::cout.precision(10);

    test_calculus_single_variable_tbb();

    test_calculus_multivariabl_tbb();

    test_calculus_single_variable_gpu();

    test_calculus_multivariabl_gpu();
}