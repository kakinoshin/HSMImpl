// HSMImpl.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include "hsm.h"

HSMStateObject_t state_top;
  HSMStateObject_t state_a;
    HSMStateObject_t state_b;
    HSMStateObject_t state_c;
      HSMStateObject_t state_d;
      HSMStateObject_t state_e;
  HSMStateObject_t state_f;

void evt_state_top(Event const evt);
void evt_state_a(Event const evt);
void evt_state_b(Event const evt);
void evt_state_c(Event const evt);
void evt_state_d(Event const evt);
void evt_state_e(Event const evt);
void evt_state_f(Event const evt);

int main()
{
	HSM_Create(&state_top, NULL, "top", NULL);
	HSM_Create(&state_a, &state_top, "state a", &evt_state_a);
	HSM_Create(&state_b, &state_a, "state b", &evt_state_b);
	HSM_Create(&state_c, &state_a, "state c", &evt_state_c);
	HSM_Create(&state_d, &state_c, "state d", &evt_state_d);
	HSM_Create(&state_e, &state_c, "state e", &evt_state_e);
	HSM_Create(&state_f, &state_top, "state f", &evt_state_f);

	HSM_Init(&state_top);

	std::cout << "[Transit to State D]\n";
	HSM_Transition(&state_d);

	std::cout << "[Transit to State E]\n";
	HSM_Transition(&state_e);

	std::cout << "[Transit to State B]\n";
	HSM_Transition(&state_b);
}

void evt_state_top(Event const evt)
{
	std::cout << "State Top : " << HSM_GetEventName(evt) << "(" << evt << ")\n";
}

void evt_state_a(Event const evt)
{
	std::cout << "State A : " << HSM_GetEventName(evt) << "(" << evt << ")\n";
}

void evt_state_b(Event const evt)
{
	std::cout << "State B : " << HSM_GetEventName(evt) << "(" << evt << ")\n";
}

void evt_state_c(Event const evt)
{
	std::cout << "State C : " << HSM_GetEventName(evt) << "(" << evt << ")\n";
}

void evt_state_d(Event const evt)
{
	std::cout << "State D : " << HSM_GetEventName(evt) << "(" << evt << ")\n";
}

void evt_state_e(Event const evt)
{
	std::cout << "State E : " << HSM_GetEventName(evt) << "(" << evt << ")\n";
}

void evt_state_f(Event const evt)
{
	std::cout << "State F : " << HSM_GetEventName(evt) << "(" << evt << ")\n";
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
