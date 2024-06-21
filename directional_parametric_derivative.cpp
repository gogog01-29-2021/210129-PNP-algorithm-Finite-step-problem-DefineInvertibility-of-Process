/*
A. Reference Videos
	
Linear Approximation of Surface, Partial Derivatives and Chain Rule
	https://youtu.be/jTMtBoWGHGo?t=3566

Adaptive Quadrature | Lecture 41 | Vector Calculus for Engineers
	https://youtu.be/U4NUXAwwR8E?t=41
	
B . Intel Arc A-Series Graphics

Intel® Arc™ A-Series Graphics – Desktop Quick Start Guide
	https://www.intel.com/content/www/us/en/support/articles/000091128/graphics.html
	
Resizable BAR Support On!
	https://www.gigabyte.com/WebPage/785/NVIDIA_resizable_bar.html
	
GeForce RTX 30 Series Performance Accelerates With Resizable BAR Support
	https://www.nvidia.com/en-us/geforce/news/geforce-rtx-30-series-resizable-bar-support/

C. Intel® oneAPI Reference Materials
 	
1. Data Parallel C++
	The PDF book
		https://tinyurl.com/yfrxytac
	
	Data Parallel C++ Book Source Samples
		https://github.com/Apress/data-parallel-CPP

2. Intel® oneAPI Programming Guide
	https://tinyurl.com/54h8z3vz
	
3. Intel® oneAPI DPC++/C++ Compiler Developer Guide and Reference
	https://tinyurl.com/mrxz3up2
	
4. oneAPI GPU Optimization Guide
	https://tinyurl.com/mrd9a2ns
	
5. The Compute Architecture of Intel® Processor Graphics Gen8
	https://tinyurl.com/37hfp8nh
	
	The Compute Architecture of Intel® Processor Graphics Gen9
	https://tinyurl.com/527kxt84

D. Must-Watch Previous Videos
	
152- How to Implement Numerical Partial Derivatives
	https://www.youtube.com/watch?v=V1MpmXGkc2c&list=PL1_C6uWTeBDEjwkxjppnQ0TmMS272eNRx&index=155

151- How to Implement Numerical Derivatives - Seven-Point Stencil
	https://www.youtube.com/watch?v=uyToBr0ViG0&list=PL1_C6uWTeBDEjwkxjppnQ0TmMS272eNRx&index=154
	
150- Mathematical Theory Behind Numerical Derivatives, Mathematica, Solve System of Linear Equations
	https://www.youtube.com/watch?v=tbngy72ePyU&list=PL1_C6uWTeBDEjwkxjppnQ0TmMS272eNRx&index=153

149- Intel DPC++, SYCL Ahead of Time Compilation (AOT) and Response Files
	https://www.youtube.com/watch?v=ttAZRUmmagA&list=PL1_C6uWTeBDEjwkxjppnQ0TmMS272eNRx&index=152

148- Implement Gradient, Curl, Divergence with SYCL For the First Time
	https://www.youtube.com/watch?v=WjVpbLmPJJg&list=PL1_C6uWTeBDEjwkxjppnQ0TmMS272eNRx&index=151
	
147- Gradient, Curl, Divergence, Random Parallel Fill, cast_ref, Multidimensional Arrays in SYCL
	https://www.youtube.com/watch?v=aYGTBfmsZfo&list=PL1_C6uWTeBDEjwkxjppnQ0TmMS272eNRx&index=150

144- (SETUP) Setup Intel oneAPI - Parallel Partial Derivatives with TBB and SYCL 1
	https://www.youtube.com/watch?v=5Y5KcrhG6mk&list=PL1_C6uWTeBDEjwkxjppnQ0TmMS272eNRx&index=149
	
*/

// clang++ -std=c++20 directional_parametric_derivative.cpp -ltbb12 -o c.exe
// g++ -std=c++20 directional_parametric_derivative.cpp -ltbb12 -o g.exe
// cl /std:c++20 /EHsc directional_parametric_derivative.cpp /Fe: m.exe
// dpcpp -Qstd=c++20 /EHsc -fno-sycl directional_parametric_derivative.cpp -o d.exe

#include <cpg/cpg_std_extensions.hpp>
#include <cpg/cpg_calculus.hpp>

namespace cna = cpg::numerical_analysis;

