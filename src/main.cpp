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
    #ifdef WIN32
    #define PREFIX_DIR "."
    #else
    #define PREFIX_DIR "/usr"
    #endif
#endif

#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include <getopt.h>

#include "help.hpp"
#include "other.hpp"
#include "print.hpp"
#include "urban++.hpp"

int main(int argc, char *argv[])
{
    static nm::Initializer init; // Initialize Urban++ transfer environment

    int ret, index, noOfResults = 0;
    std::string searchTerm = "", emojiStyle = "emoji", fontFile = "standard.flf"; // Strings required later
    bool allResults = false;
    
    #ifdef WIN32
    const std::string urbaniteFontDir = PREFIX_DIR "\\fonts\\";
    #else
    const std::string urbaniteFontDir = PREFIX_DIR "/share/urbanite/";
    #endif

    struct option longOptions[] // Long options
    {
        {"all-results",       no_argument,       0, 'a'},
        {"emoji-style",       required_argument, 0, 'e'}, // Set the style of the symbols used (emojiStyle variable)
        {"font-file",         required_argument, 0, 'f'}, // Set the fontFile variable
        {"help",              no_argument,       0, 'h'}, // Self-explanatory
        {"number-of-results", required_argument, 0, 'n'},
        {"version",           no_argument,       0, 'v'},

        {"emoji-likes",    required_argument, 0, 128}, // Custom emoji options
        {"emoji-dislikes", required_argument, 0, 129},
        {"emoji-ratio",    required_argument, 0, 130},
        {"dumpversion",    no_argument,       0, 131},
        {0, 0, 0, 0}
    };
    
    std::map<std::string, std::vector<std::string>> emojiMap =
    {
        { "emoji",       {"👍", "👎", "👍/👎"} }, 
        { "unicode",     {"↑", "↓", "↑↓"} },
        { "unicode-alt", {"↿", "⇂", "↿⇂"} },
        { "nerd-font",   {" ", " ", "﨔"} },
        { "custom",      {"👍", "👎", "👍/👎"} }
    };
    std::vector<std::string> emojiChoices = {"emoji", "unicode", "unicode-alt", "nerd-font", "custom"};

    while ((ret = getopt_long(argc, argv, "ae:f:hn:v?", longOptions, &index)) != -1)
    {
        switch (ret)
        {
            case 'a':
            allResults = true;
            break;

            case 'e':
            if(findInVector(optarg, emojiChoices)) {
                emojiStyle = optarg;
                break;
            }
            std::cerr << argv[0] << ": Invalid symbol style -- " << optarg << std::endl;
            return 1;

            case 'f': // Set font file
            fontFile = optarg;
            break;

            case 'h':
            std::cout << helpStr(argv[0]);
            return 0;

            case 'n':
            if (isNumeric(optarg)) {
                try {
                    noOfResults = std::stoi(optarg);
                }
                catch (std::out_of_range const&) { // if the user goes crazy with the number of results integer
                    std::cerr << argv[0] << ": Integer too large -- " << optarg << std::endl;
                    return 1;
                }
            }
            else {
                std::cerr << argv[0] << ": Not an integer -- " << optarg << std::endl;
                return 1;
            }
            break;

            case 'v': // Version
            std::cout << versionStr();
            return 0;

            case 128: // --emoji-likes
            emojiMap["custom"][0] = optarg;
            break;

            case 129: // --emoji-dislikes
            emojiMap["custom"][1] = optarg;
            break;

            case 130: // --emoji-ratio
            emojiMap["custom"][2] = optarg;
            break;

            case 131:
            std::cout << dumpVersion() << std::endl;
            return 0;

            case '?': // Help
            std::cout << "Run " << argv[0] << " --help for more info.\n";
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
    2. current directory

    This, however, breaks support on Windows because of the directory
    structure assumptions. Will fix cross-platform compatibility later.
    Also, this requires the C++ standard to be set to C++17 in the compiler options (for the
    filesystem library)
    */
    if (!(std::filesystem::exists(urbaniteFontDir + fontFile))) {
        if (!(std::filesystem::exists(fontFile))) {
            std::cerr << argv[0] << ": Invalid font file \"" << fontFile << "\"\n";
            return 1;
        }
    }
    else fontFile = urbaniteFontDir + fontFile;

    nm::Urban urban;

    urban.setSearchTerm(searchTerm);
    CURLcode err = urban.fetch();

    if (err == CURLE_OK) { // If transfer successful
        if (allResults) { // --all-results passed
            printTitle(urban, fontFile);
            for (int i=0; i < urban.sizeOfJSON(); ++i) {
                printDefinition(urban, emojiMap[emojiStyle][0], emojiMap[emojiStyle][1], emojiMap[emojiStyle][2], i);
                std::cout << "\n----------\n\n";
            };
            return 0;
        }
        
        if (noOfResults) { // --no-of-results passed
            if (noOfResults > urban.sizeOfJSON()) {
                std::cerr << "Provided number of results (" << noOfResults << ") too large, showing max number of results (" << urban.sizeOfJSON() << ")\n";
                noOfResults = urban.sizeOfJSON();
            }

            printTitle(urban, fontFile);
            for (int i=0; i < noOfResults; ++i) {
                printDefinition(urban, emojiMap[emojiStyle][0], emojiMap[emojiStyle][1], emojiMap[emojiStyle][2], i);
                std::cout << "\n----------\n\n";
            }
            return 0;
        }

        printTitle(urban, fontFile);
        printDefinition(urban, emojiMap[emojiStyle][0], emojiMap[emojiStyle][1], emojiMap[emojiStyle][2]);
        return 0;
    }
    if (err == CURLE_GOT_NOTHING) {
        std::cerr << argv[0] << ": No search results found for word/phrase \"" << searchTerm << "\"\e[0m\n";
        return 1;
    }
    else std::cerr << argv[0] << ": (" << err << ") " << curl_easy_strerror(err) << "\n";
    return err;
}