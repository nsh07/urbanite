/*

    Copyright (C) 2021, 2022  Nishant Mishra <https://github.com/NMrocks>

    This program is licensed under the GNU General Public License.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <stdexcept>
#include <string>

#include "Figlet.hpp"
#include "urban++.hpp"
#include "other.hpp"

#include "print.hpp"

using srilakshmikanthanp::FigletFont;
using srilakshmikanthanp::Smushed;
using srilakshmikanthanp::Kerning;
using srilakshmikanthanp::FullWidth;

void printDefinition(nm::Urban& urban, std::string likeChar, std::string dislikeChar, std::string ratioStr, int index)
{
    double likeDislikeRatio = 0, likeDislikePercentage = 0;
    double totalVote = urban.getThumbsUp(index) + urban.getThumbsDown(index);

    std::string thumbUp = " " + likeChar + " ";
    std::string thumbDown = "    " + dislikeChar + " ";
    std::string ratio = "    " + ratioStr + " ";
    
    if (urban.getThumbsDown(index) != 0) 
        likeDislikeRatio = roundToPlaces((double) urban.getThumbsUp(index)/urban.getThumbsDown(index), 2);
    
    
    likeDislikePercentage = roundToPlaces(urban.getThumbsUp(index)/totalVote, 4) * 100;

    std::cout << urban.getDefinition(index) << "\n\n";
    std::cout << urban.getExample(index) << "\n\n";
    std::cout << "by " << urban.getAuthor(index) << "\n";
    std::cout << thumbUp << urban.getThumbsUp(index) << thumbDown << urban.getThumbsDown(index) << ratio << likeDislikeRatio << ", " << likeDislikePercentage << "%" << std::endl;
}

void printTitle(nm::Urban& urban, std::string fontFile, int index)
{
    /*
    Prints the word ("Title" of the output) in the Figlet style.
    Some figlet fonts don't support the smushed and kerning style, so a nested try-catch must be used
    (I didn't have a better solution for this :P)
    Runs like so:
    1. First try to print the word smushed, and return
    2. If runtime_error occurs, try printing the word in the "kerning" style, then return
    3. If runtime_error occurs again, try printing in the full width style, them return
    4. If runtime_error occurs yet again, print the error to stderr and the word in plain text to stderr
    */
    try {
        srilakshmikanthanp::Figlet figlet(FigletFont::make(fontFile), Smushed::make());
        std::cout << figlet(urban.getWord(index));
    }
    catch (const std::runtime_error& error) {
        try {
            srilakshmikanthanp::Figlet figlet(FigletFont::make(fontFile), Kerning::make(1));
            std::cout << figlet(urban.getWord(index));
        }
        catch (const std::runtime_error& error2) {
            try {
                srilakshmikanthanp::Figlet figlet(FigletFont::make(fontFile), FullWidth::make());
                std::cout << figlet(urban.getWord(index));
            }
            catch (const std::runtime_error& error3) {
                std::cerr << "urbanite: Figlet error -- " << error3.what() << std::endl;
                std::cout << urban.getWord(index) << std::endl;
            }
        }
    }
}