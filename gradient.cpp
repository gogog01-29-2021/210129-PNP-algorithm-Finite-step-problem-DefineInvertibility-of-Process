/*
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
		
Intel® oneAPI DPC++/C++ Compiler Developer Guide and Reference
Development Reference Guides - Ahead of Time Compilation
	https://tinyurl.com/mvsnudvf
	
Standard Portable Intermediate Representation
	https://en.wikipedia.org/wiki/Standard_Portable_Intermediate_Representation

dpcpp -Qstd=c++20 /EHsc gradient.cpp -o d.exe

dpcpp -Qstd=c++20 /EHsc -fsycl-targets=spir64_gen -Xs "-device glk" gradient.cpp -o d-gpu.exe

If it does not work on your machine, you do not have SYCL-capable GPU device on your machine
dpcpp -Qstd=c++20 /EHsc -fsycl-targets=spir64_gen -Xs "-device skl" gradient.cpp -o d-gpu.exe

This command will succeed on any modern CPU devices, including AMD CPUs
dpcpp -Qstd=c++20 /EHsc -fsycl-targets=spir64_x86_64 gradient.cpp -o d-cpu.exe

dpcpp -Qstd=c++20 /EHsc -fsycl-targets=spir64_x86_64 -Xs "-march=avx2" gradient.cpp -o d-cpu.exe

If fails, you do not have SYCL-capable graphics device on your machine
dpcpp @min_gpu.txt gradient.cpp -o min.exe

This command will work on any x86_x64 CPU devices
dpcpp @any_cpu.txt gradient.cpp -o any.exe

skl	 - 6th generation Intel® Core™ processor (Skylake with Intel® Processor Graphics Gen9)
kbl	- 7th generation Intel® Core™ processor (Kaby Lake with Intel® Processor Graphics Gen9)
cfl	- 8th generation Intel® Core™ processor (Coffee Lake with Intel® Processor Graphics Gen9)
glk	- Gemini Lake with Intel® Processor Graphics Gen9
icllp - 10th generation Intel® Core™ processor (Ice Lake with Intel® Processor Graphics Gen11)
tgllp - 11th generation Intel® Core™ processor (Tiger Lake with Intel® Processor Graphics Gen12)
dg1	- Intel® Iris® Xe MAX graphics
Gen9 - Intel® Processor Graphics Gen9 
Gen11 - Intel® Processor Graphics Gen11
Gen12LP - Intel® Processor Graphics Gen12 (Lower Power)
adls - 12th generation Intel® Core™ processor (Alder Lake S with Intel® Processor Graphics Gen12.2)
aldp - 12th generation Intel® Core™ processor (Alder Lake P with Intel® Processor Graphics Gen12.2)

*/

#define CPG_INCLUDE_SYCL

#include <cpg/cpg_std_extensions.hpp>
#include <cpg/cpg_calculus.hpp>

namespace cpt = cpg::types;

namespace cna = cpg::numerical_analysis;

void test_gradient()
{
    sycl::queue queue;
    auto device = queue.get_device();

    std::cout <<"Computing Device: " 
        << device.get_info<sycl::info::device::name>() << cpg::endL;

    std::cout <<"1. Gradient Vectors" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto f =[](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y) * z * z;
    };

    auto bound = cpt::make_array(0.0, 5.0);

    std::cout <<"Gradients with CPU"<< cpg::endL;

    auto cpu_gradients = cna::gradients<1, 5, 5>(f, bound, bound, bound);
    
    for(auto& g: cpu_gradients)
        std::cout << g << std::endl; 

    std::cout << cpg::endL;

    //////////////////////////////////////////
    std::cout <<"Gradients with GPU"<< cpg::endL;
    
    auto gpu_gradients = cna::gradients<1, 5, 5>(queue, f, bound, bound, bound);
    
    for(auto& g: gpu_gradients)
        std::cout << g << std::endl; 

    std::cout << cpg::endL;
}

void test_curl()
{
    sycl::queue queue;
    auto device = queue.get_device();

    std::cout <<"Computing Device: " 
        << device.get_info<sycl::info::device::name>() << cpg::endL;

    std::cout <<"2. Curl of Vectors" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto fx =[](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y) * z * z;
    };

    auto fy =[](auto x, auto y, auto z)
    {
        return std::sin(x) * y * z;
    };

    auto fz =[](auto x, auto y, auto z)
    {
        return std::cos(x) * std::sin(y) * z;
    };

    auto bound = cpt::make_array(0.0, 5.0);

    std::cout <<"Curls with CPU" << cpg::endL;

    auto cpu_curls = cna::curls<5, 5, 1>(fx, fy, fz, bound, bound, bound);
    
    for(auto& c: cpu_curls)
        std::cout << c << std::endl; 

    std::cout << cpg::endL;

    std::cout <<"Curls with GPU" << cpg::endL;
    
    auto gpu_curls = cna::curls<5, 5, 1>(queue, fx, fy, fz, bound, bound, bound);
    
    for(auto& c: gpu_curls)
        std::cout << c << std::endl; 

    std::cout << cpg::endL;
}

void test_divergence()
{
    sycl::queue queue;
    auto device = queue.get_device();

    std::cout <<"Computing Device: " 
        << device.get_info<sycl::info::device::name>() << cpg::endL;

    std::cout <<"3. Divergence of Vectors" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto fx =[](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y) * z * z;
    };

    auto fy =[](auto x, auto y, auto z)
    {
        return std::sin(x) * y * z;
    };

    auto fz =[](auto x, auto y, auto z)
    {
        return std::cos(x) * std::sin(y) * z;
    };

    auto bound = cpt::make_array(0.0, 5.0);

    std::cout << "Divergence with CPU" << cpg::endL;

    auto cpu_divs = cna::divs<5, 5, 1>(fx, fy, fz, bound, bound, bound);
    
    for(auto& d: cpu_divs)
        std::cout << d << std::endl; 

    std::cout << cpg::endL;

    std::cout << "Divergence with GPU" << cpg::endL;
    
    auto gpu_divs = cna::divs<5, 5, 1>(queue, fx, fy, fz, bound, bound, bound);
    
    for(auto& d: gpu_divs)
        std::cout << d << std::endl; 

    std::cout << cpg::endL;
}

