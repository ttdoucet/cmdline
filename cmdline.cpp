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
    string filename;

    cmdopts()
    {
        setopt('v', verbose,  "verbose output.");
        setopt('f', filename, "file name");
        setopt('z', zflag,    "compress");
        setopt('t', tflag,    "print table");
    }
};

int main(int argc, char *argv[])
{
    cmdopts opts;
    opts.feed(argc, argv);

    cout << "verbose: " << opts.verbose << "\n";
    cout << "tflag: " << opts.tflag << "\n";
    cout << "compress: " << opts.zflag << "\n";
    cout << "file name: " << opts.filename << "\n";

    for ( auto i = opts.flags.begin(); i != opts.flags.end(); ++i)
    {
        cout << "flag: " << (*i)->flag << "\n";
    }

}

