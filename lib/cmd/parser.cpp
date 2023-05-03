#include "parser.h"

#include <iostream>

Parser::Parser(int argc, char **cmd_line_raw) {
    std::vector<std::string> args;
    std::string word;
    for (int i = 0; i < argc; ++i) {
        word = cmd_line_raw[i];
        args.push_back(word);
    }

    if (args.size() < 3) {
        std::cout << "This is a program that applies filters to a single image. "
                     " For further info please type in a path to an input file and a path to an output file"
                  << std::endl;
        return;
    }

    import_path_ = args[1];
    export_path_ = args[2];

    for (size_t i = 3; i < args.size(); ++i) {
        if (args[i][0] == '-') {
            std::string filter_name = args[i];
            filter_name.erase(0, 1);
            filter_list_.push_back(std::make_pair(filter_name, std::vector<std::string>()));
        } else {
            if (!filter_list_.empty()) {
                filter_list_.back().second.push_back(args[i]);
            } else {
                throw "Invalid arguments.";
            }
        }
    }
}

std::string Parser::GetImportPath() {
    return this->import_path_;
}

std::string Parser::GetExportPath() {
    return this->export_path_;
}

std::vector<std::pair<std::string, std::vector<std::string>>> Parser::GetFiltersList() {
    return this->filter_list_;
}
