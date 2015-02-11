

//////////////////////////////////////////////////////////////////////////

// Better


class FileSystem
{
	FileSystem(NetworkSystem& networkSystem);
	...
};

class NetworkSystem
{
	...
};

class Logger
{
public:
	Logger(FileSystem& fileSystem);
private:
	static Logger* s_instance;
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
	NetworkSystem networkSystem;
	{
		FileSystem fileSystem(networkSystem);
		{
			Logger logger(fileSystem);

			doStuff1();
			doStuff2();

			Logger::getInstance()->logMessage("Hello world");
		}
	}

	return 0;
}


