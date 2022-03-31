/*

    Urbanite, a CLI for Urban Dictionary (https://www.urbandictionary.com)
    Copyright (C) 2021  Nishant Mishra <https://github.com/NMrocks>

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

#include <iostream>
#include <cmath>

#include <curl/curl.h>
#include <string>
#include "../include/Figlet.hpp"
#include "../include/urban++.hpp"

using srilakshmikanthanp::FigletFont;
using srilakshmikanthanp::Smushed;

double roundToPlaces(double decimal, int places)
{
    double multiplier = std::pow(10, places);
    return std::ceil(decimal * multiplier) / multiplier;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cerr << "\e[33mError: No word/phrase provided\e[0m" << std::endl;
        return 1;
    }

    srilakshmikanthanp::Figlet figlet(FigletFont::make("src/Standard.flf"), Smushed::make());
    nm::Urban urban;

    urban.setSearchTerm(argv[1]);
    CURLcode err = urban.fetch();

    if (err == CURLE_OK) {
        double likeDislikeRatio = 0;
        double likeDislikePercentage = 0;
        
        if (urban.getTopThumbsDown() != 0) 
            likeDislikeRatio = roundToPlaces((double) urban.getTopThumbsUp()/urban.getTopThumbsDown(), 2);
        
        double totalVote = urban.getTopThumbsUp() + urban.getTopThumbsDown();
        likeDislikePercentage = roundToPlaces(urban.getTopThumbsUp()/totalVote, 4) * 100;

        std::cout << figlet(urban.getWord(0));

        std::cout << urban.getTopDefinition() << "\n\n";
        std::cout << urban.getTopExample() << "\n\n";
        std::cout << "by " << urban.getTopAuthor() << "\n";
        std::cout << "👍 " << urban.getTopThumbsUp() << "    👎 " << urban.getTopThumbsDown() << "    👍/👎 " << likeDislikeRatio << ", " << likeDislikePercentage << "%" << std::endl;
        
        return 0;
    }
    if (err == CURLE_GOT_NOTHING) {
        std::cerr << "No search results found for word/phrase \"" << argv[1] << "\"\n";
        return 1;
    }
    else std::cerr << "An error occured while fetching results: " << curl_easy_strerror(err) << "\n";
    return 1;
}