#include "ArgParser.h"

#include <utility>


std::string ArgumentParser::ArgParser::GetStringValue(const std::string &param, int64_t id) {
    for (auto arg : stringArguments) {
        if (arg->name == param) {
            if (arg->values != nullptr) {
                return (*arg->values)[id];
            } else {
                return arg->default_val;
            }
        }
    }
    return "";
}


int64_t ArgumentParser::ArgParser::GetIntValue(const std::string &param, int64_t id) {
    for (auto arg : integerArguments) {
        if (arg->name == param) {
            if (arg->values != nullptr) {
                return (*arg->values)[id];
            } else {
                return arg->default_val;
            }
        }
    }
    return 0;
}


bool ArgumentParser::ArgParser::GetFlag(const std::string &param, int64_t id) {
    for (auto arg : boolArguments) {
        if (arg->name == param) {
            if (arg->values != nullptr) {
                return (*arg->values)[id];
            } else {
                return arg->default_val;
            }
        }
    }
    return false;
}


ArgumentParser::Argument<std::string>& ArgumentParser::ArgParser::AddStringArgument(const std::string &param) {
    return AddStringArgument(' ', param);
}


ArgumentParser::Argument<std::string>& ArgumentParser::ArgParser::AddStringArgument(char short_param_name, const std::string &param) {
    return AddStringArgument(short_param_name, param, "No help, No Mercy");
}


ArgumentParser::Argument<std::string>& ArgumentParser::ArgParser::AddStringArgument(char short_param_name, const std::string& param, const std::string& help) {
    Argument<std::string>* arg = new Argument<std::string>(param, short_param_name, help, 2);
    stringArguments.push_back(arg);
    params.push_back(param);
    paramsString[param] = arg;
    return *arg;
}


ArgumentParser::Argument<int>& ArgumentParser::ArgParser::AddIntArgument(const std::string &param) {
    return AddIntArgument(' ', param);
}


ArgumentParser::Argument<int>& ArgumentParser::ArgParser::AddIntArgument(char short_param_name, const std::string &param) {
    return AddIntArgument(short_param_name, param, "No help, No Mercy");
}


ArgumentParser::Argument<int>& ArgumentParser::ArgParser::AddIntArgument(char short_param_name, const std::string& param, const std::string& help) {
    Argument<int>* arg = new Argument<int>(param, short_param_name, help, 1);
    integerArguments.push_back(arg);
    params.push_back(param);
    paramsInt[param] = arg;
    return *arg;
}


ArgumentParser::Argument<int>& ArgumentParser::ArgParser::AddIntArgument(const std::string &param, const std::string &help) {
    Argument<int>* arg = new Argument<int>(param, ' ', help, 1);
    integerArguments.push_back(arg);
    params.push_back(param);
    paramsInt[param] = arg;
    return *arg;
}


ArgumentParser::Argument<bool>& ArgumentParser::ArgParser::AddFlag(const std::string &param) {
    return AddFlag(' ', param);
}


ArgumentParser::Argument<bool>& ArgumentParser::ArgParser::AddFlag(char short_param_name, const std::string &param) {
    return AddFlag(short_param_name, param, "No help, No Mercy");
}


ArgumentParser::Argument<bool>& ArgumentParser::ArgParser::AddFlag(char short_param_name, const std::string& param, const std::string& help) {
    Argument<bool>* arg = new Argument<bool>(param, short_param_name, help, 3);
    arg->sizet++;
    boolArguments.push_back(arg);
    params.push_back(param);
    paramsBool[param] = arg;
    return *arg;
}


ArgumentParser::Argument<bool> &ArgumentParser::ArgParser::AddFlag(const std::string &param, const std::string &help) {
    Argument<bool>* arg = new Argument<bool>(param, ' ', help, 3);
    arg->sizet++;
    boolArguments.push_back(arg);
    params.push_back(param);
    paramsBool[param] = arg;
    return *arg;
}


ArgumentParser::Argument<std::string> &ArgumentParser::ArgParser::AddHelp(char short_param_name, const std::string &param, const std::string &help) {
    Argument<std::string>* arg = new Argument<std::string>(param, short_param_name, help, 4);
    helpArguments.push_back(arg);
    params.push_back(param);
    if_help = true;
    return *arg;
}


bool ArgumentParser::ArgParser::Help() {
    HelpDescription();
    return if_help;
}


