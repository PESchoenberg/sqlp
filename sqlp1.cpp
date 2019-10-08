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


/* sqlp_no_db - Informs that the database cannot be opened.

Arguments:
- p_a2: a2.
- p_b: true if db is available.

 */
void sqlp_db_ava(std::string p_a2, bool p_b)
{
  std::string c = " available.";
  
  if (p_b == false)
    {
      c = " unavailable.";
    }
  cout << "Database " << p_a2 << c << endl;
}


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


/* sqlp_save_results - Save results retrieved by callback function sql send_resq 
   to file. */
void sqlp_save_results(std::vector<std::string> p_sql_results)
{
  std::string res = "";
  
  for (unsigned i = 0; i < p_sql_results.size(); i++)
    {
      res = res + p_sql_results.at(i);
      if (i < (p_sql_results.size() - 1))
	{
	  /* Separate elements representing fields of records with "|". */
	  res = res + "|";
	}
    }
	  
  /* End the results string with a "|". */
  res = res + "|EOQ|";
  sqlp_write_file("sqlp_results.txt", res, "out");
}