///////////////////////

void test_gradient_gpu()
{
    sycl::queue queue;
    auto device = queue.get_device();

    std::cout <<"Computing Device: " 
        << device.get_info<sycl::info::device::name>() << cpg::endL;

    std::cout <<"1. Gradient Vectors" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto f =[](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y) * z * z;
    };

    auto bound_x = cpt::make_array(0.0, 5.0);
    auto bound_y = cpt::make_array(0.0, 5.0);
    auto bound_z = cpt::make_array(5.0, 5.0);

    std::cout <<"Gradients with GPU"<< cpg::endL;

    auto gpu_gradients = cna::gradients<100, 100, 1>(queue, f, bound_x, bound_y, bound_z);
    
    for(int i = 0; i < 10; ++i)
        std::cout << gpu_gradients[i] <<std::endl;

    std::cout << cpg::endL;
}

void test_curl_gpu()
{
    sycl::queue queue;
    auto device = queue.get_device();

    std::cout <<"Computing Device: " 
        << device.get_info<sycl::info::device::name>() << cpg::endL;

    std::cout <<"2. Curl of Vectors" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto fx =[](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y) * z * z;
    };

    auto fy =[](auto x, auto y, auto z)
    {
        return std::sin(x) * y * z;
    };

    auto fz =[](auto x, auto y, auto z)
    {
        return std::cos(x) * std::sin(y) * z;
    };

    auto bound_x = cpt::make_array(0.0, 5.0);
    auto bound_y = cpt::make_array(0.0, 5.0);
    auto bound_z = cpt::make_array(5.0, 5.0);

    std::cout <<"Curls with GPU" << cpg::endL;

    auto gpu_curls = cna::curls<100, 100, 1>(queue, fx, fy, fz, bound_x, bound_y, bound_z);
    
    for(auto& c: gpu_curls)
        std::cout << c << std::endl; 

    std::cout << cpg::endL;
}

void test_divergence_gpu()
{
    sycl::queue queue;
    auto device = queue.get_device();

    std::cout <<"Computing Device: " 
        << device.get_info<sycl::info::device::name>() << cpg::endL;

    std::cout <<"3. Divergence of Vectors" << cpg::endL;

    using namespace cpg::numerical_analysis::commands;

    auto fx =[](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y) * z * z;
    };

    auto fy =[](auto x, auto y, auto z)
    {
        return std::sin(x) * y * z;
    };

    auto fz =[](auto x, auto y, auto z)
    {
        return std::cos(x) * std::sin(y) * z;
    };

    auto bound_x = cpt::make_array(0.0, 5.0);
    auto bound_y = cpt::make_array(0.0, 5.0);
    auto bound_z = cpt::make_array(5.0, 5.0);
    
    std::cout << "Divergence with GPU" << cpg::endL;

    auto gpu_divs = cna::divs<100, 100, 1>(queue, fx, fy, fz, bound_x, bound_y, bound_z);
    
    for(auto& d: gpu_divs)
        std::cout << d << std::endl; 

    std::cout << cpg::endL;
}


void how_to_gradient()
{
    using namespace cpg::numerical_analysis::commands;

    auto f = [](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y)*z*z;
    };

    double d = 4.5;

    auto point = cpt::make_array(1.0, 2.0, 3.0);
    
    // std::cout <<"type of point: " << Cpg_GetTypeCategory(point) << cpg::endL;
    auto dx1 = cna::create_command(dx_1);
    
    std::array g{ cna::partial_derivative(dx1, f, point), 
                  cna::partial_derivative(dx1, f, point),
                  cna::partial_derivative(dx1, f, point)  };

    // auto g = cna::gradient(f, point);

    std::cout <<"gardient = " << g << cpg::endl;
}

void how_to_curl()
{
    using namespace cpg::numerical_analysis::commands;

    auto fx = [](auto x, auto y, auto z)
    {
        return std::sin(x)*z*z;
    };

    auto fy = [](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y);
    };

    auto fz = [](auto x, auto y, auto z)
    {
        return std::cos(y)*z*z;
    };

    auto args = cpt::make_array(1.0, 2.0, 3.0);

    auto curl = cna::curl(fx, fy, fz, 1.0, 3.0, 2.6);

    std::cout <<"curl = " << curl << cpg::endl;
}

void how_to_divergence()
{
    using namespace cpg::numerical_analysis::commands;

    auto fx = [](auto x, auto y, auto z)
    {
        return std::sin(x)*z*z;
    };

    auto fy = [](auto x, auto y, auto z)
    {
        return std::sin(x) * std::cos(y);
    };

    auto fz = [](auto x, auto y, auto z)
    {
        return std::cos(y)*z*z;
    };

    auto args = cpt::make_array(1.0, 2.0, 3.0);

    auto div = cna::divergence(fx, fy, fz, args);

    std::cout <<"div = " << div << cpg::endl;
}

int main()
{
    // test_gradient();
    // test_curl();
    // test_divergence();

    test_gradient_gpu();
    test_curl_gpu();
    test_divergence_gpu();

    // how_to_gradient();
    // how_to_curl();
    // how_to_divergence();
}