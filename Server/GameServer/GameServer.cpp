﻿// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>

/* 5강
void HelloThread()
{
    cout << "Hello Thread" << endl;
}

//파라미터가 있는 경우
void HelloThread2(int32 num)
{
    cout << num << endl;
}
*/

//6강
//atomic atom(원자) : All-Or-Nothing(다 실행되거나 아니면 모두 실행 하지 않거나)

//ex. DB에서,(아이템 교환)
//A라는 유저 인벤에서 집행검을 빼고
//B라는 유저 인벤에서 집행검을 추가
//=> DB상에서 트랜젝션으로 묶어서 반드시 한번에(atomic)하게 진행되어야

atomic<int32> sum = 0; //atomic 타입으로 바뀌면 sum관련 애들에 연산이 시작되면 다른 애들 연산은 살짝 멈춤(CPU에서 대기타게 함)
//어셈블리 언어를 보면 어떤 다른 함수(다른 인터럽트 발생 함수일듯)를 call해서 연산 ==> 대기타게하는거랑 call하는 것때문에 생각보다 많이느려서 필요할때만 써야함

void Add()
{
    for (int32 i = 0; i < 1'000'000; i++)
    {
        sum.fetch_add(1); //sum++로는 일반 int ++이랑 헷갈려서
        //sum++;
        //어셈블리 단계에서 하는 일
        //int32 eax = sum;
        //eax = eax + 1;
        //sum = eax; ==>이 단계에서 sum에 다른 값을 덮어쓸 수도 있음
        //=> sum++이 3단계가 아니라 한번에 실행되어야 함 ==> 블록단위로 묶기(동기화)
        

    }
}

void Sub()
{
    for (int32 i = 0; i < 100'0000; i++)
    {
        sum.fetch_add(-1); //add-1은 1을 빼는 거니까(sub도 있음)
        //sum--;
    }
}

int main()
{
    Add();
    Sub();
    cout << sum << endl;

    std::thread t1(Add);
    std::thread t2(Sub);
    t1.join();
    t2.join();
    cout << sum << endl;

    /*
    //system call(os kernel 요청)
    //객체 먼저 만들고 따로 func지정해주는 경우
    vector<std::thread> v;
    //
    //v.resize(10);
    
    //10개 스레드
    for (int32 i = 0; i < 10; i++)
    {
        v.push_back(std::thread(HelloThread2, i));
    }

    //10개 모두 끝날때까지 main이 끝나면 안되니까
    for (int32 i = 0; i < 10; i++)
    {
        if (v[i].joinable())
            v[i].join();
    }

    //출력이 02 처럼 endl 전에 출력이 될 수도 있음(endl도 안타는구나..)

    /*
    std::thread t;
    
    auto id1 = t.get_id(); //객체가 만들어지기만 해서 id가 0

    //t = std::thread(HelloThread);
    t = std::thread(HelloThread2, 10); // 인자가 있을 경우

    //미리 사이즈를 지정해두는 경우..?는 잘 모르겠다

    auto id2 = t.get_id(); //쓰레드마다 부여되는 아이디 sd_id 타입이라 auto로

    int32 count = t.hardware_concurrency(); //실질적(논리적으로) 동시에 구동할 수 있는 CPU 코어 개수는 몇개인지 힌트, 100% 정확하지 않음, 0이 나올수도
    
    //t.detach(); //join은 기다리는데 detach는 std::thread객체에서 실제 쓰레드 분리, 데몬프로세스/ 객체(t)와 스레드를 끊음 => 아예 백그라운드 스레드, 독립적으로 동작하는 / t로 이제 뭘 못함
    if(t.joinable()) //detach 상태라거나 연동된 스레드가 없다면 joinable로 테스트 / 객체를 만든 후에 t = std::thread((func));도 가능 => func을 지정하지 않으면 id는 0 / 살아 있는지 없는지
        t.join();
    //이런 식으로 joinable(연결 되어있는게 있으면) 기다려라 하는 식으로 한대
    
    cout << "Hello Main" << endl;*/
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
