#include <cpg/cpg_std_extensions.hpp>
 
int main()
{
    /*
    std::string s {"ABCDEF"};
    std::cout << s << " → ";
    std::ranges::reverse(s.begin(), s.end());
    std::cout << s << " → ";
    std::ranges::reverse(s);
    std::cout << s << " │ ";
 
    std::array a {1, 2, 3, 4, 5};
    for (auto e : a)
        std::cout << e << ' ';
    std::cout << "→ ";
    std::ranges::reverse(a);
    for (auto e : a)
        std::cout << e << ' ';
    std::cout << '\n';
    */

   auto v = std::vector<int>{1, 2, 3, 4} | std::views::reverse;

   std::cout <<"v = " << v << cpg::endl;
}