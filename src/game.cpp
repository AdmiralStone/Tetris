#include "game.hpp"
#include <random>
#include <iostream>

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("./Sounds/music.mp3");
    rotateSound = LoadSound("./Sounds/rotate.mp3");
    clearSound = LoadSound("./Sounds/clear.mp3");
    PlayMusicStream(music);
}

Game::~Game()
{
    CloseAudioDevice();
    UnloadMusicStream(music);

}

Block Game::GetRandomBlock()
{   
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin()+randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock()};
};

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11,11);
    
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255,290);
        break;
    case 4:
        nextBlock.Draw(255,280);
        break;
    default:
        nextBlock.Draw(270,270);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed !=0)
    {
        gameOver = false;
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0,1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    
    default:
        break;
    }

}

void Game::MoveBlockLeft()
{   
    if(!gameOver)
    {
        currentBlock.Move(0,-1);
        if(IsBlockOutside() || BlockFits()==false){
            currentBlock.Move(0,1);
        }
    }
    
}
void Game::MoveBlockRight()
{   
    if(!gameOver){
        currentBlock.Move(0,1);
        if(IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(0,-1);
        }
    }
}
void Game::MoveBlockDown()
{   
    if(!gameOver){
        currentBlock.Move(1,0);
        if(IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item:tiles)
    {
        if(grid.IsCellOutside(item.row,item.col))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    currentBlock.Rotate();
    if(IsBlockOutside()){
        currentBlock.UndoRotation();
    }else
    {
        PlaySound(rotateSound);
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }

    int rowsCleared = grid.ClearFullRows();
    if(rowsCleared > 0)
    {   
        UpdateScore(rowsCleared,0);
        PlaySound(clearSound);
    }
    
    currentBlock = nextBlock;

    if(BlockFits() == false)
    {
        gameOver = true;
    }

    nextBlock = GetRandomBlock();

}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item:tiles)
    {
        if(grid.IsCellEmpty(item.row,item.col) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score+=100;
        break;
    case 2:
        score+=200;
        break;
    case 3:
        score+=500;
        break;
    
    default:
        break;
    }
    score+=moveDownPoints;
}