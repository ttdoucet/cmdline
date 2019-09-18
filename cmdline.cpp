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
    int trials = 10;
    string filename;

    cmdopts()
    {
        setopt('v', verbose,  "Extra informational messages.");
        setopt('f', filename, "<file> Name of the output file.", "filename");
        setopt('n', trials,   "<num>  Number of trials to run.", "trials");
        setopt('z', zflag,    "Compress.");
        setopt('t', tflag,    "Print table.");
        setopt('b', bflag,    "Random boolean flag.");
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

