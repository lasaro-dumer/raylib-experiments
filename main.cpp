/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "myutils.cpp"

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D cubicmap_atlas = LoadTexture("resources/cubicmap_atlas_marked.png"); // Texture loading
    float texWidth = (float)cubicmap_atlas.width;
    float texHeight = (float)cubicmap_atlas.height;
    Rectangle frameRec = {texWidth * 1.0f / 2, texHeight * 1.0f / 2, texWidth / 2, texHeight / 2};

    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_THIRD_PERSON);

    Vector3 cubePosition = {0};
    Vector3 cubePositionGreen = {2.0f, 0.0f, 0.0f};
    Vector3 cubePositionBlue = {-2.0f, 0.0f, 0.0f};
    Vector3 cubePositionBlack = {0.0f, 2.0f, 0.0f};
    float verticesLength = 1.0f;
    float cameraMovement = 0.1f;
    Vector3 voxelPosition = {5.0f, 5.0f, 5.0f};
    int voxelFaces[6] = {1, 1, 1, 1, 1, 1};
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_A)){ camera.position.x += cameraMovement; camera.target.x += cameraMovement; }
        if (IsKeyDown(KEY_D)){ camera.position.x -= cameraMovement; camera.target.x -= cameraMovement; }
        if (IsKeyDown(KEY_S)){ camera.position.z -= cameraMovement; camera.target.z -= cameraMovement; }
        if (IsKeyDown(KEY_W)){ camera.position.z += cameraMovement; camera.target.z += cameraMovement; }
        if (IsKeyPressed(KEY_Q)){ camera.position.y -= 1.0f; camera.target.y -= 1.0f; }
        if (IsKeyPressed(KEY_E)){ camera.position.y += 1.0f; camera.target.y += 1.0f; }
        if (IsKeyPressed(KEY_KP_1)){ voxelFaces[0] = !voxelFaces[0]; }
        if (IsKeyPressed(KEY_KP_2)){ voxelFaces[1] = !voxelFaces[1]; }
        if (IsKeyPressed(KEY_KP_3)){ voxelFaces[2] = !voxelFaces[2]; }
        if (IsKeyPressed(KEY_KP_4)){ voxelFaces[3] = !voxelFaces[3]; }
        if (IsKeyPressed(KEY_KP_5)){ voxelFaces[4] = !voxelFaces[4]; }
        if (IsKeyPressed(KEY_KP_6)){ voxelFaces[5] = !voxelFaces[5]; }
        UpdateCamera(&camera);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

            DrawAxisTarget(camera);
            DrawVoxel(cubicmap_atlas, frameRec, voxelPosition, 1.0f, 1.0f, 1.0f, voxelFaces, WHITE);
            DrawCubeWires(voxelPosition, verticesLength, verticesLength, verticesLength, BLACK);
            DrawCube(cubePosition, verticesLength, verticesLength, verticesLength, RED);
            DrawCubeWires(cubePosition, verticesLength, verticesLength, verticesLength, MAROON);
            DrawCube(cubePositionGreen, verticesLength, verticesLength, verticesLength, GREEN);
            DrawCubeWires(cubePositionGreen, verticesLength, verticesLength, verticesLength, BLACK);
            DrawCube(cubePositionBlue, verticesLength, verticesLength, verticesLength, BLUE);
            DrawCubeWires(cubePositionBlue, verticesLength, verticesLength, verticesLength, BLACK);
            DrawCube(cubePositionBlack, verticesLength, verticesLength, verticesLength, BLACK);
            DrawCubeWires(cubePositionBlack, verticesLength, verticesLength, verticesLength, WHITE);
            DrawGrid(10, 1.0f);
            //DrawTextureRec();
            EndMode3D();

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);
            //Texture debugging labels
            // DrawText(TextFormat("frameRec={%02.02f, %02.02f, %02.02f, %02.02f}", frameRec.x, frameRec.y, frameRec.height, frameRec.width), 10, 60, 20, DARKGRAY);
            // DrawText(TextFormat("texWidth=%02.02f, texHeight=%02.02f}", texWidth, texHeight), 10, 80, 20, DARKGRAY);
            // DrawText(TextFormat("source.x/texWidth=%02.02f, source.y/texHeight=%02.02f}", frameRec.x / texWidth, frameRec.y / texHeight), 10, 100, 20, DARKGRAY);
            //voxel faces debugging label
            // DrawText(TextFormat("voxelFaces: %s, %s, %s, %s, %s, %s", voxelFaces[0] ? "true" : "false", voxelFaces[1] ? "true" : "false", voxelFaces[2] ? "true" : "false",
            //                                                           voxelFaces[3] ? "true" : "false", voxelFaces[4] ? "true" : "false", voxelFaces[5] ? "true" : "false"), 10, 120, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