void test_parameterized_derivatives()
{
    using namespace cpg::numerical_analysis::commands;
                //   0       1
    auto z = [](auto x, auto y)
    {
        return x * x * y + 3.0 * x * std::pow(y, 4);
    };

    auto x = [](auto t)
    {
        return std::sin(2 * t);
    };

    auto y = [](auto t)
    {
        return std::cos(t);
    };

    /*
        How can we evaluate dz/dt?

        1. dz/dt = dz/dx * dx/dt + dz/dy * dy/dt - Chain Rule

        2. We use mathematical definition, that is, dz/dt can be computed directly

        Most of us are familiar with Algebraic Approach to our mathematical problems,
            such as Chain Rules, or some other stupid mathematical theorems.

        These are useful for algrebraic approach, but for Numerical Solutions,
        Mathematical Definitions play the critical role.

        For example,  I = Int f(x) dx, if we apply mathematical definition,

        We can easily implement multiple integrals very compactly, simply, and easily.

        inner_integral(y) = { Int f(x, y) dx, y should be fixed, F(x) with y fixed, => Int F(x) dx  }
        I = Int { Int f(x, y) dx } dy => Int inner_integral(y) dy
    */

   auto dz_dt_chain_rule = [&](auto t)
   {
        auto dx_dt = cna::seven_point_stencil<1>(x, t); // 1st order derivative of x at t = 0
        auto dy_dt = cna::seven_point_stencil<1>(y, t); // 1st order derivative of y at t = 0

        auto cmd_dx = cna::create_command(d_0_1);
        auto cmd_dy = cna::create_command(d_1_1);

        auto dz_dx = cna::partial_derivative(cmd_dx, z, x(t), y(t));
        auto dz_dy = cna::partial_derivative(cmd_dy, z, x(t), y(t));

        return dz_dx * dx_dt + dz_dy * dy_dt; // chain rule
   };

   auto n_dz_dt_chain_rule = dz_dt_chain_rule(0.0);
   std::cout <<"Using Chain Rule = " << n_dz_dt_chain_rule << cpg::endl;

   auto dz_dt_definition = [&](auto t) // dz/dt - mathematical definition
   {
        auto z_of_t = [&](auto tt)
        {
            return z(x(tt), y(tt));
        };

        return cna::five_point_stencil<1>(z_of_t, t);
   };

   auto n_dz_dt_definition = dz_dt_definition(0.0);
   std::cout <<"Using Math Definition = " << n_dz_dt_definition << cpg::endl;

   auto n_dz_dt_definition_2 = cna::directional_derivative(z, std::tuple{x, y}, 0.0);
   std::cout <<"Using Math Definition = " << n_dz_dt_definition_2 << cpg::endl;

   auto cmd = cna::create_command(d_0_1);

   auto result = cna::parametric_derivative(cmd, z, std::tuple{x, y}, 0.0);
   std::cout <<"Using Math Definition = " << result << cpg::endl;
}

void test_parametric_derivatives()
{
    using namespace cpg::numerical_analysis::commands;

    auto z =[](auto x, auto y)
    {
        return std::exp(x) * std::sin(y);
    };

    auto x = [](auto s, auto t)
    {
        return s * t * t;
    };

    auto y = [](auto s, auto t)
    {
        return s * s * t;
    };

    auto cmd = cna::create_command(d_0_1, d_1_1);
                                                                                     // s    t                
    auto numerical = cna::parametric_derivative(cmd, z, std::tuple{x, y}, std::array{1.0, 1.0} );

    auto dz_ds = [&](auto s, auto t)
    {
        return std::exp(x(s, t))*std::sin(y(s, t))*t*t + 
            2 * std::exp(x(s, t))*std::cos(y(s, t))*s*t;
    };

    auto dz_dt = [&](auto s, auto t)
    {
        return 2 * std::exp(x(s, t))*std::sin(y(s, t))*s*t + 
            std::exp(x(s, t))*std::cos(y(s, t))*s*s;
    };

    auto algebraic = std::array{ dz_ds(1.0, 1.0), dz_dt(1.0, 1.0) };

    std::cout <<"numerical = " << numerical << std::endl;
    std::cout <<"algebraic = " << algebraic << std::endl;
}

int main()
{
    test_parameterized_derivatives();

    test_parametric_derivatives();
}