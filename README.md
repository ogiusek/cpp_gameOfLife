# Conways game of life
## What is game and how test this game ?
\
Game rules:
- Any live cell with fewer than two live neighbors dies, as if caused by underpopulation.
- Any live cell with two or three live neighbors lives on to the next generation.
- Any live cell with more than three live neighbors dies, as if by overpopulation.
- Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

### How to run game ?

run `npm start`\
or `g++ -g src/main.cpp -o dist/program -lSDL2 -lSDL2_ttf -lSDL2_image -O3 -ffast-math && echo 'compiled' && dist/program`

### How to play this game ?

![mouse image](https://image.benq.com/is/image/benqco/1-1?$ResponsivePreset$)

Use mouse button 1 to move or wasd\
Use 2 mouse button add and remove cells\
Use 3 mouse button to scroll in and out\
\
Use r to restart board\
Use space to start and stop\

## Authors

- [@ogiusek](https://www.github.com/ogiusek)

