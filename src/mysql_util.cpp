#include "mysql_util.h"

mysql_util::mysql_util(const char *user, const char *password, const char *host, int port, const char *db_name)
{
	this->result = nullptr;

	mysql_init(&this->mysql);
	this->connect_result = mysql_real_connect(&this->mysql, host, user, password, db_name, port, nullptr, 0);
}

bool mysql_util::is_connected()
{
	return this->connect_result;
}

void mysql_util::last_error(char *dst)
{
	strcpy(dst, mysql_error(&this->mysql));
}

mysql_result *mysql_util::query(const char *sql)
{
	mysql_result *ptr = nullptr;
	if (mysql_query(&this->mysql, sql))
		return ptr;

	MYSQL_RES *res = mysql_store_result(&this->mysql);
	if (res == nullptr)
	{
		return ptr;
	}

	if (this->result != nullptr)
	{
		delete this->result;
	}

	this->result = new mysql_result(res);
	return this->result;
}

int mysql_util::exec(const char *sql)
{
	if (mysql_query(&this->mysql, sql))
	{
		return -1;
	}

	return mysql_affected_rows(&this->mysql);
}

mysql_result::mysql_result(MYSQL_RES *res)
{
	this->res = res;
	this->num_fields = mysql_num_fields(res);
}

bool mysql_result::next()
{
	MYSQL_ROW row = mysql_fetch_row(this->res);
	if (row == NULL)
	{
		return false;
	}

	this->row = row;
	return true;
}

void mysql_result::get(int index, char *dst)
{
	if (index > this->num_fields)
	{
		return;
	}

	strcpy(dst, this->row[index]);
}

const char *mysql_result::get(int index)
{
	if (index > this->num_fields)
	{
		return nullptr;
	}

	return this->row[index];
}

mysql_result::~mysql_result()
{
	mysql_free_result(this->res);
}

void mysql_util::close()
{
	mysql_close(&this->mysql);
}

mysql_util::~mysql_util()
{
	this->close();
}

int mysql_result::get_num_fields()
{
	return this->num_fields;
}