std::string ArgumentParser::ArgParser::HelpDescription() {
    std::string res;
    res += name + '\n';
    for (auto help_arg : helpArguments) {
        res += help_arg->for_help + '\n';
    }
    res += '\n';
    for (auto int_arg : integerArguments) {
        if (int_arg->short_name != ' ') {
            res += '-' + std::to_string(int_arg->short_name) + ",  " + "--" + int_arg->name + "=<int>   ";
            if (int_arg->def) {
                res += "default value = " + std::to_string(int_arg->default_val) + "   ";
            }
            if (int_arg->multi_flag) {
                res += "MinAmountArgs = " + std::to_string(int_arg->amountMin) + "   ";
            }
            res += int_arg->for_help + '\n';

        } else {
            res += "--" + int_arg->name + "=<int>   ";
            if (int_arg->def) {
                res += "default value = " + std::to_string(int_arg->default_val) + "   ";
            }
            if (int_arg->multi_flag) {
                res += "MinAmountArgs = " + std::to_string(int_arg->amountMin) + "   ";
            }
            res += int_arg->for_help + '\n';
        }
    }
    for (auto string_arg : stringArguments) {
        if (string_arg->short_name != ' ') {
            res += '-' + std::to_string(string_arg->short_name) + ",  " + "--" + string_arg->name + "=<std::string>   ";
            if (string_arg->def) {
                res += "default value = " + string_arg->default_val + "   ";
            }
            if (string_arg->multi_flag) {
                res += "MinAmountArgs = " + std::to_string(string_arg->amountMin) + "   ";
            }
            res += string_arg->for_help + '\n';

        } else {
            res += "--" + string_arg->name + "=<std::string>   ";
            if (string_arg->def) {
                res += "default value = " + string_arg->default_val + "   ";
            }
            if (string_arg->multi_flag) {
                res += "MinAmountArgs = " + std::to_string(string_arg->amountMin) + "   ";
            }
            res += string_arg->for_help + '\n';
        }
    }
    for (auto bool_arg : boolArguments) {
        if (bool_arg->short_name != ' ') {
            res += '-' + std::to_string(bool_arg->short_name) + ",  " + "--" + bool_arg->name + "=<bool>   ";
            if (bool_arg->def) {
                res += "default value = " + std::to_string(bool_arg->default_val) + "   ";
            }
            if (bool_arg->multi_flag) {
                res += "MinAmountArgs = " + std::to_string(bool_arg->amountMin) + "   ";
            }
            res += bool_arg->for_help + '\n';

        } else {
            res += "--" + bool_arg->name + "=<bool>   ";
            if (bool_arg->def) {
                res += "default value = " + std::to_string(bool_arg->default_val) + "   ";
            }
            if (bool_arg->multi_flag) {
                res += "MinAmountArgs = " + std::to_string(bool_arg->amountMin) + "   ";
            }
            res += bool_arg->for_help + '\n';
        }
    }
    return res;
}


bool ArgumentParser::ArgParser::Parse(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        std::string tmp = argv[i];
        field.push_back(tmp);
    }
    Parse(field);
}


bool ArgumentParser::ArgParser::Parse(const std::vector<std::string> &args) {

    if (args.empty()) {
        return false;
    }

    executionFile = args[0];

    size_t argc = args.size();

    for (int i = 1; i < argc; i++) {
        std::string current = args[i];

        if (current[0] == '-' && current[0] == current[1]) {
            std::string param;
            std::string value;
            bool flag = true;
            for (int j = 2; j < current.length(); j++) {
                if (current[j] == '=') {
                    flag = false;
                    j++;
                }
                if (flag) {
                    param += current[j];
                } else {
                    value += current[j];
                }
            }
            std::pair type_and_pos = WhatType(param);
            if (type_and_pos.first == 0) { // такого параметра не существует
                return false;
            }
            int type = type_and_pos.first;
            int pos = type_and_pos.second;

            switch (type) {
                case 1:
                    Add(integerArguments[pos], std::stoi(value));
                    break;
                case 2:
                    Add(stringArguments[pos], value);
                    break;
                case 3:
                    Add(boolArguments[pos], true);
                    break;
                case 4:
                    if_help = true;
            }

        } else if (current[0] == '-') { // KILLED
            if (current[2] == '=') { // значит имеем дело НЕ с флагами

                std::string value;
                for (int j = 3; j < current.length(); j++) { // '-' - 0 позиция, 'p' - 1 позиция ==> '=' - 2 позиция
                    value += current[j];
                }


                std::pair type_and_pos = WhatType(current[1]);
                if (type_and_pos.first == 0) { // такого параметра не существует
                    return false;
                }
                int type = type_and_pos.first;
                int pos = type_and_pos.second;


                switch (type) {
                    case 1:
                        Add(integerArguments[pos], std::stoi(value));
                        break;
                    case 2:
                        Add(stringArguments[pos], value);
                        break;
                    case 3:
                        Add(boolArguments[pos], true);
                        break;
                    case 4:
                        if_help = true;
                }

            } else {
                for (int j = 1; j < current.length(); j++) {
                    for (auto bool_arg : boolArguments) {
                        if (bool_arg->short_name == current[j]) {
                            Add(bool_arg, true);
                        }
                    }
                }
            }
        } else { // значит существует positional аргумент
            bool is_str = true;
            for (auto int_arg : integerArguments) {
                if (int_arg->positional) {
                    Add(int_arg, std::stoi(current));
                    is_str = false;
                    break;
                }
            }
            if (is_str) {
                for (auto int_arg : stringArguments) {
                    if (int_arg->positional) {
                        Add(int_arg, current);
                        break;
                    }
                }
            }
        }
    }

    if (if_help) {
        return Help();
    }

    if (Empty()) {
        return false;
    }

    return true;
}


