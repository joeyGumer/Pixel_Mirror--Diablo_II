#include "snLose.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Timer.h"
#include "j1Textures.h"
#include "j1SceneManager.h"
#include "j1FileSystem.h"
#include "snIntro.h"


// Constructor
snLose::snLose() :j1Scene(LOSE)
{}

// Destructor
snLose::~snLose()
{}

// Called before render is available
bool snLose::Awake(pugi::xml_node& conf)
{
	return true;
}

// Called the first frame
bool snLose::Start()
{
	if (App->fs->SaveFileExists())
	{
		App->fs->DeleteSaveFile();
	}

	//back = App->tex->Load("textures/win.jpg");
	loseback = App->gui->AddGuiImage({ 0, 0 }, { 3431, 82, 640, 480 }, NULL, this);
	lose_gui.push_back(loseback);
	ret.Start();
	return true;
}

// PreUpdate
bool snLose::PreUpdate()
{
	return true;
}

// Update
bool snLose::Update(float dt)
{
	//App->render->Blit(back, -225, 0, NULL);

	if (ret.ReadSec() > 5)
		App->sm->ChangeScene(App->sm->intro);
	return true;
}

// PostUpdate
bool snLose::PostUpdate()
{
	return true;
}

// Called before quitting
bool snLose::CleanUp()
{
	//App->tex->UnLoad(back);
	for (list<GuiElement*>::iterator item = lose_gui.begin(); item != lose_gui.end(); item++)
	{
		for (list<GuiElement*>::iterator item2 = App->gui->gui_elements.begin(); item2 != App->gui->gui_elements.end(); item2++)
		{
			if ((*item2) == (*item))
			{
				RELEASE(*item2);
				App->gui->gui_elements.erase(item2);
				break;
			}
		}
	}

	lose_gui.clear();


	//RELEASE(loseback);

	return true;
}

// Called on certain event
void snLose::OnEvent(GuiElement* element, GUI_Event even)
{

}


//Load/UnLoad, called when the scene changes
bool snLose::LoadScene()
{
	Start();
	return true;
}
bool snLose::UnLoad()
{
	CleanUp();
	return true;
}


