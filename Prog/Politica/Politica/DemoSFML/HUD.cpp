#include"HUD.h"

HUD hud;

bool taxIsAppears = 0;
bool taxIsDisappears = 0;
float timerTax = 0;

void InitButtons()
{
	hud.endTurnButton = CreateButton("Assets/Images/Hud/EndTurnButton.png", PosToScreenY(150), true, ScaleToScreen(1.f, 1.f), PosToScreenX(1750));
	CreateAnimationLeftToRight(hud.endTurnButton.animation[0], 3, 1, hud.endTurnButton.texture->getSize());

	hud.openRulesTexture.loadFromFile("Assets/Images/Hud/RulesButton.png");
	hud.openRulesButton = CreateButton("Assets/Images/Hud/RulesButton.png", PosToScreenY(121.5f), true, ScaleToScreen(1.f, 1.f), PosToScreenX(39.5f));
	CreateAnimationLeftToRight(hud.openRulesButton.animation[0], 3, 1, hud.openRulesTexture.getSize());

	hud.closeRulesTexture.loadFromFile("Assets/Images/Hud/Cross.png");
	hud.closeRulesButton = CreateButton("Assets/Images/Hud/Cross.png", PosToScreenY(39.5f), true, ScaleToScreen(1.f, 1.f), PosToScreenX(1880.5f));
	CreateAnimationLeftToRight(hud.closeRulesButton.animation[0], 3, 1, hud.closeRulesTexture.getSize());

	hud.leftArrowTexture.loadFromFile("Assets/Images/Hud/LeftArrow.png");
	hud.leftArrowButton = CreateButton("Assets/Images/Hud/LeftArrow.png", PosToScreenY(1040.f), true, ScaleToScreen(1.f, 1.f), PosToScreenX(860.f));
	CreateAnimationLeftToRight(hud.leftArrowButton.animation[0], 3, 1, hud.leftArrowTexture.getSize());

	hud.rightArrowTexture.loadFromFile("Assets/Images/Hud/RightArrow.png");
	hud.rightArrowButton = CreateButton("Assets/Images/Hud/RightArrow.png", PosToScreenY(1040.f), true, ScaleToScreen(1.f, 1.f), PosToScreenX(1060.f));
	CreateAnimationLeftToRight(hud.rightArrowButton.animation[0], 3, 1, hud.rightArrowTexture.getSize());

	hud.buttonYes = CreateButton("Assets/Images/Cards/CardButtonAccept.png", PosToScreenY(738.2f), true, ScaleToScreen(1.f, 1.f), PosToScreenX(1104));
	CreateAnimationLeftToRight(hud.buttonYes.animation[0], 3, 1, hud.buttonYes.texture->getSize());

	hud.buttonNo = CreateButton("Assets/Images/Cards/CardButtonRefuse.png", PosToScreenY(738.2f), true, ScaleToScreen(1.f, 1.f), PosToScreenX(816));
	CreateAnimationLeftToRight(hud.buttonNo.animation[0], 3, 1, hud.buttonNo.texture->getSize());

	hud.dicesButton = CreateButton("Assets/Images/Hud/DiceButton.png", PosToScreenY(150), true, ScaleToScreen(1.f, 1.f), PosToScreenX(1500));
	CreateAnimationLeftToRight(hud.dicesButton.animation[0], 3, 1, hud.dicesButton.texture->getSize());

	hud.putschButton = CreateButton("Assets/Images/Hud/PutschButton.png", PosToScreenY(250.f), true, ScaleToScreen(1.f, 1.f), PosToScreenX(57.f));
	CreateAnimationLeftToRight(hud.putschButton.animation[0], 3, 1, hud.putschButton.texture->getSize());
}

