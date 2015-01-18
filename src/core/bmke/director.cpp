/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * bmonkey
 * Copyright (C) 2014 Juan Ángel Moreno Fernández
 *
 * bmonkey is free software.
 *
 * You can redistribute it and/or modify it under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * bmonkey is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with bmonkey.  If not, see <http://www.gnu.org/licenses/>
 */

#include "director.hpp"
#include <cassert>
#include "animation_factory.hpp"

#include "animations/move_in_animation.hpp"
#include "animations/move_out_animation.hpp"
#include "animations/ease_animation.hpp"

namespace bmonkey{

bool Director::m_instantiated = false;

Director::Director(Config* config):
	m_init(false),
	m_config(config),
	m_collection(nullptr),
	m_graphics(config),
	m_controls(m_graphics.getRenderWindow()),
	m_volumes(&m_sounds, &m_movies),
	m_show_fps(false),
	m_fps_update_time(sf::Time::Zero),
	m_fps_num_frames(0)
{
	assert(config);

	// Con este assert forzamos una instancia única de la clase
	assert(!m_instantiated);
	m_instantiated = true;
}

Director::~Director(void)
{
	// Si se destruye la instancia, permitimos que se cree de nuevo
	m_instantiated = false;
}

void Director::init(void)
{
	LOG_INFO("Director: Initializing...");
	m_init = true;

	// Obtenemos el directorio de trabajo
	m_config->getKey(BMONKEY_CFG_GLOBAL, "current_working_dir", m_working_dir);

    LOG_INFO("Director: Initializing renderer...");
  	m_graphics.init();

  	LOG_INFO("Director: Loading keymap...");
 	if (!m_controls.load(Glib::build_filename(m_working_dir, BMONKEY_KEYMAP_FILE)))
 	{
 		m_controls.registerDefaultControls();
 	}
    LOG_INFO("Director: Initializing volumes...");
    volumeInit();

	// Inicialización del visor de fps's
	if (!m_config->getKey(BMONKEY_CFG_SCREEN, "show_fps", m_show_fps))
	{
		m_config->setKey(BMONKEY_CFG_SCREEN, "show_fps", m_show_fps);
	}

	if (m_show_fps)
	{
		m_fps_text.setFont(*(m_fonts.getSystemFont(FontManager::DEFAULT)));
		m_fps_text.setPosition(5.f, 15.f);
		m_fps_text.setCharacterSize(15);
	}

	//-------------------------------------------
	// Objetos temporales, solo para pruebas
	back_texture.loadFromFile("backv00-800.png");
	sprite_texture.loadFromFile("sprite.png");
	back.setTexture(back_texture);
	entity.setTexture(&sprite_texture);
	entity.setPosition(400.f, 300.f);

	//entity.setColor(sf::Color(255,100,100, 150));
	//entity.setRotation(30);
	//entity.setScale(0.5, 1.2);
	//entity.setFlip(true, true);

	m_mod_text.setFont(*(m_fonts.getSystemFont(FontManager::DEFAULT)));
	m_mod_text.setPosition(125.f, 150.f);
	m_mod_text.setCharacterSize(30);
	m_mod_text.setString("Original");


    m_controls.enableEvent(ControlManager::SWITCH_ROTATION);
    m_controls.enableEvent(ControlManager::TAKE_SCREENSHOT);
    m_controls.enableEvent(ControlManager::SELECT);
    m_controls.enableEvent(ControlManager::BACK);
    m_controls.enableEvent(ControlManager::PLATFORM_PREVIOUS);
    m_controls.enableEvent(ControlManager::PLATFORM_NEXT);
    m_controls.enableEvent(ControlManager::GAME_PREVIOUS);
    m_controls.enableEvent(ControlManager::GAME_NEXT);
    m_controls.enableEvent(ControlManager::EXIT_MENU);
}

int Director::run(void)
{
	float fixed_fps = 60.f;
	sf::Time fixed_fps_time = sf::Time::Zero;
    sf::Time time_since_last_update = sf::Time::Zero;
    sf::Time delta_time  = sf::Time::Zero;
    sf::Clock clock;

  	// Obtenemos el tiempo para las actualizaciones fijas
	if (!m_config->getKey(BMONKEY_CFG_CORE, "fixed_framerate", fixed_fps))
	{
		m_config->setKey(BMONKEY_CFG_CORE, "fixed_framerate", fixed_fps);
	}
	if (fixed_fps == 0)
	{
		fixed_fps = 60.f;
	}
	fixed_fps_time = sf::seconds(1.f/fixed_fps);

    while (m_graphics.isOpen())
    {
    	delta_time = clock.restart();
    	time_since_last_update += delta_time;
        while (time_since_last_update > fixed_fps_time)
        {
        	time_since_last_update -= fixed_fps_time;
        	processInput();
            update(fixed_fps_time);
        }
    	if (m_show_fps)
    	{
    		updateFps(delta_time);
    	}
        draw();
    }

	clean();

	return EXIT_SUCCESS;
}

void Director::volumeInit(void)
{
	float master_volume = 100.f;
	float sound_volume = 100.f;
	float music_volume = 100.f;
	float movie_volume = 100.f;

	// Comprobamos las variables de configuración y fijamos valores por defecto
	if (!m_config->getKey(BMONKEY_CFG_SOUND, "master_volume", master_volume))
	{
		m_config->setKey(BMONKEY_CFG_SOUND, "master_volume", master_volume);
	}
	if (!m_config->getKey(BMONKEY_CFG_SOUND, "sound_volume", sound_volume))
	{
		m_config->setKey(BMONKEY_CFG_SOUND, "sound_volume", sound_volume);
	}
	if (!m_config->getKey(BMONKEY_CFG_SOUND, "music_volume", music_volume))
	{
		m_config->setKey(BMONKEY_CFG_SOUND, "music_volume", music_volume);
	}
	if (!m_config->getKey(BMONKEY_CFG_SOUND, "movie_volume", movie_volume))
	{
		m_config->setKey(BMONKEY_CFG_SOUND, "movie_volume", movie_volume);
	}

	m_volumes.setVolume(master_volume, sound_volume, music_volume, movie_volume);
}

void Director::processInput(void)
{
	ControlManager::Event event;

	static int choice = 29;
	float delay = 0.f;
	float duration = 1.5f;

	Animation* animation;
	MoveInAnimation* in_animation;
	MoveOutAnimation* out_animation = nullptr;
	EaseAnimation* e_animation;

	while (m_controls.poolEvent(event))
	{

		switch (event)
		{
		case ControlManager::EXIT:
			m_graphics.close();
			break;
		case ControlManager::UNFOCUSED:
			break;
		case ControlManager::FOCUSED:
			break;
		case ControlManager::SWITCH_ROTATION:
			m_graphics.switchRotation();
			break;
		case ControlManager::TAKE_SCREENSHOT:
			m_graphics.capture();
			break;
		case ControlManager::SELECT:
			switch (choice)
			{
			case 0:
				m_mod_text.setString("Left Back In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::LEFT_BACK_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 1:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Right Back In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::RIGHT_BACK_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 2:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Top Back In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::TOP_BACK_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 3:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Bottom Back In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::BOTTOM_BACK_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 4:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Left Bounce In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::LEFT_BOUNCE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 5:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Right Bounce In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::RIGHT_BOUNCE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 6:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Top Bounce In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::TOP_BOUNCE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 7:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Bottom Bounce In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::BOTTOM_BOUNCE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 8:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Left Ease In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::LEFT_EASE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 9:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Right Ease In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::RIGHT_EASE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 10:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Top Ease In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::TOP_EASE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 11:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Bottom Ease In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::BOTTOM_EASE_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 12:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Left Elastic In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::LEFT_ELASTIC_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 13:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Right Elastic In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::RIGHT_ELASTIC_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 14:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Top Elastic In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::TOP_ELASTIC_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 15:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Bottom Elastic In");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::BOTTOM_ELASTIC_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				entity.run();
				++choice;
				break;
			case 16:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Fade In");
				animation = AnimationFactory::create(AnimationFactory::FADE_IN, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;
			case 17:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Hard Roll In");
				animation = AnimationFactory::create(AnimationFactory::HARDROLL_IN, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;
			case 18:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Pop In");
				animation = AnimationFactory::create(AnimationFactory::POP_IN, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;
			case 19:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Roll In");
				animation = AnimationFactory::create(AnimationFactory::ROLL_IN, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;
			case 20:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Rotate In");
				animation = AnimationFactory::create(AnimationFactory::ROTATE_IN, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;
			case 21:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Left Back Out");
				out_animation = static_cast<MoveOutAnimation* > (AnimationFactory::create(AnimationFactory::LEFT_BACK_OUT, delay, duration));
				out_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(out_animation);
				entity.run();
				++choice;
				break;
			case 22:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Right Back Out");
				out_animation = static_cast<MoveOutAnimation* > (AnimationFactory::create(AnimationFactory::RIGHT_BACK_OUT, delay, duration));
				out_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(out_animation);
				entity.run();
				++choice;
				break;
			case 23:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Top Back Out");
				out_animation = static_cast<MoveOutAnimation* > (AnimationFactory::create(AnimationFactory::TOP_BACK_OUT, delay, duration));
				out_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(out_animation);
				entity.run();
				++choice;
				break;
			case 24:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Bottom Back Out");
				out_animation = static_cast<MoveOutAnimation* > (AnimationFactory::create(AnimationFactory::BOTTOM_BACK_OUT, delay, duration));
				out_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(out_animation);
				entity.run();
				++choice;
				break;
			case 25:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Fade Out");
				animation = AnimationFactory::create(AnimationFactory::FADE_OUT, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;

			case 26:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Ease X");
				animation = AnimationFactory::create(AnimationFactory::EASE_X, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;
			case 27:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Ease Y");
				animation = AnimationFactory::create(AnimationFactory::EASE_Y, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				++choice;
				break;
			case 28:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Fade");
				animation = AnimationFactory::create(AnimationFactory::FADE, delay, duration);
				entity.addAnimation(animation);
				entity.run();
				//++choice;
				break;
			case 29:
				entity.stop();
				entity.clearAnimations();
				m_mod_text.setString("Custom");
				in_animation = static_cast<MoveInAnimation* > (AnimationFactory::create(AnimationFactory::TOP_BACK_IN, delay, duration));
				in_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(in_animation);
				//animation = AnimationFactory::create(AnimationFactory::FADE_OUT, delay, duration);
				//entity.addAnimation(animation);
				animation = AnimationFactory::create(AnimationFactory::HARDROLL_IN, delay, duration);
				entity.addAnimation(animation);
				out_animation = static_cast<MoveOutAnimation* > (AnimationFactory::create(AnimationFactory::BOTTOM_BACK_OUT, delay, duration));
				out_animation->setWindowSize(m_graphics.getSize());
				entity.addAnimation(out_animation);
				entity.setCyclicAnimations(true);
				entity.run();
				//++choice;
				break;


/*
			case 24:
				m_mod_text.setString("Elastic In Left + Ease X");
				in_animation = new ElasticInAnimation();
				in_animation->setWindowSize(m_graphics.getSize());
				in_animation->setInFrom(InAnimation::LEFT);
				in_animation->init(&entity, delay, duration);
				entity.setStartAnimation(in_animation);
				e_animation = new EaseAnimation();
				e_animation->setAxis(EaseAnimation::X);
				e_animation->init(&entity, delay, 1.f);
				entity.setPlaceAnimation(e_animation);
				entity.run();
				++choice;
				break;
			case 25:
				m_mod_text.setString("Hard Roll In + Fade");
				animation = new HardrollInAnimation();
				animation->init(&entity, delay, duration + 1.f);
				entity.setStartAnimation(animation);
				animation = new FadeAnimation();
				animation->init(&entity, delay, 1.f);
				entity.setPlaceAnimation(animation);
				entity.run();
				++choice;
				break;


*/
			}
			break;

			/*
		case ControlManager::BACK:
			sound_manager.playSound(static_cast<SoundManager::Animation>(rand() % 13));
			break;
		case ControlManager::PLATFORM_PREVIOUS:
			sound_manager.setSoundVolume(sound_manager.getSoundVolume() - 5);
			LOG_DEBUG("snd vol: " << sound_manager.getSoundVolume());
			break;
		case ControlManager::PLATFORM_NEXT:
			sound_manager.setSoundVolume(sound_manager.getSoundVolume() + 5);
			LOG_DEBUG("snd vol: " << sound_manager.getSoundVolume());
			break;
		case ControlManager::GAME_PREVIOUS:
			sound_manager.setMusicVolume(sound_manager.getMusicVolume() + 5);
			LOG_DEBUG("mus vol: " << sound_manager.getMusicVolume());
			break;
		case ControlManager::GAME_NEXT:
			sound_manager.setMusicVolume(sound_manager.getMusicVolume() - 5);
			LOG_DEBUG("mus vol: " << sound_manager.getMusicVolume());
			break;
*/
		case ControlManager::EXIT_MENU:
			m_graphics.close();
			break;
		}
	}
}

void Director::update(sf::Time delta_time)
{
	//original.update(delta_time);
	entity.update(delta_time);
}

void Director::updateFps(sf::Time delta_time)
{
	Glib::ustring text;
	static const sf::Time one_second = sf::seconds(1.0f);

	m_fps_update_time += delta_time;
	++m_fps_num_frames;

	if (m_fps_update_time >= one_second)
	{

		text = "Frames / Second = " + utils::toStr(m_fps_num_frames) + "\n" +
				"Time / Update = " + utils::toStr(m_fps_update_time.asMicroseconds() / m_fps_num_frames) + "us";

		m_fps_text.setString(text.raw());

		m_fps_update_time -= one_second;
		m_fps_num_frames = 0;
	}
}

void Director::draw(void)
{
	float scale;

	m_graphics.clear();
	m_graphics.draw(back);

	m_graphics.draw(entity);
	m_graphics.draw(m_mod_text);
/*
	entity.setSelected(true);
	entity.setSize(600, 143);
	entity.setRotation(45);
	entity.setSize(600, 43);
	entity.setOpacity(190);
	entity.setTint(sf::Color(120,255,255));
	m_window.draw(entity);
*/

	//entity.setRotation(45);
	//entity.setFlip(true,false);


/*	for (int i = 0; i< 10; i++)
	{

		entity.setPosition(rand() % 1024, rand() % 768);
		//scale = (rand() % 200) / 100;
		//sprite.setScale(scale, scale);
		entity.setRotation(rand() % 360);
		m_window.draw(entity);
	}
*/

	// Esto debe ser lo último
	if (m_show_fps)
	{
		m_graphics.draw(m_fps_text);
	}
	m_graphics.display();
}

void Director::clean(void)
{
	// Hay que parar los videos del movie manager o produce errores
	m_movies.stopAll();

	m_controls.save();

	LOG_INFO("Director: Saving volumes...");
	m_config->setKey(BMONKEY_CFG_SOUND, "master_volume", m_volumes.getMasterVolume());
	m_config->setKey(BMONKEY_CFG_SOUND, "sound_volume", m_volumes.getSoundVolume());
	m_config->setKey(BMONKEY_CFG_SOUND, "music_volume", m_volumes.getMusicVolume());
	m_config->setKey(BMONKEY_CFG_SOUND, "movie_volume", m_volumes.getMovieVolume());
}

} // namespace bmonkey
