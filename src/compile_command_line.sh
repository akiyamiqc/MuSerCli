wsl:
静态链接:
g++ 1_1_sync_timer.cpp -o 1_1_sync_timer -lboost_system -static -pthread -lboost_thread
动态链接:
g++ 1_1_sync_timer.cpp -o 1_1_sync_timer -lboost_system -lboost_thread

msys2:
