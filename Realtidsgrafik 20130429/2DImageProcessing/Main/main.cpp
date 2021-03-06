
/* Main loop for all the example programs */

#define NOMINMAX
#include "../TinyPTC 0.8/Source/tinyptc.h"

#include "Types.h"
#include "Image.h"
#include "FloatRGBColor.h"
#include "main.h"

static int pixels[ScreenWidth * ScreenHeight];

bool running = true;

static void keyDownCallBack(WPARAM wParam)
{
	if ((wParam & 0xff) == ' ')
		running = !running;
}

int main()
{
	// Initialization

	Image* renderTarget = new Image(ScreenWidth, ScreenHeight);

	initEffect();

    if (!ptc_open(L"test", ScreenWidth, ScreenHeight)) return 1;

	ptc_keydowncallback = keyDownCallBack;

	LARGE_INTEGER performanceCounterFrequency;
	QueryPerformanceFrequency(&performanceCounterFrequency);

	LARGE_INTEGER previousPerformanceCounterValue;
	QueryPerformanceCounter(&previousPerformanceCounterValue);

	double elapsedTime = 0;

	// Run rendering loop as quickly as possible, rendering new frames, and displaying them

    while (1)
    {
		// Compute how much time has elapsed since the previous iteration through the main run,
		//  and if the program is not paused, accumulate that to the elapsed time

		LARGE_INTEGER currentPerformanceCounterValue;
		QueryPerformanceCounter(&currentPerformanceCounterValue);
		if (running)
		{
			elapsedTime += (double) (currentPerformanceCounterValue.QuadPart - previousPerformanceCounterValue.QuadPart) / (double) (performanceCounterFrequency.QuadPart);
		}

		previousPerformanceCounterValue = currentPerformanceCounterValue;

		// Let effect-specific code render one frame

		renderEffect(renderTarget, elapsedTime);

		// Convert frame from FloatRGBColors to packed ARGB8888 format by
		// clamping all colour values to [0, 255], discarding all decimals,
		// and finally packing each colour channel triplet into a 32-bit int

		static FloatRGBColor black(0.f, 0.f, 0.f);
		static FloatRGBColor white(255.f, 255.f, 255.f);

		for (uint index=0; index < ScreenWidth * ScreenHeight; index++)
        {
			FloatRGBColor clampedColor = clamp(renderTarget->m_pixels[index], black, white);
			int packedColor = (((int) clampedColor.r) << 16) | (((int) clampedColor.g) << 8) | ((int) clampedColor.b);
			pixels[index] = packedColor;
        }

		// Ask PTC to display resulting pixel array in the program's window

		ptc_update(reinterpret_cast<int*>(pixels));
    }
}