void InitTexts()
{
	hud.rulesSheet = 1;
	hud.rulesFont.loadFromFile("Assets/Fonts/RulesFont.otf");
	hud.nbSheetRulesText.setFont(hud.rulesFont);
	hud.nbSheetRulesText.setPosition(PosToScreen(sf::Vector2f(935, 1030)));
	for (int i = 0; i < NB_LINES_RULES; i++)
	{
		hud.rulesText[i].setFont(hud.rulesFont);
		hud.rulesText[i].setScale(ScaleToScreen(1.f, 1.f));
	}
	for (int i = 0; i < 16; i++)
	{
		hud.rulesText[i].setPosition(PosToScreen(sf::Vector2f(0.f, (float)i * (float)INTERLINE_SPACE)));
	}
	for (int i = 16; i < NB_LINES_RULES; i++)
	{
		hud.rulesText[i].setPosition(PosToScreen(sf::Vector2f(0.f, (float)i * (float)INTERLINE_SPACE)));
	}

	hud.rulesText[0].setString("RÈGLES");
	hud.rulesText[0].setPosition(PosToScreen(sf::Vector2f(920, 0)));

	hud.rulesText[1].setString(". Cases:");
	hud.rulesText[2].setString("	- Malus           : Subir le malus annoncé.");

	hud.rulesText[3].setPosition(PosToScreen(sf::Vector2f(0, 3 * INTERLINE_SPACE + 10)));
	hud.rulesText[3].setString("	- Bonus           : Subir le bonus annoncé.");

	hud.rulesText[4].setPosition(PosToScreen(sf::Vector2f(0, 4 * INTERLINE_SPACE + 20)));
	hud.rulesText[4].setString("	- Chance           : Tirer une carte chance et subir l'effet annoncé.");

	hud.rulesText[5].setPosition(PosToScreen(sf::Vector2f(0, 5 * INTERLINE_SPACE + 30)));
	hud.rulesText[5].setString("	- Action           : Tirer une carte action, possibilité de conserver la carte si carte d'interaction avec d'autres joueurs sinon");

	hud.rulesText[6].setPosition(PosToScreen(sf::Vector2f(0, 6 * INTERLINE_SPACE + 15)));
	hud.rulesText[6].setString("	 le joueur fait le choix d'effectuer l'action ou non.");

	hud.rulesText[7].setPosition(PosToScreen(sf::Vector2f(0, 7 * INTERLINE_SPACE + 15)));
	hud.rulesText[7].setString("	- Impôt           : Payer 20 000 argent ou obtenir un impôt impayé.");

	hud.rulesText[8].setPosition(PosToScreen(sf::Vector2f(0, 8 * INTERLINE_SPACE + 25)));
	hud.rulesText[8].setString("	- Pause           : Rien ne se passe, c'est la pause.");

	hud.rulesText[9].setPosition(PosToScreen(sf::Vector2f(0, 9 * INTERLINE_SPACE + 25)));
	hud.rulesText[9].setString("	- Conseil Parlementaire           : Débat entre tout les joueurs. Chaque joueur lance un dé, le score le plus haut");

	hud.rulesText[10].setPosition(PosToScreen(sf::Vector2f(0, 10 * INTERLINE_SPACE + 10)));
	hud.rulesText[10].setString("	 remporte 200 électeurs, le deuxième gagne 100 électeurs, le troisième perd 100 électeurs et le quatrième en perd 200.");

	hud.rulesText[11].setPosition(PosToScreen(sf::Vector2f(0, 11 * INTERLINE_SPACE - 15)));
	hud.rulesText[11].setString("	 Si la réputation d'un joueur est positive, il ajoute 1 à son lancer de dés et si la réputation d'un joueur est négative,");

	hud.rulesText[12].setPosition(PosToScreen(sf::Vector2f(0, 12 * INTERLINE_SPACE - 40)));
	hud.rulesText[12].setString("	 il retire 1 à son lancer de dés. En cas d'égalité entre deux joueurs, c'est le joueur avec le plus de réputation");

	hud.rulesText[13].setPosition(PosToScreen(sf::Vector2f(0, 13 * INTERLINE_SPACE - 65)));
	hud.rulesText[13].setString("	 qui l'emporte sinon c'est aléatoire.");

	hud.rulesText[14].setPosition(PosToScreen(sf::Vector2f(0, 14 * INTERLINE_SPACE - 70)));
	hud.rulesText[14].setString("	- Mise en examen           : Si réputation négative, le joueur perd des électeurs équivalents à sa répution x 100. Si réputation");

	hud.rulesText[15].setPosition(PosToScreen(sf::Vector2f(0, 15 * INTERLINE_SPACE - 85)));
	hud.rulesText[15].setString("	 positive, le joueur gagne des électeurs équivalents à sa réputation x 50.");



	hud.rulesText[16].setPosition(PosToScreen(sf::Vector2f(0, INTERLINE_SPACE)));
	hud.rulesText[16].setString("	- Contrôle fiscal           : Le joueur perd 30 000 argent, 2 réputation et 200 électeurs par impôt impayé.");

	hud.rulesText[17].setPosition(PosToScreen(sf::Vector2f(0, 2 * INTERLINE_SPACE)));
	hud.rulesText[17].setString("	- Salaire           : Le joueur gagne 20 000 argent s'il s'arrête sur une case salaire, il gagne seulement 10 000 s'il passe dessus");

	hud.rulesText[18].setPosition(PosToScreen(sf::Vector2f(0, 3 * INTERLINE_SPACE - 15)));
	hud.rulesText[18].setString("	 sans s'arrêter. La case départ est une case salaire.");

	hud.rulesText[19].setPosition(PosToScreen(sf::Vector2f(0, 4 * INTERLINE_SPACE - 15)));
	hud.rulesText[19].setString("	- Mystère           : Lancer un dé 6 :");

	hud.rulesText[20].setPosition(PosToScreen(sf::Vector2f(0, 5 * INTERLINE_SPACE - 30)));
	hud.rulesText[20].setString("		-> Si 1 : Impôt");

	hud.rulesText[21].setPosition(PosToScreen(sf::Vector2f(0, 6 * INTERLINE_SPACE - 55)));
	hud.rulesText[21].setString("		-> Si 2 ou 3 : Chance");

	hud.rulesText[22].setPosition(PosToScreen(sf::Vector2f(0, 7 * INTERLINE_SPACE - 80)));
	hud.rulesText[22].setString("		-> Si 4 ou 5 : Action");

	hud.rulesText[23].setPosition(PosToScreen(sf::Vector2f(0, 8 * INTERLINE_SPACE - 105)));
	hud.rulesText[23].setString("		-> Si 6 : Conseil parlementaire");

	hud.rulesText[24].setPosition(PosToScreen(sf::Vector2f(0, 9 * INTERLINE_SPACE - 105)));
	hud.rulesText[24].setString("	- Réputation x argent / électeurs           : Bonus (ou malus) de statistiques en fonction de la réputation.");

	hud.rulesText[25].setPosition(PosToScreen(sf::Vector2f(0, 10 * INTERLINE_SPACE - 95)));
	hud.rulesText[25].setString(". Si un joueur a une valeur d'argent négative, il perd 50 électeurs à chaque tour jusqu'à ce qu'il revienne dans le positif.");

	hud.rulesText[26].setPosition(PosToScreen(sf::Vector2f(0, 11 * INTERLINE_SPACE - 95)));
	hud.rulesText[26].setString(". La partie se termine une fois que les joueurs ont lancé 20 fois les dés (20 tours). A la fin de la partie, un dernier conseil");

	hud.rulesText[27].setPosition(PosToScreen(sf::Vector2f(0, 12 * INTERLINE_SPACE - 120)));
	hud.rulesText[27].setString("  parlementaire s'organise entre les joueurs. Le vainqueur est le joueur avec le plus d'électeurs, en cas");

	hud.rulesText[28].setPosition(PosToScreen(sf::Vector2f(0, 13 * INTERLINE_SPACE - 145)));
	hud.rulesText[28].setString("  d'égalité entre plusieurs joueurs c'est le joueur qui a le plus de réputation qui l'emporte.");

	hud.rulesText[29].setPosition(PosToScreen(sf::Vector2f(0, 14 * INTERLINE_SPACE - 145)));
	hud.rulesText[29].setString(". Fin alternative                : Si un joueur a -10 de réputation et plus de 125 000 argent, il peut effectuer un coup d'état.");

	hud.rulesText[30].setPosition(PosToScreen(sf::Vector2f(0, 15 * INTERLINE_SPACE - 160)));
	hud.rulesText[30].setString("  Coup d'état : lancer un dé 6 et ajouter 1 au résultat par tranche de 500 électeurs. Si le résultat est supérieur ou égal à 5,");

	hud.rulesText[31].setPosition(PosToScreen(sf::Vector2f(0, 16 * INTERLINE_SPACE - 185)));
	hud.rulesText[31].setString("  le coup d'état réussi et le joueur remporte la partie sinon il perd tout ses électeurs et 125 000 argent.");



	hud.rulesText[32].setPosition(PosToScreen(sf::Vector2f(0, INTERLINE_SPACE)));
	hud.rulesText[32].setString(". Raccourci : Il y a deux raccourcis sur la carte. Les bonus et malus sont doublés dans les raccourcis.");

	hud.rulesText[33].setPosition(PosToScreen(sf::Vector2f(0, 2 * INTERLINE_SPACE)));
	hud.rulesText[33].setString(". Double : Si un joueur effectue un double, il peut relancer les dés pendant son tour. Il n'y a pas de limites de double que peut");

	hud.rulesText[34].setPosition(PosToScreen(sf::Vector2f(0, 3 * INTERLINE_SPACE - 25)));
	hud.rulesText[34].setString("  effectuer un joueur dans le même tour.");

	hud.rulesText[35].setPosition(PosToScreen(sf::Vector2f(0, 4 * INTERLINE_SPACE - 25)));
	hud.rulesText[35].setString(". Carte d'interaction : Pour utiliser une carte d'interaction, le joueur doit dérouler sa fiche joueur pendant son tour et faire");

	hud.rulesText[36].setPosition(PosToScreen(sf::Vector2f(0, 5 * INTERLINE_SPACE - 50)));
	hud.rulesText[36].setString("  glisser la carte sur le joueur ciblé.");



	hud.notEnoughtMoneys.setFont(GetSettingsFont());
	hud.notEnoughtMoneys.setPosition(PosToScreen(sf::Vector2f(580, 310)));
	hud.notEnoughtMoneys.setFillColor(sf::Color::White);
	hud.notEnoughtMoneys.setString("Vous ne pouvez pas payer, vous avez pas asssez d'argent");

	CreateText(hud.putschText, GetSettingsFont(), "Lancez un dé pour déterminer l'issue du coup d'état", 45, sf::Color::White);
	hud.putschText.setPosition(GetScreen().width / 2.f, GetScreen().height / 4.f - PosToScreenY(10));
}

