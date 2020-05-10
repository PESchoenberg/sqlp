/* =============================================================================

sqlp1.cpp

================================================================================

 Copyright (C) 2019 - 2020  Pablo Edronkin (pablo.edronkin at yahoo.com)

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


/* sqlp_s2d - Converts a string to a double.

Arguments:
- p_s: string to convert.

Output:
- Double.

 */
double sqlp_s2d(std::string p_s)
{
  double res = 0.00;

  stringstream strs(p_s);
  strs >> res;
 
  return res;
}


/* sqlp_db_ava - Informs that the database cannot be opened.

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
   to file by means of a cursor.

Arguments:
- p_sql_results: sql_results.
 
*/
void sqlp_save_results(std::vector<std::string> p_sql_results)
{
  std::string res = "";
  
  for (unsigned i = 0; i < p_sql_results.size(); i++)
    {
      res = res + p_sql_results.at(i);
      if (i < (p_sql_results.size() - 1))
	{
	  /* Separate elements representing fields of records with a pipe 
	     character. */
	  res = res + "|";
	}
    }
	  
  res = res + "|EOQ|";
  sqlp_write_file("sqlp_results.txt", res, "out");
}


/* sqlp_file_exists - Returns true if p_f exists, false otherwise.

Arguments:
- p_f: file name.

 */
bool sqlp_file_exists(std::string p_f)
{ 
  std::ifstream file;
  file.open(p_f.c_str());
  if (file.fail())
    {
      return false;
    }
  file.close();
  
  return true;
}


/* sqlp_test_db - tests if a db file exists and reports if p_a3 is the
correct macro ("TEST_DB").

Arguments:
- p_a1: a1.
- p_a3: a3.

*/
void sqlp_test_db(std::string p_a1, std::string p_a3)
{
  if (p_a3 == "TEST_DB")
    {
      if (sqlp_file_exists(p_a1) == true)
	{
	  sqlp_db_ava(p_a1, true);
	}
      else
	{
	  sqlp_db_ava(p_a1, false);
	}
    }
}


/* sqlp_show_results_if_applicable - Shows results on the terminal
if p_a3 = OPEN_QUERY_CLOSE_SHOW.

Arguments:
- p_a3: a3.

 */
void sqlp_show_results_if_applicable(std::string p_a3, int p_cols)
{
  std::string res = "";
  if (p_a3 == "OPEN_QUERY_CLOSE_SHOW")
    {
      res = sqlp_read_file("sqlp_results.txt");
      cout << res << endl;
    }
  else if (p_a3 == "PRETTY_SHOW")
    {
      res = sqlp_read_file("sqlp_results.txt");
            
    } 
}


/* sql_send_resq2 - Returns results for hdfql queries.

 */
std::string sql_send_resq2()
{
  int dt;
  std::string res;
  
  /* This stream with a switch is an ugly construction, but seems to 
     work. */
  stringstream sz;
  dt = HDFql::cursorGetDataType(NULL);
  switch (dt){
  case HDFQL_UNSIGNED_SMALLINT:
    sz << *HDFql::cursorGetSmallInt(NULL);
    break;
  case HDFQL_VARBIGINT:
    sz << *HDFql::cursorGetInt(NULL);
    break;
  case HDFQL_UNSIGNED_VARINT:
    sz << *HDFql::cursorGetInt(NULL);
    break;
  case HDFQL_SMALLINT:
    sz << *HDFql::cursorGetSmallInt(NULL);
    break;
  case HDFQL_UNSIGNED_VARTINYINT:
    sz << *HDFql::cursorGetTinyInt(NULL);
    break;
  case HDFQL_VARINT:
    sz << *HDFql::cursorGetInt(NULL);
    break;
  case HDFQL_UNSIGNED_BIGINT:
    sz << *HDFql::cursorGetUnsignedBigInt(NULL);
    break;
  case HDFQL_BIGINT:
    sz << *HDFql::cursorGetBigInt(NULL);
    break;
  case HDFQL_UNSIGNED_VARBIGINT:
    sz << *HDFql::cursorGetBigInt(NULL);
    break;
  case HDFQL_UNSIGNED_VARSMALLINT:
    sz << *HDFql::cursorGetInt(NULL);
    break;
  case HDFQL_VARTINYINT:
    sz << *HDFql::cursorGetTinyInt(NULL);
    break;
  case HDFQL_UNSIGNED_INT:
    sz << *HDFql::cursorGetUnsignedInt(NULL);
    break;
  case HDFQL_UNSIGNED_TINYINT:
    sz << *HDFql::cursorGetUnsignedTinyInt(NULL);
    break;
  case HDFQL_TINYINT:
    sz << *HDFql::cursorGetTinyInt(NULL);
    break;
  case HDFQL_VARSMALLINT:
    sz << *HDFql::cursorGetSmallInt(NULL);
    break;
  case HDFQL_INT:
    sz << *HDFql::cursorGetInt(NULL);
    break;
  case HDFQL_DOUBLE:
    sz << *HDFql::cursorGetDouble(NULL);
    break;
  case HDFQL_VARDOUBLE:
    sz << *HDFql::cursorGetDouble(NULL);
    break;		
  case HDFQL_FLOAT:
    sz << *HDFql::cursorGetFloat(NULL);
    break;		
  case HDFQL_VARFLOAT:
    sz << *HDFql::cursorGetFloat(NULL);
    break;
  case HDFQL_CHAR:
    sz << *HDFql::cursorGetChar(NULL);
    break;
  case HDFQL_VARCHAR:
    sz << *HDFql::cursorGetChar(NULL);
    break;	     
  case HDFQL_OPAQUE:
    sz << HDFql::cursorGet(NULL);
    break;
  case HDFQL_UNDEFINED:
    sz << HDFql::cursorGet(NULL);
    break;		
  default:
    sz << HDFql::cursorGet(NULL);
    break;
  }
  sz >> res;

  return res;
}


