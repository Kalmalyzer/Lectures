
#include "TextureStreamer.h"

TextureStreamer::TextureHandle
TextureStreamer::addToSystem(const char* fileName)
{
	unsigned int i;
	for (i = 0; i < m_streamingTextures.size(); i++)
		if (m_streamingTextures[i]->fileName == fileName)
			break;

	if (i == m_streamingTextures.size())
	{
		m_streamingTextures.push_back(new StreamingTexture);
		m_streamingTextures[i]->fileName = fileName;
		m_streamingTextures[i]->texture = 0;
	}

	return m_streamingTextures[i];
}
