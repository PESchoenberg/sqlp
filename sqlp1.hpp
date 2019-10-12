/* =============================================================================

sqlp1.hpp

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


#ifndef __SQLP1_H
#define __SQLP1_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
//#include <sstream>
#include <string>
#include <vector>
#include "sqlite3.h"


using namespace std;


void sqlp_db_ava(std::string p_a2, bool p_b);


std::string sqlp_read_file(std::string p_f);


int sqlp_write_file(std::string p_f, std::string p_d, std::string p_m);


void sqlp_save_results(std::vector<std::string> p_sql_results);


#endif // !__SQLP1_H
