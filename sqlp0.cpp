/* =============================================================================

sqlp0.cpp

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

================================================================================

* Testing:
- See README.md
- Example: ./sqlp jcp_inm.db "SELECT * FROM trf_streets;"

* Compilation:

- First the Sqlite3 extensions:

  - gcc -fPIC -g -lm -Wall -shared extension-functions.c -o libsqlitefunctions.so

- Then sqlp itself:

  - g++ -std=c++17 -Wall -O3 -c sqlp0.cpp sqlp1.cpp

* Link as:

- g++ -std=c++17 -Wall -O3 sqlp0.o sqlp1.o -o sqlp -lsqlite3 -fopenmp -I/usr/include/hdfql/serial/include/ /usr/include/hdfql/serial/wrapper/cpp/libHDFql.a -ldl

Note: The paths for linking correspond to the author's setup. Change those
paths according to your system.

============================================================================= */


#include "sqlp0.hpp"


using namespace std;


/* Vector required to process sqlite query results. */
std::vector<std::string> sql_results(0);


/* sql_send_resq - Looks into a database file and brings results via the 
   sql_results vector. 

Arguments:
- data
- argc
- argv
- azColName

*/
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
  int cols = 1;
  std::string a1 = "";
  std::string a2 = "";
  std::string a3 = "OPEN_QUERY_CLOSE";
  std::string q1 = "";
  std::string q2 = "";
  std::string q3 = "";
  std::string res = "";
  sqlite3 *db;
  char *errmsg;
  const char* data = " ";
  std::vector<std::string>l_query(0);
  //size_t pos = 0;
 
  /* There must be three or four arguments, one as the argument list and two from 
     the user being:
     - 1: database file (Sqlite3 .db, HDF5 .h5 or text .txt) to operate on.
     - 2: query string or sql file to run.
     - 3: macro. 
  */
  if (argc == 3)
    {
      a1 = argv[1];
      a2 = argv[2];

      /* Some operations require three arguments instead of four, so we need to 
	 redefine a3 accordingly. 
      */
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
      /* If substring ".sql" or ".hql" is found in the second argument, then it 
	 is assumed that the second argument represents a file. Otherwise, it 
	 is assumed that it represents a query. 
      */
      l_query.push_back("TRUE");      
      if ((a2.find(".sql") != std::string::npos)||(a2.find(".hql") != std::string::npos))
	{
	  q1 = sqlp_read_file(a2);
	}
      else
	{
	  q1 = a2;
	}
      l_query.push_back(" "); // The string for each simple query out of composites.
      l_query.push_back(q1); // The composite query string itself.
    }
  
  /* If ".db" is found on the first argument, it is assumed that this is an Sqlite
     query, If ".h5" is found, it is assumed that this is an hdf5 thing. 
  */
  if (a1.find(".h5") != std::string::npos)
    {
      sqlp_test_db(a1, a3);
      if ((a3 == "OPEN_QUERY_CLOSE")||(a3 == "OPEN_QUERY_CLOSE_SHOW"))
	{
	  /* Create .h5 file if it does not exist in order to mimic the behavior 
	     of Sqlite3 in this regard. The idea is that thorough sqlp the user
	     will have a similar experience with SQL and HDFql.
	   */
	  if (sqlp_file_exists(a1) == false)
	    {
	      q2 = "CREATE FILE " + a1;
	      HDFql::execute(q2.c_str());
	    }
	  
	  /* Open .h5 file. */
	  q2 = "USE FILE " + a1;
	  HDFql::execute(q2.c_str());
	  
	  /* Execute hdfql statements. */
	  while (l_query[0] == "TRUE")
	    {
	      /* This will return new values for each l_query element. */
	      l_query = sqlp_parse_query_line(l_query);

	      /* Reassign q1. */
	      q1 = l_query[1];
	      if (l_query[0] != "NULL")
		{
		  HDFql::execute(q1.c_str());
		}
	    }

	  /* Process results vector. */
	  HDFql::cursorFirst(NULL);
	  sql_results.push_back(sql_send_resq2());
	  while(HDFql::cursorNext(NULL) == HDFQL_SUCCESS) 
	    {
	      sql_results.push_back(sql_send_resq2());
	    }	  
	  sqlp_save_results(sql_results);

	  /* Close and show results if applicable. */
	  HDFql::execute("CLOSE ALL FILE");
	  sqlp_show_results_if_applicable(a3, cols);  
	}
    }
  else if (a1.find(".db") != std::string::npos)
    {
      sqlp_test_db(a1, a3);
      if ((a3 == "OPEN_QUERY_CLOSE")||(a3 == "OPEN_QUERY_CLOSE_SHOW"))
	{
	  /* Open Sqlite3 database file (create it if it does not exist). */
	  if(sqlite3_open(a1.c_str(), &db) == 0)
	    {
	      /* Load required Sqlite3 extensions. Comment-out these two lines if 
		 for any reason you do not want to use extensions. If you want to
		 add more extensions, get the require the .c files, compile them 
		 like libsqlitefunctions and add a new sqlite3_load_extension() call
		 per extension below.
	      */
	      if (sqlite3_db_config(db, SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION, 1, NULL) == SQLITE_OK)
		{
		  sqlite3_load_extension(db, "libsqlitefunctions", 0, 0);
		}

	      /* Execute sql statements. */ 
	      sqlite3_exec(db, q1.c_str(), sql_send_resq, (void*)data, &errmsg);

	      /* Process results vector. */
	      sqlp_save_results(sql_results);

	      /* Close and show results if applicable. */
	      sqlite3_close(db);
	      sqlp_show_results_if_applicable(a3, cols);
	    }
	  else
	    {
	      sqlp_db_ava(a2, false);
	    }	
	}
    }
  else if (a1.find("sqlp_results.txt") != std::string::npos)
    {
      /*
	This option requires thre arguments:
	- a1: the name of the file to show or print.
	- a2: the number of colums (default 1).
	- a3: macros PRETTY_*
      */
    
      /* Establish the presentation format based on the number of cols selected with argument a2 */
    
      if ((a2.find("COLS=") != std::string::npos)||(a2.find("cols=") != std::string::npos))
	{
	  std::string str1 = "COLS=";
	  std::string str2 = "";
	  std::string str3 = "";
	  size_t pos1 = 0;
	  
	  // Extract the number of cols to print between COLS= and the first semicolon after that.
	  size_t found1 = a2.find(str1); 
	  if (found1 != string::npos)
	    {
	      str2 = a2.substr(pos1);
	      size_t found2 = str2.find(";");
	      str3 = str2.substr(5,(found2 - 1));
	      cols = (int)sqlp_s2d(str3);
	    }
	}
      sqlp_pretty_format(a1, cols);
      if (a3 == "PRETTY_SHOW")
	{
	  sqlp_show_results_if_applicable(a3, cols);
	}
    }
  else
    {
      sqlp_db_ava(a2, false);
    }
  
  /* Delete vectors. */
  sql_results.erase(sql_results.begin(), sql_results.end());
  l_query.erase(l_query.begin(), l_query.end());
  
  return 0;
}
