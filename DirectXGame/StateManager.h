#pragma once
#include <string>
#include <unordered_map>
#include <vector>



class StateManager
{
public:
	typedef std::string String;
	enum StateType { DEFAULT = 0, PLAY = 1, PAUSE = 2 };
	//typedef std::unordered_map<String, PhysicsComponent*> ComponentTable;
	//typedef std::vector<PhysicsComponent*> ComponentList;

	
public:
	StateType getStateType();
	StateType setStateType(StateType state);
	static StateManager* getInstance();
	static void initialize();

	StateManager(StateManager const&) = delete;
	StateManager& operator=(StateManager const&) = delete;
	StateManager(StateManager&& other) noexcept = delete;
	StateManager& operator=(StateManager&& other) noexcept = delete;


private:
	StateType currentState;
	explicit StateManager();
	~StateManager();
	static StateManager* sharedInstance;
	
};

