#include "check_error.h"
int check_error(const char* source, int result) {
    if (result == -1) {
        std::cerr << source << "Error occurred." << std::endl;
    }
    return result;
}