void InitTimeline()
{
	hud.timelineSprite = LoadSprite("Assets/Images/Hud/Timeline.png", false);
	hud.whiteSquareSprite = LoadSprite("Assets/Images/Hud/WhiteSquare.png", false);
}

void InitIcons()
{
	hud.malusIcon = LoadSprite("Assets/Images/Hud/MalusIcon.png", true);

	hud.bonusIcon = LoadSprite("Assets/Images/Hud/BonusIcon.png", true);

	hud.chanceIcon = LoadSprite("Assets/Images/Hud/ChanceIcon.png", true);

	hud.actionIcon = LoadSprite("Assets/Images/Hud/ActionIcon.png", true);

	hud.taxIcon = LoadSprite("Assets/Images/Hud/TaxIcon.png", true);

	hud.breakIcon = LoadSprite("Assets/Images/Hud/breakIcon.png", true);

	hud.parliamentIcon = LoadSprite("Assets/Images/Hud/ParliamentIcon.png", true);

	hud.examenIcon = LoadSprite("Assets/Images/Hud/ExamenIcon.png", true);

	hud.controlIcon = LoadSprite("Assets/Images/Hud/ControlIcon.png", true);

	hud.salaryIcon = LoadSprite("Assets/Images/Hud/SalaryIcon.png", true);

	hud.mysteryIcon = LoadSprite("Assets/Images/Hud/MysteryIcon.png", true);

	hud.reputationIcon = LoadSprite("Assets/Images/Hud/ReputationIcon.png", true);

	hud.putschIcon = LoadSprite("Assets/Images/Hud/PutschIcon.png", true);

	hud.votersIcon = LoadSprite("Assets/Images/Hud/IconVoters.png", true);
	hud.votersIcon.setScale(0.5f, 0.5f);
}

void InitParliamentaryResults()
{
	hud.cardTexture.loadFromFile("Assets/Images/Hud/ParliamentaryResult.png");
	hud.cardSprite = CreateSprite(hud.cardTexture, sf::Vector2f(GetScreen().width / 2.f, GetScreen().height / 2.f), true, ScaleToScreen(1.f, 1.f));//ScaleToScreen(1.6f, 1.f));

	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		CreateText(hud.playerPseudo[i], GetSettingsFont(), "chien", 25, sf::Color::White);
		CreateText(hud.playerReward[i], GetSettingsFont(), "chien", 30, sf::Color::White);
	}
	hud.playerReward[0].setString("+ 200");
	hud.playerReward[1].setString("+ 100");
	hud.playerReward[2].setString("- 100");
	hud.playerReward[3].setString("- 200");
}

void InitHUD()
{
	InitButtons();
	InitTexts();
	InitTimeline();
	InitIcons();
	InitParliamentaryResults();
	hud.areRulesDisplaying = false;
	hud.timer = 0.f;
	hud.rulesSprite = LoadSprite("Assets/Images/Hud/Rules2.png", true);
	hud.rulesSprite.setScale(GetScreen().width / hud.rulesSprite.getTexture()->getSize().x, GetScreen().height / hud.rulesSprite.getTexture()->getSize().y);
	hud.taxeLetter = LoadSprite("Assets/Images/Cards/ChanceTaxes.png", true);
	hud.putschTextBackground = LoadSprite("Assets/Images/Hud/PutschTextBackground.png", true);

	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		hud.putsch[i].hasSucceeded = CHIEN;
		hud.putsch[i].isAvailable = false;
		hud.putsch[i].isPutsching = false;
		hud.putsch[i].value = 0;
	}

	hud.turnPageSound = AddSound("Assets/Sounds/TurningPage.ogg");
}

void ReloadHud(void)
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		hud.putsch[i].hasSucceeded = CHIEN;
		hud.putsch[i].isAvailable = false;
		hud.putsch[i].isPutsching = false;
		hud.putsch[i].value = 0;
	}

	hud.rulesSheet = 1;
	hud.areRulesDisplaying = false;
	hud.timer = 0.f;
}


