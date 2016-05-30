#ifndef _HUDSTATS_H_
#define _HUDSTATS_H_

#include "hudElement.h"

class j1HUD;
class GuiElement;
class GuiImage;
class GuiLabel;

class hudStats : public hudElement
{
public:
	//Constructor
	hudStats();

	//Destructor
	~hudStats();

	//Called before fist frame
	bool Start();

	//Called before each loop iteration
	bool PreUpdate();

	//Called each frame
	bool Update(float dt);

	//Called after each loop iteration
	bool PostUpdate();

	//Called before quitting
	bool CleanUp();

	//Called when there's a gui event
	void OnEvent(GuiElement* element, GUI_Event even);


	//Utils
	void Activate();

	void SetBloodLabel(int blood);
	void SetStrengthLabel(int strenght);
	void SetDexterityLabel(int dexterity);
	void SetVitalityLabel(int vitality);
	void SetIntelligenceLabel(int intelligence);
	void SetLuckLabel(int luck);
	void SetLifeLabel(int current, int max);
	void SetStaminaLabel(int current, int max);
	void SetBasicAttackLabel(int basicAttack);
	void SetResistenceLabel(int resistence);

public:

	bool closebutton_pressed = false;

	//Images
	GuiImage* closebutton = NULL;
	GuiImage* window = NULL;
	GuiImage* name = NULL;
	GuiImage* experience = NULL;
	GuiImage* strength = NULL;
	GuiImage* strength_value = NULL;
	GuiImage* dexterity = NULL;
	GuiImage* dexterity_value = NULL;
	GuiImage* vitality = NULL;
	GuiImage* vitality_value = NULL;
	GuiImage* intelligence = NULL;
	GuiImage* intelligence_value = NULL;
	GuiImage* luck = NULL;
	GuiImage* luck_value = NULL;
	GuiImage* life = NULL;
	GuiImage* life_1 = NULL;
	GuiImage* life_2 = NULL;
	GuiImage* stamina = NULL;
	GuiImage* stamina_1 = NULL;
	GuiImage* stamina_2 = NULL;
	GuiImage* basicAttack = NULL;
	GuiImage* basicAttack_value = NULL;
	GuiImage* resistance = NULL;
	GuiImage* resistance_value = NULL;
	
	GuiLabel* player_name = NULL;
	GuiLabel* life_max = NULL;
	GuiLabel* life_name = NULL;
	GuiLabel* stamina_name = NULL;
	GuiLabel* current_life = NULL;
	GuiLabel* current_stamina = NULL;
	GuiLabel* stamina_max = NULL;
	GuiLabel* player_experience = NULL;
	GuiLabel* player_strength = NULL;
	GuiLabel* player_strength_name = NULL;
	GuiLabel* player_vitality = NULL;
	GuiLabel* player_vitality_name = NULL;
	GuiLabel* player_dexterity = NULL;
	GuiLabel* player_dexterity_name = NULL;
	GuiLabel* player_intelligence = NULL;
	GuiLabel* player_intelligence_name = NULL;
	GuiLabel* player_luck = NULL;
	GuiLabel* player_luck_name = NULL;
	GuiLabel* basicAttack_name = NULL;
	GuiLabel* player_basicAttack = NULL;
	GuiLabel* resistance_name = NULL;
	GuiLabel* player_resistance = NULL;

	p2SString text;
	vector<GuiText*> texts;
};


#endif _HUDSTATS_H_