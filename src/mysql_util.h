#include "mysql.h"
#include "string.h"
#pragma comment(lib, "libmysql.lib")

class mysql_result
{
public:
	mysql_result(MYSQL_RES *mysql_res);
	bool next();
	void get(int index, char *dst);
	const char *get(int index);
	~mysql_result();
	int get_num_fields();

protected:
	MYSQL_RES *res;
	int num_fields;
	MYSQL_ROW row;
};

class mysql_util
{
public:
	mysql_util(const char *user, const char *password, const char *host, int port, const char *db_name);
	bool is_connected();
	void last_error(char *dst);
	void close();
	int exec(const char *sql);
	mysql_result *query(const char *sql);
	~mysql_util();

protected:
	MYSQL mysql;
	bool connect_result;
	mysql_result *result;
};