void CheckMouseButtonCollisionHUD()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (!hud.areRulesDisplaying)
	{
		if (RectContains(hud.openRulesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !hud.openRulesButton.isSelected)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}

		if (RectContains(hud.openRulesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
		{
			hud.openRulesButton.isSelected = true;
		}
		else
		{
			hud.openRulesButton.isSelected = false;
		}
	}


	if (!GetPlayerIsAnAI(GetActivePlayer()) || (GetPlayerIsAnAI(GetActivePlayer()) && (GetIsBlackMailPlaying() || GetIsDenunciationPlaying())))
	{
		if (!hud.areRulesDisplaying)
		{
			if (RectContains(hud.endTurnButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && GetDiceHasRolling() && !GetPlayerIsMoving(GetActivePlayer()) && !GetDiceisAvailable() && !GetIsAnyCardDisplaying() && !hud.endTurnButton.isSelected && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && !GetIsInParliamentaryCouncil() && !GetIsDebateIsPlaying() && !GetInsertIsDisplay())
			{
				PlaySoundFromList(GetButtonSelectSound(), 5);
			}

			if (RectContains(hud.endTurnButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && GetDiceHasRolling() && !GetPlayerIsMoving(GetActivePlayer()) && !GetDiceisAvailable() && !GetIsAnyCardDisplaying() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && !GetIsInParliamentaryCouncil() && !GetIsDebateIsPlaying() && !GetInsertIsDisplay())
			{
				hud.endTurnButton.isSelected = true;
			}
			else
			{
				hud.endTurnButton.isSelected = false;
			}



			if (RectContains(hud.dicesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !GetDiceHasRolling() && !hud.dicesButton.isSelected && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()) && !GetIsInParliamentaryCouncil() && !GetPlayerIsOnMysterytile(GetActivePlayer()))
			{
				PlaySoundFromList(GetButtonSelectSound(), 5);
			}

			if (RectContains(hud.dicesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !GetDiceHasRolling() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
			{
				hud.dicesButton.isSelected = true;
			}
			else
			{
				hud.dicesButton.isSelected = false;
			}

			for (unsigned char i = 0; i < NB_PLAYERS; i++)
			{
				if (RectContains(hud.putschButton.sprite.getGlobalBounds(), sf::Vector2f(mousePos)) && !hud.putsch[i].isPutsching && !hud.putschButton.isSelected)
				{
					PlaySoundFromList(GetButtonSelectSound(), 5);
				}
				if (RectContains(hud.putschButton.sprite.getGlobalBounds(), sf::Vector2f(mousePos)) && !hud.putsch[i].isPutsching)
				{
					hud.putschButton.isSelected = true;
				}
				else
				{
					hud.putschButton.isSelected = false;
				}
			}
		}
	}

}

void UpdateRules(float& _dt)
{
	UpdateAnimationButton(hud.closeRulesButton.animation[0], hud.closeRulesButton.sprite, hud.closeRulesButton.isSelected, hud.closeRulesButton.isPressed, _dt);
	UpdateAnimationButton(hud.leftArrowButton.animation[0], hud.leftArrowButton.sprite, hud.leftArrowButton.isSelected, hud.leftArrowButton.isPressed, _dt);
	UpdateAnimationButton(hud.rightArrowButton.animation[0], hud.rightArrowButton.sprite, hud.rightArrowButton.isSelected, hud.rightArrowButton.isPressed, _dt);

	if (hud.areRulesDisplaying)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		if (RectContains(hud.closeRulesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !hud.closeRulesButton.isSelected)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}

		if (RectContains(hud.closeRulesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
		{
			hud.closeRulesButton.isSelected = true;
		}
		else
		{
			hud.closeRulesButton.isSelected = false;
		}

		if (RectContains(hud.leftArrowButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !hud.leftArrowButton.isSelected && hud.rulesSheet == 2)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}
		if (RectContains(hud.leftArrowButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
		{
			hud.leftArrowButton.isSelected = true;
		}
		else
		{
			hud.leftArrowButton.isSelected = false;
		}

		if (RectContains(hud.rightArrowButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !hud.rightArrowButton.isSelected && hud.rulesSheet == 1)
		{
			PlaySoundFromList(GetButtonSelectSound(), 5);
		}

		if (RectContains(hud.rightArrowButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
		{
			hud.rightArrowButton.isSelected = true;
		}
		else
		{
			hud.rightArrowButton.isSelected = false;
		}
	}
}

void UpdateButtonsHUD(float& _dt)
{
	UpdateAnimationButton(hud.endTurnButton.animation[0], hud.endTurnButton.sprite, hud.endTurnButton.isSelected, hud.endTurnButton.isPressed, _dt);
	UpdateAnimationButton(hud.openRulesButton.animation[0], hud.openRulesButton.sprite, hud.openRulesButton.isSelected, hud.openRulesButton.isPressed, _dt);
	UpdateAnimationButton(hud.dicesButton.animation[0], hud.dicesButton.sprite, hud.dicesButton.isSelected, hud.dicesButton.isPressed, _dt);
	UpdateAnimationButton(hud.putschButton.animation[0], hud.putschButton.sprite, hud.putschButton.isSelected, hud.putschButton.isPressed, _dt);

	UpdateAnimationButton(hud.buttonNo.animation[0], hud.buttonNo.sprite, hud.buttonNo.isSelected, hud.buttonNo.isPressed, _dt);
	UpdateAnimationButton(hud.buttonYes.animation[0], hud.buttonYes.sprite, hud.buttonYes.isSelected, hud.buttonYes.isPressed, _dt);

	if (hud.showNotEnoughtMoneys)
	{
		hud.timer += _dt;
		std::cout << hud.timer << std::endl;
		if (hud.timer > 1.5f)
		{
			hud.timer = 0;
			hud.showNotEnoughtMoneys = false;
		}
	}

	if (!GetDiceHasRolling() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		for (int i = 0; i < 12; i++)
		{
			AddParticleHud(hud.dicesButton.pos);
		}

	}
	UpdateParticleHudPlayer(_dt);
}

void UpdatePutsch()
{
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		if (GetPlayersReputation(i) <= -10 && GetPlayerMoney(i) >= 125000 && GetActivePlayer() == i && hud.putsch[i].hasSucceeded != FAIL)
		{
			hud.putsch[i].isAvailable = true;
		}
		else
		{
			hud.putsch[i].isAvailable = false;
		}

		if (hud.putsch[i].isPutsching)
		{
			SetLaunchedDices(1);

			if (!GetDiceisAvailable() && GetDiceHasRolling())
			{
				hud.putsch[i].value = GetFirstDiceValue() + (int)(GetPlayersVoters(i) / 500);
				std::cout << hud.putsch[i].value << std::endl;
				if (hud.putsch[i].value >= 5)
				{
					hud.putsch[i].hasSucceeded = SUCCESS;
					SetGameFadeOut(true);
				}
				else
				{
					hud.putsch[i].hasSucceeded = FAIL;
					AddPlayerMoney(i, -125000);
					AddPlayerVoters(i, -GetPlayersVoters(i));
				}
				hud.putsch[i].isPutsching = false;
			}
		}
	}
}

void UpdateParliamentaryResults(float& _dt)
{
	if (hud.isParliamentaryFinished)
	{
		hud.parliamentaryResultsTimer += _dt;
		if (hud.parliamentaryResultsTimer >= 4)
		{
			SetLaunchedDices(2);
			SetActivePlayer(GetLastPlayerPlayed());
			setDiceHasRolling(true);
			SetNoOneIsMoving(false);
			SetIsInParliamentaryCouncil(false);
			SetPlayerHasTookMysteryAction(GetActivePlayer(), true);
			if (GetNbTurns() == MAX_TURN)
			{
				SetGameFadeOut(true);
			}
			ClearDicesVector();
			hud.parliamentaryResultsTimer = 0;
			hud.isParliamentaryFinished = false;
		}
	}
}

void UpdateHUD(float& _dt)
{
	CheckMouseButtonCollisionHUD();
	UpdateButtonsHUD(_dt);
	UpdatePutsch();
	UpdateParliamentaryResults(_dt);
	if (GetDiceHasRolling() && !GetPlayerIsMoving(GetActivePlayer()) && !GetDiceisAvailable() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()) && !GetIsAnyCardDisplaying() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && !GetIsInParliamentaryCouncil() && !GetIsDebateIsPlaying() && !GetInsertIsDisplay())
	{
		for (int i = 0; i < 12; i++)
		{
			AddParticleHud(hud.endTurnButton.pos);
		}
	}
	if (GetActionStackCanBeSelected())
	{

		for (int i = 0; i < 18; i++)
		{
			AddParticleStack(GetActionStackPosition());
		}
	}
	if (GetChanceStackCanBeSelected())
	{
		for (int i = 0; i < 18; i++)
		{
			AddParticleStack(GetChanceStackPosition());
		}
	}
	UpdateTaxScale(_dt);
}

void UpdateTaxScale(float& _dt)
{
	if (GetPlayerIsOnTaxe(GetActivePlayer()))
	{
		if (taxIsAppears)
		{
			timerTax += 2 * _dt;
			if (timerTax < 1)
			{
				hud.taxeLetter.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
				hud.buttonNo.sprite.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
				hud.buttonYes.sprite.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
			}
			else
			{
				hud.taxeLetter.setScale(1.f, 1.f);
				hud.buttonNo.sprite.setScale(1.f, 1.f);
				hud.buttonYes.sprite.setScale(1.f, 1.f);
				taxIsAppears = false;
				timerTax = 1;
			}
		}
		else if (taxIsDisappears)
		{

			timerTax -= 2 * _dt;
			if (timerTax > 0)
			{

				hud.taxeLetter.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
				hud.buttonNo.sprite.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
				hud.buttonYes.sprite.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
			}
			else if (timerTax <= 0)
			{

				hud.taxeLetter.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
				hud.buttonNo.sprite.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
				hud.buttonYes.sprite.setScale(EaseInOutQuart(timerTax), EaseInOutQuart(timerTax));
				taxIsDisappears = false;
				timerTax = 0;
				if (hud.lastButton /*&& GetPlayerMoney(GetActivePlayer()) >= 20000*/)
				{
					SetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer(), true);
					AddPlayerMoney(GetActivePlayer(), -20000);
				}
				//else if (hud.lastButton && GetPlayerMoney(GetActivePlayer()) < 20000)
				//{
				//	hud.showNotEnoughtMoneys = true;
				//}
				else if (!hud.lastButton)
				{
					SetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer(), true);
					AddTaxes(GetActivePlayer(), 1);
				}
			}
		}
	}
}


void DisplayRulesTexts(sf::RenderWindow& _window)
{
	if (hud.areRulesDisplaying)
	{
		if (hud.rulesSheet == 1)
		{
			for (int i = 0; i < 16; i++)
			{
				_window.draw(hud.rulesText[i]);
			}
		}
		else if (hud.rulesSheet == 2)
		{
			for (int i = 16; i < 32; i++)
			{
				_window.draw(hud.rulesText[i]);
			}
		}
		else if (hud.rulesSheet == 3)
		{
			for (int i = 32; i < NB_LINES_RULES; i++)
			{
				_window.draw(hud.rulesText[i]);
			}
		}
		hud.nbSheetRulesText.setString("" + ToString(hud.rulesSheet) + " / 3");
		_window.draw(hud.nbSheetRulesText);
	}
}

void DisplayRulesButtons(sf::RenderWindow& _window)
{
	_window.draw(hud.closeRulesButton.sprite);
	if (hud.rulesSheet == 1 || hud.rulesSheet == 2)
	{
		_window.draw(hud.rightArrowButton.sprite);
	}
	if (hud.rulesSheet == 2 || hud.rulesSheet == 3)
	{
		_window.draw(hud.leftArrowButton.sprite);
	}
}

void DisplayIcons(sf::RenderWindow& _window)
{
	if (hud.areRulesDisplaying)
	{
		if (hud.rulesSheet == 1)
		{
			BlitSprite(hud.malusIcon, PosToScreen(sf::Vector2f(195, 160)), _window, 0);
			BlitSprite(hud.bonusIcon, PosToScreen(sf::Vector2f(195, 240)), _window, 0);
			BlitSprite(hud.chanceIcon, PosToScreen(sf::Vector2f(205, 320)), _window, 0);
			BlitSprite(hud.actionIcon, PosToScreen(sf::Vector2f(205, 400)), _window, 0);
			BlitSprite(hud.taxIcon, PosToScreen(sf::Vector2f(195, 525)), _window, 0);
			BlitSprite(hud.breakIcon, PosToScreen(sf::Vector2f(195, 605)), _window, 0);
			BlitSprite(hud.parliamentIcon, PosToScreen(sf::Vector2f(440, 675)), _window, 0);
			BlitSprite(hud.examenIcon, PosToScreen(sf::Vector2f(330, 930)), _window, 0);
		}
		else if (hud.rulesSheet == 2)
		{
			BlitSprite(hud.controlIcon, PosToScreen(sf::Vector2f(335, 90)), _window, 0);
			BlitSprite(hud.salaryIcon, PosToScreen(sf::Vector2f(215, 160)), _window, 0);
			BlitSprite(hud.mysteryIcon, PosToScreen(sf::Vector2f(225, 285)), _window, 0);
			BlitSprite(hud.reputationIcon, PosToScreen(sf::Vector2f(585, 545)), _window, 0);
			BlitSprite(hud.putschIcon, PosToScreen(sf::Vector2f(310, 845)), _window, 0);
		}
	}
}

void DisplayRules(sf::RenderWindow& _window)
{
	if (hud.areRulesDisplaying)
	{
		BlitSprite(hud.rulesSprite, PosToScreen(sf::Vector2f(960, 540)), _window, 0);
	}
	DisplayRulesTexts(_window);
	DisplayRulesButtons(_window);
	DisplayIcons(_window);
}

void DisplayEndTurn(sf::RenderWindow& _window)
{
	if (GetDiceHasRolling() && !GetPlayerIsMoving(GetActivePlayer()) && !GetDiceisAvailable() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()) && !GetIsAnyCardDisplaying() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && !GetIsInParliamentaryCouncil() && !GetInsertIsDisplay())
	{
		hud.endTurnButton.sprite.setColor(sf::Color(255, 255, 255));

	}
	else
	{
		hud.endTurnButton.sprite.setColor(sf::Color(150, 150, 150));
	}
	_window.draw(hud.endTurnButton.sprite);
}

void DisplayButtons(sf::RenderWindow& _window)
{
	_window.draw(hud.openRulesButton.sprite);
	_window.draw(hud.dicesButton.sprite);
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		if (hud.putsch[i].isAvailable)
		{
			_window.draw(hud.putschButton.sprite);
		}
	}

	if (!GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		BlitSprite(hud.taxeLetter, PosToScreen(sf::Vector2f(960, 540)), _window, 0);
		_window.draw(hud.buttonNo.sprite);
		_window.draw(hud.buttonYes.sprite);
	}
	if (hud.showNotEnoughtMoneys)
	{
		_window.draw(hud.notEnoughtMoneys);
	}
}

void DisplayTimeline(sf::RenderWindow& _window)
{
	if (!hud.areRulesDisplaying)
	{
		for (int i = 0; i < 10; i++)
		{
			if (i < GetNbTurns())
			{
				hud.whiteSquareSprite.setColor(sf::Color(80, 204, 101, 255));
			}
			else
			{
				hud.whiteSquareSprite.setColor(sf::Color(247, 109, 123, 255));
			}
			BlitSprite(hud.whiteSquareSprite, PosToScreen(sf::Vector2f((float)(25 + (20 * i)), 24.f)), _window, 90);
		}
		for (int i = 10; i < MAX_TURN; i++)
		{
			if (i < GetNbTurns())
			{
				hud.whiteSquareSprite.setColor(sf::Color(80, 204, 101, 255));
			}
			else
			{
				hud.whiteSquareSprite.setColor(sf::Color(247, 109, 123, 255));
			}
			BlitSprite(hud.whiteSquareSprite, PosToScreen(sf::Vector2f((float)(25 + (20 * (i - 10))), 58)), _window, 90);
		}
		BlitSprite(hud.timelineSprite, PosToScreen(sf::Vector2f(0, 0)), _window, 0);
	}
}

void DisplayPutsch(sf::RenderWindow& _window)
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		if (hud.putsch[i].isPutsching)
		{
			BlitSprite(hud.putschTextBackground, { GetScreen().width / 2, GetScreen().height / 4 }, _window, 0);
			_window.draw(hud.putschText);
		}
	}
}

void DisplayParliamentaryResults(sf::RenderWindow& _window)
{
	if (hud.isParliamentaryFinished)
	{
		sf::Vector2f initialOffset = { hud.cardSprite.getGlobalBounds().left, hud.cardSprite.getPosition().y - hud.playerIcon[GetParliamentaryPlayerOrder(3)].getGlobalBounds().height / 2.f +PosToScreenY(7)};

		_window.draw(hud.cardSprite);

		hud.playerIcon[GetParliamentaryPlayerOrder(3)].setPosition(initialOffset.x + hud.playerIcon[GetParliamentaryPlayerOrder(3)].getGlobalBounds().width, initialOffset.y);
		_window.draw(hud.playerIcon[GetParliamentaryPlayerOrder(3)]);


		hud.playerPseudo[GetParliamentaryPlayerOrder(3)].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(3)].getPosition().x + PosToScreenX(5), hud.playerIcon[GetParliamentaryPlayerOrder(3)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(3)].getGlobalBounds().height / 2 + PosToScreenY(20)));
		_window.draw(hud.playerPseudo[GetParliamentaryPlayerOrder(3)]);

		hud.playerReward[0].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(3)].getPosition().x - PosToScreenX(30), hud.playerIcon[GetParliamentaryPlayerOrder(3)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(3)].getGlobalBounds().height + PosToScreenY(20)));
		_window.draw(hud.playerReward[0]);

		BlitSprite(hud.votersIcon, sf::Vector2f(hud.playerReward[0].getPosition().x + hud.playerReward[0].getGlobalBounds().width / 2.f + PosToScreenX(30), hud.playerReward[0].getPosition().y + hud.votersIcon.getGlobalBounds().height / 4.f), _window);


		hud.playerIcon[GetParliamentaryPlayerOrder(2)].setPosition(initialOffset.x + hud.cardSprite.getGlobalBounds().width / 4 + hud.playerIcon[GetParliamentaryPlayerOrder(2)].getGlobalBounds().width, initialOffset.y);
		_window.draw(hud.playerIcon[GetParliamentaryPlayerOrder(2)]);

		hud.playerPseudo[GetParliamentaryPlayerOrder(2)].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(2)].getPosition().x, hud.playerIcon[GetParliamentaryPlayerOrder(2)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(2)].getGlobalBounds().height / 2 + PosToScreenY(20)));
		_window.draw(hud.playerPseudo[GetParliamentaryPlayerOrder(2)]);

		hud.playerReward[1].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(2)].getPosition().x - PosToScreenX(30), hud.playerIcon[GetParliamentaryPlayerOrder(2)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(2)].getGlobalBounds().height + PosToScreenY(20)));
		_window.draw(hud.playerReward[1]);

		BlitSprite(hud.votersIcon, sf::Vector2f(hud.playerReward[1].getPosition().x + hud.playerReward[1].getGlobalBounds().width / 2.f + PosToScreenX(30), hud.playerReward[1].getPosition().y + hud.votersIcon.getGlobalBounds().height / 4.f), _window);


		hud.playerIcon[GetParliamentaryPlayerOrder(1)].setPosition(initialOffset.x + hud.cardSprite.getGlobalBounds().width / 2 + hud.playerIcon[GetParliamentaryPlayerOrder(1)].getGlobalBounds().width, initialOffset.y);
		_window.draw(hud.playerIcon[GetParliamentaryPlayerOrder(1)]);

		hud.playerPseudo[GetParliamentaryPlayerOrder(1)].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(1)].getPosition().x, hud.playerIcon[GetParliamentaryPlayerOrder(1)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(1)].getGlobalBounds().height / 2 + PosToScreenY(20)));
		_window.draw(hud.playerPseudo[GetParliamentaryPlayerOrder(1)]);

		hud.playerReward[2].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(1)].getPosition().x - PosToScreenX(30), hud.playerIcon[GetParliamentaryPlayerOrder(1)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(1)].getGlobalBounds().height + PosToScreenY(20)));
		_window.draw(hud.playerReward[2]);

		BlitSprite(hud.votersIcon, sf::Vector2f(hud.playerReward[2].getPosition().x + hud.playerReward[2].getGlobalBounds().width / 2.f + PosToScreenX(30), hud.playerReward[2].getPosition().y + hud.votersIcon.getGlobalBounds().height / 4.f), _window);


		hud.playerIcon[GetParliamentaryPlayerOrder(0)].setPosition(initialOffset.x + hud.cardSprite.getGlobalBounds().width * 3 / 4 + hud.playerIcon[GetParliamentaryPlayerOrder(0)].getGlobalBounds().width, initialOffset.y);
		_window.draw(hud.playerIcon[GetParliamentaryPlayerOrder(0)]);

		hud.playerPseudo[GetParliamentaryPlayerOrder(0)].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(0)].getPosition().x, hud.playerIcon[GetParliamentaryPlayerOrder(0)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(0)].getGlobalBounds().height / 2 + PosToScreenY(20)));
		_window.draw(hud.playerPseudo[GetParliamentaryPlayerOrder(0)]);

		hud.playerReward[3].setPosition(sf::Vector2f(hud.playerIcon[GetParliamentaryPlayerOrder(0)].getPosition().x - PosToScreenX(30), hud.playerIcon[GetParliamentaryPlayerOrder(0)].getPosition().y + hud.playerIcon[GetParliamentaryPlayerOrder(0)].getGlobalBounds().height + PosToScreenY(20)));
		_window.draw(hud.playerReward[3]);

		BlitSprite(hud.votersIcon, sf::Vector2f(hud.playerReward[3].getPosition().x + hud.playerReward[3].getGlobalBounds().width / 2.f + PosToScreenX(30), hud.playerReward[3].getPosition().y + hud.votersIcon.getGlobalBounds().height / 4.f), _window);
	}
}

