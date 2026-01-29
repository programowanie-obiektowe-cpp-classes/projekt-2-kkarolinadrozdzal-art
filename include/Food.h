#pragma once
#include <cstdlib>
#include "Snake.h"

class Food {
    SDL_FRect body{};
public:
    Food() { respawn(); }

    void respawn() {
        body.x = (std::rand() % COL) * KWADRAT;
        body.y = (std::rand() % ROW) * KWADRAT;
        body.w = body.h = KWADRAT;
    }

    void draw(SDL_Renderer* r) const {
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255); // czerwony
        SDL_RenderFillRect(r, &body);
    }

    const SDL_FRect& apple() const { return body; }  
};