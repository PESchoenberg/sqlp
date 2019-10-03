/* =============================================================================

sqlp1.cpp

================================================================================

 Copyright (C) 2019  Pablo Edronkin (pablo.edronkin at yahoo.com)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.

============================================================================= */


#include "sqlp1.hpp"


using namespace std;


/* sqlp_read_file - Reads a file and returns it as a std::string.

Arguments:
- p_f: file to read.

 */
std::string sqlp_read_file(std::string p_f)
{
  std::string res = "";
  std::string file_line = "";
  
  std::ifstream file;
  file.open(p_f.c_str());
  while (getline(file,file_line))
    {
      res = res + file_line;
    }
  file.close();
  
  return res;
}


/* sqlp_write_file - Writes data p_d to a flat file p_d using mode p_m.

Arguments:
- p_f: file name.
- p_d: string to save into p_f.
- p_m: mode.

 */
int sqlp_write_file(std::string p_f, std::string p_d, std::string p_m)
{
  std::string f = p_f;
  std::string d = p_d;
  std::string m = p_m;

  ofstream file;
  if (m == "app")
    {
      file.open(f, std::ios::app);
    }
  else if (m == "out")
    {
      file.open(f, std::ios::out);
    }
  else
    {
      return 1;
    }
  file << d << "\n";
  file.close();

  return 0;
}
