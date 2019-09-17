#pragma once

#include <memory>
#include <string>
#include <vector>

using namespace std;

class cmdline
{
public:

    vector<string> Args;

    void parse(int argc, char *argv[])
    {
        for (; argc; --argc, ++argv)
            Args.push_back(argv[0]);

        for (string& s : Args)
        {
            if (s[0] == '-')
            {
                if  (s[1] == '-')
                    full_flag(s.substr(2));
                else
                    for (char ch : s.substr(1))
                        short_flag(ch);
            }
            else
                cout << "arg: " << s << "\n";
        }
    }

    template<typename T>
    void setopt(char flag, T& val, string help, string longform=""s)
    {
        auto e = make_unique<entry<T>>(flag, val, help, longform);
        flags.push_back(move(e));
    }

private:

    void full_flag(const string& f)
    {
        cout << "full flag: " << f << "\n";        
    }

    void short_flag(char ch)
    {
        cout << "flag: " << ch << "\n";
    }

    struct ebase
    {
        char flag;
        string help;
        string longform;

        ebase(char f, string h, string _longform) : flag(f), help(h), longform(_longform) { }

        // We do not need to know the type of the destination here.
        // We only need to be able to set it from a string or istream.
        virtual istream& set_value(istream& s) { return s; }
    };

    template<typename T>
    struct entry: public ebase
    {
        T& val;

        entry(char flag, T& v, string help, string lform): ebase{flag, help, lform}, val{v}
        {
            cout << "ctor entry for flag " << flag << "\n";
        }

        istream& set_value(istream& s)
        {
            return s >> val;
        }
    };

public: // public during debugging
    vector<unique_ptr<ebase>> flags;
};

template<>
struct cmdline::entry<bool> : public cmdline::ebase
{
    bool& val;

    entry(char flag, bool& v, string help, string lform): ebase{flag, help, lform}, val{v}
    {
        cout << "ctor spec entry<bool> for flag " << flag << "\n";
    }

    istream& set_value(istream& s)
    {
        val = !val;
        return s;
    }
};

