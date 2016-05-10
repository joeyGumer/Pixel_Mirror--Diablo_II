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
#include "hudBlood.h"
#include "Entity.h"
#include "EntEnemy.h"
#include "EntItem.h"
#include "Item.h"
#include "EntPortal.h"
#include "PlayerSkills.h"
#include "SDL/include/SDL.h"
#include "j1Audio.h"
#include "hudStats.h"
#include "Buff.h"
//NOTE:Partciles in development, for now we will include this
//#include "playerParticle.h"

#include "j1Collision.h"


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
	//Create skills:
	basic_attack = new sklBasicAttack();
	blood_arrow = new sklBloodArrow();

	//
	player_attack = App->audio->LoadFx("audio/fx/PlayerAttack.ogg");
	player_death = App->audio->LoadFx("audio/fx/PlayerDeath.ogg");
	player_gethit = App->audio->LoadFx("audio/fx/PlayerGetHit.ogg");

	//Debug tile
	p_debug = App->tex->Load("maps/mini_path.png");
	
	//Sprites
	p_sprite = p_idle = App->tex->Load("textures/vamp_idle.png");
	p_walk = App->tex->Load("textures/vamp_walk.png");
	p_attack = App->tex->Load("textures/vamp_attack.png");
	p_casting = App->tex->Load("textures/vamp_cast.png");
	p_run = App->tex->Load("textures/vamp_run.png");
	p_death = App->tex->Load("textures/vamp_death.png");
	SetAnimations();
	SetParticles();



	//states
	previous_action = NOTHING;
	input_locked = false;
	current_action = IDLE;
	current_direction = D_FRONT;
	current_input = INPUT_NULL;
	current_animation_set = idle;
	current_animation = &current_animation_set[current_direction];

	current_skill = left_skill = basic_attack;
	right_skill = blood_arrow;

	//Positioning
	p_position = { 0, 500 };
	p_pivot = { (PLAYER_SPRITE_W / 2), (PLAYER_SPRITE_H - PLAYER_PIVOT_OFFSET) };
	movement = false;
	attacking = false;
	running = false;

	//Collider
	p_collider = App->collision->AddCollider({GetPivotPosition().x-20, GetBlitPosition().y + 20, 37, GetPlayerRect().h - 20}, COLLIDER_PLAYER, this);

	//initial stats
	HP_max = HP_current = 200.0f;
	MP_max = MP_current = 100;
	ST_max = ST_current = 200.0f;
	blood_current = 0;



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

		if (current_skill->skill_type == SKILL_MELEE)
		{
			CheckToAttack();
		}

		//NOTE:Make this more elegant
		switch (current_action)
		{
		case IDLE:
			break;
		case WALKING:
			UpdateMovement(dt);
			break;
		case RUNNING:
			UpdateMovement(dt);
			LowerStamina();
			break;
		case SKILL:
			current_skill->SkillUpdate();
			break;

		}

		if (current_action != RUNNING)
		{
			RecoverStamina();
		}
	}
	else
	{
		if (respawn_timer.ReadSec() >= 5)
		{
			Respawn();
		}
	}

	if (App->debug == false)
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
	if (p_collider)
		p_collider->to_delete = true;

	App->tex->UnLoad(p_idle);
	App->tex->UnLoad(p_walk);
	App->tex->UnLoad(p_run);
	App->tex->UnLoad(p_attack);
	App->tex->UnLoad(p_casting);
	App->tex->UnLoad(p_death);
	
	//Skills deleted
	if (basic_attack)
	{
		RELEASE(basic_attack);
	}	

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
	p_collider->rect.x = GetPivotPosition().x - 20;
	p_collider->rect.y = GetBlitPosition().y + 20;
	movement = false;
	attacking = false;
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


