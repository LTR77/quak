#ifndef MAINMENU_H
#define MAINMENU_H
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>

class Map {
    public:
        float Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;

        Vector3 CubePos;

        BoundingBox CubeBoundingBox;
        BoundingBox GreenWall;
        BoundingBox RedWall;
        BoundingBox BlueWall;
        BoundingBox OrangeWall;

        std::vector<Vector3> positions;
        std::vector<BoundingBox> boundingBoxesers;

        Map() {
            CubePos = {10.0f, 0.0f, 0.0f};
            CubeBoundingBox = {(Vector3){CubePos.x - 2.5f, CubePos.y - 32.0f, CubePos.z - 2.5f}, (Vector3){CubePos.x + 2.5f, CubePos.y + 32.0f, CubePos.z + 2.5f}};
        }
        void GetAndAddPositions() {
            Pos1 = GetRandomValue(-64.0f, 64.0f);
            Pos2 = GetRandomValue(-64.0f, 64.0f);
            Pos3 = GetRandomValue(-64.0f, 64.0f);
            Pos4 = GetRandomValue(-64.0f, 64.0f);
            Pos5 = GetRandomValue(-64.0f, 64.0f);
            Pos6 = GetRandomValue(-64.0f, 64.0f);
            Pos7 = GetRandomValue(-64.0f, 64.0f);
            Pos8 = GetRandomValue(-64.0f, 64.0f);

            positions.push_back({Pos1, 2.0f, Pos2});
            positions.push_back({Pos2, 4.0f, Pos1});
            positions.push_back({Pos3, 1.0f, Pos2});
            positions.push_back({Pos2, 8.0f, Pos3});
            positions.push_back({Pos4, 3.0f, Pos3});
            positions.push_back({Pos3, 9.0f, Pos4});
            positions.push_back({Pos4, 4.8f, Pos3});
            positions.push_back({Pos5, 2.2f, Pos4});
            positions.push_back({Pos4, 8.3f, Pos5});
            positions.push_back({Pos6, 4.3f, Pos5});
            positions.push_back({Pos5, 6.6f, Pos6});
            positions.push_back({Pos7, 5.8f, Pos6});
            positions.push_back({Pos6, 1.1f, Pos7});
            positions.push_back({Pos8, 7.9f, Pos7});
            positions.push_back({Pos7, 5.4f, Pos8});
            positions.push_back({Pos7, 3.2f, Pos4});
            positions.push_back({Pos6, 8.2f, Pos2});
            positions.push_back({Pos7, 5.4f, Pos3});
            positions.push_back({Pos2, 3.2f, Pos5});
            positions.push_back({Pos6, 8.2f, Pos2});
            positions.push_back({Pos2, 2.7f, Pos7});
        }
        void CreateBounds() {
            boundingBoxesers.clear();
            for(size_t i = 0;i<positions.size();i++) {
                Vector3 pos = positions[i];
                Vector3 min = {pos.x - 2.5f, pos.y - 10.0f, pos.z - 2.5f};
                Vector3 max = {pos.x + 2.5f, pos.y + 10.0f, pos.z + 2.5f};
                BoundingBox boxerd = {min, max};
                boundingBoxesers.push_back(boxerd);
            }
            GreenWall = {(Vector3){64.0f - 5.0f, 2.0f - 22.5f, 0.0f - 64.0f}, (Vector3){64.0f + 5.0f, 2.0f + 22.5f, 0.0f + 64.0f}};
            BlueWall = {(Vector3){-69.0f - 5.0f, 2.0f - 22.5f, 0.0f - 64.0f}, (Vector3){-64.0f + 5.0f, 2.0f + 22.5f, 0.0f + 64.0f}};
            OrangeWall = {(Vector3){0.0f - 64.0f, 2.0f - 22.5f, 64.0f - 5.0f}, (Vector3){0.0f + 64.0f, 2.0f + 22.5f, 64.0f + 5.0f}};
            RedWall = {(Vector3){0.0f - 64.0f, 2.0f - 22.5f, -64.0f - 5.0f}, (Vector3){0.0f + 64.0f, 2.0f + 22.5f, -64.0f + 5.0f}};
        }
        void Draw() {
            for(auto& obj : positions) {
                DrawCube(obj, 5.0f, 20.0f, 5.0f, DARKBLUE);
            }
            for(size_t i = 0;i<positions.size();i++) {
                DrawBoundingBox(boundingBoxesers[i], RED);
            }
            // Walls
            DrawCube((Vector3){64.0f, 2.0f, 0.0f}, 10.0f, 45.0f, 128.0f, DARKGREEN);
            DrawCube((Vector3){-64.0f, 2.0f, 0.0f,}, 10.0f, 45.0f, 128.0f, BLUE);
            DrawCube((Vector3){0.0f, 2.0f, 64.0f}, 128.0f, 45.0f, 10.0f, ORANGE);
            DrawCube((Vector3){0.0f, 2.0f, -64.0f}, 128.0f, 45.0f, 10.0f, RED);
            DrawBoundingBox(GreenWall, RED);
            // SpawnCube
            DrawCube(CubePos, 5.0f, 64.0f, 5.0f, DARKBLUE);
            DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){128.0f, 128.0f}, LIGHTGRAY);
        }
};


#endif