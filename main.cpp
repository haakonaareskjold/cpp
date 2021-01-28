#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <utility>
#include <stack>
#include <vector>

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:

    enum flags {
        SOUTH_FACE = 0x2,
        EAST_FACE = 0X4,
        VISITED = 0X8
    };

    enum faces {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    int totalCells;
    int* cells;
    int visited;
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
        totalCells = height*width;
        visited = 1;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        if (visited >= totalCells || stack.empty()) {
            return true;
        }
        auto getOffset = [&](int x, int y) {
            return cells[x + y * width];
        };

        auto calcOffset = [&](int x, int y) {
            return x + y * width;
        };

        int x = stack.top().first;
        int y = stack.top().second;

        std::vector<faces> candidates = std::vector<faces>();

        // check north
        if(y > 0 && !(getOffset(x,y-1) & VISITED)) {
            candidates.push_back(NORTH);
        }

        // check south
        if (y < (height -1) && !(getOffset(x,y+1) & VISITED)) {
            candidates.push_back(SOUTH);
        }

        // check east
        if (x < (width -1) && !(getOffset(x+1,y) & VISITED)) {
            candidates.push_back(EAST);
        }

        // check west
        if (x > 0 && !(getOffset(x-1,y) & VISITED)) {
            candidates.push_back(WEST);
        }


        if(candidates.empty()) {
            stack.pop();
        } else {
        
            faces drawn = candidates[rand() % candidates.size()];

            switch (drawn) {
                case NORTH:
                    cells[calcOffset(x,y-1)] |= SOUTH_FACE;
                    cells[calcOffset(x,y-1)] |= VISITED;
                    stack.push(std::make_pair(x, y-1));
                break;
                case SOUTH:
                    cells[calcOffset(x,y)] |= SOUTH_FACE;
                    cells[calcOffset(x,y+1)] |= VISITED;
                    stack.push(std::make_pair(x, y+1));
                break;
                case EAST:
                    cells[calcOffset(x+1,y)] |= EAST_FACE;
                    cells[calcOffset(x+1,y)] |= VISITED;
                    stack.push(std::make_pair(x+1, y));
                break;
                case WEST:
                    cells[calcOffset(x-1,y)] |= EAST_FACE;
                    cells[calcOffset(x-1, y)] |= VISITED;
                    stack.push(std::make_pair(x-1, y));
            }

            visited++;        
        }



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
	if (demo.Construct(64*8, 64*8, 4,4))
		demo.Start();
	return 0;
}