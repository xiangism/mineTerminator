#pragma once
#include "Block.h"
#include "AdapterGame.h"
#include <shangjing/TwoDimesionArray.hpp>
#include <boost/shared_ptr.hpp>
using namespace shangjing;
using namespace boost;

class AnalyseData;
class AdapterGame;

class GamePanel
{    
public:
    GamePanel(void);
    ~GamePanel(void);
    GameState allRun();   //ȫ�Զ� ��ֱ����Ϸ��������Ϸʤ�����û���ѡ�����¿�ʼ
    void semiRun();         //���Զ���ֻ���ȷ�������׵Ŀ�
    
private:
    shared_ptr<AnalyseData> analyser;
    shared_ptr<AdapterGame> adapter;

};
