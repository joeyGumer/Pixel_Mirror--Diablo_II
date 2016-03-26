#include "j1Player.h"
#include "j1Render.h"
#include "j1Textures.h"
//NOTE: doubts about including the map to player
#include "j1Map.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1HUD.h"
#include "SDL/include/SDL.h"

j1Player::j1Player()
{
}

//Destructor
j1Player::~j1Player()
{
}

// Called before render is available
bool j1Player::Awake(pugi::xml_node& conf)
{
	return true;
}

// Called the first frame
bool j1Player::Start()
{
	//Debug tile
	p_debug = App->tex->Load("maps/path.png");
	
	//Idle sprites
	p_sprite = App->tex->Load("textures/vamp_idle.png");
	SetSpriteRects();


	current_sprite = idle_front;

	//Positioning
	p_map_pos = { 20, 20 };
	p_pivot = { (PLAYER_W / 2), (PLAYER_H - PLAYER_PIVOT_OFFSET) };

	//initial stats
	HP_max = HP_current = 100;
	MP_max = MP_current = 100;
	


	return true;
}

//PreUpdate
bool j1Player::PreUpdate()
{
	
	return true;
}

//Update
bool j1Player::Update(float dt)
{
	//NOTE: provisional movement for the player
	//NOTE: and provisional state machine for the player
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		current_sprite = idle_left_back;
		p_map_pos.x -= 1;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		current_sprite = idle_right_front;
		p_map_pos.x += 1;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		current_sprite = idle_right_back;
		p_map_pos.y -= 1;
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
	{
		current_sprite = idle_left_front;
		p_map_pos.y += 1;
	}
	//

	//NOTE: provisional mana and life changers
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (HP_current <= 0)
		{
			HP_current = 0;
		}
		else
		{
			HP_current--;
		}

		PlayerEvent(HP_DOWN);
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (HP_current >= HP_max)
		{
			HP_current = HP_max;
		}
		else
		{
			HP_current++;
		}

		PlayerEvent(HP_UP);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (MP_current <= 0)
		{
			MP_current = 0;
		}
		else
		{
			MP_current--;
		}

		PlayerEvent(MP_DOWN);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (MP_current >= MP_max)
		{
			MP_current = MP_max;
		}
		else
		{
			MP_current++;
		}

		PlayerEvent(MP_UP);
	}
	//

	//Camera idea to put it with an event, so it just iterates when it moves, see it later when we have done the pathfinding
	//Create the variable pivot because it will be more needed
	//NOTe : maybe is a good
	iPoint pos = App->map->MapToWorld(p_map_pos.x, p_map_pos.y);
	pos.x += App->map->data.tile_width/2;
	pos.y += App->map->data.tile_height/2;
	App->render->CenterCamera(pos.x, pos.y);

	return true;
}

//PostUpdate
bool j1Player::PostUpdate()
{
	
	return true;
}

// Called before quitting
bool j1Player::CleanUp()
{
	return true;
}


//Draws the player sprite to the scene
void j1Player::Draw() const
{
	
	iPoint pos = GetBlitPosition();

	//Debug mode
	if (App->debug)
	{
		Debug();
	}

	//Draws Actual sprite
	App->render->Blit(p_sprite, pos.x, pos.y, &current_sprite);
}

//Debug

void j1Player::Debug() const
{
	iPoint t_pos = GetTilePosition();
	iPoint p_pos = GetPivotPosition();

	App->render->Blit(p_debug, t_pos.x, t_pos.y);
	App->render->DrawQuad(App->player->GetPlayerRect(), 255, 0, 0, 1000, false);
	//App->render->DrawCircle(p_pos.x, p_pos.y, 5, 255, 0, 0, 1000);
	App->render->DrawQuad({ p_pos.x, p_pos.y, 3, 3 }, 255, 0, 0);
}

/*
//-------Structural functions
*/

void j1Player::SetSpriteRects()
{
	//it will be an animation, but for now, it will be with rect
	idle_front = { 0, 0, 96, 92 };
	idle_left_front = { 0, 93, 96, 92 };
	//idle_left &= NULL;
	idle_left_back = { 0, 279, 96, 92 };
	//idle_back = NULL;
	idle_right_back = { 0, 465, 96, 92 };
	//idle_right = NULL;
	idle_right_front = { 0, 651, 96, 92 };
}

/*
//-------Getters
*/

iPoint j1Player::GetMapPosition()const
{
	return p_map_pos;
}

iPoint j1Player::GetTilePosition()const
{
	return App->map->MapToWorld(p_map_pos.x, p_map_pos.y);
}

iPoint j1Player::GetBlitPosition()const
{
	iPoint ret = GetPivotPosition();
	ret.x -= p_pivot.x;
	ret.y -= p_pivot.y;

	return  ret;
}

iPoint j1Player::GetPivotPosition()const
{
	//NOTE : put a tile pivot?, more accesible
	iPoint ret = GetTilePosition();
	ret.x += App->map->data.tile_width / 2;
	ret.y += App->map->data.tile_height / 2;

	return ret;
}

SDL_Rect j1Player::GetPlayerRect() const
{
	//NOTE: this may be adapted when we use colliders
	iPoint pos = GetBlitPosition();

	return{ pos.x, pos.y, current_sprite.w, current_sprite.h };
}

//NOTE : this is because in the future, the player will need events, for example, when it get hits, low the HP downor other things
//maybe it ends being provisional
//There's HP_DOWN and HP_UP instead of HP change because it will act different (when down, it's a inmediat change, when up it's slower)
void j1Player::PlayerEvent(PLAYER_EVENT even)
{
	switch (even)
	{
	case HP_DOWN:
		{
			App->HUD->SetLife(HP_max, HP_current);
		}
		break;
	case HP_UP:
		{
			App->HUD->SetLife(HP_max, HP_current);
		}
		break;
	case MP_DOWN:
		{
			App->HUD->SetMana(MP_max, MP_current);
		}
		break;
	case MP_UP:
		{
			App->HUD->SetMana(MP_max, MP_current);
		}
		break;
	}
}