#pragma once
#include "grid.hpp"
#include "blocks.cpp"

class Game{
    public:
        Game();
        ~Game();
        std::vector<Block> GetAllBlocks();
        void Draw();
        void HandleInput();
        void MoveBlockDown();
        bool gameOver;
        int score;
        Music music;

    private:
        Grid grid;
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        Sound rotateSound;
        Sound clearSound;
        Block GetRandomBlock();
        void MoveBlockLeft();
        void MoveBlockRight();
        bool IsBlockOutside();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void Reset();
        void UpdateScore(int linesCleared, int moveDownPoints);
        
};