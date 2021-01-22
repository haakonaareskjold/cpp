#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <utility>
#include <stack>

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:

    enum flags {
        SOUTH_FACE = 0x2,
        EAST_FACE = 0X4,
        VISITED = 0X8
    };

    int* cells;
    std::stack<std::pair<int, int >> stack;
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
		cells = new int[height*width];

        memset(cells, 0, (height*width));

        stack.push(std::make_pair(0,0));
        cells[0] |= VISITED;
        cells[0] |= SOUTH_FACE;
        cells[1] |= VISITED;
        cells[0] |= EAST_FACE;
        cells[width] = VISITED;
    

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        auto getOffset = [&](int x, int y) {
            return cells[x + y * width];
        };

		Clear(olc::Pixel(olc::BLACK));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {

                if (getOffset(x,y) & SOUTH_FACE) {
                    //South (horizontal lines)
                    FillRect(x*8, y*8 + 7, 7, 1);
                }
                
            
                if (getOffset(x,y) & EAST_FACE) {    
                //East (vertical lines)
                FillRect(x*8 + 7, y*8, 1, 7);
                }

                if (getOffset(x,y) & VISITED) {
                //Fill
                FillRect(x*8, y*8, 7, 7);
                }
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