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
#include "hudInventory.h"
#include "Entity.h"
#include "EntEnemy.h"
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
	p_walk = App->tex->Load("textures/vamp_walk.png");
	p_attack = App->tex->Load("textures/vamp_attack.png");
	p_run = App->tex->Load("textures/vamp_run.png");
	p_death = App->tex->Load("textures/vamp_death.png");
	SetAnimations();

	current_action = IDLE;
	current_direction = D_FRONT;
	current_input = INPUT_NULL;
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	//Positioning
	p_position = { 0, 500 };
	p_pivot = { (PLAYER_SPRITE_W / 2), (PLAYER_SPRITE_H - PLAYER_PIVOT_OFFSET) };
	movement = false;
	attacking = false;

	//initial stats
	HP_max = HP_current = 200.0f;
	MP_max = MP_current = 100;
	ST_max = ST_current = 200.0f;

	//Sprite creation
	SDL_Rect current_sprite = current_animation->GetCurrentFrame();

	iPoint pos(p_position.x, p_position.y);
	sprite = new Sprite(p_sprite, pos, p_pivot, current_sprite);
	App->render->AddSpriteToList(sprite);
	
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
	if (current_action != DEATH)
	{
		if (!App->gui->mouse_hovering)
		{
			HandleInput();
		}

		CheckToAttack();

		//NOTE:Make this more elegant
		switch (current_action)
		{
		case IDLE:
			RecoverStamina();
			break;
		case WALKING:
			UpdateMovement(dt);
			RecoverStamina();
			break;
		case RUNNING:
			UpdateMovement(dt);
			LowerStamina();
			break;
		case ATTACKING:
			UpdateAttack();
			RecoverStamina();
			break;

		}
	}
	else
	{
		if (respawn_timer.ReadSec() >= 5)
		{
			Respawn();
		}
	}

		App->render->CenterCamera(p_position.x, p_position.y);

		

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

	SDL_DestroyTexture(p_sprite);
	//Take an eye on this
	if (sprite)
	{
		App->render->sprites.remove(sprite);
		RELEASE(sprite);
	}

	return true;
}

void j1Player::Respawn()
{
	//Cosnumable attributes restablished
	HP_current = HP_max;
	MP_current = MP_max;
	ST_current = ST_max;

	PlayerEvent(HP_UP);
	PlayerEvent(MP_UP);
	PlayerEvent(ST_UP);

	//Reset state and animation
	current_action = IDLE;
	current_direction = D_FRONT;
	current_input = INPUT_STOP_MOVE;
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];


	//Init position and booleans
	p_position = { 0, 500 };
	movement = false;
	attacking = false;
	running = false;
	enemy = NULL;
}

