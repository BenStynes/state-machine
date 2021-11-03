#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SDL.h>
#include "timer.h"
#include <vector>
#include <Debug.h>


class AnimatedSprite 
{
public:
	AnimatedSprite();
	AnimatedSprite(SDL_Texture*);
	AnimatedSprite(SDL_Texture*,SDL_Rect);
	~AnimatedSprite();

	const Timer& getTimer();
	float getTime();
	const std::vector<SDL_Rect>& getFrames();
	void clearFrames();
	const SDL_Rect& getFrame(int);
	void addFrame(const SDL_Rect&);
	const int getCurrentFrame();
	void setLooped(bool);
	const bool getLooped();
	void setPlayed(bool);
	const bool getPlayed();
	void setTime(float);

	void setTextureRect(SDL_Rect);
	SDL_Texture* getTex() {return m_texture;}

	void setTextureDimensions(int,int);
	void render(float,float,SDL_Renderer*);
	void update();
	
private:
	Timer m_timer;
	float m_time;
	std::vector<SDL_Rect> m_frames;
	unsigned int m_current_frame;
	bool m_loop;
	unsigned int m_play_count;
	unsigned int m_max_plays;
	bool m_played;

	SDL_Texture* m_texture;
	SDL_Rect m_clip;
	int m_textureWidth;
	int m_textureHeight;
};

#endif // !ANIMATED_SPRITE_H
