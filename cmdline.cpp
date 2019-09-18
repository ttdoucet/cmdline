#include <iostream>
#include <string>
#include "cmdline.h"
using namespace std;

class cmdopts: public cmdline
{
public:
    bool verbose = 0;
    bool tflag = 1;
    bool zflag = 0;
    bool bflag = false;
    string filename;

    cmdopts()
    {
        setopt('v', verbose,  "verbose output.");
        setopt('f', filename, "file name", "filename"
            );
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
    cout << "bflag: " << opts.bflag << "\n";
}

