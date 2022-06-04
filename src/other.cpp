/*

    Copyright (C) 2021, 2022  Nishant Mishra <https://github.com/NMrocks>

    This program is licensed under the GNU General Public License.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <cmath>

#include "../include/other.hpp"

double roundToPlaces(double decimal, int places)
{
    double multiplier = std::pow(10, places);
    return std::ceil(decimal * multiplier) / multiplier;
};

bool findInVector(std::string str, std::vector<std::string> vector)
{
    for (auto i:vector)
    {
        if (i == str)
        {
            return true;
        }
    };
    return false;
}