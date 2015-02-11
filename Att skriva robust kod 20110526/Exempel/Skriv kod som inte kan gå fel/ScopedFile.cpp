
#include "ScopedFile.h"

ScopedFile::ScopedFile(const char* name, const char* mode)
{
	m_file = fopen(name, mode);
	m_success = (m_file != 0);
}

ScopedFile::~ScopedFile()
{
	if (m_file)
		fclose(m_file);
}

bool ScopedFile::isOpen() const
{
	return m_success;
}

FILE* ScopedFile::get() const
{
	return m_file;
}
