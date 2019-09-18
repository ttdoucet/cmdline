#include <iostream>
#include <string>
#include "cmdline.h"
using namespace std;

class cmdopts: public cmdline
{
public:
    string filename;
    bool verbose = false;
    bool tflag = true;
    bool zflag = false;
    bool bflag = false;
    int trials = 10;
    float alpha = 0.05;
    float gamma = 0;


    cmdopts()
    {
        setopt('v', verbose, "Extra informational messages.");

        setopt('z', zflag,   "Compress.");
        setopt('t', tflag,   "Print table.");
        setopt('b', bflag,   "Random boolean flag.");

        setopt('f', "--filename", filename, "<file> Name of the output file.");
        setopt('n', "--trials",   trials,   "<num> Number of games to play.");
        setopt('a', "--alpha",    alpha,    "<float> Learning rate.");

        setopt("--gamma", gamma, "<float> Credit decay rate.");

        set_summary("Meaningless set of switches to test code.\n");
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
    cout << "trials: " << opts.trials << "\n";
    cout << "alpha: " << opts.alpha << "\n";
    cout << "gamma: " << opts.gamma << "\n";

    cout << "\n";
    cout << "ExtraArgs:\n";
    for (string& s : opts.ExtraArgs)
        cout << s << "\n";
}