void DisplayHUD(sf::RenderWindow& _window)
{
	DisplayEndTurn(_window);
	DisplayButtons(_window);
	DisplayTimeline(_window);
	DisplayPutsch(_window);
	DisplayParliamentaryResults(_window);
}

void MousePressedRules(sf::Event _event, GameData& _gameData)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && RectContains(hud.closeRulesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
	{
		hud.closeRulesButton.isPressed = true;
		hud.areRulesDisplaying = false;
		PlaySoundFromList(GetButtonPressSound(), 50);
		_gameData.gameState = GAME;
	}

	if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && RectContains(hud.leftArrowButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && (hud.rulesSheet == 2 || hud.rulesSheet == 3))
	{
		if (hud.rulesSheet == 2)
		{
			hud.rulesSheet = 1;
		}
		else if (hud.rulesSheet == 3)
		{
			hud.rulesSheet = 2;
		}
		hud.leftArrowButton.isPressed = true;
		PlaySoundFromList(hud.turnPageSound, 50);
	}
	if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && RectContains(hud.rightArrowButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && (hud.rulesSheet == 1 || hud.rulesSheet == 2))
	{
		if (hud.rulesSheet == 1)
		{
			hud.rulesSheet = 2;
		}
		else if (hud.rulesSheet == 2)
		{
			hud.rulesSheet = 3;
		}
		hud.rightArrowButton.isPressed = true;
		PlaySoundFromList(hud.turnPageSound, 50);
	}
}

