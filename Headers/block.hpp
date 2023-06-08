#pragma once
#include <vector>
#include <map>
#include "position.hpp"
#include "colors.hpp"

class Block{
    public:
        Block();
        int id;
        std::map<int,std::vector<Position>> cells;
        void Draw(int offsetX, int offsetY);
        void Move(int rows, int cols);

        std::vector<Position> GetCellPositions();
        void Rotate();
        void UndoRotation();


    private:
        int cellSize;
        int rotationState;
        std::vector<Color> colors;
        int rowOffset;
        int colOffset;
};