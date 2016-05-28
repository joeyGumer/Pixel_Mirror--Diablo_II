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
#include "j1SceneManager.h"
#include "snIntro.h"
#include "snLose.h"


j1Player::j1Player()
{
	name.create("player");
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
	stinging_strike = new sklStingingStrike();
	wild_talon = new sklWildTalon();
	bat_strike = new sklBatStrike();
	soul_of_ice = new sklSoulOfIce();
	krobus_arts = new sklKrobusArts();
	vampire_breath = new sklVampireBreath();
	blood_bomb = new sklBloodBomb();
	red_feast = new sklRedFeast();
	shadow_walker = new sklShadowsWalker();
	clotted_blood = new sklClottedBloodSkin();
	heard_of_bats = new sklHeardOfBats();
	lust = new sklLust();
	undead = new sklUndead();
	night_ward = new sklNightWard();

	skills.push_back(basic_attack);
	skills.push_back(blood_arrow);
	skills.push_back(stinging_strike);
	skills.push_back(wild_talon);
	skills.push_back(bat_strike);
	skills.push_back(soul_of_ice);
	skills.push_back(krobus_arts);
	skills.push_back(vampire_breath);
	skills.push_back(blood_bomb);
	skills.push_back(red_feast);
	skills.push_back(shadow_walker);
	skills.push_back(clotted_blood);
	skills.push_back(heard_of_bats);
	skills.push_back(lust);
	skills.push_back(undead);
	skills.push_back(night_ward);


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

	basic_attack->unlocked = true;
	current_skill = left_skill = right_skill = basic_attack;

	//Positioning
	p_position = { 0, 500 };
	p_pivot = { (PLAYER_SPRITE_W / 2), (PLAYER_SPRITE_H - PLAYER_PIVOT_OFFSET) };
	movement = false;
	attacking = false;
	running = false;

	//Collider
	p_collider = App->collision->AddCollider({GetPivotPosition().x-20, GetBlitPosition().y + 20, 37, GetPlayerRect().h - 20}, COLLIDER_PLAYER, this);

	//initial stats
	HP_max = HP_current = HP_base = 60.0f;
	HP_recover_final = HP_recover_base;
	MP_max = MP_current = MP_base = 100;
	ST_max = ST_current = ST_base = 79.0f;
	blood_current = 0;

	//Attack
	atk_damage_final_up = atk_damage_base_up = 15;
	atk_damage_final_down = atk_damage_final_down = 10;

	//dAtk = (float)atk_damage_base / 100;

	//Armor
	armor_final = armor_base = 0;

	
	enemy = NULL;


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
	UpdateBuffs();
	UpdatePassiveSkills();
	UpdateSkillsCooldown();
	CalculateFinalStats();

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

		if (independent_skill)
		{
			independent_skill->SkillIndependentUpdate(dt);
		}
		//NOTE:Make this more elegant
		switch (current_action)
		{
		case IDLE:
			if (input_locked)
				input_locked = false;
			break;
		case WALKING:
			UpdateMovement(dt);
			break;
		case RUNNING:
			UpdateMovement(dt);
			LowerStamina();
			break;
		case SKILL:
			current_skill->SkillUpdate(dt);
			break;

		}

		if (current_action != RUNNING)
		{
			RecoverStamina();
		}

		RecoverHP(dt);
	}
	else
	{
		if (respawn_timer.ReadSec() >= 5)
		{
			App->sm->ChangeScene(App->sm->lose);
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
	list<Buff*>::iterator item = buffs.begin();

	for (; item != buffs.end(); item++)
	{
		RELEASE(*item);
	}

	buffs.clear();

	if (p_collider)
		p_collider->to_delete = true;

	App->tex->UnLoad(p_idle);
	App->tex->UnLoad(p_walk);
	App->tex->UnLoad(p_run);
	App->tex->UnLoad(p_attack);
	App->tex->UnLoad(p_casting);
	App->tex->UnLoad(p_death);

	//Skills unload
	RELEASE(basic_attack)
		RELEASE(blood_arrow)
		RELEASE(stinging_strike)
		RELEASE(wild_talon)
		RELEASE(bat_strike)
		RELEASE(soul_of_ice)
		RELEASE(krobus_arts)
		RELEASE(vampire_breath)
		RELEASE(blood_bomb)
		RELEASE(red_feast)
		RELEASE(shadow_walker)
		RELEASE(clotted_blood)
		RELEASE(heard_of_bats)
		RELEASE(lust)
		RELEASE(undead)
		RELEASE(night_ward)

		skills.clear();
	
	//Take an eye on this
	if (sprite)
	{
		App->render->sprites.remove(sprite);
		RELEASE(sprite);
	}

	return true;
}

bool j1Player::Load(pugi::xml_node& node)
{
	p_position.x = node.child("position").attribute("x").as_float();
	p_position.y = node.child("position").attribute("y").as_float();

	pugi::xml_node skl = node.child("skills").child("skill");

	for (int i = 0; i < skills.size(); i++, skl = skl.next_sibling("skill"))
	{
		Skill* skill = skills[i];

		skill->unlocked = skl.append_attribute("unlocked").as_bool();
		skill->level = skl.append_attribute("level").as_int();
	}

	return true;
}

bool j1Player::Save(pugi::xml_node& node) const
{
	pugi::xml_node pos = node.append_child("position");
	pugi::xml_node skls = node.append_child("skills");

	pos.append_attribute("x") = p_position.x;
	pos.append_attribute("y") = p_position.y;

	for (int i = 0; i < skills.size(); i++)
	{
		pugi::xml_node skill = skls.append_child("skill");

		skill.append_attribute("unlocked") = skills[i]->unlocked;
		skill.append_attribute("level") = skills[i]->level;
	}

	return true;
}

void j1Player::Respawn()
{
	App->sm->ChangeScene(App->sm->intro);
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
			App->game->HUD->belt->SetLife(int(HP_max), int(HP_current));
			App->game->HUD->stats->SetLifeLabel(int(HP_current),int(HP_max));
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
			App->game->HUD->blood->SetBlood(blood_current);
			App->game->HUD->stats->SetBloodLabel(blood_current);
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

	if (objective && objective->type == ENEMY && current_skill->skill_type == SKILL_MELEE)
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

			//Specify effect
			//enemy->TakeDamage(atk_damage_final);
			//App->audio->PlayFx(player_attack, 0);

			movement = false;

			if (current_skill->avaliable)
			{
				current_input = INPUT_SKILL;
				attacking = true;
			}
			else
			{
				current_input = INPUT_STOP_MOVE;
			}
				
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

void j1Player::TakeDamage(float damage)
{
	if (!inmune)
	{

		float reduction = (float)damage / 100 * armor_final;
		float final_damage = damage - reduction;

		if (night_ward->unlocked && night_ward->avaliable)
		{
			if (!night_ward->active)
			{
				night_ward->SkillInit();
			}
			else if (night_ward->active)
			{
				night_ward->SkillEffect();
				final_damage -= (HP_max / 100) * night_ward->damage_reduction_base;
			}
		}

		if (final_damage < 0)
			final_damage = 0;

		HP_current -= final_damage;
		PlayerEvent(HP_DOWN);

		if (HP_current <= 0 && Alive())
		{
			HP_current = 0;
			if (undead->unlocked && undead->avaliable)
			{
				undead->SkillEffect();
			}
			else
			{
				current_input = INPUT_DEATH;
				App->audio->PlayFx(player_death, 0);
			}
		}
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
	if (App->debug)
	{
		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
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
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_REPEAT)
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

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_REPEAT)
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
		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_REPEAT)
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
		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_REPEAT)
		{
			if (blood_current <= 0)
			{
				blood_current = 0;
			}
			else
			{
				blood_current -= 500;
			}

			PlayerEvent(BLOOD_DOWN);
		}
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_REPEAT)
		{
		
				blood_current += 1000;

			PlayerEvent(BLOOD_DOWN);
		}
	}
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
			if (current_skill->avaliable)
			{
				current_skill->SkillInit();
				current_input = INPUT_SKILL;
				input_locked = true;
			}
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
	blood_current += int(float(blood) + float(float(blood)/100 * extra_pure_blood));
}

