#include <stdio.h>

#include <string>
#include <iostream>
#include <sstream>

#include "ghostscript/psi/ierrors.h"
#include "ghostscript/psi/iapi.h"

void print_usage()
{
    std::cout << "Usage:\n  rgb-to-cmyk [from RGB PDF file] [to CMYK PDF file]" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "ERROR: Missing arguments!" << std::endl;
        print_usage();
        exit(666);
    }

    const char *inputFile = argv[1];
    std::stringstream outputFile;
    outputFile << "-sOutputFile=" << argv[2];
    const std::string outputArg = outputFile.str();

    char const *gsargv[11];
    int gsargc;
    gsargv[0] = "gpdfc";
    gsargv[1] = "-dSAFER";
    gsargv[2] = "-dBATCH";
    gsargv[3] = "-dNOPAUSE";
    gsargv[4] = "-dNOCACHE";
    gsargv[5] = "-sDEVICE=pdfwrite";
    gsargv[6] = "-sColorConversionStrategy=CMYK";
    gsargv[7] = "-dProcessColorModel=/DeviceCMYK";
    gsargv[8] = outputArg.c_str();
    gsargv[9] = "-q";
    gsargv[10] = inputFile;
    gsargc = 11;

    void *instance;
    int code;

    code = gsapi_new_instance(&instance, NULL);
    if (code < 0)
        return 1;

    code = gsapi_set_arg_encoding(instance, GS_ARG_ENCODING_UTF8);
    if (code == 0)
        code = gsapi_init_with_args(instance, gsargc, const_cast<char **>(gsargv));

    if ((code == 0) || (code == gs_error_Quit))
        code = gsapi_exit(instance);

    if ((code == 0) || (code == gs_error_Quit))
        gsapi_delete_instance(instance);

    if ((code == 0) || (code == gs_error_Quit))
        return 0;
    
    return 1;
}