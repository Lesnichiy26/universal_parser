#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>

namespace ArgumentParser {

    template<typename T>
    struct Argument {


        std::string name;
        char short_name;
        std::string for_help;
        int type; // 1 - int; 2 - string; 3 - bool

        bool def;
        T default_val;

        bool multi_flag;
        size_t amountMin; // for multi value / amount == 1 is default
        int sizet;

        T* value;
        std::vector<T>* values;

        bool positional;

        Argument(std::string name, char short_name, std::string for_help, int type) :
                name(std::move(name)),
                short_name(short_name),
                for_help(std::move(for_help)),
                amountMin(1),
                positional(false),
                type(type),
                sizet(0),
                values(nullptr),
                value(nullptr),
                multi_flag(false),
                def(false)
                {}

        std::string& GetName() {
            return name;
        }

        std::vector<T> &GetValues() {
            return *values;
        }

        T GetDefault() {
            return default_val;
        }

        size_t GetAmountMin() {
            return amountMin;
        }

        Argument<T>& Default(T anything) {
            sizet++;
            def = true;
            default_val = anything;
            return *this;
        }

        Argument<T>& StoreValue(T &tmp) {
            value = &tmp;
            return *this;
        }

        Argument<T>& StoreValues(std::vector<T> &tmp) {
            values = &tmp;
            return *this;
        }

        Argument<T> &MultiValue(size_t size = 1) {
            amountMin = size;
            multi_flag = true;
            return *this;
        }

        Argument<T> &Positional() {
            positional = true;
            return *this;
        }

    };


    class ArgParser {
    public:
        ArgParser(std::string name) : name(std::move(name)), if_help(false) {}

        ~ArgParser() = default;

        bool Parse(const std::vector<std::string> &args);

        bool Parse(int argc, char** argv);

        std::string GetStringValue(const std::string &param, int64_t id = 0);

        int64_t GetIntValue(const std::string &param, int64_t id = 0);

        bool GetFlag(const std::string &param, int64_t id = 0);

        Argument<std::string> &AddStringArgument(const std::string &param);

        Argument<std::string> &AddStringArgument(char short_param_name, const std::string &param);

        Argument<std::string> &AddStringArgument(char short_param_name, const std::string &param, const std::string &help);

        Argument<int> &AddIntArgument(const std::string &param);

        Argument<int> &AddIntArgument(char short_param_name, const std::string &param);

        Argument<int> &AddIntArgument(const std::string &param, const std::string &help);

        Argument<int> &AddIntArgument(char short_param_name, const std::string &param, const std::string &help);

        Argument<bool> &AddFlag(const std::string &param);

        Argument<bool> &AddFlag(char short_param_name, const std::string &param);

        Argument<bool> &AddFlag(char short_param_name, const std::string &param, const std::string &help);

        Argument<bool> &AddFlag(const std::string &param, const std::string &help);

        Argument<std::string> &AddHelp(char short_param_name, const std::string &param, const std::string &help);

        bool Help();

        std::string HelpDescription();

        std::pair<int, int> WhatType(std::string& param);

        std::pair<int, int> WhatType(char param);

        void Add(Argument<int>* obj, int value);

        void Add(Argument<std::string>* obj, std::string value);

        void Add(Argument<bool>* obj, bool value);

        bool Empty();

    private:
        std::vector<Argument<std::string>*> stringArguments;
        std::vector<Argument<int>*> integerArguments;
        std::vector<Argument<bool>*> boolArguments;
        std::vector<Argument<std::string>*> helpArguments;
        std::vector<std::string> params; // чтобы знать порядок вхождения параметров
        std::map<std::string, Argument<int>*> paramsInt; // to know all int params
        std::map<std::string, Argument<std::string>*> paramsString; // to know all string params
        std::map<std::string, Argument<bool>*> paramsBool; // to know all bool params
        std::string name;
        std::string executionFile;
        bool if_help;
        std::vector<std::string> field;
    };

} // namespace ArgumentParser