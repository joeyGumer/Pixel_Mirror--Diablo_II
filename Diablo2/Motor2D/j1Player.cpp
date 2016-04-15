#include "j1Player.h"
#include "j1Render.h"
#include "j1Textures.h"
//NOTE: doubts about including the map to player
#include "j1Map.h"
#include "j1App.h"
#include "j1Game.h"
#include "j1Input.h"
#include "j1HUD.h"
#include "j1Gui.h"
#include "hudBelt.h"
#include "j1Pathfinding.h"
#include "j1EntityManager.h"
#include "Entity.h"
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
	p_debug = App->tex->Load("maps/mini_path.png");
	
	//Sprites
	p_sprite = p_idle = App->tex->Load("textures/vamp_idle.png");
	p_walk = App->tex->Load("textures/vamp_run.png");
	p_attack = App->tex->Load("textures/vamp_attack.png");
	SetAnimations();

	current_action = IDLE;
	current_direction = D_FRONT;
	current_input = INPUT_NULL;
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	//Positioning
	p_position = { 0, 0 };
	p_pivot = { (PLAYER_SPRITE_W / 2), (PLAYER_SPRITE_H - PLAYER_PIVOT_OFFSET) };
	movement = false;
	attacking = false;

	//initial stats
	HP_max = HP_current = 100;
	MP_max = MP_current = 100;
	ST_max = ST_current = 100;
	
	return true;
}

//PreUpdate
bool j1Player::PreUpdate()
{
	UpdateAction();

	return true;
}

//Update
bool j1Player::Update(float dt)
{
		if (!App->gui->mouse_hovering)
		{
			HandleInput();
		}

		//Test for attack

		UpdateMovement(dt);

		App->render->CenterCamera(p_position.x, p_position.y);

		if (current_action == WALKING)
		{
			if (ST_current > 0)
			{
				ST_current--;
				PlayerEvent(ST_DOWN);
			}
		}
		else
		{
			if (ST_current == ST_max)
			{
				ST_current = ST_max;
			}	
			else
			{
				ST_current++;
				PlayerEvent(ST_UP);
			}
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
	SDL_Rect current_sprite = current_animation->GetCurrentFrame();
	//Draws Actual sprite
	App->render->Blit(p_sprite, pos.x, pos.y, &current_sprite);
}

//Debug

void j1Player::DrawDebug() const
{
	iPoint t_pos = GetTilePosition();
	fPoint p_pos = GetPivotPosition();

	App->render->Blit(p_debug, t_pos.x, t_pos.y);
	//App->render->DrawQuad(GetPlayerRect(), 255, 0, 0, 1000, false);
	//App->render->DrawCircle(p_pos.x, p_pos.y, 5, 255, 0, 0, 1000);
	App->render->DrawQuad({ p_pos.x, p_pos.y, 3, 3 }, 255, 0, 0, 255, false);

	
	App->render->DrawCircle(p_pos.x, p_pos.y, attack_range, 255, 0, 0);

	if (movement)
	{
		App->render->DrawLine(p_position.x, p_position.y, p_target.x, p_target.y, 0, 0, 255);
		App->render->DrawLine(p_position.x, p_position.y, p_velocity.x+ p_position.x, p_velocity.y + p_position.y, 0, 255, 255);

		//Path
		for (int i = 0; i < path.size(); i++)
		{
			iPoint tmp = path[i];
			tmp = App->map->GetTileBlit(tmp.x, tmp.y);
			App->render->Blit(p_debug, tmp.x, tmp.y);
		}
	}
	
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
	fPoint tmp = GetPivotPosition();
	iPoint ret(tmp.x, tmp.y);
	ret.x -= p_pivot.x;
	ret.y -= p_pivot.y;

	return  ret;
}

fPoint j1Player::GetPivotPosition()const
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
			App->game->HUD->belt->SetLife(HP_max, HP_current);
		}
		break;
	case HP_UP:
		{
			App->game->HUD->belt->SetLife(HP_max, HP_current);
		}
		break;
	case MP_DOWN:
		{
			App->game->HUD->belt->SetMana(MP_max, MP_current);
		}
		break;
	case MP_UP:
		{
			App->game->HUD->belt->SetMana(MP_max, MP_current);
		}
		break;
	case ST_DOWN:
		{
			App->game->HUD->belt->SetStamina(ST_max, ST_current);
		}
		break;
	case ST_UP:
		{
			App->game->HUD->belt->SetStamina(ST_max, ST_current);
		}
		break;

	case STATE_CHANGE:
		{
			StateMachine();
		}
	}
}

