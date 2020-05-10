/* =============================================================================

sqlp1.hpp

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


#ifndef __SQLP1_H
#define __SQLP1_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "sqlite3.h"
#include "/usr/include/hdfql/serial/include/HDFql.hpp"


using namespace std;


double sqlp_s2d(std::string p_s);


void sqlp_db_ava(std::string p_a2, bool p_b);


std::string sqlp_read_file(std::string p_f);


int sqlp_write_file(std::string p_f, std::string p_d, std::string p_m);


void sqlp_save_results(std::vector<std::string> p_sql_results);


bool sqlp_file_exists(std::string p_f);


void sqlp_test_db(std::string p_a1, std::string p_a3);


void sqlp_show_results_if_applicable(std::string p_a3, int p_cols);


std::string sql_send_resq2();


std::vector<std::string> sqlp_parse_query_line(std::vector<std::string> p_l_query);


std::string sqlp_pretty_format(std::string p_s1, int p_cols);


#endif // !__SQLP1_H
