#include <stdio.h>
#include <stdlib.h>

extern "C"{
    #include <sqlite3.h> 
}
//build: gcc -l sqlite3 orm.c 
//http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
// https://github.com/paulftw/hiberlite
// http://www.qxorm.com/qxorm_en/home.html

typedef struct _table {
    int key;            //"ID INT PRIMARY KEY     NOT NULL,"
    char name[32];      //"NAME           TEXT    NOT NULL,
    int age;            //"AGE            INT     NOT NULL,
    char address[50];   //"ADDRESS        CHAR(50),
    float salary;       //"SALARY         REAL 
} table;

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    if (NULL != data) {
        fprintf(stdout, "data %s: ", (const char*)data);
    }
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

sqlite3* my_db_open()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    return db;
}

int my_db_close(sqlite3 *db)
{
    sqlite3_close(db);
    return 0;
}

int my_db_exec(sqlite3 *db, char *sql)
{
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{
    sqlite3 *db;
    char *drop = "DROP TABLE COMPANY";

    char *create = "CREATE TABLE COMPANY("  \
                   "ID INT PRIMARY KEY     NOT NULL," \
                   "NAME           TEXT    NOT NULL," \
                   "AGE            INT     NOT NULL," \
                   "ADDRESS        CHAR(50)," \
                   "SALARY         REAL );";

    char *query = "SELECT * from COMPANY";

    char *update = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
                   "SELECT * from COMPANY";

    char *insert =  "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
                    "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
                    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
                    "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
                    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
                    "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
                    "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
                    "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    char *del   = "DELETE from COMPANY where ID=2; " \
                   "SELECT * from COMPANY";

    char *clear = "DELETE from COMPANY";

    db = my_db_open();
    //my_db_exec(db, create);
    my_db_exec(db, update);
    my_db_exec(db, query);
    my_db_exec(db, insert);
    my_db_close(db);
    return 0;
}
