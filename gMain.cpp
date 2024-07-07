#include "DxLib.h"
#include "fps.h"
#include "gameManager.h"
#include "key.h"
#include "titleScene.h"
#include "playScene.h"
#include "cursorCntrol.h"
#include "player.h"

/*naming
ヘッダファイル Xxxxx.h
マクロ定義　　 XXXX_XXXX_XXXX
変数    xxxXxxXxx
関数　　XxxxXxxxXxxx()

*/
typedef enum  //誰のターン
{
    TURN_PLYAER          //プレイヤーのターン　すべての敵の行動終了後　playerのターンに移す 
,   TURN_ENEMY           //エネミーのターン　　すべてのplayerの行動終了後　敵のターンに移す
,   TURN_COUNT
,
}E_TURN_T;

typedef enum //盤面の状態
{
  MASU_NONE     //何もない
, MASU_PLAYER   //プレイヤーがすでにいる
, MASU_ENEMY    //エネミーがすでにいる

};


FPS g_fps;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


    //画面描画関連の初期化処理
    ChangeWindowMode(TRUE); //ウィンドウモードで起動
    SetOutApplicationLogValidFlag(FALSE); //log.txtが作られなくなる
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BIT); //画面の解像度指定 ここで８００ｘ６００　３２色
    SetWindowSizeChangeEnableFlag(FALSE); //画面サイズ変更不可
    SetMainWindowText("トレジャーハンタズー"); //ウィンドウの名前を変更する

    //DxLib初期化処理
    if (DxLib_Init() < 0)
    {    
   
        return -1;//Dxlib初期化失敗ならソフト終了
    }
   
    


    //裏画面に描写する
    SetDrawScreen(DX_SCREEN_BACK);
   
    
    Player player;
    Cursor cursor(player);

    //FPS初期化
    FPSInit();
    //キーボードの初期化
    KeyInit();
    //タイトル画面の初期化
    TitleInit();
    //最初はタイトル画面から
    TitleMenuInit();
    //プレイ画面のバトルフィールドの初期化
    PlaySceneInit();
    //コンストラクタ
    player.GraphicLoad();

    player.PlayerPosInit();

    nowGameScene = TITLE_SCENE;


    
    while (1)
    {
        //強制終了
        if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
        {
            break;
        }

        //Windows特有の面倒な処理をDXlibにやらせる
        if (ProcessMessage() < 0)
        {
            break;
        }
        if (ClearDrawScreen() != 0) 
        {
            break;
        }
       
        //ここにすべてのゲームの動作が入る
       
            FPSCheck();
            KeyUpdata(); //キーボード更新
          
            //シーン切り替え
            switch (nowGameScene)
            {
            case TITLE_SCENE:
                TitleCtrl();
                
                break;
            case PLAY_SCENE:
                PlayCtrl();
               // ScenarioDraw();
                
                    FieldLaOutDraw();
                    cursor.CursorDraw();
                    cursor.CursorControl();
                    cursor.MapInfoShow();
                    player.PlayerMove();
                    //キャラのステータスを表示する
                    
               
                break;
            case END_SCENE:
                EndCtrl();
                break;
          
            default:
                break;
            }
            FPSDraw();
            FPSWait();

        ScreenFlip();
    }
    //ロードした画像をまとめて削除
    //DeleteGraph();
   //waitKey(); //キー入力待ち
    
    DxLib_End(); //DxLibの終了

    return 0;

}