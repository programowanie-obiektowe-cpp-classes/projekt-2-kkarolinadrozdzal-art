#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "Snake.h"
#include "Food.h"
#include "Zmienne.h"

class Game {
public:
    Game() {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Snake",OKNO_SZEROKOSC, OKNO_WYSOKOSC, 0);
        renderer = SDL_CreateRenderer(window, nullptr);
    }

    ~Game() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void run() {
        while (running) {
            events();
            update();
            render();
            SDL_Delay(SNAKE_DELAY);
        }
    }

private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    bool running= true;
    int score=0;

    Snake snake;
    Food food;

    void events() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

        const bool* keys = SDL_GetKeyboardState(nullptr);
        if (keys[SDL_SCANCODE_ESCAPE])
            running = false;

        snake.move(keys);
    }

    void update() {
        if (collision(snake.head(), food.apple())) {
            food.respawn();
            snake.grow();
            score++;
            SDL_SetWindowTitle(window,
                ("Punkty: " + std::to_string(score)).c_str());
        }

        if (snake.selfCollision()) {
            running = false;
        }
    }

    void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        snake.draw(renderer);
        food.draw(renderer);
        drawGrid();

        SDL_RenderPresent(renderer);
    }

    bool collision(const SDL_FRect& a, const SDL_FRect& b) const {
        return a.x == b.x && a.y == b.y;
    }

    void drawGrid() const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_FRect line{ 0,0,OKNO_SZEROKOSC,0 };
        for (line.y = 0; line.y <= OKNO_WYSOKOSC; line.y += KWADRAT)
            SDL_RenderRect(renderer, &line);

        line = { 0,0,0,OKNO_WYSOKOSC };
        for (line.x = 0; line.x <= OKNO_SZEROKOSC; line.x += KWADRAT)
            SDL_RenderRect(renderer, &line);
    }
};