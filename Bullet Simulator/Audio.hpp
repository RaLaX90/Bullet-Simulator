#pragma once

#include <SDL_mixer.h>

#include <array>
#include <string>

class Audio // singleton "audio" class
{
private:
	Audio();
	~Audio();

	static Audio* m_audio;

	bool m_audio_opened;

	std::array<Mix_Chunk*, 1> m_effects;
	std::array<Mix_Music*, 1> m_musics;

	std::array<std::string, 1> m_effects_paths;
	std::array<std::string, 1> m_music_path;

	void loadMusics();
	void loadEffects();

public:
	Audio(Audio& _other) = delete;
	void operator=(const Audio&) = delete;

	enum class EffectType
	{
		wall_hit,
		wall_destroy,
		bullet_appear,
		bullet_disappear
	};

	enum class Music
	{
		music_1
	};

	static Audio* GetInstance();

	void PlayMusic(Music _music_type, const int& _loop_flag);
	void PlayEffect(EffectType _effect_type);
};