# sqlp - Simple terminal query and .sql file processing for Sqlite3 and
HDF5 databases.

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3471779.svg)](https://doi.org/10.5281/zenodo.3471779)


## Overview:

This C++ program allows you to send SQL queries as strings or entire .sql files 
containing several queries to any Sqlite3 or HDF5 databases.

It performs its tasks without using any dot command, so it might be an
alternative for anyone that needs to use Sqlite3 without its command line
interpreter.


## Dependencies:

* Sqlite3.

* HDF5.

* HDFql.

See the Sources section below for links to these dependencies.


## Installation:

* Install the required Slite3, HDF5 and HDFql files first and make sure that
they work. Both Sqlite3 and HDFql offer command-line interpreters, so
testing them should not be difficult.

* You may want to add your Sqlite3 and HDFql installations to your $PATH
variable at this point.

* Uncompress and copy the contents of your sqlp file wherever you want in your
system.

* Copy sqlite3.cpp and sqlite3.h to the same folder or open sqlp1.hpp and
modify the #include "sqlite3.h" line accordingly with the path to sqlite3.h
on your system.

* Check that the paths to your HDFql installation in the include HDFql.h call
in sqlp1.hpp is correct; change it accordingly.


* Compile as (Linux):

- g++ -std=c++17 -Wall -O3 -c sqlp0.cpp sqlp1.cpp

* Link as:

- g++ -std=c++17 -Wall -O3 sqlp0.o sqlp1.o -o sqlp -lsqlite3 -fopenmp -I
  [path to your HDFql include folder]
  [path to your HDFql wrapper/cpp folder]/libHDFql.a -ldl

where [path to your HDFql include folder] is the path on your computer to
the include folder of HDFql. In my case, for example, this is

- /usr/include/hdfql/serial/include/

and for the wrappers

- /usr/include/hdfql/serial/wrapper/cpp/


## Uninstall:

* Delete the folder containing the contents of this file from your system.

* For Sqlite3, HDFql and HDF5 files, see the corresponding manuals.


## Usage:

* For more details, read doc/sqlp.pdf. This is a brief introduction.

* Assuming that you have sqlp on the same folder that holds your database, 
briefly, in a terminal write:

- ./sqlp [db] [query]

where

- [db] is the database that you want to query.

- [query] is a Sqlite3 - compatible SQL query or the name of a .sql file
  or an HDFql query, in the case that you want to access an HDF5 database.

consider that

- [db] is a name file that should end with ".db" for Sqlite3 databases.

- [db] should end with ".h5" for HDF5 databases. Example: my_database.h5

otherwise sqlp will ignore your query.

* Query results are written as a continuous string to sqlp_results.txt. Data 
fields are separated with a "|" character. Results for both Sqlite3 and
HDF5 databases are writteh to this file.

* Pay attention to the path to [db] and [query] if it is a .sql or .hql file.
If they are not in the same folder as sqlc, then you will need to provide
full paths or add those files or folders to your $PATH.

* Read the manual found at doc/sqlp.pdf.


## Credits and Sources:

* Sqlite.org. (2000). SQLite Home Page. [online] Available at: 
https://www.sqlite.org/index.html [Accessed 26 Aug. 2019].

* The HDF Group. (2019). The HDF Group - ensuring long-term access and
usability of HDF data and supporting users of HDF technologies. [online]
Available at: https://www.hdfgroup.org [Accessed 18 Oct. 2019].


* Hdfql.com. (2019). The easy way to manage HDF5 data. [online] Available
at: http://www.hdfql.com/ [Accessed 18 Oct. 2019].


Please let me know if I forgot to add any credits or sources.


## License:

* GPL-3.0-or-later. This license is applicable to the code of sqlp. Note that
the required software may have additional licenses and terms of use.