/*
//-------------------------------------------Linear Movement
*/
void j1Player::SetInitVelocity()
{
	p_target = App->input->GetMouseWorldPosition();

	p_velocity.x = p_target.x - p_position.x;
	p_velocity.y = p_target.y - p_position.y;

	p_velocity.SetModule(PLAYER_SPEED);

}

void j1Player::Move(float dt)
{
	fPoint vel = p_velocity * dt;

	p_position.x += int(vel.x);
	p_position.y += int(vel.y);
}

void j1Player::UpdateVelocity(float dt)
{
	p_velocity.x = p_target.x - p_position.x;
	p_velocity.y = p_target.y - p_position.y;

	p_velocity.SetModule(PLAYER_SPEED);

	SetDirection();
}

bool j1Player::IsTargetReached()
{
	fPoint vel;

	vel.x = p_target.x - p_position.x;
	vel.y = p_target.y - p_position.y;

	//NOTE: provisional attack state
	if (enemy)
	{
		//Don't fucking know why but it doesn't give a fuck if it's null
		if (IsInRange(enemy))
		{
			movement = false;
			//attacking = false;
			current_input = INPUT_ATTACK;

			return true;

		}
		else
		{
			int ret = 0;
		}
		
		
	}

	else
	{
		if (vel.GetModule() <= target_radius)
		{
			if (!path_on)
			{
				current_input = INPUT_STOP_MOVE;
				movement = false;
			}

			return true;
		}
	}

	return false;
}

void j1Player::SetTarget(iPoint target)
{
	p_target = target;
	movement = true;
	target_reached = false;
}

void j1Player::GetNewTarget()
{
	if (enemy)
	{
		if (!IsInRange(enemy) && (uint)p_current_node + 1< path.size())
		{
			p_current_node++;
			SetTarget(App->map->GetTileCenter(path[p_current_node].x, path[p_current_node].y));
		}
		else
		{
			current_input = INPUT_STOP_MOVE;
			movement = false;
		}
	}
	else
	{
		if ((uint)p_current_node + 1 < path.size())
		{
			p_current_node++;
			SetTarget(App->map->GetTileCenter(path[p_current_node].x, path[p_current_node].y));
		}
		else
		{
			current_input = INPUT_STOP_MOVE;
			movement = false;
		}
	}
}

void j1Player::UpdateMovement(float dt)
{
	if (movement)
	{
		if (!target_reached)
		{
			UpdateVelocity(dt);
			Move(dt);
			if (IsTargetReached())
				target_reached = true;
		}
		else
		{
			GetNewTarget();
		}
	}
}

void j1Player::SetMovement(int x, int y)
{
	if (path_on)
	{ 
		SetNewPath(x,y);
	}
	else
	{
		iPoint target = App->map->GetTileCenter(x, y);
		SetTarget(target);
		
		//StateMachine change
		current_input = INPUT_MOVE;
	}
}

void j1Player::SetNewPath(int x, int y)
{
	iPoint start = App->map->WorldToMap(p_position.x, p_position.y);
	iPoint goal = { x, y };

	int steps = App->pathfinding->GetNewPath(start, goal, path);

	if (steps > 0)
	{
		//StateMachine change
		current_input = INPUT_MOVE;

		movement = true;
		p_current_node = -1;
		GetNewTarget();
	}

}
//---------------------------

/*
//---------Attack
*/

bool j1Player::IsInRange(Entity* enemy)
{
	fPoint target_enemy = enemy->GetPivotPosition();

	fPoint dist;

	dist.x = target_enemy.x - p_position.x;
	dist.y = target_enemy.y - p_position.y;

	float ret = dist.GetModule();
	ret = ret;

	if (attack_range > ret)
	{
		return true;
	}

	return false;
}

