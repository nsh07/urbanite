/*

    Urbanite, a CLI for Urban Dictionary (https://www.urbandictionary.com)
    Copyright (C) 2021, 2022  Nishant Mishra <https://github.com/NMrocks>

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

#include "../include/urban++.hpp"
#include "../include/print.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) { // If no search term is provided
        std::cerr << "\e[33mError: No word/phrase provided\e[0m" << std::endl;
        return 1;
    }

    nm::Urban urban;

    urban.setSearchTerm(argv[1]); // Set the search term to argv[1], all other args are discarded
    CURLcode err = urban.fetch();

    if (err == CURLE_OK) {
        printTitle(urban, "src/Standard.flf"); // Print the word (title)
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