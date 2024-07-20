#include "cursorCntrol.h"
#include "playScene.h"

// コンストラクタ カーソルの情報を初期化
Cursor::Cursor(Player& player) : player(player) {
    this->x1 = (GRID__WIDTH - 1) * MASU___SIZE;  //カーソルの初期生成地　X１
    this->x2 = GRID__WIDTH * MASU___SIZE;        //カーソルの初期生成地　Y１
    this->y1 = (GRID_HEIGHT - 1) * MASU___SIZE;  //カーソルの初期生成地　X２
    this->y2 = GRID_HEIGHT * MASU___SIZE;        //カーソルの初期生成地　Y２

    this->isMapCursor = TRUE; // TRUEの場合 マップカーソル描画ON

    this->playerX1 = 560;                                     //playerUIカーソルの初期生成地　X１
    this->playerY1 = GRID_HEIGHT * MASU___SIZE;               //playerUIカーソルの初期生成地　Y１
    this->playerX2 = 560 + MASU___SIZE;                       //playerUIカーソルの初期生成地　X２
    this->playerY2 = GRID_HEIGHT * MASU___SIZE + MASU___SIZE; //playerUIカーソルの初期生成地　Y２

    this->isPlayerUICursor = FALSE; // 初期状態でプレイヤUIカーソルを非表示

    this->color = GetColor(255, 255, 0);
    this->lastMoveTime = 0;
    this->isPlayerSelected = false; // 初期状態ではプレイヤーは選択されていない
    this->isBlink = true; // 初期状態で点滅表示
    this->lastBlinkTime = GetNowHiPerformanceCount(); // 現在の時刻を取得
    this->isPlayerMoveShow = FALSE;
    this->playerUI_Is = PLAYER_UI_INVALID; // playerUIの状態を初期化します
    for (int i = 0; i < 256; i++) {
        this->key[i] = 0;
    }
}

// カーソル制御
VOID Cursor::CursorControl() {
    GetHitKeyStateAll(this->key); // すべてのキーの状態を取得
    LONGLONG currentTime = GetNowHiPerformanceCount(); // 現在の時刻を取得

    // 移動のタイミングを制御するための間隔（マイクロ秒）
    const LONGLONG moveInterval = 100000; // 0.1秒

    if (currentTime - lastMoveTime > moveInterval) {
        int newX1 = this->x1;
        int newX2 = this->x2;
        int newY1 = this->y1;
        int newY2 = this->y2;

        if (this->key[KEY_INPUT_LEFT] == 1 && this->x1 >= MASU___SIZE) {
            newX1 -= MASU___SIZE;
            newX2 -= MASU___SIZE;
        }
        else if (this->key[KEY_INPUT_RIGHT] == 1 && this->x1 <= (GRID__WIDTH - 2) * MASU___SIZE) {
            newX1 += MASU___SIZE;
            newX2 += MASU___SIZE;
        }
        else if (this->key[KEY_INPUT_UP] == 1 && this->y1 >= MASU___SIZE) {
            newY1 -= MASU___SIZE;
            newY2 -= MASU___SIZE;
        }
        else if (this->key[KEY_INPUT_DOWN] == 1 && this->y1 <= (GRID_HEIGHT - 2) * MASU___SIZE) {
            newY1 += MASU___SIZE;
            newY2 += MASU___SIZE;
        }

        if (this->isPlayerMoveShow) {
            // キャラクターの移動範囲内にいるかを確認
            int playerPosX = player.getPosX() * MASU___SIZE;
            int playerPosY = player.getPosY() * MASU___SIZE;
            bool isWithinMoveRange = (abs(newX1 - playerPosX) / MASU___SIZE + abs(newY1 - playerPosY) / MASU___SIZE <= player.getMove());

            // 新しい座標の地形情報を取得
            int newLayoutX = newX1 / MASU___SIZE;
            int newLayoutY = newY1 / MASU___SIZE;
            E_LAYOUT_T layout = g_layout[newLayoutY][newLayoutX];

            // 岩、川、壁のマスではないことを確認
            if (isWithinMoveRange && (layout != LAYOUT_STONE && layout != LAYOUT_DRIVE && layout != LAYOUT_WALL)) {
                this->x1 = newX1;
                this->x2 = newX2;
                this->y1 = newY1;
                this->y2 = newY2;
                lastMoveTime = currentTime;
            }
        }
        else {
            // 通常状態ではカーソルを自由に移動可能
            this->x1 = newX1;
            this->x2 = newX2;
            this->y1 = newY1;
            this->y2 = newY2;
            lastMoveTime = currentTime;
        }

        // mapカーソルをプレイヤを指定する  
       //this->x1 == player.getPosX() * MASU___SIZE カーソルのX＝プレイヤのX 　TRUE
       //this->x1 == player.getPosX() * MASU___SIZE カーソルのY＝プレイヤのY　 TRUE
       //両方が１になると　isPlayerSelected= TRUE
        this->isPlayerSelected = (this->x1 == player.getPosX() * MASU___SIZE && this->y1 == player.getPosY() * MASU___SIZE);
    }


        if (this->isPlayerSelected == TRUE && this->key[KEY_INPUT_SPACE] == 1) { // カーソルの座標がプレイヤの座標と一致する場合
            isMapCursor = FALSE;
            lastMoveTime = currentTime;
        }
       
    if (this->isPlayerMoveShow == TRUE) {
        player.PlayerAbleMove(); // プレイヤーの移動範囲を表示する
    }

    //移動範囲が表示しかつ移動範囲の中にmapカーソルも描画した場合
    if (this->isPlayerMoveShow == TRUE && this->isMapCursor == TRUE) {
        //指定場合を確定したらspaceキを押し　キャラの座標 ＝　指定座標
        if (this->key[KEY_INPUT_SPACE] == 1)
        {  
            
            int decideNewX1 = this->x1/ MASU___SIZE; //x1 = x1 * MASU___SIZE 
            int decideNewY1 = this->y1/ MASU___SIZE;
            //指定座標をキャラ座標の中に代入(セットset)           
            player.setPosX(decideNewX1);
            player.setPosY(decideNewY1);
            player.PlayerAction--;
            
        }


    }
  
    
    
}

