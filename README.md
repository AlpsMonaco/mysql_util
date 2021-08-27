# mysql_util
**a mysql util based on c mysql lib**



## usage

### 1.connect to mysql

```
const char *user = "user";
const char *pass = "password";
const char *host = "host";
const char *db_name = "db_name";
const int port = port;

mysql_util mysql_util(user, pass, host, port, db_name);
// call is_connected() to know whether the mysql is connected or not
if (!m->is_connected()){
	return 1;
}
```



### 2.Query SQL

```
mysql_result *result = m->query("select id,name from user");
// return nullptr if error occurs.
if(result == nullptr){
	return 1;
}else
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
```



### 3.Execute SQL

```
int num = m->exec("insert into user values (255,'jack')");
// return -1 if there's an error on query.
if (num == -1)
{
	char err_msg[256];
	m->last_error(err_msg);
	println(err_msg);
	return 1;
}else //return affected nums if success.
{
	std::cout << "num affected " << num << std::endl;
}
```



## look src/cmd/main.cpp for full demo;
