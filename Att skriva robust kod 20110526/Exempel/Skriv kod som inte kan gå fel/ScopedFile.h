
#ifndef _ScopedFile_h_
#define _ScopedFile_h_

#include <stdio.h>

class ScopedFile
{
public:
	ScopedFile(const char* name, const char* mode);
	~ScopedFile();

	bool isOpen() const;
	FILE* get() const;

private:
	FILE* m_file;
	bool m_success;

};

#endif // _ScopedFile_h_
