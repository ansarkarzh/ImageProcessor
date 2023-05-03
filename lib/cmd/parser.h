#pragma once

#include <string>
#include <vector>

class Parser {
public:
    explicit Parser(int argc, char **cmd_line_raw);
    std::string GetImportPath();
    std::string GetExportPath();
    std::vector<std::pair<std::string, std::vector<std::string>>> GetFiltersList();

private:
    std::string program_name_;
    std::string import_path_;
    std::string export_path_;

    std::vector<std::pair<std::string, std::vector<std::string>>> filter_list_;
};