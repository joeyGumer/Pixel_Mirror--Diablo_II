#include "j1ParticleManager.h"
#include "j1App.h"
#include <math.h>
#include <time.h>
#include "j1Textures.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Timer.h"
#include "j1Audio.h"
#include "j1Collision.h"

// PARTICLE MANAGER---------------

j1ParticleManager::j1ParticleManager() : j1Module()
{

}

j1ParticleManager::~j1ParticleManager()
{
	name.create("particle_manager");
}

bool j1ParticleManager::Awake(pugi::xml_node &node)
{
	LOG("Particle Manager: Awake");
	textureFile.assign(node.child("particle_manager").first_attribute().as_string());
	std::srand(time(NULL));

	return true;
}

bool j1ParticleManager::Start()
{
	bool ret = true;
	LOG("Particle Manager: Start");
	texture = App->tex->Load(textureFile.c_str());

	ret = LoadParticlesFile(particle_file);

	return ret;
}

bool j1ParticleManager::Update(float dt)
{
	bool ret = true;

	// TODO 2: Iterate the particles list, if update returns false, delete the particle. 

	std::list<Particle*>::iterator tmp = particleList.begin();

	while (tmp != particleList.end())
	{
		if ((*tmp)->Update(dt) == false)
		{
			if (tmp._Ptr->_Myval->collider != NULL)
			{
				tmp._Ptr->_Myval->collider->to_delete = true;
			}

			if (tmp._Ptr->_Myval->sprite != NULL)
			{
				App->render->sprites.remove(tmp._Ptr->_Myval->sprite);
				RELEASE(tmp._Ptr->_Myval->sprite);
			}

			RELEASE((*tmp));
			tmp = particleList.erase(tmp);
		}
		else
		{
			++tmp;
		}
	}

	return ret;
}

bool j1ParticleManager::PostUpdate()
{
	bool ret = true;

	//TODO 2: Iterate the particle list and call postUpdate

	std::list<Particle*>::reverse_iterator tmp = particleList.rbegin();

	for (; tmp != particleList.rend(); ++tmp)
	{
		(*tmp)->PostUpdate();
	}

	return ret;
}

bool j1ParticleManager::CleanUp()
{
	LOG("Particle Manager: CleanUp");
	App->tex->UnLoad(texture);

	//TODO 2: Iterate the particle list and clear, release the particle and clear the list.

	std::list<Particle*>::iterator tmp = particleList.begin();

	for (; tmp != particleList.end(); ++tmp)
		RELEASE((*tmp));

	particleList.clear();

	return true;
}

//TODO 2.1 : Uncomment when you finished TODO 2

bool j1ParticleManager::CleanActiveParticles()
{
	std::list<Particle*>::iterator tmp = particleList.begin();

	for (; tmp != particleList.end(); ++tmp)
		RELEASE((*tmp));

	particleList.clear();

	return true;
}

bool j1ParticleManager::LoadParticlesFile(pugi::xml_document& file)
{
	bool ret = true;

	char* buff;
	int size = App->fs->Load("particles/particles.xml", &buff);
	pugi::xml_parse_result result = file.load_buffer(buff, size);
	RELEASE(buff);

	if (result == NULL)
	{
		ret = false;
		LOG("Could not load particles xml file. Pugi error: %s", result.description());
	}

	return ret;
}

Particle* j1ParticleManager::AddParticle(const Particle& p, int x, int y, Uint32 secLife, SDL_Texture* texture, unsigned int sfx, uint32 delay)
{
	Particle* part = NULL;

	part = new Particle(p);
	part->position.x = x - p.anim.PeekCurrentFrame().w / 2;
	part->position.y = y - p.anim.PeekCurrentFrame().h / 2;
	part->initialPosition = p.position;
	part->alive = true;
	part->life = secLife;
	if (texture)
		part->image = texture;
	else
		part->image = p.image;

	part->fx = sfx;
	part->timer.Start();

	SDL_Rect collider_pos;
	collider_pos.x = part->position.x + part->collider_margin.x + part->collider_pivot.x;
	collider_pos.y = part->position.y + part->collider_margin.y + part->collider_pivot.y;
	collider_pos.w = part->anim.PeekCurrentFrame().w - part->collider_margin.x * 2;
	collider_pos.h = part->anim.PeekCurrentFrame().h - part->collider_margin.y * 2;
	if (part->type == PARTICLE_PLAYER_CAST)
	{
		part->collider = App->collision->AddCollider(collider_pos, COLLIDER_PLAYER_PARTICLE);
	}
	else if (part->type == PARTICLE_ENEMY_CAST)
	{
		part->collider = App->collision->AddCollider(collider_pos, COLLIDER_ENEMY_PARTICLE);
	}
	else
	{
		part->collider = App->collision->AddCollider(collider_pos, COLLIDER_NONE);
	}

	//Sprite creation
	SDL_Rect current_sprite = part->anim.GetCurrentFrame();

	iPoint pos;
	pos.x = part->position.x + part->collider_margin.x + part->collider_pivot.x + part->collider->rect.w / 2;
	pos.y = part->position.y + part->collider_margin.y + part->collider_pivot.y + part->collider->rect.h / 2;

	iPoint pivot;
	pivot.x = part->collider_margin.x + part->collider_pivot.x + part->collider->rect.w / 2;
	pivot.y = part->collider_margin.y + part->collider_pivot.y + part->collider->rect.h / 2;

	part->sprite = new Sprite(part->image, pos, pivot, current_sprite);
	App->render->AddSpriteToList(part->sprite);

	//TODO 3: insert the particle in the particleList
	particleList.push_back(part);

	return part;
}

