#include <catch2/catch_session.hpp>

#include "circle_literals.h"
#include "circle_strongtypes.h"
#include "circle_types.h"

int main(const int argc, const char* const argv[])
{
    return Catch::Session().run(argc, argv);
}
