#include <cpg/cpg_std_extensions.hpp>

void print(std::tuple<char const&, int const&, std::string const&> t, int pos)
{
    const auto& [a, b, c] = t;
    std::cout << '(' << a << ' ' << b << ' ' << c << ')' << (pos % 4 ? " " : "\n");
}
 
int main()
{
    const auto x = std::array{'A', 'B'};
    const auto y = std::vector{1, 2, 3};
    const auto z = std::list<std::string>{"α", "β", "γ", "δ"};
 
    for (int i{1}; auto const& tuple : std::views::cartesian_product(x, y, z))
        print(tuple, i++);
}
