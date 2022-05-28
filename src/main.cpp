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

#include <filesystem>
#include <getopt.h>

#include "../include/help.hpp"
#include "../include/print.hpp"
#include "../include/urban++.hpp"

int main(int argc, char *argv[])
{
    int ret, index;
    std::string searchTerm = "", fontFile = "standard.flf";
    const std::string prefix = PREFIX_DIR;
    const std::string figletFontDir = "/usr/share/figlet/";
    const std::string urbaniteFontDir = prefix + "/share/urbanite/";

    struct option longOptions[]
    {
        {"font-file", required_argument, 0, 'f'},
        {"help",      no_argument,       0, 'h'},
        {"version",   no_argument,       0, 'v'},
        {0, 0, 0, 0}
    };

    while ((ret = getopt_long(argc, argv, "f:hv?", longOptions, &index)) != -1)
    {
        switch (ret)
        {
            case 'f':
            fontFile = optarg;
            break;

            case '?':
            case 'h':
            std::cout << helpStr();
            return 0;

            case 'v':
            std::cout << versionStr();
            return 0;
        }
    }

    for (index = optind; index < argc; ++index)
    {
        if (searchTerm.size() == 0)
            searchTerm += argv[index];
        else {
            searchTerm += " ";
            searchTerm += argv[index];
        }
    }

    if (searchTerm.size() == 0) {
        std::cerr << "\e[33mError: No word/phrase provided\e[0m" << std::endl;
        return 1;
    }

    if (!(std::filesystem::exists(urbaniteFontDir + fontFile))) {
        if (std::filesystem::exists(figletFontDir + fontFile)) fontFile = figletFontDir + fontFile;
        else if (!(std::filesystem::exists(fontFile))) {
            std::cerr << "\e[33mInvalid font file \"" << fontFile << "\"\e[0m\n";
            return 1;
        }
    }
    else fontFile = urbaniteFontDir + fontFile;

    nm::Urban urban;

    urban.setSearchTerm(searchTerm);
    CURLcode err = urban.fetch();

    if (err == CURLE_OK) {
        printTitle(urban, fontFile); // Print the word (title)
        printDefinition(urban, "👍", "👎");   // and the definition
        return 0;
    }
    if (err == CURLE_GOT_NOTHING) {
        std::cerr << "\e[33mNo search results found for word/phrase \"" << argv[1] << "\"\e[0m\n";
        return 1;
    }
    else std::cerr << "\e[31mAn error occured while fetching results: " << curl_easy_strerror(err) << "\e[0m\n";
    return 1;
}