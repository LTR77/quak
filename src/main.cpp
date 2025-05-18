#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#include <iostream>
#include <vector>
#include <string>
#include "Map.h"

Vector3 PreviousCameraPosition;

const int screenWidth = 2000;
const int screenHeight = 1300;

bool IsJumping = false;
float JumpVelocity = 0.0f;
double gravity = -0.005d;
float JumpStrength = 0.3f;
int PauseCounter = 0;

class Game {
    public:
        Camera3D gunCamera;
        Camera3D camera;
        BoundingBox CameraBoundingBox;
        Map map;
        Game() {
            std::cout << "Initialized main Game Class\n";

            // Camera
            camera = {0};
            camera.position = (Vector3){0.0f, 2.0f, 2.0f};
            camera.target = (Vector3){0.0f, 2.0f, 0.0f};
            camera.up = (Vector3){0.0f, 1.0f, 0.0f};
            camera.fovy = 90.0f;
            camera.projection = CAMERA_PERSPECTIVE;

            gunCamera = {0};
            gunCamera.position = (Vector3){0.0f, 0.0f, 0.0f}; 
            gunCamera.target = (Vector3){0.0f, 0.0f, 1.0f};   
            gunCamera.up = (Vector3){0.0f, 1.0f, 0.0f};
            gunCamera.fovy = 90.0f;
            gunCamera.projection = CAMERA_PERSPECTIVE;
        }
        void SetupCameraPositions() {
            // Camera Positions
            static Vector3 CameraSize = {1.0f, 2.0f, 1.0f};
            CameraBoundingBox = {(Vector3){camera.position.x - CameraSize.x/2, camera.position.y - CameraSize.y/2, camera.position.z - CameraSize.z/2}, (Vector3){camera.position.x + CameraSize.x/2, camera.position.y + CameraSize.y/2, camera.position.z + CameraSize.z/2}};
        }
        void Draw3D() {
            map.Draw();
        }
        void Draw() {
            DrawFPS(10, 10);
            DrawText("quak 0.0.2 (TEST 2)", 900, 10, 30, WHITE);
            DrawCircle(screenWidth/2, screenHeight/2, 3, WHITE);
        }
        void Setup() {
            map.GetAndAddPositions();
        }
        void CheckFellOffMap() {
            // Check If player fell of map
            if(camera.position.x >= 64.0f || camera.position.z >= 64.0f || camera.position.z <= -64.0f || camera.position.y <= -64.0f) {
                camera.position.y -= 0.3f;
            }
            if(camera.position.y <= -64.0f) {
                camera.position.y = 4.0f;
                camera.position = (Vector3){0.0f, 2.0f, 4.0f};
            }
        }
}; 

int main(int argc, char* argv[]) {
    bool debug = false;
    for(int i = 0;i<argc;++i) {
        if(std::string(argv[i]) == "-debug") {
            debug = true;
        }
    }

    InitWindow(screenWidth, screenHeight, "3d Test");
    std::cout << "If the Jump snaps your camera down just wait a fy\n";

    Model gun = LoadModel("resources/low-poly_sig_p365_xl.glb");
    Model Speed = LoadModel("resources/SpeedBubble.glb");

    InitAudioDevice();
    Sound GunShot = LoadSound("resources/fixed_gunshot.wav");

    DisableCursor();

    SetTargetFPS(90);

    Game game;
    game.Setup();        
    game.map.CreateBounds(); 
    while(!WindowShouldClose()) {
        // upd Camera
        PreviousCameraPosition = game.camera.position;

        UpdateCameraPro(&game.camera,
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
        game.SetupCameraPositions();
        if(debug == true) {
            std::cout << PreviousCameraPosition.x << " x," << PreviousCameraPosition.y << " y," << PreviousCameraPosition.z << " z," <<  std::endl;
        }

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
                game.camera.position.y += JumpVelocity;
                game.camera.target.y += JumpVelocity;
                JumpVelocity += gravity;
                if(game.camera.position.y < 2.0f) {
                    game.camera.position.y = 2.0f;
                    IsJumping = false;
                }
            }
            if(IsKeyPressed(KEY_R)) {
                game.camera.position = (Vector3){0.0f, 2.0f, 4.0f};
            }
            // Shoot
            Ray LookRay = GetScreenToWorldRay((Vector2){screenWidth/2, screenHeight/2}, game.camera);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                PlaySound(GunShot);
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
            if(CheckCollisionBoxes(game.CameraBoundingBox, game.map.CubeBoundingBox)) {
                game.camera.position = PreviousCameraPosition;
            }

            for(auto& Box : game.map.boundingBoxesers) {
                if(CheckCollisionBoxes(game.CameraBoundingBox, Box)) {
                    game.camera.position = PreviousCameraPosition;
                }
            }
            if(CheckCollisionBoxes(game.CameraBoundingBox, game.map.GreenWall) || CheckCollisionBoxes(game.CameraBoundingBox, game.map.BlueWall) || CheckCollisionBoxes(game.CameraBoundingBox, game.map.OrangeWall) || CheckCollisionBoxes(game.CameraBoundingBox, game.map.RedWall)) game.camera.position = PreviousCameraPosition;

        // Draw      
        BeginDrawing();
        ClearBackground(SKYBLUE);
            BeginMode3D(game.camera);
                game.Draw3D();
           EndMode3D();
           BeginMode3D(game.gunCamera);
                Vector3 GunPos = (Vector3){-0.15f, -0.2f, 0.5f};
                DrawModelEx(gun, GunPos, (Vector3){0.0f, 1.0f, 0.0f}, -95.0f, (Vector3){0.08f, 0.08f, 0.08f}, WHITE);
            EndMode3D();
        game.Draw();
        EndDrawing();
    }
    UnloadModel(gun);
    UnloadModel(Speed);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
