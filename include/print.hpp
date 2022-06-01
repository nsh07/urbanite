/*

    Copyright (C) 2021, 2022  Nishant Mishra <https://github.com/NMrocks>

    This program is licensed under the GNU General Public License.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

// Header for the print functions

#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>

#include "urban++.hpp"

void printDefinition(nm::Urban& urban, std::string likeChar, std::string dislikeChar, std::string ratioStr, int index=0); // Function to print definition of given word
void printTitle(nm::Urban& urban, std::string fontFile, int index=0); // Function to print word in Figlet style

#endif