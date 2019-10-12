/* =============================================================================

sqlp0.cpp

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

================================================================================

* Testing:
- See README.md
- Example: ./sqlp jcp_inm.db "SELECT * FROM trf_streets;"

============================================================================= */


#include "sqlp0.hpp"


using namespace std;


/* Vector required to process sqlite query results. */
std::vector<std::string> sql_results(0);


/* sql_send_resq - Looks into a database file and brings results via the 
   sql_results vector. */
static int sql_send_resq(void *data, int argc, char **argv, char **azColName)  
{  
  for(int i = 0; i < argc; i++)
    {
      sql_results.push_back(argv[i] ? argv[i] : " ");
    }
   
  return 0;
}


/* Main program.*/
int main(int argc, char** argv)
{  
  std::string a1 = "";
  std::string a2 = "";
  std::string a3 = "OPEN_QUERY_CLOSE";
  std::string query = "";
  std::string res = "";

  sqlite3 *db;
  char *errmsg;
  const char* data = " ";
  
  /* There must be three ot four arguments, one as the argument list and two from 
     the user being:
     - 1: database to operate on.
     - 2: query string or sql file to run.
     - 3: macro. 
  */
  if (argc == 3)
    {
      a1 = argv[1];
      a2 = argv[2];

      /* Some operations require three arguments instead of four, so we need to 
	 redefine a3 accordingly. */
      if (a2 == "TEST_DB")
	{
	  a3 = a2;
	}
    }
  else if (argc == 4)
    {
      a1 = argv[1];
      a2 = argv[2];
      if ((a3 == "OPEN_QUERY_CLOSE")||(a3 == "TEST_DB"))
	{
	  a3 = argv[3];
	}
    }

  /* Perform this if the number of arguments is correct. */
  if ((argc == 3) || (argc == 4))
    {
      /* If substring ".sql" is found in the secon argument, then it is assumed 
	 that the second argument represents a file. Otherwise, it is assumed 
	 that it represents a query. */

      if (a2.find(".sql") != std::string::npos)
	{
	  query = sqlp_read_file(a2);
	}
      else
	{
	  query = a2;
	}
    } 
  
  /* Opening, querying and closing according to a3. */
  if ((a3 == "OPEN_QUERY_CLOSE")||(a3 == "OPEN_QUERY_CLOSE_SHOW"))
    {        
      if(sqlite3_open(a1.c_str(), &db) == 0)
	{
	  sqlite3_exec(db, query.c_str(), sql_send_resq, (void*)data, &errmsg);
	  sqlp_save_results(sql_results);
	  sqlite3_close(db);
	  if (a3 == "OPEN_QUERY_CLOSE_SHOW")
	    {
	      std::string res = sqlp_read_file("sqlp_results.txt");
	      cout << res << endl;
	    }
	}
      else
	{
	  sqlp_db_ava(a2, false);
	}	
    }
  else if (a3 == "TEST_DB")
    {
      if(sqlite3_open(a1.c_str(), &db) == 0)
	{
	  sqlp_db_ava(a2, true);
	}
      else
	{
	  sqlp_db_ava(a2, false);
	}	  
    }
  
  /* Delete the results vector. */
  sql_results.erase(sql_results.begin(), sql_results.end());
  
  return 0;
}
