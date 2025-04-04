#include "scrolling_background.h"
const std::string LAYER[BACKGROUND_LAYER] = {
    "D:\\gamebansung\\background\\layer1.png",
    "D:\\gamebansung\\background\\layer2.png",
    "D:\\gamebansung\\background\\layer3.png",
    "D:\\gamebansung\\background\\layer4.png",
    "D:\\gamebansung\\background\\layer05.png",
    "D:\\gamebansung\\background\\layer6.png",
    "D:\\gamebansung\\background\\layer7.png",
    "D:\\gamebansung\\background\\layer8.png",
    "D:\\gamebansung\\background\\layer9.png",
};
void RenderScrollingBackground(std::vector<double>& offsetSpeed,
                               BaseOj(&gBackgroundTexture)[BACKGROUND_LAYER],
                               SDL_Renderer* gRenderer)
{
    const std::vector<double> layer_speed = {
        LAYER_1_SPEED, LAYER_2_SPEED, LAYER_3_SPEED,
        LAYER_4_SPEED, LAYER_5_SPEED, LAYER_6_SPEED,
        LAYER_7_SPEED, LAYER_8_SPEED, LAYER_9_SPEED
    };
    if (offsetSpeed.size() != BACKGROUND_LAYER) return;
    for (int i = 0; i < BACKGROUND_LAYER; ++i)
    {
        offsetSpeed[i] -= layer_speed[i];
        int layer_width = gBackgroundTexture[i].GetRect().w;
        if (offsetSpeed[i] < -layer_width)
        {
            offsetSpeed[i] = 0;
        }
        gBackgroundTexture[i].SetRect(offsetSpeed[i], 0);
        gBackgroundTexture[i].Render(gRenderer);

        gBackgroundTexture[i].SetRect(offsetSpeed[i] + layer_width, 0);
        gBackgroundTexture[i].Render(gRenderer);
    }
}

