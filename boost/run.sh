clang++ -std=c++11 -stdlib=libc++ -Weverything -I /usr/local/Cellar/boost/1.57.0/include -L /usr/local/Cellar/boost/1.57.0/lib -lboost_system-mt -lboost_thread-mt chat_client.cpp -o client
clang++ -std=c++11 -stdlib=libc++ -Weverything -I /usr/local/Cellar/boost/1.57.0/include -L /usr/local/Cellar/boost/1.57.0/lib -lboost_system-mt -lboost_thread-mt chat_server.cpp -o server
