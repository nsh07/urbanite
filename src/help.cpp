#include "../include/help.hpp"
#include <string>

#define URBANITE_VERSION "v1.3.0"
#ifndef PREFIX_DIR /* PREFIX_DIR should be defined at compile time. If not: */
#define PREFIX_DIR "/usr"
#endif

std::string helpStr(std::string progName)
{
    return
    "Usage: " + progName + " ... [OPTIONS] ...\n"
    "Search words on Urban Dictionary at the comfort of your terminal.\n\n"
    "Basic options:\n"
    "Mandatory arguments to long options are mandatory for short options too.\n"
    "  -e, --emoji-style=STYLE\n"
    "                        Set the \"style\" of the emojis/symbols used to show the\n"
    "                        vote count. STYLE is one of emoji (default), unicode,\n"
    "                        unicode-alt, nerd-font or custom. See the custom symbol\n"
    "                        options below.\n"
    "  -f, --font-file=FONT  Set the figlet font file to use for printing the word.\n"
    "                        See the \"Using Figlet Fonts\" section below\n"
    "  -h, --help            Show this help and exit\n"
    "  -v, --version         Print version info and options set at compile-time\n\n"
    "Custom symbol options:\n"
    "You can set the -e option to \"custom\" to use you own characters as the symbols\n"
    "for the like/dislike count. Symbol in the context of this program is a string\n"
    "used to denote the vote (like/dislike) counts. You can then set each individual\n"
    "symbol using these options. If you do not set all symbols, the unset symbols\n"
    "will be replaced by the default emojis. The order of calling these and the -e\n"
    "option does not matter.\n"
    "  --emoji-likes=STRING  Set the symbol used to denote the number of likes\n"
    "  --emoji-dislikes=STRING\n"
    "                        Set the symbol used to denote the number of dislikes\n"
    "  --emoji-ratio=STRING  Set the symbol used to denote the like dislike ratio\n"
    "                        and like percentage out of all votes.\n"
    "Any passed command line arguments that don't belong to an option will be treated\n"
    "as part of the search term. For example, `urbanite hello -f filename.flf world`\n"
    "will search for the phrase \"hello world\". If an option that requires an\n"
    "argument is passed more than once, only the last time that it is used will have\n"
    "an effect.\n\n"
    "Using Figlet Fonts\n"
    "The argument passed to the -f option should be a valid font file path or name.\n"
    "A \"font file\" in the context of this program is a figlet font file (.flf).\n"
    "If a file name is passed, the file is searched in the following order:\n"
    "1. " PREFIX_DIR "/share/urbanite\n"
    "2. Current directory\n"
    "If it is not found in any of these directories, the program exits with an error.\n";
}

std::string versionStr()
{
    return
    "Urbanite - search words on Urban Dictionary at the comfort of your terminal\n"
    "https://github.com/NMrocks/urbanite\n"
    URBANITE_VERSION "\n"
    "Copyright (C) 2021, 2022 Nishant Mishra <https://github.com/NMrocks>\n"
    "This program comes with ABSOLUTELY NO WARRANTY.\n"
    "This is free software, and you are welcome to redistribute it\n"
    "under certain conditions. See http://www.gnu.org/licenses/ for more info.\n\n"
    "Compile-time options:\n"
    "Filesystem prefix directory: " PREFIX_DIR "\n"
    "└─ Urbanite share directory: " PREFIX_DIR "/share/urbanite\n";
}