#include "../include/help.hpp"
#include <string>

#define URBANITE_VERSION "v1.1.0"
#ifndef PREFIX_DIR /* PREFIX_DIR should be defined at compile time. If not: */
#define PREFIX_DIR "/usr"
#endif

std::string helpStr(std::string progName)
{
    return
    "Usage: " + progName + " ... [OPTIONS] ...\n"
    "Search words on Urban Dictionary at the comfort of your terminal.\n\n"
    "Options:\n"
    "Mandatory arguments to long options are mandatory for short options too.\n"
    "  -f, --font-file=FONT  Set the figlet font file to use for printing the word.\n"
    "                        See the \"Using Figlet Fonts\" section below\n"
    "  -h, -?, --help        Show this help and exit\n\n"
    "Any passed command line arguments that don't belong to an option will be treated\n"
    "as part of the search term. For example, `urbanite hello -f filename.flf world`\n"
    "will search for the phrase \"hello world\".\n\n"
    "Using Figlet Fonts\n"
    "The argument passed to the -f option should be a valid font file path or name.\n"
    "A \"font file\" in the context of this program is a figlet font file (.flf).\n"
    "If a file name is passed, the file is first searched in " PREFIX_DIR "/share/urbanite,\n"
    "then in /usr/share/figlet and then in the current directory. If it is not found\n"
    "in any of these directories, the program exits with an error.\n";
}

std::string versionStr()
{
    return
    "Urbanite - search words on Urban Dictionary\n"
    URBANITE_VERSION "\n"
    "Copyright (C) 2021, 2022 Nishant Mishra <https://github.com/NMrocks>\n"
    "This program comes with ABSOLUTELY NO WARRANTY.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions. See http://www.gnu.org/licenses/ for more info.\n";
}