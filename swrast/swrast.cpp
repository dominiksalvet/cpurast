// https://github.com/dominiksalvet/swrast

#include "swrast.hpp"
#include <iostream>

using namespace swr;

void swr::test()
{
    std::cout << "hello from test(), int(5)=" << inc(5) << std::endl;
}

int swr::inc(int value) {
    return ++value;
}
