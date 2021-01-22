#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:

    int* cell;
    int height;
    int width;

	Example()
	{
		// Name your application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
        height = 64;
        width = 64;
		cell = new int[height*width];
    
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::Pixel(olc::BLACK));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                FillRect(x*4, y*4 + 3, 4, 1);
            }
        }
        return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(64*4, 64*4, 4, 4))
		demo.Start();
	return 0;
}