// カーソル描画
VOID Cursor::CursorDraw() {
    LONGLONG currentTime = GetNowHiPerformanceCount();

    // 移動状態時に点滅しないようにする
    if (!this->isPlayerMoveShow) {
        // 点滅の間隔が経過したら表示フラグを切り替える
        if (currentTime - lastBlinkTime > blink) {
            isBlink = !isBlink;
            lastBlinkTime = currentTime;
        }
    }
    else {
        isBlink = true; // 移動状態時は常に表示
    }

    if (isBlink) {
        DrawBox(this->x1, this->y1, this->x2, this->y2, color, TRUE);
    }
}

// マップ情報表示
VOID Cursor::MapInfoShow() {
    // カーソルがあるマップの座標を計算
    int mapX = this->x1 / MASU___SIZE;
    int mapY = this->y1 / MASU___SIZE;

    if (mapX >= 0 && mapX < GRID__WIDTH && mapY >= 0 && mapY < GRID_HEIGHT) {
        // マップ情報を取得
        E_LAYOUT_T mapInfo = g_layout[mapY][mapX];
        switch (mapInfo) {
        case LAYOUT_GRASS:
            DrawString(200, 0, "草", 0x00ff00);
            break;
        case LAYOUT_VILLAGE:
            DrawString(200, 0, "村", 0xC8BFE7);
            break;
        case LAYOUT_STONE:
            DrawString(200, 0, "石", 0xCCDDE7);
            break;
        case LAYOUT_DRIVE:
            DrawString(200, 0, "川", 0x0000ff);
            break;
        case LAYOUT_FOREST:
            DrawString(200, 0, "森", 0x8E403A);
            break;
        case LAYOUT_WALL:
            DrawString(200, 0, "壁", 0xE7E6CD);
            break;
        case LAYOUT_BRIDGE:
            DrawString(200, 0, "橋", 0xE7C385);
            break;
        default:
            DrawString(200, 0, "エラー", 0xFF0000);
            break;
        }
    }

    // プレイヤーが選択されている場合にステータスを表示
    if (this->isPlayerSelected) {
        player.StatusShow();
    }
}

// プレイヤUIカーソル描画
VOID Cursor::PlayerUICursorDraw() {
    DrawBox(playerX1 + 1, playerY1 + 1, playerX2 - 1, playerY2 - 1, 0x00ff00, FALSE);
}

