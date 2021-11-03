#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() : 
	m_current_frame(0),
	m_time(0.5f),
	m_loop(true),
	m_play_count(0),
	m_max_plays(0),
	m_played(false)
{
	DEBUG_MSG("AnimatedSprite()");
}

AnimatedSprite::AnimatedSprite(SDL_Texture* t) : AnimatedSprite() 
{
	DEBUG_MSG("AnimatedSprite(SDL_Texture* t)");
	m_texture = t;
}

AnimatedSprite::AnimatedSprite(SDL_Texture* t, SDL_Rect rect) : 
	AnimatedSprite(t)
{
	DEBUG_MSG("AnimatedSprite(const Texture&, const IntRect&)");
	m_frames.push_back(rect);
}

AnimatedSprite::~AnimatedSprite() {
	DEBUG_MSG("~AnimatedSprite()");
}

const Timer& AnimatedSprite::getTimer() {
	return m_timer;
}

 float AnimatedSprite::getTime() {
	return m_time;
}

void AnimatedSprite::setTime(float t)
{
	this->m_time = t;
}

const std::vector<SDL_Rect>& AnimatedSprite::getFrames() {
	return m_frames;
}

void AnimatedSprite::clearFrames() {
	m_current_frame = 0;
	m_played = false;
	if (!m_frames.empty())
	{
		m_frames.clear();
	}
}

const SDL_Rect& AnimatedSprite::getFrame(int n) {
	return m_frames[n];
}

void AnimatedSprite::addFrame(const SDL_Rect& frame) {
	m_frames.push_back(frame);
}

const int AnimatedSprite::getCurrentFrame() {
	return m_current_frame;
}

void AnimatedSprite::setLooped(bool loop) {
	this->m_loop = loop;
}

const bool AnimatedSprite::getLooped() {
	return this->m_loop;
}

void AnimatedSprite::setPlayed(bool played) {
	this->m_played = played;
}

const bool AnimatedSprite::getPlayed() {
	return this->m_played;
}

void AnimatedSprite::update(){
	// If not looped only play once
	if (m_played == true && !m_loop)
	{
		m_current_frame = m_frames.size() - 1;
	}
	else {
		if (m_timer.getTicksAsSeconds() > m_time) {
			if (m_frames.size() > m_current_frame + 1)
			{
				m_current_frame++;
			}
			else {
				m_current_frame = 0;
				m_played = true;
			}
			m_timer.restart();
		}
	}
	
}
void AnimatedSprite::setTextureRect(SDL_Rect rect)
{
	m_clip = rect;
}

void AnimatedSprite::setTextureDimensions(int w, int h)
{
	m_textureWidth = w;
	m_textureHeight = h;
}

void AnimatedSprite::render(float x, float y, SDL_Renderer* renderer)
{
	SDL_FRect renderQuad = { x, y, static_cast<float>(m_clip.w), static_cast<float>(m_clip.h) };

	SDL_RenderCopyF(renderer, m_texture, &m_clip, &renderQuad);
}