std::pair<int, int> ArgumentParser::ArgParser::WhatType(std::string &param) {
    for (int i = 0; i < integerArguments.size(); i++) {
        auto arg = integerArguments[i];
        if (arg->name == param) {
            return {1, i};
        }
    }
    for (int i = 0; i < stringArguments.size(); i++) {
        auto arg = stringArguments[i];
        if (arg->name == param) {
            return {2, i};
        }
    }
    for (int i = 0; i < boolArguments.size(); i++) {
        auto arg = boolArguments[i];
        if (arg->name == param) {
            return {3, i};
        }
    }
    for (int i = 0; i < helpArguments.size(); i++) {
        auto arg = helpArguments[i];
        if (arg->name == param) {
            return {4, i};
        }
    }
    return {0, 0};
}


std::pair<int, int> ArgumentParser::ArgParser::WhatType(char param) {
    for (int i = 0; i < integerArguments.size(); i++) {
        auto arg = integerArguments[i];
        if (arg->short_name == param) {
            return {1, i};
        }
    }
    for (int i = 0; i < stringArguments.size(); i++) {
        auto arg = stringArguments[i];
        if (arg->short_name == param) {
            return {2, i};
        }
    }
    for (int i = 0; i < boolArguments.size(); i++) {
        auto arg = boolArguments[i];
        if (arg->short_name == param) {
            return {3, i};
        }
    }
    for (int i = 0; i < helpArguments.size(); i++) {
        auto arg = helpArguments[i];
        if (arg->short_name == param) {
            return {4, i};
        }
    }
    return {0, 0};
}


void ArgumentParser::ArgParser::Add(ArgumentParser::Argument<int> *obj, int value) {
    if (obj->value == nullptr) {
        obj->value = new int;
    }
    if (obj->values == nullptr) {
        obj->values = new std::vector<int>;
    }
    *obj->value = value;
    obj->sizet++;
    obj->values->push_back(value);
}


void ArgumentParser::ArgParser::Add(ArgumentParser::Argument<std::string> *obj, std::string value) {
    if (obj->value == nullptr) {
        obj->value = new std::string;
    }
    if (obj->values == nullptr) {
        obj->values = new std::vector<std::string>;
    }
    *obj->value = value;
    obj->sizet++;
    obj->values->push_back(value);
}


void ArgumentParser::ArgParser::Add(ArgumentParser::Argument<bool> *obj, bool value) {
    if (obj->value == nullptr) {
        obj->value = new bool;
    }
    if (obj->values == nullptr) {
        obj->values = new std::vector<bool>;
    }
    *obj->value = value;
    obj->sizet++;
    obj->values->push_back(value);
}


bool ArgumentParser::ArgParser::Empty() {
    for (auto arg : integerArguments) {
        if ((arg->amountMin > arg->sizet && arg->multi_flag) || !arg->sizet) {
            return true;
        }
    }
    for (auto arg : stringArguments) {
        if ((arg->amountMin > arg->sizet && arg->multi_flag) || !arg->sizet) {
            return true;
        }
    }
    for (auto arg : boolArguments) {
        if ((arg->amountMin > arg->sizet && arg->multi_flag) || !arg->sizet) {
            return true;
        }
    }
    return false;
}
