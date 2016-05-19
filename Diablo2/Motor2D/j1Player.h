#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
//WARNING provisional sdl including
#include "SDL/include/SDL.h"
#include "j1Timer.h"
//#include "PlayerSkills.h"
#include "j1ParticleManager.h"
#include <vector>
#include <list>

using namespace std;

//NOTE: player speed, put it at the config file
#define PLAYER_SPEED 200.0f
#define PLAYER_RUN_SPEED 250.0f
#define DIRECTIONS 8
#define PLAYER_SPRITE_W int (96)
#define PLAYER_SPRITE_H int (92)
#define SPRITE_MARGIN int(1)
#define PLAYER_PIVOT_OFFSET int(10)
#define STAMINA_SPEED 0.1f
#define WALK_FRAMES_COUNT 60


//NOTE: provisional, this will go somewhere alse to apply to all entities, or maybe deleted because the state machine
enum DIRECTION
{
	D_FRONT,
	D_FRONT_LEFT,
	D_LEFT,
	D_BACK_LEFT,
	D_BACK,
	D_BACK_RIGHT,
	D_RIGHT,
	D_FRONT_RIGHT,
	D_DEFAULT
};

enum PLAYER_EVENT
{
	HP_DOWN,
	HP_UP,
	MP_DOWN,
	MP_UP,
	ST_DOWN,
	ST_UP,
	STATE_CHANGE,
	GET_ITEM,
	BLOOD_UP,
	BLOOD_DOWN,
	TELEPORT,
	CHANGE_ATTRIBUTE,
	CHANGE_STRENGTH,
	CHANGE_VITALITY,
	CHANGE_DEXTERITY,
	CHANGE_INTELLIGENCE,
	CHANGE_LUCK,
	CHANGE_BASICATTACK,
	CHANGE_RESISTENCE
};

enum ACTION_STATE
{
	IDLE,
	WALKING,
	RUNNING,
	SKILL,
	DEATH,
	NOTHING,
};

enum INPUT_STATE
{
	INPUT_MOVE,
	INPUT_RUN,
	INPUT_STOP_MOVE,
	INPUT_SKILL,
	INPUT_DEATH,
	INPUT_NULL,
};

enum PLAYER_ATTRIBUTE
{
	STRENGHT,
	DEXTERITY,
	INTELLIGENCE,
	VITALITY,
	LUCK,
	HP, //Not vitality
	BLOOD,
	BLOOD_MAX,
	ARMOR,
	COOLDOWN,
	EXTRA_DAMAGE,
	INVISIBILITY,
	PURE_BLOOD,
	POTION,
};

class EntEnemy;
class EntItem;
class Entity;
class Sprite;
class j1Scene;
class Skill;
class sklBasicAttack;
class sklBloodArrow;
class sklStingingStrike;
class sklWildTalon;
class sklKrobusArts;
class sklBatStrike;
class sklSoulOfIce;
class sklVampireBreath;
class sklBloodBomb;
class sklRedFeast;
class sklShadowsWalker;
class sklClottedBloodSkin;
class sklHeardOfBats; 
class sklLust;
class sklUndead;
class sklNightWard;
class Collider;
struct Buff;

class j1Player : public j1Module
{
//Methods

public:
	j1Player();

	//Destructor
	virtual ~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called the first frame
	bool Start();

	//PreUpdate
	bool PreUpdate();

	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	//Draws the player each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	//Debug mode
	void DrawDebug() const ;

	//Collision
	void OnCollision(Collider* c1, Collider* c2);

	//Movement
	void Move(float dt);
	void SetMovement(int x, int y);
	void SetInitVelocity();
	void SetTarget(iPoint target);
	void SetNewPath(int x, int y);
	void UpdateVelocity(float dt);
	void UpdateMovement(float dt);
	void InitMovement();
	bool IsTargetReached();
	void GetNewTarget();

	bool RunOn();
	
	//Attack
	bool IsInRange(Entity* enemy);
	void UpdateAttack();
	void CheckToAttack();
	void TakeDamage(float damage);

	//Pure Blood System
	void ReceiveBlood(int blood);

	bool Alive();

	void Respawn();

	//NOTE: some of these may go to the entities
	//Getters
	iPoint		GetMapPosition() const;
	iPoint		GetTilePosition() const;
	iPoint		GetBlitPosition() const;
	fPoint		GetPivotPosition() const;
	SDL_Rect	GetPlayerRect() const;

	//Estructuralfunctions
	void SetAnimations();
	void SetParticles();
	void SetDirection();
	void SetDirection(fPoint pos);
	void SetPosition(fPoint pos);

	//StateMachine functions
	ACTION_STATE UpdateAction();
	void StateMachine();

	//Utils
	void PlayerEvent(PLAYER_EVENT even);

	//Input
	void HandleInput();
	void SetInput(INPUT_STATE input);

	//Stats realted
	void LowerStamina();
	void RecoverStamina();
	void IncreaseBlood(int blood);
	void ChangeMP(int MP);
	void RecoverHP(float dt);
	void RestoreHP(int hp);
	void StartRecoverHP(int recovered_HP);

	void SetAttribute(PLAYER_ATTRIBUTE attribute, float value);
	void CalculateFinalStats();
	void UpdateBuffs();

