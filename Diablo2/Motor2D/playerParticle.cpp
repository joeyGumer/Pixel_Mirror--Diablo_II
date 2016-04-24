#include "playerParticle.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Player.h"
#include "j1Game.h"

//NOTE: Everything is for testing purposes, must be changed

playerParticle::playerParticle()
{
	
}

playerParticle::playerParticle(fPoint init, fPoint end)
{
	particle_rect.x = init.x;
	particle_rect.y = init.y;
	particle_rect.w = 5;
	particle_rect.h = 5;

	destination.x = end.x;
	destination.y = end.y;

	speed = 5;

	SetInitVelocity();
}

playerParticle::~playerParticle()
{

}

bool playerParticle::Update(float dt)
{
	particle_rect.x += velocity.x;
	particle_rect.y += velocity.y;
	Draw();

	return true;
}

void playerParticle::Draw()
{
	App->render->DrawQuad(particle_rect, 255, 0, 0, 255, true, true);
}

void playerParticle::SetInitVelocity()
{
	iPoint target = App->input->GetMouseWorldPosition();

	velocity.x = target.x - particle_rect.x;
	velocity.y = target.y - particle_rect.y;

	velocity.SetModule(speed);
}



