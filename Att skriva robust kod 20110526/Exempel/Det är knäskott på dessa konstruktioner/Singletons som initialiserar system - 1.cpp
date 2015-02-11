

//////////////////////////////////////////////////////////////////////////

// BAD


class FileSystem
{
	static FileSystem* getInstance();
	...
};

class NetworkSystem
{
	static NetworkSystem* getInstance();
	...
};

class Logger
{
	static Logger* getInstance();
	...
};

///////////////////////////////////////////////////////////////////////////

void doStuff()
{
	read_configuration_file();
}

void doStuff2()
{
	activate_network();
}

///////////////////////////////////////////////////////////////////////////

int main()
{
	doStuff1();
	doStuff2();

	Logger::getInstance()->logMessage("Hello world");

	return 0;
}


