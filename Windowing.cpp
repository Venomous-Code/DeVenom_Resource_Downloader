#include "Windowing.h"

PackageInstaller::Windowing::Windowing() {
    SDL_Init(SDL_INIT_VIDEO);

    CreateApplicationWindow("SDL3_WINDOW");

    bool isWindowClosed = false;

    while (!isWindowClosed) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                isWindowClosed = true;
            }
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        SDL_RenderClear(mainRenderer);
        SDL_RenderTexture(mainRenderer, mainTexture, NULL, NULL);
        // Build your GUI

        ImGui::SetNextWindowPos(ImVec2(5, 430));
        ImGui::SetNextWindowSize(ImVec2(910, 45));
        ImGui::Begin("Title", 0,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove);
        ImGui::Text("This is a simple Dear ImGui window.");
        ImGui::End();


        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),mainRenderer);
        SDL_RenderPresent(mainRenderer);
    
    }



    SDL_Quit();
}

PackageInstaller::Windowing::~Windowing() { 
    SDL_DestroyWindow(mainWindow); 
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroySurface(mainSurface);
    SDL_DestroyTexture(mainTexture);

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();
}

int PackageInstaller::Windowing::CreateApplicationWindow(
    const char* WindowsName) { 

    mainWindow =
        SDL_CreateWindow(WindowsName, 920, 480,
                         SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS);

    if (mainWindow == NULL) {
        Log.CustomLogger(
            "SDL FAILED TO CREATE WINDOW. AN UNEXPECTED ERROR OCCURED WHILE "
            "IINITIALIZING WINDOW.",
            spdlog::level::critical);
        return 1;
    }

    SDL_Rect PictureFrame = Div(420, 910, 5, 5);

    mainRenderer = SDL_CreateRenderer(mainWindow, NULL);

    mainSurface = SDL_LoadBMP("Images\\Cover.bmp");

    mainTexture = SDL_CreateTextureFromSurface(mainRenderer, mainSurface);

    SDL_SetRenderViewport(mainRenderer, &PictureFrame);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(mainWindow, mainRenderer);
    ImGui_ImplSDLRenderer3_Init(mainRenderer);

    return 0;
}

SDL_Rect PackageInstaller::Windowing::Div(int RectHeight, int RectWidth,
                                          int RectXPos, int RectYPos) { 

    SDL_Rect TextureRectangle;
    TextureRectangle.h = RectHeight;
    TextureRectangle.w = RectWidth;
    TextureRectangle.x = RectXPos;
    TextureRectangle.y = RectYPos;

    return TextureRectangle;

}
