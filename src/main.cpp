/*

    Urbanite, a CLI for Urban Dictionary (https://www.urbandictionary.com)
    Copyright (C) 2021, 2022 Nishant Mishra <https://github.com/NMrocks>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef PREFIX_DIR /* PREFIX_DIR should be defined at compile time. If not: */
#define PREFIX_DIR "/usr"
#endif
#ifndef FIGLET_DIR /* Same with the figlet font directory */
#define FIGLET_DIR "/usr/share/figlet"
#endif

#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include <getopt.h>

#include "../include/help.hpp"
#include "../include/print.hpp"
#include "../include/urban++.hpp"

int main(int argc, char *argv[])
{
    static nm::Initializer init; // Initialize Urban++ transfer environment

    int ret, index;
    std::string searchTerm = "", emojiStyle = "emoji", fontFile = "standard.flf";
    const std::string figletFontDir = FIGLET_DIR "/";
    const std::string urbaniteFontDir = PREFIX_DIR "/share/urbanite/";

    struct option longOptions[] // Long options
    {
        {"emoji-style", required_argument, 0, 'e'},
        {"font-file",   required_argument, 0, 'f'},
        {"help",        no_argument,       0, 'h'},
        {"version",     no_argument,       0, 'v'},
        {0, 0, 0, 0}
    };

    while ((ret = getopt_long(argc, argv, "e:f:hv?", longOptions, &index)) != -1)
    {
        switch (ret)
        {
            case 'e':
            emojiStyle = optarg;
            break;

            case 'f': // Set font file
            fontFile = optarg;
            break;

            case '?': // Help
            std::cout << "Run " << argv[0] << " --help for more info.\n";
            return 0;

            case 'h':
            std::cout << helpStr(argv[0]);
            return 0;

            case 'v': // Version
            std::cout << versionStr();
            return 0;
        }
    }

    for (index = optind; index < argc; ++index) // Set rest of the arguments as search term
    {
        if (searchTerm.size() == 0) // Don't append a space if string is empty
            searchTerm += argv[index];
        else {
            searchTerm += " ";
            searchTerm += argv[index];
        }
    }

    if (searchTerm.size() == 0) { // If search term is still empty
        std::cerr << argv[0] << ": No word/phrase provided" << std::endl;
        return 1;
    }

    /*
    Font file setting algorithm. Prioritizes directories in the following order:
    1. PREFIX_DIR/share/urbanite/
    2. /usr/share/figlet/
    3. current directory

    This, however, breaks support on OSs other than Linux distributions because of the directory
    structure assumptions. Will fix cross-platform compatibility later.
    Also, this requires the C++ standard to be set to C++17 in the compiler options (for the
    filesystem library)
    */
    if (!(std::filesystem::exists(urbaniteFontDir + fontFile))) {
        if (std::filesystem::exists(figletFontDir + fontFile)) fontFile = figletFontDir + fontFile;
        else if (!(std::filesystem::exists(fontFile))) {
            std::cerr << argv[0] << ": Invalid font file \"" << fontFile << "\"\n";
            return 1;
        }
    }
    else fontFile = urbaniteFontDir + fontFile;

    std::map<std::string, std::vector<std::string>> emojiMap =
    {
        { "emoji",       {"👍", "👎", "👍/👎"} }, 
        { "unicode",     {"↑", "↓", "↑↓"} },
        { "unicode-alt", {"↿", "⇂", "↿⇂"} },
        { "nerd-font",   {" ", " ", "﨔"} }
    };
    nm::Urban urban;

    urban.setSearchTerm(searchTerm);
    CURLcode err = urban.fetch();

    if (err == CURLE_OK) { // If transfer successful
        printTitle(urban, fontFile); // Print the word (title)
        printDefinition(urban, emojiMap[emojiStyle][0], emojiMap[emojiStyle][1], emojiMap[emojiStyle][2]);   // and the definition
        return 0;
    }
    if (err == CURLE_GOT_NOTHING) {
        std::cerr << argv[0] << ": No search results found for word/phrase \"" << searchTerm << "\"\e[0m\n";
        return 1;
    }
    else std::cerr << argv[0] << ": (" << err << ") " << curl_easy_strerror(err) << "\n";
    return err;
}