// PARTICLE--------------------------------


Particle::Particle() : fx(0), life(0), fxPlayed(false), alive(false)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p)
{
	fx = p.fx;
	life = p.life;
	initialPosition = p.position;
	speed = p.speed;
	alive = p.alive;
	anim = p.anim;
	image = p.image;
	collider_margin = p.collider_margin;
	collider_pivot = p.collider_pivot;
	type = p.type;
	damage = p.damage;
	directions = p.directions;
	anim_vector = p.anim_vector;
}

Particle::~Particle()
{

}

void Particle::FollowPoint(int x, int y)
{
	position.x = x - anim.PeekCurrentFrame().w / 2;
	position.y = y - anim.PeekCurrentFrame().h / 2;
}

void Particle::DestroyParticle()
{
	alive = false;
}

bool Particle::Update(float dt)
{
	bool ret = true;

	if (life > 0)
	{
		// TODO 4: if timer is bigger than the life of the particle OR particle isn't alive, then return false
		if (timer.Read() >= life * 1000 || alive == false)
		{
			ret = false;
		}
	}
	else
	{
		if (anim.Finished() || alive == false)
			ret = false;
	}

	if (alive == true && active == true)
	{
		//NOTE: Changed, the original one didn't work as expected
		fPoint vel = speed * dt;

		position.x += vel.x;
		position.y += vel.y;

		if (collider)
		{
			collider->rect.x = position.x + collider_margin.x + collider_pivot.x;
			collider->rect.y = position.y + collider_margin.y + collider_pivot.y;
		}
	}

	return ret;
}
bool Particle::PostUpdate()
{
	if (alive && active)
	{
		if (image != NULL)
		{
			//TODO 5: Get animation frame and then blit. 

			SDL_Rect current_sprite = anim.GetCurrentFrame();

			iPoint pos;
			pos.x = position.x + collider_margin.x + collider_pivot.x + collider->rect.w / 2;
			pos.y = position.y + collider_margin.y + collider_pivot.y + collider->rect.h / 2;

			iPoint pivot;
			pivot.x = collider_margin.x + collider_pivot.x + collider->rect.w / 2;
			pivot.y = collider_margin.y + collider_pivot.y + collider->rect.h / 2;

			sprite->UpdateSprite(image, pos, pivot, current_sprite);

			//SDL_Rect sect = anim.GetCurrentFrame();
			//App->render->Blit(image, position.x, position.y, &sect);
		}

		if (fxPlayed == false)
		{
			fxPlayed = true;
			App->audio->PlayFx(fx);
		}
	}


	return true;
}

void Particle::Enable()
{
	active = true;
	timer.Start();
}

void Particle::Disable()
{
	active = false;
}

void Particle::SetSpeed(float velocity, float minAngle, float maxAngle)
{
	float angle = minAngle + (rand() % (int)(maxAngle - minAngle));
	speed.x = velocity * cos(angle * (PI / 180));
	speed.y = velocity * sin(angle * (PI / 180));
}

//NOTE: This wasn't in the original code
void Particle::SetPointSpeed(float velocity, fPoint target)
{
	fPoint _target;
	_target.x = target.x - anim.PeekCurrentFrame().w / 2;
	_target.y = target.y - anim.PeekCurrentFrame().h / 2;
	speed.x = _target.x - position.x;
	speed.y = _target.y - position.y;

	speed.SetModule(velocity);

	if (directions)
	{
		SetDirection(_target);
	}
}

void Particle::SetDirection(fPoint target)
{
	//NOTE: This has been created to change the direction without moving the player
	fPoint direction;
	direction.x = target.x - position.x;
	direction.y = target.y - position.y;

	direction.SetModule(1);

	float angle = direction.GetAngle();

	PARTICLE_DIRECTION dir;

	if (angle < 22.5 && angle > -22.5)
		dir = PARTICLE_DIR_RIGHT;
	else if (angle >= 22.5 && angle <= 67.5)
		dir = PARTICLE_DIR_UPRIGHT;
	else if (angle > 67.5 && angle < 112.5)
		dir = PARTICLE_DIR_UP;
	else if (angle >= 112.5 && angle <= 157.5)
		dir = PARTICLE_DIR_UPLEFT;
	else if (angle > 157.5 || angle < -157.5)
		dir = PARTICLE_DIR_LEFT;
	else if (angle >= -157.5 && angle <= -112.5)
		dir = PARTICLE_DIR_DOWNLEFT;
	else if (angle > -112.5 && angle < -67.5)
		dir = PARTICLE_DIR_DOWN;
	else if (angle >= -67.5 && angle <= -22.5)
		dir = PARTICLE_DIR_DOWNRIGHT;

	if (dir != current_direction)
	{
		current_direction = dir;
		anim = anim_vector[current_direction];
	}
}
//-----------------------------------------------------

