#pragma once
#include "Scene.h"
#include"SceneManager.h"
#include"SelectScene.h"
#include"Platform.h"
#include"Player.h"
extern SceneManager scene_manager;
extern IMAGE img_hills;
extern IMAGE img_sky;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;
extern Camera main_camera;
extern std::vector<Platform> list_platform;
extern bool is_debug;
extern Player* player1;
extern Player* player2;
class GameScene : public Scene
{
public:
    GameScene()=default;
    ~GameScene()=default;
    void on_enter(){
        mciSendString(L"play bgm_game repeat from 0", NULL, 0, NULL);
        pos_hills.x = (getwidth() - img_hills.getwidth()) / 2;
        pos_hills.y = (getheight() - img_hills.getheight()) / 2;
        pos_sky.x = (getwidth() - img_sky.getwidth()) / 2;
        pos_sky.y = (getheight() - img_sky.getheight()) / 2;

        list_platform.resize(4);
        Platform& large_platform = list_platform[0];
        large_platform.img = &img_platform_large;
        large_platform.pos_render = { 122,455 };
        large_platform.shape.x_begin = large_platform.pos_render.x + 30;
        large_platform.shape.x_end = large_platform.pos_render.x+img_platform_large.getwidth() - 30;
        large_platform.shape.y = large_platform.pos_render.y + 60;

        Platform& small_platform_1 = list_platform[1];
        small_platform_1.img = &img_platform_small;
        small_platform_1.pos_render = { 175,360 };
        small_platform_1.shape.x_begin = small_platform_1.pos_render.x + 40;
        small_platform_1.shape.x_end = small_platform_1.pos_render.x + img_platform_small.getwidth() - 40;
        small_platform_1.shape.y = small_platform_1.pos_render.y + img_platform_small.getheight() / 2;

        Platform& small_platform_2 = list_platform[2];
        small_platform_2.img = &img_platform_small;
        small_platform_2.pos_render = { 855,360 };
        small_platform_2.shape.x_begin = small_platform_2.pos_render.x + 40;
        small_platform_2.shape.x_end = small_platform_2.pos_render.x + img_platform_small.getwidth() - 40;
        small_platform_2.shape.y = small_platform_2.pos_render.y + img_platform_small.getheight() / 2;

        Platform& small_platform_3 = list_platform[3];
        small_platform_3.img = &img_platform_small;
        small_platform_3.pos_render = { 515,255 };
        small_platform_3.shape.x_begin = small_platform_3.pos_render.x + 40;
        small_platform_3.shape.x_end = small_platform_3.pos_render.x + img_platform_small.getwidth() - 40;
        small_platform_3.shape.y = small_platform_3.pos_render.y + img_platform_small.getheight() / 2;
    }
    void on_input(const ExMessage& msg)
    {
        if (msg.message == WM_KEYDOWN)
        {
            switch (msg.vkcode)
            {
            case 'Q':
                is_debug = !is_debug;
                break;
            default:
                break;
            }
        }
        player1->on_input(msg);
        player2->on_input(msg);
    }
    void on_updata(int delta)
    {
        main_camera.on_updata(delta);
        player1->on_updata(delta);
        player2->on_updata(delta);
    }
    void on_draw()
    {
        putimage_alpha(pos_sky.x, pos_sky.y, &img_sky,&main_camera);
        putimage_alpha(pos_hills.x, pos_hills.y, &img_hills,&main_camera);
        for (size_t i = 0; i < list_platform.size(); i++)
        {
            list_platform.at(i).on_draw(main_camera);
        }
        if (is_debug)
        {
            settextcolor(RED);
            outtextxy(0, 150, L"调试模式已开启,按Q关闭");
        }
        player1->on_draw(main_camera);
        player2->on_draw(main_camera);
    }
    void on_exit() 
    {

    }
private:
    POINT pos_hills = { 0,0 };
    POINT pos_sky= { 0,0 };
    std::function<POINT()> callback;
};

