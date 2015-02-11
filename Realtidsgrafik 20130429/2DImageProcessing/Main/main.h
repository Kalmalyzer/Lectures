
#ifndef MAIN_H
#define MAIN_H

enum { ScreenWidth = 640 };
enum { ScreenHeight = 480 };

class Image;

void initEffect();
void renderEffect(Image* output, double elapsedTime);

#endif
