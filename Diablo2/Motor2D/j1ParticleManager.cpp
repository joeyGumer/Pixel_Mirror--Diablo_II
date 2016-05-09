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
			tmp._Ptr->_Myval->collider->to_delete = true;
			RELEASE((*tmp));
			tmp = particleList.erase(tmp);
		}
		else
		{
			++tmp;
		}
	}

	// TODO 2: Iterate the emisor list, if update returns false, delete the particle. 

	std::list<Emisor*>::iterator tmp2 = emisorList.begin();

	while (tmp2 != emisorList.end())
	{
		if ((*tmp2)->Update(dt) == false)
		{
			RELEASE((*tmp2));
			tmp2 = emisorList.erase(tmp2);
		}
		else
		{
			++tmp2;
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

	//TODO 2: Iterate the emisor list and call postUpdate 

	std::list<Emisor*>::iterator tmp2 = emisorList.begin();

	for (; tmp2 != emisorList.end(); ++tmp2)
	{
		(*tmp2)->PostUpdate();
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

	//TODO 2: Iterate the emisor list and clear, release the particle and clear the list.

	std::list<Emisor*>::iterator tmp2 = emisorList.begin();

	for (; tmp2 != emisorList.end(); ++tmp2)
		RELEASE((*tmp2));

	emisorList.clear();

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

bool j1ParticleManager::CleanActiveEmisors()
{
	std::list<Emisor*>::iterator tmp = emisorList.begin();

	for (; tmp != emisorList.end(); ++tmp)
		RELEASE((*tmp));

	emisorList.clear();

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
	part->collider_margin = p.collider_margin;
	part->timer.Start();

	SDL_Rect collider_pos;
	collider_pos.x = part->position.x + part->collider_margin.x;
	collider_pos.y = part->position.y + part->collider_margin.y;
	collider_pos.w = part->anim.PeekCurrentFrame().w - part->collider_margin.x * 2;
	collider_pos.h = part->anim.PeekCurrentFrame().h - part->collider_margin.y * 2;
	part->collider = App->collision->AddCollider(collider_pos, COLLIDER_PARTICLE);

	//TODO 3: insert the particle in the particleList
	particleList.push_back(part);

	return part;
}

Emisor* j1ParticleManager::AddEmisor(Particle& p, int x, int y, float emisorDuration, Uint32 particleLife, int particleVelocity,
	float minAngle, float maxAngle, SDL_Texture* tex)  // If all particles are load at creation point
{
	Emisor* ret = NULL;

	ret = new Emisor(p);
	ret->position.x = x;
	ret->position.y = y;
	ret->duration = emisorDuration;
	ret->particleEmited.life = particleLife;
	ret->velocity = particleVelocity;
	ret->minAngle = minAngle;
	ret->maxAngle = maxAngle;
	ret->particleEmited.image = tex;

	ret->timer->Start();
	ret->active = ret->alive = true;

	//TODO 3: insert the emisor in the emisorLists
	emisorList.push_back(ret);

	return ret;
}

FireEmisor* j1ParticleManager::AddFire(int x, int y, float duration)
{
	FireEmisor* ret = NULL;

	ret = new FireEmisor(duration);
	ret->position.x = x;
	ret->position.y = y;

	ret->timer->Start();
	ret->active = ret->alive = true;

	//TODO 3: insert the emisor in the emisorList
	emisorList.push_back(ret);

	return ret;
}

BurstEmisor* j1ParticleManager::AddBurst(int x, int y)
{
	BurstEmisor* ret = NULL;

	ret = new BurstEmisor();
	ret->position.x = x;
	ret->position.y = y;

	ret->timer->Start();
	ret->active = ret->alive = true;

	//TODO 3: insert the emisor in the emisorList
	emisorList.push_back(ret);

	return ret;
}
//-----------------------------------------

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
			collider->rect.x = position.x + collider_margin.x;
			collider->rect.y = position.y + collider_margin.y;
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
			SDL_Rect sect = anim.GetCurrentFrame();
			App->render->Blit(image, position.x, position.y, &sect);
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
}
//-----------------------------------------------------

// EMISOR----------------------------------------------

Emisor::Emisor()
{
	position.SetToZero();
	speed.SetToZero();
	active = alive = fxPlayed = false;
}

Emisor::Emisor(Particle& p)
{
	particleEmited = p;
	fx = p.fx;
	position.SetToZero();
	speed.SetToZero();
	fxPlayed = false;
}

Emisor::~Emisor()
{

}

bool Emisor::Update(float dt) // If particles are created each frame
{
	bool ret = true;

	// TODO 4: if timer is bigger than the life of the emisor OR emisor isn't alive, then return false
	if (timer->Read() >= duration * 1000 || alive == false)
	{
		ret = false;
	}

	if (alive && active)
	{
		// TODO 5: Create a new particle with the particleEmited info and set his speed with method setSpeed
		Particle* q = App->pm->AddParticle(particleEmited, position.x, position.y, particleEmited.life);
		q->SetSpeed(velocity, minAngle, maxAngle);

		position.x += speed.x * dt / 1000;
		position.y += speed.y * dt / 1000;
	}

	return ret;
}

bool Emisor::PostUpdate()
{
	if (alive)
	{
		if (fxPlayed == false)
		{
			fxPlayed = true;
			App->audio->PlayFx(fx);
		}
	}

	return true;
}

void Emisor::SetParticle(Particle& particle)
{
	particleEmited = particle;
}

void Emisor::Enable()
{
	active = true;
	timer->Start();
}

void Emisor::Disable()
{
	active = false;
}

void Emisor::Destroy()
{
	alive = false;
}
//---------------------------------------------------------

// FIRE EMISOR---------------------------------------------
FireEmisor::FireEmisor(float time) : Emisor()
{
	duration = time;

	pugi::xml_node fire1 = App->pm->particle_file.child("particles").child("fire1");

	int fireX = fire1.child("fire_anim").attribute("x").as_int();
	int fireY = fire1.child("fire_anim").attribute("y").as_int();
	int fireW = fire1.child("fire_anim").attribute("w").as_int();
	int fireH = fire1.child("fire_anim").attribute("h").as_int();
	int fireFPR = fire1.child("fire_anim").attribute("frames_per_row").as_int();
	int fireFPC = fire1.child("fire_anim").attribute("frames_per_column").as_int();
	int fireFrames = fire1.child("fire_anim").attribute("frame_number").as_int();
	float fireAnimSpeed = fire1.child("fire_anim").attribute("speed").as_float();
	bool fireLoop = fire1.child("fire_anim").attribute("loop").as_bool();
	float fireSpeedX = fire1.child("fire_speed").attribute("x").as_float();
	float fireSpeedY = fire1.child("fire_speed").attribute("y").as_float();
	const char* firePath = fire1.child("fire_file").attribute("value").as_string();

	//PARTICLE_NOTE: Adapt to our code
	for (int i = 0; i < fireFPC; i++)
	{
		fire.anim.SetFrames(fireX, fireY, fireW, fireH, fireFPR);
	}
	fire.anim.speed = fireAnimSpeed;
	fire.anim.loop = fireLoop;
	fire.speed.x = fireSpeedX;
	fire.speed.y = fireSpeedY;
	fire.image = App->tex->Load(firePath);
	fire.life = duration;

	int smokeX = fire1.child("smoke_anim").attribute("x").as_int();
	int smokeY = fire1.child("smoke_anim").attribute("y").as_int();
	int smokeW = fire1.child("smoke_anim").attribute("w").as_int();
	int smokeH = fire1.child("smoke_anim").attribute("h").as_int();
	int smokeFPR = fire1.child("smoke_anim").attribute("frames_per_row").as_int();
	int smokeFPC = fire1.child("smoke_anim").attribute("frames_per_column").as_int();
	int smokeFrames = fire1.child("smoke_anim").attribute("frame_number").as_int();
	float smokeAnimSpeed = fire1.child("smoke_anim").attribute("speed").as_float();
	bool smokeLoop = fire1.child("smoke_anim").attribute("loop").as_bool();
	float smokeSpeedX = fire1.child("smoke_speed").attribute("x").as_float();
	float smokeSpeedY = fire1.child("smoke_speed").attribute("y").as_float();
	float smokeFreq = fire1.child("smoke_frequence").attribute("value").as_float();
	float smokeStart = fire1.child("smoke_start").attribute("value").as_float();
	int smokeOffsetX = fire1.child("smoke_offset").attribute("x").as_int();
	int smokeOffsetY = fire1.child("smoke_offset").attribute("y").as_int();
	float smokeLife = fire1.child("smoke_life").attribute("value").as_float();
	const char* smokePath = fire1.child("smoke_file").attribute("value").as_string();

	//PARTICLE_NOTE: Adapt to our code
	for (int i = 0; i < smokeFPC; i++)
	{
		smoke.anim.SetFrames(smokeX, smokeY, smokeW, smokeH, smokeFPR);
	}
	smoke.anim.speed = smokeAnimSpeed;
	smoke.anim.loop = smokeLoop;
	smoke.speed.x = smokeSpeedX;
	smoke.speed.y = smokeSpeedY;
	smokeFrequence = smokeFreq;
	smokeStart = smokeStart;
	smokeOffset.x = smokeOffsetX;
	smokeOffset.y = smokeOffsetY;
	smoke.image = App->tex->Load(smokePath);
	smoke.life = smokeLife;
}

FireEmisor::~FireEmisor()
{

}

bool FireEmisor::Update(float dt)
{
	bool ret = true;

	if (timer->Read() >= duration * 1000 || alive == false)
	{
		ret = false;
	}
	if (alive && active)
	{
		if (!fireStarted)
		{
			fireStarted = true;
			App->pm->AddParticle(fire, position.x, position.y, fire.life);
		}
		if (timer->Read() >= smokeStart * 1000)
		{
			if (acumulator >= smokeFrequence * 1000)
			{
				App->pm->AddParticle(smoke, position.x + smokeOffset.x, position.y + smokeOffset.y, smoke.life);
				acumulator = 0.0f;
			}
			acumulator += dt;
		}

		position.x += speed.x * dt / 1000;
		position.y += speed.y * dt / 1000;
	}


	return ret;
}

bool FireEmisor::PostUpdate()
{
	bool ret = true;

	if (alive && active)
	{
		if (!fxPlayed)
		{
			fxPlayed = true;
			App->audio->PlayFx(fx);
		}
	}

	return ret;
}
//---------------------------------------------------

//BURST EMISOR---------------------------------------
BurstEmisor::BurstEmisor() : Emisor()
{

	pugi::xml_node burst1 = App->pm->particle_file.child("particles").child("burst");

	int burstX = burst1.child("burst_anim").attribute("x").as_int();
	int burstY = burst1.child("burst_anim").attribute("y").as_int();
	int burstW = burst1.child("burst_anim").attribute("w").as_int();
	int burstH = burst1.child("burst_anim").attribute("h").as_int();
	int burstFPR = burst1.child("burst_anim").attribute("frames_per_row").as_int();
	int burstFPC = burst1.child("burst_anim").attribute("frames_per_column").as_int();
	int burstFrames = burst1.child("burst_anim").attribute("frame_number").as_int();
	float burstAnimSpeed = burst1.child("burst_anim").attribute("speed").as_float();
	bool burstLoop = burst1.child("burst_anim").attribute("loop").as_bool();
	float burstSpeedX = burst1.child("burst_speed").attribute("x").as_float();
	float burstSpeedY = burst1.child("burst_speed").attribute("y").as_float();
	const char* burstPath = burst1.child("burst_file").attribute("value").as_string();
	int burstLife = burst1.child("burst_life").attribute("value").as_int();
	float emisor_duration = burst1.child("emisor_duration").attribute("value").as_float();
	float emisor_velocity = burst1.child("emisor_velocity").attribute("value").as_float();
	float min_angle = burst1.child("min_angle").attribute("value").as_float();
	float max_angle = burst1.child("max_angle").attribute("value").as_float();

	//PARTICLE_NOTE: Adapt to our code
	for (int i = 0; i < burstFPC; i++)
	{
		burst.anim.SetFrames(burstX, burstY, burstW, burstH, burstFPR);
	}
	//burst.anim.SetFrames(burstX, burstY, burstW, burstH, burstFPR, burstFPC, burstFrames);
	burst.anim.speed = burstAnimSpeed;
	burst.anim.loop = burstLoop;
	burst.SetSpeed(burstSpeedX, burstSpeedY);
	burst.image = App->tex->Load(burstPath);
	burst.life = burstLife;
	emisor_burst.duration = emisor_duration;
	emisor_burst.velocity = emisor_velocity;
	emisor_burst.minAngle = min_angle;
	emisor_burst.maxAngle = max_angle;

}

BurstEmisor::~BurstEmisor()
{

}

bool BurstEmisor::Update(float dt)
{
	bool ret = true;

	if (timer->Read() >= duration * 1000 || alive == false)
	{
		ret = false;
	}
	if (alive && active)
	{
		if (!burstStarted)
		{
			burstStarted = true;
			App->pm->AddEmisor(burst, position.x, position.y, emisor_burst.duration, burst.life, emisor_burst.velocity, emisor_burst.minAngle, emisor_burst.maxAngle, burst.image);
		}
		position.x += speed.x * dt / 1000;
		position.y += speed.y * dt / 1000;
	}


	return ret;
}

bool BurstEmisor::PostUpdate()
{
	bool ret = true;

	if (alive && active)
	{
		if (!fxPlayed)
		{
			fxPlayed = true;
			App->audio->PlayFx(fx);
		}
	}

	return ret;
}

//----------------------------------------------------------------------