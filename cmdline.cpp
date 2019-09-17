#include <iostream>
#include <string>
#include "cmdline.h"
using namespace std;

class cmdopts: public cmdline
{
public:
    int verbose = 0;
    int tflag = 1;
    int zflag = 0;
    bool bflag = false;
    string filename;

    cmdopts()
    {
        setopt('v', verbose,  "verbose output.");
        setopt('f', filename, "file name");
        setopt('z', zflag,    "compress");
        setopt('t', tflag,    "print table");
        setopt('b', bflag,    "boolean flag");
    }
};

int main(int argc, char *argv[])
{
    cmdopts opts;
    opts.parse(argc, argv);

    cout << "verbose: " << opts.verbose << "\n";
    cout << "tflag: " << opts.tflag << "\n";
    cout << "compress: " << opts.zflag << "\n";
    cout << "file name: " << opts.filename << "\n";

    // hack to test the machinery & concept
    auto& vflag = opts.flags[0];
    cout << "vflag char: " << vflag->flag << "\n";
    cout << "vflag help: " << vflag->help << "\n";
    vflag->set_value(cin);

    cout << "now vflag is " << opts.verbose << "\n";

}

