objects = base64.o error_debug.o helper.o sha1.o uri.o ws_buff.o ws_message.o ws_message_queue.o websocket_client.o ws_client_example.o
CXXFLAGS = -I.
VPATH = test
websocket_client_test:$(objects)
	g++ -o websocket_client_test $(objects)

base64.o:base64.h
error_debug.o:constants.h error_debug.h
helper.o:helper.h config.h
sha1.o:sha1.h 
uri.o:uri.h config.h error_debug.h constants.h
ws_buff.o:ws_buff.h 
ws_message.o:ws_message.h helper.h config.h base64.h sha1.h
ws_message_queue.o:ws_message.h config.h helper.h
websocket_client.o:websocket_client.h helper.h error_debug.h
ws_client_example.o:websocket_client.h constants.h ws_client_example.cpp 

.PHONY:clean
clean:
	rm websocket_client_test $(objects)