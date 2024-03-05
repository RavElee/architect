#include "iautogen.h"


int main(int argc, char* argv[])
{
    assert(argc == 3);
    auto path2proto = argv[1];
    auto path2autogen = argv[2];

    autogenerator ag;
    ag.generate(path2proto, path2autogen);
    return 0;
}