/*
//--------Input
*/

void j1Player::HandleInput()
{
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
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (ST_current <= 0)
		{
			ST_current = 0;
		}
		else
		{
			ST_current--;
		}

		PlayerEvent(ST_DOWN);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (ST_current >= ST_max)
		{
			ST_current = ST_max;
		}
		else
		{
			ST_current++;
		}

		PlayerEvent(ST_UP);
	}
	//

	//Linear Movement activation
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		iPoint target;
		enemy = App->em->EntityOnMouse();

		if (enemy)
		{
			attacking = true;
		}
		
		target = App->input->GetMouseWorldPosition();
		target = App->map->WorldToMap(target.x, target.y);
		SetMovement(target.x, target.y);

	}
}

//StateMachine Functions
ACTION_STATE j1Player::UpdateAction()
{
	if (current_input != INPUT_NULL && current_input != previous_input)
	{
		switch (current_action)
		{
		case IDLE:
		{
			if (current_input == INPUT_MOVE)
			{
				current_action = WALKING;
			}
		}
		break;

		case WALKING:
		{
			if (current_input == INPUT_STOP_MOVE)
			{
				current_action = IDLE;
			}

			if (current_input == INPUT_ATTACK)
			{
				current_action = ATTACKING;
			}			
		}
		break;

		case RUNNING:
		{

		}
		break;

		case ATTACKING:
		{
			 if (current_animation->Finished())
			{
				 current_action = IDLE;
			}
		}
		break;
		}

		previous_input = current_input;
		PlayerEvent(STATE_CHANGE);
	}

	current_input = INPUT_NULL;
	return current_action;
}

/*
//-------Structural functions
*/

void j1Player::SetAnimations()
{
	//Idle
	for (int i = 0; i < 8; i++)
	{
		Animation id;
		id.SetFrames(0, (PLAYER_SPRITE_H + SPRITE_MARGIN) * i, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, SPRITE_MARGIN);
		id.speed = 0.2f;

		idle.push_back(id);
	}

	//Walk
	for (int i = 0; i < 8; i++)
	{
		Animation wlk;
		wlk.SetFrames(0, (PLAYER_SPRITE_H + SPRITE_MARGIN) * i, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 8, SPRITE_MARGIN);
		wlk.speed = 0.2f;

		walk.push_back(wlk);
	}

	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation atk;
		atk.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 20, SPRITE_MARGIN);
		atk.speed = 0.3f;
		atk.loop = false;

		attack.push_back(atk);
	}
}

void j1Player::SetDirection()
{
	float angle = p_velocity.GetAngle();

	DIRECTION dir;

	if (angle < 22.5 && angle > -22.5)
		dir = D_RIGHT;
	else if (angle >= 22.5 && angle <= 67.5)
		dir = D_FRONT_RIGHT;
	else if (angle > 67.5 && angle < 112.5)
		dir = D_FRONT;
	else if (angle >= 112.5 && angle <= 157.5)
		dir = D_FRONT_LEFT;
	else if (angle > 157.5 || angle < -157.5)
		dir = D_LEFT;
	else if (angle >= -157.5 && angle <= -112.5)
		dir = D_BACK_LEFT;
	else if (angle > -112.5 && angle < -67.5)
		dir = D_BACK;
	else if (angle >= -67.5 && angle <= -22.5)
		dir = D_BACK_RIGHT;

	if (dir != current_direction)
	{
		current_direction = dir;
		current_animation = &current_animation_set[current_direction];
	}

}

void j1Player::StateMachine()
{
	switch (current_action)
	{
	case IDLE:
		p_sprite = p_idle;
		current_animation_set = idle;
		break;
	case WALKING:
		p_sprite = p_walk;
		current_animation_set = walk;
		/*
		--ST_current;
		PlayerEvent(ST_DOWN);
		*/
		break;
	case RUNNING:
		break;
	case ATTACKING:
		p_sprite = p_attack;
		current_animation_set = attack;
		break;
	}
}