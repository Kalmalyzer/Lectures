
/* This system allows the game to work with more textures than can fit into video memory at once.
   The user registers all textures with the streamer, and then informs the streamer about when
   usage of a specific texture begins/ends; the streamer will then attempt to load the texture whenever
   it is in use.

   A texture is available when isAvailable() returns non-zero.
*/

class Texture;

class TextureStreamer
{

public:

	void load(const char* fileName);
	void unload(const char* fileName);

	void beginUse(const char* fileName);
	void endUse(const char* fileName);

	void isAvailable(const char* fileName);

	Texture* getTexture(const char* fileName);
};

