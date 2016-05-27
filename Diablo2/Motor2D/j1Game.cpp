#include "j1App.h"
#include "j1Game.h"
#include "j1Player.h"
#include "j1HUD.h"
#include "j1EntityManager.h"
#include "Item.h"
#include "j1Input.h"


j1Game::j1Game() : j1Module()
{
	name.create("game");

	//Init modules
	player	= new j1Player();
	em		= new j1EntityManager();
	HUD		= new j1HUD();

	//Add modules to the list
	AddModule(player);
	AddModule(em);
	AddModule(HUD);
}

//Destructor
j1Game::~j1Game()
{
	list<j1Module*>::reverse_iterator item = game_modules.rbegin();

	while (item != game_modules.rend())
	{
		RELEASE(*item);
		++item;
	}

	game_modules.clear();
}

// Called before render is available
bool j1Game::Awake(pugi::xml_node& conf)
{
	return true;
}

// Called before the first frame
bool j1Game::Start()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->Start();
	}

	return true;
}

//PreUpdate
bool j1Game::PreUpdate()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->PreUpdate();
	}

	//NOTE: DEBUG mode for items
	if (App->debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
		{
			DropItem(App->input->GetMouseWorldPosition());
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		App->SaveGame("save_state");
	}

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		App->LoadGame("save_state");
	}

	return true;
}

//Update
bool j1Game::Update(float dt)
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end() && active == true; item++)
	{
		if (!pause)
			(*item)->Update(dt);
		
		if (active)
			(*item)->Draw();
	}


	return true;
}

//PostUpdate
bool j1Game::PostUpdate()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->PostUpdate();
	}

	return true;
}

// Called before quitting
bool j1Game::CleanUp()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->CleanUp();
	}

	active = false;
	return true;
}

void j1Game::Draw()
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->Draw();
	}
}

void j1Game::AddModule(j1Module* module)
{
	module->Init();
	game_modules.push_back(module);
}

void j1Game::DropItem(iPoint pos)
{
	//NOTE: thinking of using srand for more equally distributed random generation
	//NOTE: have to change this, the random isn't equal at all. Even when there's a 60% to have no item, it almost always drops items
	int chance = rand() % 100;
	ITEM_RARITY rarity;

	//note: HAVE TO CHANGE THIS TO VARIABLES SO IT CAN BE CHANGED BY LUCK
	if (chance < base_no_drop - player->luck_final)
		rarity = NO_DROP;
	else if (chance < (base_no_drop + base_common_drop - player->luck_final))
		rarity = RARITY_COMMON;
	else if (chance < (base_no_drop + base_common_drop + base_rare_drop - player->luck_final))
		rarity = RARITY_RARE;
	else 
		rarity = RARITY_LEGENDARY;

	/*itmConsumable* item;
	item = new itmConsumable(rarity, pos);
	if (!item->ent_item)
	{
		RELEASE(item);
	}*/

	if (rarity != NO_DROP)
	{
		chance = rand() % 100;

		if (chance < 65)
		{
			chance = rand() % 100;

			if (chance < 35)
			{
				itmStone* item;
				item = new itmStone(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance < 55)
			{
				itmRing* item;
				item = new itmRing(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance < 65)
			{
				itmJewel* item;
				item = new itmJewel(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance < 90)
			{
				itmRune* item;
				item = new itmRune(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
			else if (chance >= 90)
			{
				itmArmor* item;
				item = new itmArmor(rarity, pos);
				if (!item->ent_item)
				{
					RELEASE(item);
				}
			}
		}
		else if (chance >= 65)
		{
			itmConsumable* item;
			item = new itmConsumable(rarity, pos);
			if (!item->ent_item)
			{
				RELEASE(item);
			}
		}
	}

}

bool j1Game::Load(pugi::xml_node& node)
{
	list<j1Module*>::iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->Load(node.child((*item)->name.GetString()));
	}

	return true;
}

bool j1Game::Save(pugi::xml_node& node) const
{
	list<j1Module*>::const_iterator item = game_modules.begin();

	for (; item != game_modules.end(); item++)
	{
		(*item)->Save(node.append_child((*item)->name.GetString()));
	}

	return true;
}