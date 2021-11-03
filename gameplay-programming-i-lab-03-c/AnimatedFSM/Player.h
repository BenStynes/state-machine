#ifndef PLAYER_H
#define PLAYER_H
#include <Events.h>
#include <PlayerState.h>
#include <AnimatedSprite.h>
#include <RunRightPlayerState.h>
struct vector2f
{
	float x,y;
};

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;
	vector2f m_pos;

	bool m_run{false};
	bool m_jump{false};
	bool m_fall{false};
	float m_speed{0.5f};
public:
	Player(const AnimatedSprite&);
	virtual void handleInput(gpp::Events);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
	void render(SDL_Renderer* renderer);
};
#endif

