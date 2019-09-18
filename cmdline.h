/*
   Todo:
     - Stop on errors instead of continuing.
     - usage() construction
     - figure out what is happening with the -- sequence
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

using namespace std;

class cmdline
{
public:

    vector<string> Args;
    vector<string> ExtraArgs;

    void parse(int argc, char *argv[])
    {
        for (; argc; --argc, ++argv)
            Args.push_back(argv[0]);

        try
        {
            for (string& s : Args)
            {
                if (s[0] == '-')
                {
                    if  (s[1] == '-')
                        flag(' ', s.substr(2));
                    else
                        for (char ch : s.substr(1))
                            flag(ch, " "s);
                }
                else if (need.empty())
                    ExtraArgs.push_back(s);
                else
                {
                    int i = need.front();
                    need.pop();
                    flags[i]->set_value(s);
                }
            }

            if (need.empty() == false)
                throw runtime_error("Missing parameter value"s);
        }
        catch(exception& e)
        {
            usage(e.what());
        }
    }

    void usage(string s=""s)
    {
        if (s.length())
            cerr << s << "\n";

        cerr << "Usage:\n";
        for (auto& flag : flags)
        {
            cerr << " -" << flag->flag;
            if (flag->longform.length())
                cerr << ", --" << flag->longform;
            cerr << "  " << flag->help << "\n";
        }

        std::exit(1);
    }

    template<typename T>
    void setopt(char flag, T& val, string help, string longform=""s)
    {
        auto e = make_unique<entry<T>>(flag, val, help, longform);
        flags.push_back(move(e));
    }

private:

    int find_flag(char ch, string longform)
    {
        for (int i = 0; i < flags.size(); ++i)
            if (flags[i]->flag == ch)
                return i;
            else if (flags[i]->longform == longform)
                return i;

        return flags.size();
    }

    void flag(char ch, string longform)
    {
        int i = find_flag(ch, longform);
        if (i == flags.size() )
            throw runtime_error("unknown flag");

        if (flags[i]->needs_arg)
            need.push(i);
        else
            flags[i]->set_value(""s);
    }

    struct ebase
    {
        char flag;
        string help;
        string longform;
        bool needs_arg;

        ebase(char f, string h, string lform, bool needs = true)
            : flag(f), help(h), longform(lform), needs_arg(needs) { }

        // We do not need to know the type of the destination here.
        // We only need to be able to set it from a string.
        virtual void set_value(string s) = 0;
    };

    template<typename T>
    struct entry: public ebase
    {
        T& val;

        entry(char flag, T& v, string help, string lform)
            : ebase{flag, help, lform}, val{v}  { }

        void set_value(string s)
        {
            stringstream ss{s};
            ss >> val;  // nyi: check for error
        }
    };

    vector<unique_ptr<ebase>> flags;
    queue<int> need;
};

template<>
struct cmdline::entry<bool> : public cmdline::ebase
{
    bool& val;

    entry(char flag, bool& v, string help, string lform)
        : ebase{flag, help, lform, false}, val{v} { }

    void set_value(string unused) { val = !val; }
};

