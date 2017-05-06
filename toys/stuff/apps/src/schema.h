// schema
//
/* record structure */
typedef struct s_record {
	unsigned int irecord; /* index of record in main database */
	char * name; /* movie name used as key */
	char * category;
	unsigned int year;
	char * format;
	char * language;
	char * url;
} nodevalue;

