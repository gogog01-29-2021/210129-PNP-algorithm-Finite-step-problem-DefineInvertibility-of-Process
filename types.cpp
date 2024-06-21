#include <cpg/cpg_std_extensions.hpp>

namespace cpt = cpg::types;

void test_basic_operations()
{
    using list_1 = std::tuple<int, short, double, long>;
    std::cout << "list_1 = " >> list_1{} << cpg::endl;

    using pop_front = cpt::pop_front_t<list_1>;
    std::cout << "pop_front = " >> pop_front{} << cpg::endl;

    using push_front = cpt::push_front_t<char, list_1>;
    std::cout << "push_front  = " >> push_front{} << cpg::endl;

    using push_back = cpt::push_back_t<char, list_1>;
    std::cout << "push_back  = " >> push_back{} << cpg::endl;
}

void test_pop_back()
{
    using list_1 = std::tuple<int, short, double, long>;
    std::cout << "list_1 = " >> list_1{} << cpg::endl;

    using pop_back = cpt::pop_back_t<list_1>;
    std::cout << "pop_back = " >> pop_back{} << cpg::endl;

    using variant_type = cpt::make_variant_t<pop_back>;
    std::cout << "variant_type = " >> variant_type{} << cpg::endl;

    using second_t = cpt::get_type_t<2, list_1>;
    std::cout <<"second_t = " >> second_t{} << cpg::endl;
}

void test_get_type_parameter_count()
{
    using list_1 = cpt::nontype_container<1, 2, 3, 4, 5>;
    std::cout << "list_1 = " >> list_1{} << cpg::endl;

    constexpr auto count = cpt::get_count_v<list_1>;

    constexpr auto a = cpt::get<0>(list_1{});
}

int main()
{
    // test_basic_operations();

    test_pop_back();

    // test_get_type_parameter_count();
}