#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include <vector>
#include <string>
#include "Cube.h"

class CubeManager {
public:
    // Get the singleton instance
    static CubeManager& GetInstance() {
        static CubeManager instance;
        return instance;
    }

    // Add a game object
    void AddCube(Cube* cube) {
        cube_list.push_back(cube);
    }

    // Remove a game object
    void RemoveCube(Cube* cube) {
        cube_list.erase(
            std::remove(cube_list.begin(), cube_list.end(), cube),
            cube_list.end()
        );
    }
    
    void SetSelectedCube(Cube* cube) {
        this->selectedCube = cube;
    }

    Cube* GetSelectedCube() {
        return this->selectedCube;
    }

    // Get the list of game objects
    const std::vector<Cube*>& GetCubeList() const {
        return cube_list;
    }

private:
    std::vector<Cube*> cube_list;
    Cube* selectedCube = nullptr;

    CubeManager() = default;

    // Disable copy and assignment
    CubeManager(const CubeManager&) = delete;
    CubeManager& operator=(const CubeManager&) = delete;

};

#endif // GAME_OBJECT_MANAGER_H