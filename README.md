# sqlp - Simple terminal query and .sql file processing for Sqlite3.

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3471779.svg)](https://doi.org/10.5281/zenodo.3471779)


## Overview:

This C++ program allows you to send SQL queries as strings or entire .sql files 
containing several queries to any Sqlite3 database without any additional 
libraries or add ons aside from Sqlite3 itself. 


## Dependencies:

* Sqlite3 (See sources).


## Installation:

* Uncompress and copy the contents of this file wherever you want in your
system.

* Copy sqlite3.cpp and sqlite3.h to the same folder or open sqlp1.hpp and
modify the #include "sqlite3.h" line accordingly with the path to sqlite3.h
on your system.

* Compile as (Linux):

	- g++ -std=c++17 -Wall -O3 -c sqlp0.cpp sqlp1.cpp

* Link as:

	- g++ -std=c++17 -Wall -O3 sqlp0.o sqlp1.o -o sqlp -lsqlite3


## Uninstall:

* Delete the folder containing the contents of this file from your system.


## Usage:

* Assuming that you have sqlp on the same folder that holds your database, 
briefly, in a terminal write:

	- ./sqlp [db] [query]

where

	- [db] is the database that you want to query.

	- [query] is a Sqlite3 - compatible SQL query or the name of a .sql file.

* Query results are written as a continuous string to sqlp_results.txt. Data 
fields are separated with a "|" character.

* Pay attention to the path to [db] and [query] if it is a .sql file. If they 
are not in the same folder as sqlc, then you will need to provide full paths or
add those files or folders to your $PATH.

* Read the manual found at doc/sqlp.pdf.


## Credits and Sources:

* Sqlite.org. (2000). SQLite Home Page. [online] Available at: 
https://www.sqlite.org/index.html [Accessed 26 Aug. 2019].

Please let me know if I forgot to add any credits or sources.


## License:

* GPL-3.0-or-later.


