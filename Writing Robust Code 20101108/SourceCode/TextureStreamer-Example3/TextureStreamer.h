
/* This system allows the game to work with more textures than can fit into video memory at once.
   The user registers all textures with the streamer, and then informs the streamer about when
   usage of a specific texture begins/ends; the streamer will then attempt to load the texture
   whenever it is in use.

   A texture is available when getTexture() returns non-zero.
*/

#include <string>
#include <vector>

class Texture;

class TextureStreamer
{
private:
	struct StreamingTexture;

public:
	typedef StreamingTexture* TextureHandle;

	TextureHandle addToSystem(const char* fileName);
	void removeFromSystem(TextureHandle handle);

	void increaseRefCount(TextureHandle handle);
	void decreaseRefCount(TextureHandle handle);

	Texture* getTexture(TextureHandle handle);

private:

	struct StreamingTexture
	{
		std::string fileName;
		int refCount;
		Texture* texture;
	};

	std::vector<StreamingTexture*> m_streamingTextures;
};