/* sqlp_parse_query_line - Prepares queries as single ones extracted from 
composite query strings. This function uses trinary logic, but instead of 
boolean type variables, it employs strings to indicate the state.

Arguments:
- p_l_query: l_query.
  - [0]: string "TRUE", "FALSE" or "NULL".
  - [1]: string of simple query extracted from [2].
  - [2]: string with complete composite query.

Returns:
- p_l_query with updated elements.
  - [0]: "TRUE", "FALSE" or "NULL". Notice the trinary nature of this element.
  - [1]: parsed, simple query without the ";" separator.
  - [2]: remainder of composite query string, minus [1].

 */
std::vector<std::string> sqlp_parse_query_line(std::vector<std::string> p_l_query)
{
  std::string e0 = p_l_query[0];
  std::string e1 = p_l_query[1];
  std::string e2 = p_l_query[2];
  std::string s1 = ";";
  std::string s2 = "QUERY_FINISHED";
  
  std::size_t found_s1 = e2.find(s1);
  std::size_t found_s2 = e2.find(s2);
  if (found_s1 != std::string::npos)
    {
      /* Tell the world that we have a query from a composite query. */
      p_l_query[0] = "TRUE";

      /* Extract the string of the subquery without the s1 character. */
      p_l_query[1] = e2.substr(0,(found_s1));

      /* Get the reduced composite query from the caracter following the found
       s1 character to the end of the string. */
      p_l_query[2] = e2.substr(found_s1 + 1);
    }
  else
    {
      /* If no s1 is found but there is no s2 as contents of e2 then return the 
	 query as a single one. If e2 = s2, return NULL as first element. */
      if (found_s2 != std::string::npos)
	{
	  p_l_query[0] = "NULL";
	  p_l_query[1] = "";
	  p_l_query[2] = "";
	}
      else
	{
	  p_l_query[0] = "FALSE";
	  p_l_query[1] = e2;
	  p_l_query[2] = s2;
	}
    }
  
  return p_l_query;
}


/* sqlp_pretty_format - Formats string p_s1 for columnar presentation with p_cols
columns.

Arguments:
- p_a1 string to format.
- p_cols: number of columns to divide p_s1 into.

 */
std::string sqlp_pretty_format(std::string p_a1, int p_cols)
{
  int cols = p_cols - 1;
  //int cols = 12 - 1;
  int col = 0;
  int ll = 0;
  std::string t_file = "sqlp_pretty_tmp.txt";
  std::string file_line = "";
  std::string res = sqlp_read_file(p_a1);
  std::vector<int> l_cols; 

  /* Set all vector elements to zero. */
  for(int i = 0; i <= cols; i++)
    {
      l_cols.push_back(0);
    }
  
  /* Get rid of some special characters first, just in case */
  replace(res.begin(), res.end(), '\n', ' ');
  replace(res.begin(), res.end(), '\r', ' ');
  
  /* Replace pipes with newlines so that every column field is in a different line */
  replace(res.begin(), res.end(), '|', '\n');

  /* Save to temp file. */
  sqlp_write_file(t_file, res, "out");  
  
  /* Find the max length of each field and store those values on l_cols. */
  std::ifstream file1;
  file1.open(t_file.c_str());
  while (getline(file1, file_line))
    {
      if (file_line != "EOF\n")
	{
	  ll = 0;
	  ll = file_line.length();
	  if (ll > l_cols[col])
	    {
	      l_cols[col] = ll;
	    }
	  col++;
	  if (col > cols)
	    {
	      col = 0;
	    }
	}
    }
  file1.close();

  /* Pad each field to achieve the max length contained in l_cols per field. */
  col = 0;
  res = "";
  std::ifstream file2;
  file2.open(t_file.c_str());
  while (getline(file2, file_line))
    {
      if (file_line != "EOF\n")
	{
	  /* We take out the new line char per field  */
	  replace(file_line.begin(), file_line.end(), '\n', ' ');	  
	  
	  /*  Pad file_line to the max length of this field type contained in l_cols */
	  if ((int)file_line.length() < l_cols[col])
	    {
	      file_line.append(l_cols[col] - file_line.length(), ' ');
	    }
	  res = res + "|" + file_line;
	  col++;
	  if (col > cols)
	    {
	      col = 0;
	      res = res + "\n";
	    }
	}
    }
  file2.close();

  /* Save to pretty file. */
  sqlp_write_file(t_file, res, "out");
  
  return res;
}




