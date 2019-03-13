#include "controller.h"

#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char* argv[])

try {
    // You can change how you start your game class if you want (but
    // you probably don't need to):
    Controller().run();
}

// This prints out error messages if, say, the command-line argument
// cannot be parsed as `int`s.
catch (exception const& e) {
    cerr << argv[0] << ": " << e.what() << "\n";
    return 1;
}