// プレイヤUIカーソルのコントロール
VOID Cursor::PlayerUIControl() {
    GetHitKeyStateAll(this->key); // すべてのキーの状態を取得
    LONGLONG currentTime = GetNowHiPerformanceCount(); // 現在の時刻を取得

    // 移動のタイミングを制御するための間隔（マイクロ秒）
    const LONGLONG moveInterval = 100000; // 0.1秒

    // プレイヤーUIカーソルの移動範囲
    const int playerMinX = 560;
    const int playerMaxX = 680;
    const int playerMinY = 480;
    const int playerMaxY = 560;

    if (currentTime - lastMoveTime > moveInterval) {
        if (this->key[KEY_INPUT_LEFT] == 1 && this->playerX1 > playerMinX) {
            this->playerX1 = this->playerX1 - MASU___SIZE;
            this->playerX2 = this->playerX2 - MASU___SIZE;
            lastMoveTime = currentTime;
        }
        else if (this->key[KEY_INPUT_RIGHT] == 1 && this->playerX1 < playerMaxX) {
            this->playerX1 = this->playerX1 + MASU___SIZE;
            this->playerX2 = this->playerX2 + MASU___SIZE;
            lastMoveTime = currentTime;
        }
        else if (this->key[KEY_INPUT_UP] == 1 && this->playerY1 > playerMinY) {
            this->playerY1 = this->playerY1 - MASU___SIZE;
            this->playerY2 = this->playerY2 - MASU___SIZE;
            lastMoveTime = currentTime;
        }
        else if (this->key[KEY_INPUT_DOWN] == 1 && this->playerY1 < playerMaxY) {
            this->playerY1 = this->playerY1 + MASU___SIZE;
            this->playerY2 = this->playerY2 + MASU___SIZE;
            lastMoveTime = currentTime;
        }
    }

    // プレイヤUIカーソルが moveアイコンの座標と一致した場所
    if (this->playerX1 == 560 && this->playerY1 == 480) {
        // moveメッセージを描画(UIに表示)
        player.PlayerMoveMessage();
        playerUI_Is = PLAYER_UI_MOVE;
    }
    else if (this->playerX1 == 560 + MASU___SIZE && this->playerY1 == 480) {
        player.PlayerAttackMessage();
        playerUI_Is = PLAYER_UI_ATTACK;
    }
    else if (this->playerX1 == 560 + 2 * MASU___SIZE && this->playerY1 == 480) {
        player.PlayerItemMessage();
        playerUI_Is = PLAYER_UI_ITEM;
    }
    else if (this->playerX1 == 560 + 3 * MASU___SIZE && this->playerY1 == 480) {
        player.PlayerWaitMessage();
        playerUI_Is = PLAYER_UI_WAIT;
    }

    switch (playerUI_Is) {
    case PLAYER_UI_MOVE:
        // Mキーを押したら isPlayerMove
        if (this->key[KEY_INPUT_M] == 1) {
            this->isPlayerMoveShow = TRUE; // TRUEになり TRUEなるとキャラの移動範囲マスを描画
            this->isPlayerUICursor = FALSE; // 同時にplayerUIカーソルの制御をoffする
            this->isMapCursor = TRUE; // 描画し（移動範囲はPlayerAbleMoveのマス中）
        }
        break;
    case PLAYER_UI_ATTACK:
        if (this->key[KEY_INPUT_A] == 1) {
            // player.PlayerAttack();
        }
        break;
    case PLAYER_UI_ITEM:
        if (this->key[KEY_INPUT_I] == 1) {
            // player.PlayerItem();
        }
        break;
    case PLAYER_UI_WAIT:
        if (this->key[KEY_INPUT_W] == 1) {
            // player.PlayerWait();
        }
        break;
    default:
        break;
    }
}

// カーソル切り替え
VOID Cursor::Switching() {
    if (isMapCursor == FALSE) { // playerUIカーソルを描画
        if (this->key[KEY_INPUT_X] == 1) { // プレイヤUIからエスケープ
            isMapCursor = FALSE; // マップカーソル描画OFFし
            isPlayerUICursor = TRUE; // プレイヤUIカーソル描画ON プレイヤUIカーソルに切り替える
 //         isPlayerSelected = false; // 初期状態ではプレイヤーは選択されていない
        }
    }
}
