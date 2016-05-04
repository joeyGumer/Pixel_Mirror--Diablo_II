#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "Animation.h"
//WARNING provisional sdl including
#include "SDL/include/SDL.h"
#include "j1Timer.h"
//#include "PlayerSkills.h"
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
	TELEPORT
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

class EntEnemy;
class EntItem;
class Entity;
class Sprite;
class playerParticle;
class j1Scene;
class Skill;
class sklBasicAttack;
class sklBloodArrow;
class Collider;

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

	//Movement
	void Move(float dt);
	void SetMovement(int x, int y);
	void SetInitVelocity();
	void SetTarget(iPoint target);
	void SetNewPath(int x, int y);
	void UpdateVelocity(float dt);
	void UpdateMovement(float dt);
	bool IsTargetReached();
	void GetNewTarget();

	bool RunOn();
	
	//Attack
	bool IsInRange(Entity* enemy);
	void UpdateAttack();
	void CheckToAttack();
	void TakeDamage(int damage);

	//Casting
	void UpdateMagic();

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

	void RestoreHP(int health);

	j1Scene* GetDestiny();
	bool TeleportReady();
	void ResetTeleport();

	//Collider
	void OnCollision(Collider* c1, Collider* c2);

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

	//Attack
	bool		attacking;
	int			atk_damage = 50;

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

	//Rects for each state and direction
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

	//Attributes
	int HP_max;
	int HP_current;

	int MP_max;
	int MP_current;

	float ST_max;
	float ST_current;

	int blood_current;

	float attack_range = 65.0f;

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
	list<playerParticle*>	particle_list;
	fPoint					particle_destination;
	bool					particle_is_casted = false;

	//NOTE: Portal attributes, may be changed;
	bool teleport = false;
	j1Scene* scene_to_teleport = NULL;

	//Skills
	Skill* left_skill = NULL;
	Skill* right_skill = NULL;
	Skill* current_skill = NULL;

	//Those skills
	sklBasicAttack* basic_attack = NULL;
	sklBloodArrow* blood_arrow = NULL;

	//Collider
	Collider* p_collider;

};

#endif // __j1PLAYER_H__

