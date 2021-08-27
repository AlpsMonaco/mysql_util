#include "../mysql_util.h"
#include <iostream>

template <typename T>
void println(T t)
{
	std::cout << t << std::endl;
}

const char *user = "user";
const char *pass = "password";
const char *host = "host";
const char *db_name = "db_name";
const int port = port;

int main(int argc, char **argv)
{
	mysql_util mysql_util(user, pass, host, port, db_name);
	auto m = &mysql_util;
	if (!m->is_connected())
	{
		char err_msg[256];
		m->last_error(err_msg);
		println(err_msg);
		return 1;
	}

	mysql_result *result = m->query("select id,name from user");
	// return nullptr if error occurs.
	if (result == nullptr)
	{
		char err_msg[256];
		m->last_error(err_msg);
		println(err_msg);
		return 1;
	}
	else
	{
		while (result->next())
		{
			// directly get row
			const char *id = result->get(0);

			// copy row to char*
			char name[256];
			result->get(1, name);
		}
	}

	int num = m->exec("insert into user values (255,'jack')");
	// return -1 if there's an error on query.
	if (num == -1)
	{
		char err_msg[256];
		m->last_error(err_msg);
		println(err_msg);
		return 1;
	}
	else //return affected nums if success.
	{
		std::cout << "num affected " << num << std::endl;
	}

	return 0;
}