bool j1Player::RunOn()
{
	running = !running;
	if (current_action == RUNNING || current_action == WALKING)
	{
		SetInput(INPUT_MOVE);
	}

	return running;
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
			App->game->HUD->stats->SetLifeLabel(HP_current,HP_max);
		}
		break;
	case HP_UP:
		{
			App->game->HUD->belt->SetLife(HP_max, HP_current);
			App->game->HUD->stats->SetLifeLabel(HP_current, HP_max);
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
			App->game->HUD->stats->SetStaminaLabel(ST_current, ST_max);
		}
		break;
	case ST_UP:
		{
			App->game->HUD->belt->SetStamina(ST_max, ST_current);
			App->game->HUD->stats->SetStaminaLabel(ST_current, ST_max);
		}
		break;
	case GET_ITEM:
		{
			if (objective->type = ITEM)
			{
				((EntItem*)objective)->nexus->ConvertToGui();
				objective = NULL;
			}
		}
		break;
	case BLOOD_UP:
		{
			App->game->HUD->blood->SetBlood(blood_current);
			App->game->HUD->stats->SetBloodLabel(blood_current);
		}
		break;
	case BLOOD_DOWN:
		{
			//Code here
			//NOTE: why there's blood up and blood down? Don't copy me if you don't know what i'm doing this xD
			//I put HP_UP and HP_DOWN because the HP recovery is over time and the Hp decrease is instant.
		}
		break;
	case TELEPORT:
		{
			EntPortal* portal = (EntPortal*)objective;
			objective = NULL;
			teleport = true;
			scene_to_teleport = portal->destiny;
		}
		break;
	case STATE_CHANGE:
		{
			StateMachine();
		}
		break;
	case CHANGE_STRENGTH:
		{
			App->game->HUD->stats->SetStrengthLabel(str_final);
		}
		break;
	case CHANGE_VITALITY:
		{
			App->game->HUD->stats->SetVitalityLabel(vit_final);
		}
		break;
	case CHANGE_DEXTERITY:
		{
			App->game->HUD->stats->SetDexterityLabel(dex_final);
		}
		break;
	case CHANGE_INTELLIGENCE:
		{
			App->game->HUD->stats->SetIntelligenceLabel(int_final);
		}
		break;
	case CHANGE_LUCK:
		{
			App->game->HUD->stats->SetLuckLabel(luck_final);
		}
		break;
	case CHANGE_BASICATTACK:
		{
			App->game->HUD->stats->SetBasicAttackLabel(basic_damage);
		}
		break;
	case CHANGE_RESISTENCE:
		{
			//App->game->HUD->stats->SetResistenceLabel(vitality);
		}
		break;
	case CHANGE_ATTRIBUTE:
		{
			CalculateFinalStats();
		}
		break;
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

	//NOTE: Collider movement, may be changed
	p_collider->rect.x += int(vel.x);
	p_collider->rect.y += int(vel.y);
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
			current_input = INPUT_STOP_MOVE;
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

void j1Player::InitMovement()
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
			App->audio->PlayFx(player_attack, 0);

			movement = false;
			current_input = INPUT_SKILL;
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
			attacking = false;
			current_input = INPUT_STOP_MOVE;
			
			if (objective->type == ITEM)
				PlayerEvent(GET_ITEM);
			else if (objective->type == PORTAL)
				PlayerEvent(TELEPORT);
			objective = NULL;
		}
	}
}

void j1Player::TakeDamage(int damage)
{

	HP_current -= damage;
	PlayerEvent(HP_DOWN);

	if (HP_current <= 0 && Alive())
	{
		HP_current = 0;
		current_input = INPUT_DEATH;
		App->audio->PlayFx(player_death, 0);
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
	/*
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
	}*/
	//

	//NOTE: has to be changed for the skill 
	//Linear Movement activation
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN && !input_locked)
	{
		current_skill = left_skill;

		if (current_skill->skill_type != SKILL_MELEE && current_action != SKILL)
		{ 
			current_skill->SkillInit();
			current_input = INPUT_SKILL;
			input_locked = true;
		}
		else 
		{
			InitMovement();
		}
	}

	//NOTE: Debug purposes, must be changed! (Particle system)
	//------------
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && !input_locked)
	{
		current_skill = right_skill;

		if (current_skill->skill_type != SKILL_MELEE && current_action != SKILL)
		{
			current_skill->SkillInit();
			current_input = INPUT_SKILL;
			input_locked = true;
		}
		/*if (!input_locked)
		{
			particle_destination.x = App->input->GetMouseWorldPosition().x;
			particle_destination.y = App->input->GetMouseWorldPosition().y;
			SetDirection(particle_destination);
			SetInput(INPUT_CAST);
			input_locked = true;
		}*/
		else 
		{
			InitMovement();
		}
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		if (current_skill->skill_type == SKILL_MELEE)
		{
			walk_frame++;

			if (walk_frame >= WALK_FRAMES_COUNT && App->map->IsAtTileCenter(p_position.x, p_position.y))
			{
				InitMovement();
			}
		}
		

	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		if (current_skill->skill_type == SKILL_MELEE)
		{
			walk_frame++;

			if (walk_frame >= WALK_FRAMES_COUNT && App->map->IsAtTileCenter(p_position.x, p_position.y))
			{
				InitMovement();
			}
		}
	}
	//------------
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

			else if (current_input == INPUT_SKILL)
			{
				current_action = SKILL;
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

			else if (current_input == INPUT_SKILL)
			{
				current_action = SKILL;
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
			
			else if (current_input == INPUT_SKILL)
			{
				current_action = SKILL;
			}

			else if (current_input == INPUT_DEATH)
			{
				current_action = DEATH;
			}
		}
		break;

		case SKILL:
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
		App->game->HUD->belt->RunningOn();
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

void j1Player::IncreaseBlood(int blood)
{
	blood_current += blood;
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

bool j1Player::TeleportReady()
{
	return teleport;
}

j1Scene* j1Player::GetDestiny()
{
	return scene_to_teleport;
}

void j1Player::ResetTeleport()
{
	teleport = NULL;
	scene_to_teleport = NULL;
}

void j1Player::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_ENEMY_PARTICLE)
	{
		Particle* part = NULL;
		list<Particle*>::iterator item = App->pm->particleList.begin();
		for (; item != App->pm->particleList.end(); item++)
		{
			if (item._Ptr->_Myval->collider == c2)
			{
				part = item._Ptr->_Myval;
			}
		}

		if (part != NULL)
		{
			TakeDamage(part->damage);
			part->DestroyParticle();
		}
	}
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
		wlk.speed = 0.3f;

		walk.push_back(wlk);
	}

	//Run
	for (int i = 0; i < 8; i++)
	{
		Animation rn;
		rn.SetFrames(0, (PLAYER_SPRITE_H + SPRITE_MARGIN) * i, PLAYER_SPRITE_W, PLAYER_SPRITE_H, 8, SPRITE_MARGIN);
		rn.speed = 0.3f;

		run.push_back(rn);
	}

	//Attack
	for (int i = 0; i < 8; i++)
	{
		Animation atk;
		atk.SetFrames(0, (92 + SPRITE_MARGIN) * i, 119, 92, 20, SPRITE_MARGIN);
		atk.speed = 0.4f;
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

	//Skills animations

	basic_attack->SetSkillAnimations();
	blood_arrow->SetSkillAnimations();
}

