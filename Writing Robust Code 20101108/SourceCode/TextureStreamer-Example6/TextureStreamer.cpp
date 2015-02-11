
#include "TextureStreamer.h"

TextureStreamer::TextureHandle
TextureStreamer::addToSystem(const char* fileName)
{
	for (StreamingTextures::const_iterator streamingTextureIt = m_streamingTextures.begin(), end = m_streamingTextures.end();
		streamingTextureIt != end;
		streamingTextureIt++)
	{
		StreamingTexture* streamingTexture = *streamingTextureIt;
		if (streamingTexture->m_fileName == fileName)
			return streamingTexture;
	}

	StreamingTexture* streamingTexture = new StreamingTexture(fileName);

	m_streamingTextures.push_back(streamingTexture);

	return streamingTexture;
}

TextureStreamer::StreamingTexture::StreamingTexture(const char* fileName)
: m_fileName(fileName)
, m_refCount(0)
, m_texture(0)
{
}
