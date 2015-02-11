
/////////////////////////

// BAD

FileCache fileCache;

int main(void)
{
	return 0;
}

/////////////////////////

// Better

FileCache* fileCache = 0;

int main(void)
{
	fileCache = new FileCache;
	...
	delete fileCache;
	return 0;
}

