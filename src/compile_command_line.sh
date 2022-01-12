wsl:
静态链接:
g++ 1_1_sync_timer.cpp -o 1_1_sync_timer -lboost_system -static -pthread -lboost_thread
动态链接:
g++ 1_1_sync_timer.cpp -o 1_1_sync_timer -lboost_system -lboost_thread

mac:
clang 1_1_sync_timer.cpp -o 1_1_sync_timer -lstdc++ -std=c++17 -Wall
