#include <raylib.h>
#include <stdlib.h>
#include <string.h>

static int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointResultCount);

int main(void){
    InitWindow(0,0,"HOLA MUNDO");
    const int width = GetScreenWidth();
    const int height = GetScreenHeight();
    SetWindowSize(width,height);
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    SetTargetFPS(30);
    Image i = LoadImage("parrots.png");
    Texture2D t = LoadTextureFromImage(i);
    UnloadImage(i);
    const char *str = "The quick brown fox jumps over the lazy dog"
                      "|El veloz murciélago hindú comía feliz cardillo y kiwi. La cigüeña tocaba el saxofón detrás del palenque de paja."
                      "|덧글은통신 예절 지키면서 표현 자유 추구하는 방향으로";
    int num_strs = 0;
    const char **strs = TextSplit(str,'|',&num_strs);
    int codepointCount = 0;
    int *codepoints = LoadCodepoints(str, &codepointCount);
    int codepointsNoDupsCount = 0;
    int *codepointsNoDups = CodepointRemoveDuplicates(codepoints, codepointCount, &codepointsNoDupsCount);
    UnloadCodepoints(codepoints);
    Font fontAsian = LoadFontEx("Pretendard-Regular.ttf",36,codepointsNoDups,codepointsNoDupsCount);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        DrawTextEx(fontAsian,strs[0],(Vector2){40,40},fontAsian.baseSize,1.0f,BLACK);
        DrawTextEx(fontAsian,strs[1],(Vector2){40,70},fontAsian.baseSize,1.0f,BLACK);
        DrawTextEx(fontAsian,strs[2],(Vector2){40,100},fontAsian.baseSize,1.0f,BLACK);
        DrawTexture(t,300,300,WHITE);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
static int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointsResultCount)
{
    int codepointsNoDupsCount = codepointCount;
    int *codepointsNoDups = (int *)calloc(codepointCount, sizeof(int));
    memcpy(codepointsNoDups, codepoints, codepointCount*sizeof(int));

    // Remove duplicates
    for (int i = 0; i < codepointsNoDupsCount; i++)
    {
        for (int j = i + 1; j < codepointsNoDupsCount; j++)
        {
            if (codepointsNoDups[i] == codepointsNoDups[j])
            {
                for (int k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

                codepointsNoDupsCount--;
                j--;
            }
        }
    }

    // NOTE: The size of codepointsNoDups is the same as original array but
    // only required positions are filled (codepointsNoDupsCount)

    *codepointsResultCount = codepointsNoDupsCount;
    return codepointsNoDups;
}