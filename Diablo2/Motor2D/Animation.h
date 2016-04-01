#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "p2DynArray.h"
#include "SDL/include/SDL.h"
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	bool loop;
	vector<SDL_Rect> frames;

private:
	float current_frame;
	int loops;

public:
	Animation() : frames(0), speed(1.0f), current_frame(0), loop(true), loops(0)
	{}

	Animation(const Animation& a) : frames(a.frames), speed(a.speed), current_frame(0), loop(a.loop), loops(0)
	{}

	void SetFrames(int x, int y, int sprite_w, int sprite_h, int num_frames, int margin = 0)
	{
		for (int i = 0; i < num_frames; i++)
		{
			frames.push_back({ x + (sprite_w + margin) * i, y, sprite_w, sprite_h });
		}
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
		{
			current_frame = (loop) ? 0.0f : frames.size() - 1;
			loops++;
		}

		return frames[(int)current_frame];
	}

	const SDL_Rect& PeekCurrentFrame() const
	{
		return frames[(int)current_frame];
	}

	bool Finished()
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
		loops = 0;
	}

	int CurrentFrame() const
	{
		return current_frame;
	}
};

#endif _ANIMATION_H_