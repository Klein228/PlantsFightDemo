#pragma once
#include "Scene.h"
#include"SceneManager.h"

extern  SceneManager scene_manager;
class GameScene : public Scene
{
public:
    GameScene()=default;
    ~GameScene()=default;
    void on_enter(){
        std::cout << "进入游戏场景" << std::endl;
    }
    void on_input(const ExMessage& msg){
        if (msg.message == WM_KEYDOWN)
        {
            scene_manager.switch_to(SceneManager::sceneType::Menu);
        }
    }
    void on_updata(){
        std::cout << "数据处理" << std::endl;
    }
    void on_draw(){
        outtextxy(0, 0, _T("游戏画面绘制"));
    }
    void on_exit() {
        std::cout << "退出游戏场景" << std::endl;
    };
private:

};

