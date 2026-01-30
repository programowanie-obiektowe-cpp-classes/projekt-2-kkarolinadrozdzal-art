#pragma once
#include <vector>
#include <algorithm>
#include "Zmienne.h"

enum class Direction : unsigned char {
    UP, DOWN, LEFT, RIGHT
};

class Snake {
    std::vector<SDL_FRect> body;
    Direction dir{ Direction::RIGHT };
public:
    Snake() {
        body = {
            {10 * KWADRAT,10 * KWADRAT,KWADRAT,KWADRAT},
            { 9 * KWADRAT,10 * KWADRAT,KWADRAT,KWADRAT},
            { 8 * KWADRAT,10 * KWADRAT,KWADRAT,KWADRAT}
        };
    }

    void move(const bool* key) {
        if (key[SDL_SCANCODE_UP] && dir != Direction::DOWN)  dir = Direction::UP;
        if (key[SDL_SCANCODE_DOWN] && dir != Direction::UP)    dir = Direction::DOWN;
        if (key[SDL_SCANCODE_LEFT] && dir != Direction::RIGHT) dir = Direction::LEFT;
        if (key[SDL_SCANCODE_RIGHT] && dir != Direction::LEFT)  dir = Direction::RIGHT;

        std::copy_backward(body.begin(), body.end() - 1, body.end());

        switch (dir) {
        case Direction::UP:    body[0].y -= KWADRAT; break;
        case Direction::DOWN:  body[0].y += KWADRAT; break;
        case Direction::LEFT:  body[0].x -= KWADRAT; break;
        case Direction::RIGHT: body[0].x += KWADRAT; break;
        }

        sciany_nie_istnieja();
    }

    void draw(SDL_Renderer* r) const {
        SDL_SetRenderDrawColor(r, 0, 255, 0, 255); //glowa - jasny zielony
        SDL_RenderFillRect(r, &body[0]);

        SDL_SetRenderDrawColor(r, 0, 180, 0, 255); //cialo - ciemny zielony
        for (size_t i = 1; i < body.size(); ++i)
            SDL_RenderFillRect(r, &body[i]);
    }

    void grow() {
        body.push_back(body.back());
    }

    bool selfCollision() const {
        for (size_t i = 1; i < body.size(); ++i)
            if (body[0].x == body[i].x && body[0].y == body[i].y)
            {
                return true;
            }
        return false;
    }

    const SDL_FRect& head() const { return body[0]; }
    const std::vector<SDL_FRect>& getBody() const { return body; }

    void sciany_nie_istnieja() {
        if (body[0].x < 0) body[0].x = (COL - 1) * KWADRAT;
        if (body[0].x >= COL * KWADRAT) body[0].x = 0;
        if (body[0].y < 0) body[0].y = (ROW - 1) * KWADRAT;
        if (body[0].y >= ROW * KWADRAT) body[0].y = 0;
    }
};