void MousePressedHUD(sf::Event _event, GameData& _gameData)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && RectContains(hud.endTurnButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && GetDiceHasRolling() && !GetPlayerIsMoving(GetActivePlayer()) && !GetDiceisAvailable() && GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()) && !GetIsAnyCardDisplaying() && !GetActionStackCanBeSelected() && !GetChanceStackCanBeSelected() && !GetIsInParliamentaryCouncil() && !GetIsDebateIsPlaying() && !GetInsertIsDisplay())
	{
		if (GetPlayerMoney(GetActivePlayer()) < 0)
		{
			AddPlayerVoters(GetActivePlayer(), -50);
		}

		SetPlayerHasAlreadyMoved(GetActivePlayer(), false);
		SetPlayerHasFinishedTurn(GetActivePlayer(), true);
		setDiceHasRolling(false);
		hud.endTurnButton.isPressed = true;
		if (!GetInsertIsDisplay())
		{
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
		
	}
	for (int i = 0; i < NB_PLAYERS; i++)
	{
		if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && RectContains(hud.putschButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && hud.putsch[i].isAvailable && !hud.putsch[i].isPutsching)
		{
			hud.putsch[i].isPutsching = true;
			hud.putschButton.isPressed = true;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
	}

	if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left) && RectContains(hud.openRulesButton.sprite.getGlobalBounds(), (sf::Vector2f)mousePos))
	{
		hud.openRulesButton.isPressed = true;
		hud.areRulesDisplaying = true;
		PlaySoundFromList(GetButtonPressSound(), 50);
		_gameData.gameState = RULES;
	}

	if (RectContains(hud.buttonNo.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && hud.buttonNo.isSelected && !GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			taxIsDisappears = true;
			hud.lastButton = false;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
	}

	if (RectContains(hud.buttonYes.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && hud.buttonYes.isSelected && !GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		if (_event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			taxIsDisappears = true;
			hud.lastButton = true;
			PlaySoundFromList(GetButtonPressSound(), 50);
		}
	}
}

void MouseMovedHUD()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (RectContains(hud.buttonNo.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()) && !hud.buttonNo.isSelected)
	{
		PlaySoundFromList(GetButtonSelectSound(), 5);
	}

	if (RectContains(hud.buttonNo.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		hud.buttonNo.isSelected = true;
	}
	else
	{
		hud.buttonNo.isSelected = false;
	}

	if (RectContains(hud.buttonYes.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()) && !hud.buttonYes.isSelected)
	{
		PlaySoundFromList(GetButtonSelectSound(), 5);
	}

	if (RectContains(hud.buttonYes.sprite.getGlobalBounds(), (sf::Vector2f)mousePos) && !GetPlayerHasChooseToPaidTaxesOrNot(GetActivePlayer()))
	{
		hud.buttonYes.isSelected = true;
	}
	else
	{
		hud.buttonYes.isSelected = false;
	}
}


void KeyPressedRules(sf::Event& _event, GameData& _gameData)
{
	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Right && (hud.rulesSheet == 1 || hud.rulesSheet == 2))
	{
		if (hud.rulesSheet == 1)
		{
			hud.rulesSheet = 2;
		}
		else if (hud.rulesSheet == 2)
		{
			hud.rulesSheet = 3;
		}
		PlaySoundFromList(hud.turnPageSound, 50);
	}
	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Left && (hud.rulesSheet == 2 || hud.rulesSheet == 3))
	{
		if (hud.rulesSheet == 2)
		{
			hud.rulesSheet = 1;
		}
		else if (hud.rulesSheet == 3)
		{
			hud.rulesSheet = 2;
		}
		PlaySoundFromList(hud.turnPageSound, 50);
	}

	if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Escape && hud.areRulesDisplaying)
	{
		hud.areRulesDisplaying = false;
		_gameData.gameState = GAME;
	}
}

