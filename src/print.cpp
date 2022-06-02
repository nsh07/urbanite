/*

    Copyright (C) 2021, 2022  Nishant Mishra <https://github.com/NMrocks>

    This program is licensed under the GNU General Public License.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include <string>

#include "../include/Figlet.hpp"
#include "../include/urban++.hpp"
#include "../include/other.hpp"

#include "../include/print.hpp"

using srilakshmikanthanp::FigletFont;
using srilakshmikanthanp::Smushed;

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
    srilakshmikanthanp::Figlet figlet(FigletFont::make(fontFile), Smushed::make());
    std::cout << figlet(urban.getWord(index));
}