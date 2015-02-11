
#include "TextureStreamer.h"

int main(void)
{
	TextureStreamer* textureStreamer = new TextureStreamer();

	TextureStreamer::TextureHandle textureHandle = textureStreamer->addToSystem("/data/texture1.jpg");

	textureStreamer->increaseRefCount(textureHandle);
	textureStreamer->increaseRefCount(textureHandle);
	textureStreamer->decreaseRefCount(textureHandle);

	textureStreamer->removeFromSystem(textureHandle);

	delete textureStreamer;

	return 0;
}