//NOTE: why is this at player and not at the skill that uses this?
void j1Player::SetParticles()
{
	particle_skill_1.image = App->tex->Load("particles/Burn/Building_Burn_1.png");

	particle_skill_1.life = 5;
	particle_skill_1.type = PARTICLE_PLAYER_CAST;
	particle_skill_1.damage = 20;
	particle_skill_1.speed.x = 0;
	particle_skill_1.speed.y = 0;
	particle_skill_1.anim.frames.push_back({ 0, 0, 64, 64 });
	particle_skill_1.anim.frames.push_back({ 64, 0, 64, 64 });
	particle_skill_1.anim.frames.push_back({ 128, 0, 64, 64 });
	particle_skill_1.anim.frames.push_back({ 192, 0, 64, 64 });
	particle_skill_1.anim.frames.push_back({ 256, 0, 64, 64 });
	particle_skill_1.anim.frames.push_back({ 320, 0, 64, 64 });
	particle_skill_1.anim.frames.push_back({ 384, 0, 64, 64 });
	particle_skill_1.anim.frames.push_back({ 448, 0, 64, 64 });
	particle_skill_1.anim.speed = 0.5f;
	particle_skill_1.anim.loop = true;
	particle_skill_1.anim.Reset();

	particle_skill_1.collider_margin.x = particle_skill_1.anim.GetCurrentFrame().w / 3;
	particle_skill_1.collider_margin.y = particle_skill_1.anim.GetCurrentFrame().h / 4;
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

void j1Player::SetDirection(fPoint pos)
{
	//NOTE: This has been created to change the direction without moving the player
	fPoint direction;
	direction.x = pos.x - p_position.x;
	direction.y = pos.y - p_position.y;

	direction.SetModule(1);

	float angle = direction.GetAngle();

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

void j1Player::SetPosition(fPoint pos)
{
	p_position = pos;
	p_collider->rect.x = GetPivotPosition().x - 20;
	p_collider->rect.y = GetBlitPosition().y + 20;
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
	case SKILL:
		p_sprite = current_skill->skill_tex;
		current_animation_set = current_skill->skill_animation_set;
		break;
	case DEATH:
		p_sprite = p_death;
		current_animation_set = death;
		respawn_timer.Start();
		break;
	}
	current_animation = &current_animation_set[current_direction];
}

/*
//Player attributes
*/
void j1Player::SetAttribute(PLAYER_ATTRIBUTE attribute, float value)
{
	//NOTE: make the labels to be changed only at the end of all the calculation
	switch (attribute)
	{
	case STRENGHT:
	{
		str_final += value;
		//basic_damage += ( ( basic_damage ) * ((1 / 100) * value ) );
		//strength = ((basic_damage)* ((1 / 100) * value));
		//PLAYER_EVENT(CHANGE_BASICATTACK);
		
	}
		break;
	case DEXTERITY:
	{
		dex_final += value;
		//bonus_martial_damage = dexterity += value;
	
	}
		break;
	case INTELLIGENCE:
	{
		int_final += value;
		//bonus_spell_damage = intelligence +=  value;

	}
		break;
	case VITALITY:
	{
		vit_final += value;
		//life += (life + (value*4));
		//stamina += 1;
		
	}
		break;
	case LUCK:
	{
		luck_final += value;
		//drop = value;
	}
		break;
	}

}

void j1Player::CalculateFinalStats()
{

	str_final = str_base;
	dex_final = dex_base;
	vit_final = vit_base;
	int_final = int_base;
	luck_final = luck_base;

	list<Buff*>::iterator item = buffs.begin();

	for (; item != buffs.end(); item++)
	{
		SetAttribute((*item)->attribute, (*item)->value);
	}

	App->game->HUD->stats->SetStrengthLabel(str_final);
	App->game->HUD->stats->SetVitalityLabel(vit_final);
	App->game->HUD->stats->SetDexterityLabel(dex_final);
	App->game->HUD->stats->SetIntelligenceLabel(int_final);
	App->game->HUD->stats->SetLuckLabel(luck_final);
	App->game->HUD->stats->SetBasicAttackLabel(basic_damage);


}