void j1Player::ChangeMP(int MP)
{
	MP_current += MP;

	if (MP_current > MP_max)
	{
		MP_current = MP_max;
	}
	else if (MP_current == 0)
	{
		MP_current = 0;
	}

	PlayerEvent(MP_UP);
}
void j1Player::RecoverHP(float dt)
{
	
	HP_current += HP_recover_final * dt;
	if (HP_current >= HP_max)
	{
		HP_current = HP_max;
	}

	PlayerEvent(HP_UP);
}

void j1Player::RestoreHP(int hp)
{
	HP_current += hp;
	if (HP_current >= HP_max)
	{
		HP_current = HP_max;
	}

	else if (HP_current <= 0)
	{
		HP_current = 0;
		current_input = INPUT_DEATH;
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
	stinging_strike->SetSkillAnimations();
	wild_talon->SetSkillAnimations();
	bat_strike->SetSkillAnimations();
	soul_of_ice->SetSkillAnimations();
	krobus_arts->SetSkillAnimations();
	vampire_breath->SetSkillAnimations();
	blood_bomb->SetSkillAnimations();
	red_feast->SetSkillAnimations();
	shadow_walker->SetSkillAnimations();
	clotted_blood->SetSkillAnimations();
	heard_of_bats->SetSkillAnimations();
}

//NOTE: why is this at player and not at the skill that uses this?
void j1Player::SetParticles()
{
	//Particle 1
	particle_skill_1.image = App->tex->Load("particles/Special/Player/BloodArrow.png");

	particle_skill_1.life = 5;
	particle_skill_1.type = PARTICLE_PLAYER_CAST;
	particle_skill_1.damage = 20;
	particle_skill_1.speed.x = 0;
	particle_skill_1.speed.y = 0;
	for (int i = 0; i < 3; i++)
	{
		particle_skill_1.anim.SetFrames(0, 0 + 32 * i, 34, 32, 5);
	}
	particle_skill_1.anim.speed = 0.5f;
	particle_skill_1.anim.loop = true;
	particle_skill_1.anim.Reset();

	particle_skill_1.collider_margin.x = 3;
	particle_skill_1.collider_margin.y = 3;

	particle_skill_1.collider_pivot.x = 0;
	particle_skill_1.collider_pivot.y = 0;

	//Particle2
	particle_skill_2.image = App->tex->Load("particles/Special/Player/BloodBomb.png");

	particle_skill_2.life = 5;
	particle_skill_2.type = PARTICLE_PLAYER_CAST;
	particle_skill_2.damage = 20;
	particle_skill_2.speed.x = 0;
	particle_skill_2.speed.y = 0;

	for (int i = 0; i < 8; i++)
	{
		Animation tmp;
		tmp.SetFrames(0, 0 + 109 * i, 221, 109, 8);
		tmp.speed = 0.2f;
		particle_skill_2.anim_vector.push_back(tmp);
		if (i == 0)
		{
			particle_skill_2.anim = tmp;
		}
	}
	particle_skill_2.directions = true;

	
	particle_skill_2.anim.loop = true;
	particle_skill_2.anim.Reset();

	particle_skill_2.collider_margin.x = particle_skill_2.anim.GetCurrentFrame().w / 3 + 30;
	particle_skill_2.collider_margin.y = particle_skill_2.anim.GetCurrentFrame().h / 3 + 10;

	particle_skill_2.collider_pivot.x = 0;
	particle_skill_2.collider_pivot.y = -5;
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
		//bonus_spell_damage = intelligence +=  value

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
	case ARMOR:
	{
		armor_final += value;
	}
	break;
	case EXTRA_DAMAGE:
	{
		extra_damage += value;
	}
	break;
	case INVISIBILITY:
	{
		visible = false;
	}
	break;
	case PURE_BLOOD:
	{
		extra_pure_blood += value;
	}
	break;
	case COOLDOWN:
	{
		exta_cooldown += value;
	}
	case POTION:
	{
		extra_potion += value;
	}
	break;
	case BLOOD_MAX:
	{
		extra_blood_charge += value;
	}
	break;
	default:
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
	atk_damage_final_up = atk_damage_base_up;
	atk_damage_final_down = atk_damage_base_down;
	armor_final = armor_base;
	extra_damage = 0;
	extra_pure_blood = 0;
	exta_cooldown = 0;
	extra_potion = 0;
	extra_blood_charge = 0;
	life_steal = 0;
	visible = true;

	HP_max = HP_base;
	MP_max = MP_base;
	HP_recover_final = HP_recover_base;
	ST_max = ST_base;


	list<Buff*>::iterator item = buffs.begin();

	for (; item != buffs.end(); item++)
	{
		SetAttribute((*item)->attribute, (*item)->value);
	}

	//Stats that varies dependieng on main attributes:

	//Security
	//Strength
	if (str_final < 0)
		str_final = 0;


	atk_damage_final_down += str_final/2;
	atk_damage_final_up += str_final;



	//Dexterity
	if (dex_final < 0)
		dex_final = 0;

	//Intelligence 
	if (int_final < 0)
		int_final = 0;

	//Vitality
	if (vit_final < 0)
		vit_final = 0;

	HP_max += HP_dt * vit_final;
	HP_recover_final += HP_recover_dt * vit_final;
	ST_max += ST_dt * vit_final;

	MP_max += extra_blood_charge;

	if (lust->unlocked)
	{
		HP_max += lust->increased_HP;
	}

	if (HP_current > HP_max)
		HP_current = HP_max;

	if (ST_current > ST_max)
		ST_current = ST_max;

	//Luck
	if (luck_final < 0)
		luck_final = 0;

	//Armor
	if (armor_final < 0)
		armor_final = 0;

	//Passive skills intervention
	if (undead->unlocked  && undead->active)
	{
		extra_damage += undead->extra_damage;
		life_steal += undead->life_steal;
	}
	//Label actualization
	App->game->HUD->stats->SetStrengthLabel(str_final);
	App->game->HUD->stats->SetVitalityLabel(vit_final);
	App->game->HUD->stats->SetDexterityLabel(dex_final);
	App->game->HUD->stats->SetIntelligenceLabel(int_final);
	App->game->HUD->stats->SetLuckLabel(luck_final);
	App->game->HUD->stats->SetBasicAttackLabel(atk_damage_final_up);
	App->game->HUD->stats->SetResistenceLabel(armor_final);

	//HUD related
	PlayerEvent(HP_DOWN);
	PlayerEvent(ST_DOWN);
	PlayerEvent(MP_DOWN);

}

void j1Player::UpdateBuffs()
{
	bool buff_change = false;

	list<Buff*>::iterator item = buffs.begin();

	for (; item != buffs.end(); item++)
	{
		if (!(*item)->Update())
		{
			RELEASE(*item);
			item = item--;
			buffs.erase(item++);
			buff_change = true;
		}
	}

	if (buff_change)
		CalculateFinalStats();
}

void j1Player::UpdatePassiveSkills()
{
	if (undead->unlocked)
	{
		undead->SkillUpdate(0);
	}

	if (night_ward->unlocked)
	{
		night_ward->SkillUpdate(0);
	}
}

void j1Player::UpdateSkillsCooldown()
{
	for (int i = 0; i < skills.size(); i++)
	{
		if (skills[i]->unlocked)
		{
			skills[i]->UpdateCooldown();
		}
	}
}