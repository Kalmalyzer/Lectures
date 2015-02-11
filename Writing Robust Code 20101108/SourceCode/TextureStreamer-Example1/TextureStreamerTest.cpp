
#include "TextureStreamer.h"

int main(void)
{
	TextureStreamer* textureStreamer = new TextureStreamer();

	textureStreamer->load("/data/texture1.jpg");
	textureStreamer->unload("/data/../data/texture1.jpg");

	textureStreamer->load("/data/texture1.jpg");

	textureStreamer->beginUse("/data/texture1.jpg");
	textureStreamer->beginUse("/data/texture1.jpg");
	textureStreamer->endUse("/data/texture1.jpg");

	textureStreamer->unload("/data/texture1.jpg");

	delete textureStreamer;

	return 0;
}