//Draws the player sprite to the scene
//NOTE: had to take out the const because of the animation
void j1Player::Draw() 
{
	//NOTE: for pause mode, this will have to be on update to vary on dt
	if (sprite)
	{
		SDL_Rect current_sprite = current_animation->GetCurrentFrame();
		iPoint pos(p_position.x, p_position.y);
		sprite->UpdateSprite(p_sprite, pos, p_pivot, current_sprite);
	}

	//Debug mode
	if (App->debug)
	{
		DrawDebug();
	}
	

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


void j1Player::RunOn()
{
	running = !running;
	if (current_action == RUNNING || current_action == WALKING)
	{
		SetInput(INPUT_MOVE);
	}
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
	case GET_ITEM:
		{
			//NOTE: GUARRALITY
			if (App->game->HUD->inventory->AddPotion())
			{
				App->game->em->Remove(objective->id);	
			}
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

	p_velocity.SetModule(p_speed);

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

	p_velocity.SetModule(p_speed);

	SetDirection();
}

bool j1Player::IsTargetReached()
{
	fPoint vel;

	vel.x = p_target.x - p_position.x;
	vel.y = p_target.y - p_position.y;



		if (vel.GetModule() <= target_radius)
		{
			if (!path_on)
			{
				SetInput(INPUT_STOP_MOVE);
				movement = false;
			}

			return true;
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
		if ((uint)p_current_node + 1 < path.size())
		{
			p_current_node++;
			SetTarget(App->map->GetTileCenter(path[p_current_node].x, path[p_current_node].y));
		}
		else
		{
			SetInput(INPUT_STOP_MOVE);
			movement = false;
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
		SetInput(INPUT_MOVE);
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

void j1Player::UpdateAttack()
{
	//NOTE: provisional attack state
		if (current_animation->Finished())
		{
			current_input = INPUT_STOP_MOVE;
			attacking = false;
			input_locked = false;
		}
	
}

void j1Player::CheckToAttack()
{
	if (enemy && !attacking)
	{
		if (IsInRange(enemy))
		{

			fPoint target = enemy->GetPivotPosition();

			fPoint dist = { target - p_position };
			p_velocity = dist;

			SetDirection();

			enemy->TakeDamage(atk_damage);

			movement = false;
			current_input = INPUT_ATTACK;
			enemy = NULL;
			objective = NULL;
			attacking = true;
			input_locked = true;
		}
	}

	else if (objective && !enemy)
	{
		if (IsInRange(objective))
		{
			fPoint target = objective->GetPivotPosition();

			fPoint dist = { target - p_position };
			p_velocity = dist;

			SetDirection();

			movement = false;
			current_input = INPUT_STOP_MOVE;
			
			PlayerEvent(GET_ITEM);
			objective = NULL;
		}
	}
}

void j1Player::TakeDamage(int damage)
{
	HP_current -= damage;
	PlayerEvent(HP_DOWN);

	if (HP_current <= 0)
	{
		HP_current = 0;
		current_input = INPUT_DEATH;
	}

}

bool j1Player::Alive()
{
	return current_action != DEATH;
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
		//NOTE: this will be later changed
		objective = App->game->em->EntityOnMouse();
		if (objective && objective->type == ENEMY)
		{
			enemy = (EntEnemy*)App->game->em->EntityOnMouse();
		}
		


		
		target = App->input->GetMouseWorldPosition();
		target = App->map->WorldToMap(target.x, target.y);
		SetMovement(target.x, target.y);

	}
}

void j1Player::SetInput(INPUT_STATE input)
{
	if (!input_locked)
	{
		current_input = input;
	}
}

//StateMachine Functions
ACTION_STATE j1Player::UpdateAction()
{
	if (current_input != INPUT_NULL)
	{
		switch (current_action)
		{
		case IDLE:
		{
			if (current_input == INPUT_MOVE)
			{
				if (!running)
					current_action = WALKING;
				else
					current_action = RUNNING;
			}

			else if (current_input == INPUT_ATTACK)
			{
				current_action = ATTACKING;
			}
			else if (current_input == INPUT_DEATH)
			{
				current_action = DEATH;
			}
			
		}
		break;

		case WALKING:
		{
			if (current_input == INPUT_STOP_MOVE)
			{
				current_action = IDLE;
			}

			else if (current_input == INPUT_ATTACK)
			{
				current_action = ATTACKING;
			}		

			else if (current_input == INPUT_MOVE && running)
			{
				current_action = RUNNING;
			}
			else if (current_input == INPUT_DEATH)
			{
				current_action = DEATH;
			}
		}
		break;

		case RUNNING:
		{
			if (current_input == INPUT_STOP_MOVE)
			{
				current_action = IDLE;
			}
			else if (current_input == INPUT_MOVE && !running)
			{
				current_action = WALKING;
			}
			else if (current_input == INPUT_ATTACK)
			{
				current_action = ATTACKING;
			}
			else if (current_input == INPUT_DEATH)
			{
				current_action = DEATH;
			}
		}
		break;

		case ATTACKING:
		{
			if (current_input == INPUT_STOP_MOVE)
			{
				current_action = IDLE;
			}
			else if (current_input == INPUT_DEATH)
			{
				current_action = DEATH;
			}
			
		}
		break;

		case DEATH:
		{
			if (current_input == INPUT_STOP_MOVE)
			{
				current_action = IDLE;
			}
		}
		break;
		}

		if (previous_action != current_action)
			PlayerEvent(STATE_CHANGE);

		previous_action = current_action;
	}

	current_input = INPUT_NULL;
	return current_action;
}

/*
//-------Stats related
*/

void j1Player::LowerStamina()
{
	if (ST_current > 0)
	{
		ST_current -= STAMINA_SPEED;
		PlayerEvent(ST_DOWN);
	}

	if (ST_current <= 0)
	{
		running = false;
		SetInput(INPUT_MOVE);
	}
}

void j1Player::RecoverStamina()
{
	if (ST_current != ST_max)
	{
		if (ST_current > ST_max)
		{
			ST_current = ST_max;
		}
		else
		{
			ST_current += STAMINA_SPEED;
			PlayerEvent(ST_UP);
		}
	}
}

void j1Player::RestoreHP(int health)
{
	
	HP_current += health;
	if (HP_current >= HP_max)
	{
		HP_max = HP_current;
	}

	PlayerEvent(HP_UP);
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

	//Run
	for (int i = 0; i < 8; i++)
	{
		Animation rn;
		rn.SetFrames(0, (PLAYER_SPRITE_H + SPRITE_MARGIN) * i, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 8, SPRITE_MARGIN);
		rn.speed = 0.2f;

		run.push_back(rn);
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

	//Death
	for (int i = 0; i < 8; i++)
	{
		Animation dth;
		dth.SetFrames(0, (PLAYER_SPRITE_H + SPRITE_MARGIN)* i, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 14, SPRITE_MARGIN);
		dth.speed = 0.2f;
		dth.loop = false;

		death.push_back(dth);
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
		p_speed = PLAYER_SPEED;
		break;
	case RUNNING:
		p_sprite = p_run;
		current_animation_set = run;
		p_speed = PLAYER_RUN_SPEED;
		break;
	case ATTACKING:
		p_sprite = p_attack;
		current_animation_set = attack;
		break;
	case DEATH:
		p_sprite = p_death;
		current_animation_set = death;
		respawn_timer.Start();
	}
	current_animation = &current_animation_set[current_direction];
}