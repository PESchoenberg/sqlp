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
   to file by means of a cursor. */
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
void sqlp_show_results_if_applicable(std::string p_a3)
{
  if (p_a3 == "OPEN_QUERY_CLOSE_SHOW")
    {
      std::string res = sqlp_read_file("sqlp_results.txt");
      cout << res << endl;
    }
}


/* sql_send_resq2 - Returns results for hdfql queries.

 */
std::string sql_send_resq2()
{
  int dt;
  std::string res;
  
  /* This stream with a switch is an ugly construction, but seems to 
     work.*/
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


/*

 */
std::vector<std::string> sqlp_parse_query_line(std::vector<std::string> p_l_query)
{

  return p_l_query;
}


