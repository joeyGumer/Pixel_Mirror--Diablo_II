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
	SetAnimations();


	current_animation = idle_front;

	//Positioning
	p_position = { 0, 0 };
	p_pivot = { (PLAYER_SPRITE_W / 2), (PLAYER_SPRITE_H - PLAYER_PIVOT_OFFSET) };

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
	//NOTE: Have to apply a totally diferent pause method
	if (App->pause == false)
	{
		HandleInput();

		if (movement)
		{
			Move(dt);
		}
		//Camera idea to put it with an event, so it just iterates when it moves, see it later when we have done the pathfinding
		//Create the variable pivot because it will be more needed
		//NOTe : maybe is a good
		App->render->CenterCamera(p_position.x, p_position.y);
	}

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
//NOTE: had to take out the const because of the animation
void j1Player::Draw() 
{
	
	iPoint pos = GetBlitPosition();

	//Debug mode
	if (App->debug)
	{
		DrawDebug();
	}
	//NOTE: for pause mode, this will have to be on update to vary on dt
	SDL_Rect current_sprite = current_animation.GetCurrentFrame();
	//Draws Actual sprite
	App->render->Blit(p_sprite, pos.x, pos.y, &current_sprite);
}

//Debug

void j1Player::DrawDebug() const
{
	iPoint t_pos = GetTilePosition();
	iPoint p_pos = GetPivotPosition();

	App->render->Blit(p_debug, t_pos.x, t_pos.y);
	App->render->DrawQuad(App->player->GetPlayerRect(), 255, 0, 0, 1000, false);
	//App->render->DrawCircle(p_pos.x, p_pos.y, 5, 255, 0, 0, 1000);
	App->render->DrawQuad({ p_pos.x, p_pos.y, 3, 3 }, 255, 0, 0);

	if (movement)
	{
		if (movement)
		{
			App->render->DrawLine(p_position.x, p_position.y, p_target.x, p_target.y, 0, 0, 255);

			App->render->DrawLine(p_position.x, p_position.y, p_velocity.x+ p_position.x, p_velocity.y + p_position.y, 0, 255, 255);
		}
	}
}

/*
//-------Structural functions
*/

void j1Player::SetAnimations()
{
	//NOTE: think of a easier way to know the speed you are going to put the animation
	idle_front.SetFrames(0, 0, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_front.speed = 0.2f;

	idle_left_front.SetFrames(0, (PLAYER_SPRITE_H + 1) * D_FRONT_LEFT, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_left_front.speed = 0.2f;
	
	idle_left.SetFrames(0, (PLAYER_SPRITE_H + 1) * D_LEFT, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_left.speed = 0.2f;

	idle_left_back.SetFrames(0, (PLAYER_SPRITE_H + 1) * D_BACK_LEFT, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_left_back.speed = 0.2f;

	idle_back.SetFrames(0, (PLAYER_SPRITE_H + 1) * D_BACK, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_back.speed = 0.2f;

	idle_right_back.SetFrames(0, (PLAYER_SPRITE_H + 1) * D_BACK_RIGHT, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_right_back.speed = 0.2f;

	idle_right.SetFrames(0, (PLAYER_SPRITE_H + 1) * D_RIGHT, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_right.speed = 0.2f;

	idle_right_front.SetFrames(0, (PLAYER_SPRITE_H + 1) * D_FRONT_RIGHT, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, 1);
	idle_right_front.speed = 0.2f;
	
	/*idle_left_front = { 0, 93, 96, 92 };
	//idle_left &= NULL;
	idle_left_back = { 0, 279, 96, 92 };
	//idle_back = NULL;
	idle_right_back = { 0, 465, 96, 92 };
	//idle_right = NULL;
	idle_right_front = { 0, 651, 96, 92 };*/
}

void j1Player::SetDirection()
{
	float angle = p_velocity.GetAngle();

		
	//NOTE: should be a more elegant way to do this, and also, is provisional for the animations of the player, should be with the ENUM DIRECTION
	//Also, the angles will have to be especified again because in isometric , the intervals are not the same.
	if (angle < 22.5 && angle > -22.5)
		current_animation = idle_right;
	else if (angle >= 22.5 && angle <= 67.5)
		current_animation = idle_right_front;
	else if (angle > 67.5 && angle < 112.5)
		current_animation = idle_front;
	else if (angle >= 112.5 && angle <= 157.5)
		current_animation = idle_left_front;
	else if (angle > 157.5 || angle < -157.5)
		current_animation = idle_left;
	else if (angle >= -157.5 && angle <= -112.5)
		current_animation = idle_left_back;
	else if (angle > -112.5 && angle < -67.5)
		current_animation = idle_back;
	else if (angle >= -67.5 && angle <= -22.5)
		current_animation = idle_right_back;


}
/*
//-------Getters
*/

//NOTE: some of these things can go to map
iPoint j1Player::GetMapPosition()const
{
	return App->map->WorldToMap(p_position.x , p_position.y);
}

iPoint j1Player::GetTilePosition()const
{
	iPoint ret = GetMapPosition();
	ret = App->map->MapToWorld(ret.x, ret.y);
	ret.x -= App->map->data.tile_width / 2;
	return ret;
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
	return p_position;
}

SDL_Rect j1Player::GetPlayerRect() const
{
	//NOTE: this may be adapted when we use colliders
	iPoint pos = GetBlitPosition();

	return{ pos.x, pos.y, PLAYER_SPRITE_W, PLAYER_SPRITE_H};
}

/*
//-------Events
*/
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

/*
//---Linear Movement
*/
void j1Player::SetInitVelocity()
{
	p_target = App->input->GetMouseWorldPosition();

	p_velocity.x = p_target.x - p_position.x;
	p_velocity.y = p_target.y - p_position.y;

	p_velocity.SetModule(PLAYER_SPEED);

	SetDirection();

}

void j1Player::Move(float dt)
{
	fPoint vel = p_velocity * dt;

	p_position.x += int(vel.x);
	p_position.y += int(vel.y);

	movement = !IsTargetReached();

	if (movement)
	{
		UpdateVelocity(dt);
	}
	
	//Debug mode
	/*if (App->debug)
	{
		if (movement)
		{
			App->render->DrawLine(p_position.x, p_position.y, p_target.x, p_target.y, 0, 0, 255);

			App->render->DrawLine(p_position.x, p_position.y, vel.x * 50 + p_position.x, vel.y * 50 + p_position.y, 0, 255, 255);
		}
	}*/

}

void j1Player::UpdateVelocity(float dt)
{
	p_velocity.x = p_target.x - p_position.x;
	p_velocity.y = p_target.y - p_position.y;

	p_velocity.SetModule(PLAYER_SPEED);
}

bool j1Player::IsTargetReached()
{
	fPoint vel;

	vel.x = p_target.x - p_position.x;
	vel.y = p_target.y - p_position.y;

	if (vel.GetModule() <= target_radius)
	{
		return true;
	}

	return false;
}

//---------------------------

/*
//--------Input
*/

void j1Player::HandleInput()
{
	
	//NOTE: and provisional state machine for the player
	//
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = idle_left;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		current_animation = idle_right;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		current_animation = idle_back;
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		current_animation = idle_front;
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

	//Linear Movement activation
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		SetInitVelocity();
		movement = true;
	}
}