	//Portals
	j1Scene* GetDestiny();
	bool TeleportReady();
	void ResetTeleport();
	
	//Skills
	void UpdatePassiveSkills();
	void UpdateSkillsCooldown();

//Attributes

public:
	bool		running = false;
	
public:

	//Position
	fPoint p_position;
	iPoint p_pivot;
	
	//Movement
	//NOTE: All this will be used with the moving unities too
	vector<iPoint> path;
	iPoint		p_target;
	int			p_current_node;
	//NOTE: the declaration will go somewhere else
	float		target_radius = 2.5f;
	fPoint		p_velocity;
	float		p_speed = PLAYER_SPEED;
	bool		movement;
	bool		target_reached;
	bool		path_on = true;
	int			walk_frame = 0;

	//Attack
	bool		attacking;
	int			atk_damage_base_up = 15;
	int			atk_damage_base_down = 10;
	int			atk_damage_final_up;
	int			atk_damage_final_down;
	float		dAtk;
	float		attack_range = 65.0f;

	//Textures
	Sprite* sprite = NULL;
	SDL_Texture* p_debug = NULL;
	SDL_Texture* p_sprite = NULL;
	SDL_Texture* p_idle = NULL;
	SDL_Texture* p_walk = NULL;
	SDL_Texture* p_run = NULL;
	SDL_Texture* p_attack = NULL;
	SDL_Texture* p_casting = NULL;
	SDL_Texture* p_death = NULL;

	
	//--------------------
	Animation* current_animation;
	//Idle
	//NOTE : Can i make this more elegant (maybe with a list)
	vector<Animation> idle;
	vector<Animation> walk;
	vector<Animation> attack;
	vector<Animation> cast;
	vector<Animation> run;
	vector<Animation> death;
	//--------------------

	/*
	//-----Attributes
	*/

	bool visible = true;
	bool inmune = false;

	float life_steal = 0;

	//HP
	float HP_max;
	float HP_current;
	float HP_base;
	float HP_dt = 4;
	float HP_recover_dt = 0.2f;
	float HP_recover_base = 1;
	float HP_recover_final;
	bool HP_potion;

	//MP
	float MP_max;
	float MP_current;
	float MP_base;

	//ST
	float ST_max;
	float ST_current;
	float ST_base;
	int		ST_dt = 1;

	//This is mana basically...?
	int blood_current;

	//Strength
	int str_base = 0;
	int str_final;

	//Dexterity
	int dex_base = 0;
	int dex_final;

	//Vitality
	int vit_base = 0;
	int vit_final;

	//Intelligence
	int int_base = 0;
	int int_final;

	//Luck
	int luck_base = 0;
	int luck_final;

	//Armor
	int armor_base = 0;
	int armor_final;

	int extra_damage = 0;
	int extra_pure_blood = 0;

	int exta_cooldown = 0;
	int extra_potion = 0;
	int extra_blood_charge = 0;
	

	float life;
	float stamina;
	float basic_damage;
	float bonus_martial_damage;
	float bonus_spell_damage;
	float drop;

	//Buffs list
	list<Buff*> buffs;
	//---------
	//Fx
	int player_death;
	int player_attack;
	int player_gethit;

	//StateMachine Attributes
	ACTION_STATE	current_action;
	vector<Animation> current_animation_set;
	DIRECTION		current_direction;
	INPUT_STATE		current_input;
	ACTION_STATE	previous_action = NOTHING;
	bool			input_locked = false;
	j1Timer			respawn_timer;

	//NOTE: will be cahnged to a enemy once entity manager structure is changed
	//Enemy target
	EntEnemy* enemy = NULL;
	Entity*	objective = NULL;

	//NOTE: this might be changed, particles in development
	Particle				particle_skill_1;
	fPoint					particle_destination;
	bool					particle_is_casted = false;

	//NOTE: Portal attributes, may be changed;
	bool teleport = false;
	j1Scene* scene_to_teleport = NULL;

	//Skills
	Skill* left_skill = NULL;
	Skill* right_skill = NULL;
	Skill* current_skill = NULL;
	Skill* independent_skill = NULL;

	//Those skills
	sklBasicAttack* basic_attack = NULL;


	//Martial Blood
	sklStingingStrike* stinging_strike = NULL;
	sklWildTalon* wild_talon = NULL;
	sklBatStrike* bat_strike = NULL;
	sklSoulOfIce* soul_of_ice = NULL;
	sklKrobusArts* krobus_arts = NULL;

	//Blood Spells
	sklBloodArrow* blood_arrow = NULL;
	sklVampireBreath* vampire_breath = NULL;
	sklBloodBomb* blood_bomb =  NULL;
	sklRedFeast* red_feast = NULL;
	sklHeardOfBats* heard_of_bats = NULL;

	//Night passives
	sklShadowsWalker* shadow_walker = NULL;
	sklClottedBloodSkin* clotted_blood = NULL;
	sklLust* lust = NULL;
	sklUndead* undead = NULL;
	sklNightWard* night_ward = NULL;

	vector<Skill*> skills;

	//Collider
	Collider* p_collider;

};

#endif // __j1PLAYER_H__

