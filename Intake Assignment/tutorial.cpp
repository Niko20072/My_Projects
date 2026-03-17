#include "tutotial.h"
#include "input.h"
#include "inventory.h"
#include "car.h"
#include "house.h"
#include "wateringCan.h"
#include "player.h"

namespace Tmpl8
{
    Tutorial::Tutorial(Player &pl, Car &c, House &h) : player(pl), car(c), house(h), inventory(pl.pInventory()), wateringCan(pl.pWateringCan()) {};
	void Tutorial::Update()
	{
		// Tutorial logic here
        switch (tutorialState)
        {
        case TutorialState::Move:
            sprintf(tutorialText, "How to play: Use WASD to move");
            tutorialText2[0] = '\0';
            if (Input::GetKey(SDL_SCANCODE_W) || Input::GetKey(SDL_SCANCODE_A) || Input::GetKey(SDL_SCANCODE_S) || Input::GetKey(SDL_SCANCODE_D))
                tutorialState = TutorialState::OpenInventory;
            break;

        case TutorialState::OpenInventory:
            sprintf(tutorialText, "Press E to open the inventory");
            if (Input::GetKeyPressed(SDL_SCANCODE_E))
                tutorialState = TutorialState::InteractInventory;
            break;

        case TutorialState::InteractInventory:
            sprintf(tutorialText, "Click on the inventory buttons");
            sprintf(tutorialText2, "to interact with it");
            if(inventory.getFrame()!=0)
                tutorialState = TutorialState::ExitInventory;
            break;

		case TutorialState::ExitInventory:
            sprintf(tutorialText, "Press E, Q or click outside");
			sprintf(tutorialText2, "the inventory to close it");
            if (!inventory.MainInvIsOpen())
                tutorialState = TutorialState::GoToCar;
			break;

        case TutorialState::GoToCar:
            sprintf(tutorialText, "Go to the car and click on it. You need");
            sprintf(tutorialText2, "to be close to objects to interact with them!");
            if (car.CarInvIsOpen())
                tutorialState = TutorialState::BuySeeds;
			break;

        case TutorialState::BuySeeds:
            sprintf(tutorialText, "Buy some seeds from the car shop");
            tutorialText2[0] = '\0';
            if (car.getFrame() == 4 && car.CheckIfAnySeedButtonPressed())
				tutorialState = TutorialState::CheckOrders;
			break;

        case TutorialState::CheckOrders:
            sprintf(tutorialText, "Check out the orders (envelope icon)");
            tutorialText2[0] = '\0';
            if (car.getFrame() == 5)
                tutorialState = TutorialState::HowOrdersWork;
			break;

        case TutorialState::HowOrdersWork:
            sprintf(tutorialText, "You can complete orders by crafting");
			sprintf(tutorialText2, "the required potions (send them to earn money)");
            if(!car.CarInvIsOpen())
                tutorialState = TutorialState::ClickFarmTile;
            break;
        case TutorialState::ClickFarmTile:
            sprintf(tutorialText, "Go to the field and click on a");
            sprintf(tutorialText2, "farm tile that's close to you");
            if (inventory.SeedInvIsOpen())
                tutorialState = TutorialState::PlantSeed;
			break;
        case TutorialState::PlantSeed:
            sprintf(tutorialText, "Plant a seed");
            tutorialText2[0] = '\0';
            if (planted == true)
				tutorialState = TutorialState::WaterSeed;
            break;
		case TutorialState::WaterSeed:
            sprintf(tutorialText, "Water the plant by pressing R to equip");
            sprintf(tutorialText2, "the watering can, then clicking on the plant");
            if(wateringCan.getState() && Input::GetMouseButtonPressed(1))
				tutorialState = TutorialState::ClickHouse;
            break;
        case TutorialState::ClickHouse:
            sprintf(tutorialText, "Good job! Don't forget to water the plants");
            sprintf(tutorialText2, "every day! Now go inside the house");
            if (house.IsOpen())
				tutorialState = TutorialState::InteractTable;
			break;
        case TutorialState::InteractTable:
            sprintf(tutorialText, "Click on the potion table");
            tutorialText2[0] = '\0';
			if (house.hCrafting().CraftingIsOpen())
				tutorialState = TutorialState::ExplainTable;
            break;
		case TutorialState::ExplainTable:
            sprintf(tutorialText, "You can craft potions here using the");
            sprintf(tutorialText2, "plants you grow. Try crafting a potion!");
            if (house.hCrafting().getTutorialCraft())
                tutorialState = TutorialState::ExitTable;
			break;
        case TutorialState::ExitTable:
            sprintf(tutorialText, "Exit the crafting menu by pressing Q. Remember that");
            sprintf(tutorialText2, "you can close any interface by pressing Q!");
            if (!house.hCrafting().CraftingIsOpen())
				tutorialState = TutorialState::ClickNightstand;
			break;
        case TutorialState::ClickNightstand:
            sprintf(tutorialText, "Now click on the nightstand");
            tutorialText2[0] = '\0';
            if (house.NightstandIsOpen())
				tutorialState = TutorialState::ExplainNightstand;
			break;
        case TutorialState::ExplainNightstand:
            sprintf(tutorialText, "Here is how you can finish the game:");
            sprintf(tutorialText2, "Make 2000 coins and get your broom back!");
            if(!house.NightstandIsOpen())
				tutorialState = TutorialState::ClickBed;
            break;
		case TutorialState::ClickBed:
            sprintf(tutorialText, "Finally, click on the bed");
            tutorialText2[0] = '\0';
			if (house.BedIsOpen())
				tutorialState = TutorialState::ExplainBed;
            break;
		case TutorialState::ExplainBed:
            sprintf(tutorialText, "Sleeping will advance the day, causing");
            sprintf(tutorialText2, "your plants to grow and orders to refresh (every 5 days)");
			if (!house.BedIsOpen() || house.ConfirmedToSleep())
				tutorialState = TutorialState::HaveFun;
            break;
        case TutorialState::HaveFun:
            sprintf(tutorialText, "That's all you need to know.");
            sprintf(tutorialText2, "Have fun playing!");
            if (!house.IsOpen() || house.hCrafting().CraftingIsOpen() || house.NightstandIsOpen())
                tutorialState = TutorialState::Done;
			break;
        case TutorialState::Done:
            tutorialText[0] = '\0';
            tutorialText2[0] = '\0';
            break;
        }
        if(Input::GetKeyPressed(SDL_SCANCODE_X))
			tutorialState = TutorialState::Done;
	}
    void Tutorial::Draw(Surface* screen)
    {
        if (tutorialState != TutorialState::Done)
        {
            if (tutorialState != TutorialState::ExplainBed)
                screen->Bar(box[0], box[1], box[2], box[3], 0x0);
            if (tutorialState == TutorialState::InteractInventory)
            {
                screen->PrintScaled("here:", 260, 488, 2, 2, 0xff0000);
            }
            if (tutorialState == TutorialState::ExplainTable || tutorialState == TutorialState::ExitTable)
            {
                screen->CentreScaled(tutorialText, 409 + 15, 2, 2, 0xff0000);
                screen->CentreScaled(tutorialText2, 409 + 35, 2, 2, 0xff0000);
                box[0] = 85;
                box[1] = 417;
                box[2] = 712;
                box[3] = 459;
            }
            else if (tutorialText2[0] == '\0')
            {
                screen->CentreScaled(tutorialText, 20, 2, 2, 0xff0000);
                box[0] = 175;
                box[1] = 13;
                box[2] = 619;
                box[3] = 34;
            }
            else
            {
                screen->CentreScaled(tutorialText, 10, 2, 2, 0xff0000);
                screen->CentreScaled(tutorialText2, 30, 2, 2, 0xff0000);
                box[0] = 121;
                box[1] = 3;
                box[2] = 675;
                box[3] = 46;
            }
            if (tutorialState == TutorialState::Move || tutorialState == TutorialState::OpenInventory || tutorialState == TutorialState::InteractInventory)
                screen->PrintScaled("Press X to skip the tutorial", 10, 580, 2, 2, 0x8f0d7d);
        }
	}
}