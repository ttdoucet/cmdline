#pragma once

#include <string>
#include <vector>
using namespace std;


class cmdline
{
public:
    void feed(int argc, char *argv[])
    {
    }

    template<typename T>
    void setopt(char flag, T& val, string help)
    {
        // LEAK
        auto e = new entry{flag, val, help};
        flags.push_back(e);
    }

private:

    class ebase
    {
    public:
        char flag;
        string help;

        ebase(char f, string h) : flag(f), help(h) { }

        // We do not need to know the type of the destination here.
        // We only need to be able to set it from a string or istream.
        virtual istream& set_value(istream& s) { return s; }

    };

    template<typename T>
    struct entry: public ebase
    {
        T& val;

        entry(char flag, T& v, string help): ebase{flag, help}, val{v} { }

        istream& set_value(istream& s)
        {
            return s >> val;
        }

    };

public: // debugging
    vector<ebase*> flags;

};
