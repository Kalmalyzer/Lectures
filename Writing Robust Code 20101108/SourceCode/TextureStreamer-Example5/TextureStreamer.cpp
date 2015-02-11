
#include "TextureStreamer.h"

TextureStreamer::TextureHandle
TextureStreamer::addToSystem(const char* fileName)
{
	for (StreamingTextures::const_iterator streamingTextureIt = m_streamingTextures.begin(), end = m_streamingTextures.end();
		streamingTextureIt != end;
		streamingTextureIt++)
	{
		StreamingTexture* streamingTexture = *streamingTextureIt;
		if (streamingTexture->fileName == fileName)
			return streamingTexture;
	}

	StreamingTexture* streamingTexture = new StreamingTexture;
	streamingTexture->fileName = fileName;
	streamingTexture->texture = 0;

	m_streamingTextures.push_back(streamingTexture);

	return streamingTexture;
}
