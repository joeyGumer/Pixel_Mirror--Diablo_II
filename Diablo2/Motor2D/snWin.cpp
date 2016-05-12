#include "snWin.h"
#include "j1Render.h"
#include "j1App.h"
#include "j1Timer.h"
#include "j1Textures.h"
#include "j1SceneManager.h"
#include "snIntro.h"


	// Constructor
snWin::snWin()
{}

	// Destructor
snWin::~snWin()
{}

	// Called before render is available
bool snWin::Awake(pugi::xml_node& conf)
{
	return true;
}

	// Called the first frame
bool snWin::Start()
{
	
	//back = App->tex->Load("textures/win.jpg");
	winback = App->gui->AddGuiImage({ -80, -60 }, { 2630, 82, 800, 600 }, NULL, this);
	win_gui.push_back(winback);


	ret.Start();
	return true;
}

	// PreUpdate
bool snWin::PreUpdate()
{
	return true;
}

	// Update
bool snWin::Update(float dt)
{
	//App->render->Blit(back, -225, 0, NULL);

	if (ret.ReadSec() > 5)
		App->sm->ChangeScene(App->sm->intro);
	return true;
}

	// PostUpdate
bool snWin::PostUpdate()
{
	return true;
}

	// Called before quitting
bool snWin::CleanUp()
{
	//App->tex->UnLoad(back);
	for (list<GuiElement*>::iterator item = win_gui.begin(); item != win_gui.end(); item++)
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

	win_gui.clear();

	return true;
}

	// Called on certain event
void snWin::OnEvent(GuiElement* element, GUI_Event even)
{
	
}


	//Load/UnLoad, called when the scene changes
bool snWin::Load()
{
	Start();
	return true;
}
bool snWin::UnLoad()
{
	CleanUp();
	return true;
}