bool GetHudAreRulesDisplaying()
{
	return hud.areRulesDisplaying;
}

Button& GetDicesButton()
{
	return hud.dicesButton;
}

void SetButtonYesTaxes()
{
	hud.lastButton = true;
}
void SetButtonNoTaxes()
{
	hud.lastButton = false;
}

bool GetTaxesButtonPressed(void)
{
	if (hud.buttonYes.isPressed || hud.buttonNo.isPressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GetPutschIsAvailable(unsigned char& _activePlayer)
{
	return hud.putsch[_activePlayer].isAvailable;
}

bool GetPlayerIsPutsching(unsigned char& _activePlayer)
{
	return hud.putsch[_activePlayer].isPutsching;
}

void SetPlayerIsPutsching(unsigned char& _activePlayer)
{
	hud.putsch[_activePlayer].isPutsching = true;
	hud.putschButton.isPressed = true;
	PlaySoundFromList(GetButtonPressSound(), 50);
}

int GetPlayerHasSucceededPutsch(int _i)
{
	return hud.putsch[_i].hasSucceeded;
}

void SetIsParliamentaryFinished(bool _bool)
{
	hud.isParliamentaryFinished = _bool;
}

bool GetIsParliamentaryFinished()
{
	return hud.isParliamentaryFinished;
}

void SetHUDPlayerPseudo()
{
	for (unsigned char i = 0; i < NB_PLAYERS; i++)
	{
		hud.playerPseudo[i].setString(GetPlayerPseudo(i));
		hud.playerPseudo[i].setOrigin(hud.playerPseudo[i].getGlobalBounds().width / 2, hud.playerPseudo[i].getGlobalBounds().height / 2);
	}
}

void SetHUDPlayerIcon()
{
	hud.playerIcon[GetPlayerCharacterChosen(PLAYER_1)] = LoadSprite("Assets/Images/Hud/MargaretTchatcheur.png", true);
	hud.playerIcon[GetPlayerCharacterChosen(PLAYER_2)] = LoadSprite("Assets/Images/Hud/RonaldRayban.png", true);
	hud.playerIcon[GetPlayerCharacterChosen(PLAYER_3)] = LoadSprite("Assets/Images/Hud/JVFranco.png", true);
	hud.playerIcon[GetPlayerCharacterChosen(PLAYER_4)] = LoadSprite("Assets/Images/Hud/VladInput.png", true);
}

void SetTaxIsAppears(bool _isAppears)
{
	if (timerTax == 0)
	{
		taxIsAppears = _isAppears;
		hud.taxeLetter.setScale(0.f, 0.f);
		hud.buttonNo.sprite.setScale(0.f, 0.f);
		hud.buttonYes.sprite.setScale(0.f, 0.f);
	}
}

void SetTaxIsDisappears(bool _isDisappears)
{
	taxIsDisappears = _isDisappears;
}