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
        std::cout << "������Ϸ����" << std::endl;
    }
    void on_input(const ExMessage& msg){
        if (msg.message == WM_KEYDOWN)
        {
            scene_manager.switch_to(SceneManager::sceneType::Menu);
        }
    }
    void on_updata(int delta){
        
    }
    void on_draw(){

    }
    void on_exit() {
        std::cout << "�˳���Ϸ����" << std::endl;
    };
private:
};

