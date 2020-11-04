all:
	g++ -pthread -o server server_lin.c serv_func.c threading.c
	g++ -o client client_lin.c client_fun.c get_mouse_pos.c UI.c
server:
	g++ -pthread -o server server_lin.c serv_func.c threading.c
client:
	g++ -o client client_lin.c client_fun.c get_mouse_pos.c UI.c
clean:
	rm -rf server client