#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#include <iostream>
#include <vector>

const int screenWidth = 2000;
const int screenHeight = 1300;

bool IsJumping = false;
float JumpVelocity = 0.0f;
float gravity = -0.005f;
float JumpStrength = 0.3f;
int PauseCounter = 0;

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

class Game {
    public:
        Map map;
        Game() {
            std::cout << "Initialized main Game Class\n";
        }
        void Draw3D() {
            map.Draw();
        }
        void Draw() {
            DrawFPS(10, 10);
            DrawText("quak (TEST)d", 1800, 10, 30, WHITE);
            DrawCircle(screenWidth/2, screenHeight/2, 3, WHITE);
        }
        void Setup() {
            map.GetAndAddPositions();
        }
}; 

int main() {
    InitWindow(screenWidth, screenHeight, "3d Test");
    std::cout << "If the Jump snaps your camera down just wait a few seconds the game is still calculating gravity\n";

    Model gun = LoadModel("resources/low-poly_sig_p365_xl.glb");

    // Camera
    Camera camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 2.0f};
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Camera3D gunCamera = {0};
    gunCamera.position = (Vector3){0.0f, 0.0f, 0.0f}; 
    gunCamera.target = (Vector3){0.0f, 0.0f, 1.0f};   
    gunCamera.up = (Vector3){0.0f, 1.0f, 0.0f};
    gunCamera.fovy = 90.0f;
    gunCamera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();

    SetTargetFPS(90);

    Game game;
    game.Setup();        
    game.map.CreateBounds(); 
    while(!WindowShouldClose()) {
        // upd Camera
        Vector3 PreviousCameraPosition = camera.position;
        UpdateCameraPro(&camera,
            (Vector3){
                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.3f -
                (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.3f,    
                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.3f -
                (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.3f,
                0.0f                                              
            },
            (Vector3){
                GetMouseDelta().x*0.07f,                          
                GetMouseDelta().y*0.07f,                          
                0.0f                                                
            },
            GetMouseWheelMove()*2.0f);                    
        // Camera Positions
        static Vector3 CameraSize = {1.0f, 2.0f, 1.0f};
        BoundingBox CameraBoundingBox = {(Vector3){camera.position.x - CameraSize.x/2, camera.position.y - CameraSize.y/2, camera.position.z - CameraSize.z/2}, (Vector3){camera.position.x + CameraSize.x/2, camera.position.y + CameraSize.y/2, camera.position.z + CameraSize.z/2}};

        // Features
            // Jump
            if(IsKeyPressed(KEY_SPACE) && !IsJumping) {
                IsJumping = true;
                JumpVelocity = JumpStrength;
            } 
            if(IsKeyPressed(KEY_C)) {
                IsJumping = true;
                JumpVelocity = JumpStrength;
            }
            if(IsJumping) {
                camera.position.y += JumpVelocity;
                camera.target.y += JumpVelocity;
                JumpVelocity += gravity;
                if(camera.position.y < 2.0f) {
                    camera.position.y = 2.0f;
                    IsJumping = false;
                }
            }
            if(IsKeyPressed(KEY_R)) {
                camera.position = (Vector3){0.0f, 2.0f, 4.0f};
            }
            // Shoot
            Ray LookRay = GetScreenToWorldRay((Vector2){screenWidth/2, screenHeight/2}, camera);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                RayCollision GunCollision = GetRayCollisionBox(LookRay, game.map.CubeBoundingBox);
                if(GunCollision.hit) {
                    std::cout << "pressded left mosue btn!\n";
                }
            }
            // Pause
            if(IsKeyPressed(KEY_P)) {
                if(PauseCounter == 0) {
                    EnableCursor();
                    PauseCounter++;
                }
                else {
                    DisableCursor();
                    PauseCounter = 0;
                }
            }

        // Check Collisions
        if(CheckCollisionBoxes(CameraBoundingBox, game.map.CubeBoundingBox)) {
            camera.position = PreviousCameraPosition;
        }        

        for(auto& Box : game.map.boundingBoxesers) {
            if(CheckCollisionBoxes(CameraBoundingBox, Box)) {
                camera.position = PreviousCameraPosition;
            }
        }
        if(CheckCollisionBoxes(CameraBoundingBox, game.map.GreenWall) || CheckCollisionBoxes(CameraBoundingBox, game.map.BlueWall) || CheckCollisionBoxes(CameraBoundingBox, game.map.OrangeWall) || CheckCollisionBoxes(CameraBoundingBox, game.map.RedWall)) camera.position = PreviousCameraPosition;

            // Check If player fell of map
            if(camera.position.x >= 64.0f || camera.position.z >= 64.0f || camera.position.z <= -64.0f || camera.position.y <= -64.0f) {
                camera.position.y -= 0.3f;
            }
            if(camera.position.y <= -64.0f) {
                camera.position.y = 4.0f;
                camera.position = (Vector3){0.0f, 2.0f, 4.0f};
            }
            
        // Draw      
        BeginDrawing();
        ClearBackground(SKYBLUE);
            BeginMode3D(camera);
                game.Draw3D();
           EndMode3D();
           BeginMode3D(gunCamera);
                Vector3 GunPos = (Vector3){-0.15f, -0.2f, 0.5f};
                DrawModelEx(gun, GunPos, (Vector3){0.0f, 1.0f, 0.0f}, -95.0f, (Vector3){0.08f, 0.08f, 0.08f}, WHITE);
            EndMode3D();
        game.Draw();
        EndDrawing();
    }
    UnloadModel(gun);
    CloseWindow();
    return 0;
}
