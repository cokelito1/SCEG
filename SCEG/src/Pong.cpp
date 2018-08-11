#include "Pong.h"

#include <random>

#include "SCEG.h"
#include "Player.h"
#include "ResourceManager.h"

#include <SFML/Audio.hpp>

#include <string.h>

Pong::Pong() : SCEG::Engine() { }
Pong::~Pong() { }

void Pong::run() {
	int PlayerOneScore = 0;
	int PlayerTwoScore = 0;

	sf::Font font = fontMngr->GetResource("font.ttf");

	sf::Text P1ScoreText;
	sf::Text P2ScoreText;

	sf::Sound pongSound;
	pongSound.setBuffer(soundMngr->GetResource("pong.wav"));

	sf::Music oofSong;
	oofSong.openFromFile("media/sounds/oofSong.wav");

	P1ScoreText.setFont(font);
	P2ScoreText.setFont(font);

	P1ScoreText.setPosition(100, 0);
	P2ScoreText.setPosition(window->getSize().x - 100, 0);

	P1ScoreText.setCharacterSize(32);
	P2ScoreText.setCharacterSize(32);

	P1ScoreText.setString(std::to_string(PlayerOneScore));
	P2ScoreText.setString(std::to_string(PlayerTwoScore));

	SCEG::Player *p1 = new SCEG::Player(this);
	p1->SetImage(imgMngr->GetResource("rectangle.png"));
	p1->SetPosition(sf::Vector2f(0.0f, 0.0f));
	p1->SetVelocity(440.0f);
	p1->SetName("Player");
	p1->RegisterSprite();

	SCEG::Player *p2 = new SCEG::Player(this);
	p2->SetImage(imgMngr->GetResource("rectangle.png"));
	p2->SetPosition(sf::Vector2f(window->getSize().x - p2->GetSprite().getTexture()->getSize().x, 0.0f));
	p2->SetName("p2");
	p2->SetVelocity(440.0f);
	p2->SetMoving(true);
	p2->RegisterSprite();

	SCEG::Player *ball = new SCEG::Player(this);
	ball->SetImage(imgMngr->GetResource("ball.png"));
	ball->GetSprite().scale(0.25f, 0.25f);
	ball->SetName("ball");
	ball->SetVelocity(200.0f);
	ball->SetMoving(true);
	ball->RegisterSprite();

	SCEG::Entity::MovementTo ballTo = SCEG::Entity::MovementTo::MOV_OESTE;

	std::random_device rd;
	std::default_random_engine gen(rd());

	std::uniform_int_distribution<int> dist(1, 3);
	std::uniform_int_distribution<int> distF(15, 30);

	entitys["Player"]->SetPosition(sf::Vector2f(0, (window->getSize().y / 2) - (entitys["Player"]->GetSprite().getTexture()->getSize().y / 2)));
	entitys["p2"]->SetPosition(sf::Vector2f(window->getSize().x - entitys["p2"]->GetSprite().getTexture()->getSize().x, (window->getSize().y / 2) - (entitys["p2"]->GetSprite().getTexture()->getSize().y / 2)));
	entitys["ball"]->SetPosition(sf::Vector2f((window->getSize().x / 2) - ((ball->GetSprite().getTexture()->getSize().x / 2) * ball->GetSprite().getScale().x), (window->getSize().y / 2) - ((ball->GetSprite().getTexture()->getSize().y / 2) * ball->GetSprite().getScale().y)));

	SCEG::Entity::MovementTo PjMoveTo = SCEG::Entity::MovementTo::MOV_SUR;
	SCEG::Entity::MovementTo Pj2MoveTo = SCEG::Entity::MovementTo::MOV_SUR;

	delta.restart();
	while (window->isOpen()) {
		deltaTime = delta.restart();
		sf::Event evt;
		sf::Text t;
		t.setFont(font);
		t.setCharacterSize(100);
		t.setString("K for bot\nL for 2 players");
		if (state == GameState::GAME_SELECT) {
			while (window->pollEvent(evt)) {
				switch (evt.type) {
				case sf::Event::KeyPressed:
					if (evt.key.code == sf::Keyboard::K) {
						bot = true;
						(*logger) << SCEG::Logger::LogType::LOG_DEBUG << "Seleccionado modo bot\n";
						entitys["p2"]->SetMoving(true);
						entitys["Player"]->SetMoving(false);
						state = GameState::GAME_PLAYING;
					}
					if (evt.key.code == sf::Keyboard::L) {
						bot = false;
						(*logger) << SCEG::Logger::LogType::LOG_DEBUG << "Seleccionado modo 2 players\n";
						entitys["p2"]->SetMoving(false);
						entitys["Player"]->SetMoving(false);
						state = GameState::GAME_PLAYING;
					}
					break;
				case sf::Event::Closed:
					window->close();
					break;
				}
			}
			window->clear(sf::Color::Black);
			window->draw(t);
			window->display();
		}
		if (state == GameState::GAME_PLAYING) {
			while (window->pollEvent(evt)) {
				switch (evt.type) {
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::KeyPressed:
					if (evt.key.code == sf::Keyboard::W) {
						entitys["Player"]->SetMoving(true);
						PjMoveTo = SCEG::Entity::MovementTo::MOV_NORTE;
					}
					if (evt.key.code == sf::Keyboard::S) {
						entitys["Player"]->SetMoving(true);
						PjMoveTo = SCEG::Entity::MovementTo::MOV_SUR;
					}
					if (!bot) {
						if (evt.key.code == sf::Keyboard::Up) {
							entitys["p2"]->SetMoving(true);
							Pj2MoveTo = SCEG::Entity::MovementTo::MOV_NORTE;
						}

						if (evt.key.code == sf::Keyboard::Down) {
							entitys["p2"]->SetMoving(true);
							Pj2MoveTo = SCEG::Entity::MovementTo::MOV_SUR;
						}
					}
					break;
				case sf::Event::KeyReleased:
					if (evt.key.code == sf::Keyboard::W || evt.key.code == sf::Keyboard::S) {
						entitys["Player"]->SetMoving(false);
					}
					if (!bot) {
						if (evt.key.code == sf::Keyboard::Up || evt.key.code == sf::Keyboard::Down) {
							entitys["p2"]->SetMoving(false);
						}
					}
				default:
					break;
				}
			}

			entitys["Player"]->Move(PjMoveTo);
			if (!bot) {
				entitys["p2"]->Move(Pj2MoveTo);
			}

			entitys["ball"]->Move(ballTo);
			if (entitys["Player"]->intersects(entitys["ball"])) {
				int sel = dist(gen);
				switch (sel) {
				case 1:
					ballTo = SCEG::Entity::MovementTo::MOV_SURESTE;
					break;
				case 2:
					ballTo = SCEG::Entity::MovementTo::MOV_ESTE;
					break;
				case 3:
					ballTo = SCEG::Entity::MovementTo::MOV_NORESTE;
					break;
				}
				pongSound.play();
				entitys["ball"]->SetVelocity(entitys["ball"]->GetVelocity() + 20.0f);
			}
			else if (entitys["p2"]->intersects(entitys["ball"])) {
				int sel = dist(gen);
				switch (sel) {
				case 1:
					ballTo = SCEG::Entity::MovementTo::MOV_SUROESTE;
					break;
				case 2:
					ballTo = SCEG::Entity::MovementTo::MOV_OESTE;
					break;
				case 3:
					ballTo = SCEG::Entity::MovementTo::MOV_NOROESTE;
					break;
				}
				pongSound.play();
				entitys["ball"]->SetVelocity(entitys["ball"]->GetVelocity() + 20.0f + distF(gen));
			}

			if ((entitys["ball"]->GetPosition().y + entitys["ball"]->GetSprite().getTexture()->getSize().y * entitys["ball"]->GetSprite().getScale().y) + 1.0f > window->getSize().y || entitys["ball"]->GetPosition().y - 1.0f < 0.0f) {
				switch (ballTo)
				{
				case SCEG::Entity::MovementTo::MOV_NORESTE:
					ballTo = SCEG::Entity::MovementTo::MOV_SURESTE;
					break;
				case SCEG::Entity::MovementTo::MOV_NOROESTE:
					ballTo = SCEG::Entity::MovementTo::MOV_SUROESTE;
					break;
				case SCEG::Entity::MovementTo::MOV_SURESTE:
					ballTo = SCEG::Entity::MovementTo::MOV_NORESTE;
					break;
				case SCEG::Entity::MovementTo::MOV_SUROESTE:
					ballTo = SCEG::Entity::MovementTo::MOV_NOROESTE;
					break;
				default:
					break;
				}
				pongSound.play();
			}

			if ((entitys["ball"]->GetPosition().x - entitys["ball"]->GetSprite().getTexture()->getSize().x) + 1.0f > window->getSize().x) {
				*logger << SCEG::Logger::LogType::LOG_DEBUG << "Score p1\n";
				PlayerOneScore++;
				entitys["ball"]->SetPosition(sf::Vector2f((window->getSize().x / 2) - ((ball->GetSprite().getTexture()->getSize().x / 2) * ball->GetSprite().getScale().x), (window->getSize().y / 2) - ((ball->GetSprite().getTexture()->getSize().y / 2) * ball->GetSprite().getScale().y)));
				entitys["Player"]->SetPosition(sf::Vector2f(0, (window->getSize().y / 2) - (entitys["Player"]->GetSprite().getTexture()->getSize().y / 2)));
				entitys["p2"]->SetPosition(sf::Vector2f(window->getSize().x - entitys["p2"]->GetSprite().getTexture()->getSize().x, (window->getSize().y / 2) - (entitys["p2"]->GetSprite().getTexture()->getSize().y / 2)));
				entitys["Player"]->SetVelocity(440.0f);
				entitys["p2"]->SetVelocity(440.0f);
				entitys["ball"]->SetVelocity(200.0f);
				std::random_device rd;
				gen.seed(rd());
				P1ScoreText.setString(std::to_string(PlayerOneScore));
				P2ScoreText.setString(std::to_string(PlayerTwoScore));
			}
			else if ((entitys["ball"]->GetPosition().x + entitys["ball"]->GetSprite().getTexture()->getSize().x) - 1.0f < 0.0f) {
				*logger << SCEG::Logger::LogType::LOG_DEBUG << "Score p2\n";
				PlayerTwoScore++;
				entitys["ball"]->SetPosition(sf::Vector2f((window->getSize().x / 2) - ((ball->GetSprite().getTexture()->getSize().x / 2) * ball->GetSprite().getScale().x), (window->getSize().y / 2) - ((ball->GetSprite().getTexture()->getSize().y / 2) * ball->GetSprite().getScale().y)));
				entitys["Player"]->SetPosition(sf::Vector2f(0, (window->getSize().y / 2) - (entitys["Player"]->GetSprite().getTexture()->getSize().y / 2)));
				entitys["p2"]->SetPosition(sf::Vector2f(window->getSize().x - entitys["p2"]->GetSprite().getTexture()->getSize().x, (window->getSize().y / 2) - (entitys["p2"]->GetSprite().getTexture()->getSize().y / 2)));
				entitys["Player"]->SetVelocity(440.0f);
				entitys["p2"]->SetVelocity(440.0f);
				entitys["ball"]->SetVelocity(200.0f);
				std::random_device rd;
				gen.seed(rd());
				P1ScoreText.setString(std::to_string(PlayerOneScore));
				P2ScoreText.setString(std::to_string(PlayerTwoScore));
			}

			if (bot) {
				if (entitys["p2"]->GetPosition().y + (entitys["p2"]->GetSprite().getTexture()->getSize().y / 2) < entitys["ball"]->GetPosition().y) {
					entitys["p2"]->Move(SCEG::Entity::MovementTo::MOV_SUR);
				}
				else if (entitys["p2"]->GetPosition().y - (entitys["p2"]->GetSprite().getTexture()->getSize().y / 2) > entitys["ball"]->GetPosition().y - entitys["ball"]->GetSprite().getTexture()->getSize().y * (1.0f - entitys["ball"]->GetSprite().getScale().y)) {
					entitys["p2"]->Move(SCEG::Entity::MovementTo::MOV_NORTE);
				}
			}
			if (PlayerOneScore < 10 && PlayerTwoScore < 10) {
				window->clear(sf::Color::Black);
				window->draw(P1ScoreText);
				window->draw(P2ScoreText);
				for (auto it : entitys) {
					it.second->draw(window);
				}
				window->display();
			}
			else {
				state = GameState::GAME_LOSE_SCREEN;
			}
		}
		else if (state == GameState::GAME_LOSE_SCREEN) {
			while (window->pollEvent(evt)) {
				switch (evt.type) {
				case sf::Event::Closed:
					window->close();
					break;
				case sf::Event::KeyPressed:
					if (evt.key.code == sf::Keyboard::Space) {
						if (oofSong.getStatus() == sf::Music::Status::Playing) {
							oofSong.stop();
						}
						entitys["ball"]->SetPosition(sf::Vector2f((window->getSize().x / 2) - (ball->GetSprite().getTexture()->getSize().x / 4), (window->getSize().y / 2) - (ball->GetSprite().getTexture()->getSize().y / 4)));
						entitys["Player"]->SetPosition(sf::Vector2f(0, (window->getSize().y / 2) - (entitys["Player"]->GetSprite().getTexture()->getSize().y / 2)));
						entitys["p2"]->SetPosition(sf::Vector2f(window->getSize().x - entitys["p2"]->GetSprite().getTexture()->getSize().x, (window->getSize().y / 2) - (entitys["p2"]->GetSprite().getTexture()->getSize().y / 2)));
						entitys["Player"]->SetVelocity(440.0f);
						entitys["p2"]->SetVelocity(440.0f);
						entitys["ball"]->SetVelocity(200.0f);
						std::random_device rd;
						gen.seed(rd());
						PlayerOneScore = 0;
						PlayerTwoScore = 0;
						P1ScoreText.setString(std::to_string(PlayerOneScore));
						P2ScoreText.setString(std::to_string(PlayerTwoScore));
						state = GameState::GAME_SELECT;
					}
				}
			}
			window->clear(sf::Color::Red);
			if (oofSong.getStatus() != sf::Music::Status::Playing && state == GameState::GAME_LOSE_SCREEN) {
				oofSong.play();
				(*logger) << SCEG::Logger::LogType::LOG_DEBUG << "Playing song oofSong\n";
			}
			window->display();
		}
	}
}