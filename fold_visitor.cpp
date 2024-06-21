#include <cpg/cpg_std_extensions.hpp>

namespace cpt = cpg::types;

void pack_handle_1(auto... args)
{
    std::cout << "pack_handler_1 == " << std::endl;

    cpt::fold_visitor visitor
    {
        [](auto arg)
        {
            std::cout << arg;
        }
    };

    ( visitor << ... << args );

    std::cout << std::endl;
    visitor.reset();

    ( args >> ... >> visitor);

    std::cout << cpg::endL;
}

void pack_handle_2(auto... args)
{
    std::cout << "pack_handler_2 == " << std::endl;

    auto arg_count = sizeof...(args);
    
    auto operation = [](auto arg) { std::cout << arg; };

    auto delimiter = []{ std::cout <<", "; };

    cpt::fold_visitor visitor{ arg_count, operation, delimiter };

    ( visitor << ... << args );

    std::cout << std::endl;
    visitor.reset();

    ( args >> ... >> visitor);

    std::cout << cpg::endL;
}

void pack_handle_3(auto... args)
{
    std::cout << "pack_handler_3 == " << std::endl;

    auto arg_count = sizeof...(args);
    
    auto operation = [](auto arg) { std::cout << arg; };
    auto open_delimiter = []{ std::cout <<"{ "; };
    auto delimiter = []{ std::cout <<", "; };
    auto close_delimiter = []{ std::cout <<" }"; };
    cpt::fold_visitor visitor{ arg_count, operation, open_delimiter, delimiter, close_delimiter };

    ( visitor << ... << args );

    std::cout << std::endl;
    visitor.reset();

    ( args >> ... >> visitor);

    std::cout << cpg::endL;
}

void pack_handle_4(auto... args)
{
    std::cout << "pack_handler_4 == " << std::endl;

    int sum = 0;

    cpt::fold_visitor visitor
    {
        [&sum](auto arg)
        {
            sum += (int)arg;
        }
    };

    ( visitor << ... << args );

    std::cout << "sum = " << sum << cpg::endL;
}

void test_fold_visitor()
{
    pack_handle_1(1, 2, 3, 4, 5 );
    pack_handle_2(1, 2, 3, 4, 5 );
    pack_handle_3(1, 2, 3, 4, 5 );

    pack_handle_4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10 );
}

int main()
{
    test_fold_visitor();
}