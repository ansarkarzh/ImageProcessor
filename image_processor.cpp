#include "image_processor.h"
#include "lib/common/image.h"
#include "lib/common/bmp.h"
#include "lib/cmd/parser.h"
#include "lib/filters/filter_handler.h"

#include <iostream>

int main(int argc, char** argv) {
    try {
        Parser parser(argc, argv);
        Image image = Import(parser.GetImportPath());
        ImageProcessor process(image, parser.GetFiltersList());
        ExportImage(parser.GetExportPath(), image);
    } catch (char const* error_message) {
        std::cerr << "Error: " << error_message << std::endl;
    } catch (...) {
        std::cerr << "Error occurred." << std::endl;
    }
    return 0;
}
