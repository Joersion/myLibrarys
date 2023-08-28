#include "httplib.h"
#include <iostream>
#include <thread>

using namespace std;
using namespace httplib;
#define HOST_NAME "localhost"
#define PORT 8080
#define PATH "/hi"
#define CONTENT_TYPE "text/plain"
#define CONTENT "Hello Joersion!"

void httpServer(const string& content) {
	cout << "the http server start..." << endl;
	cout << "httpServer,host:" << HOST_NAME << ",port:" << PORT << ",action:" << "Get" << endl;
	Server svr;
	svr.Get(PATH, [&](const Request & , Response &res) {
		res.set_content(content, CONTENT_TYPE);
	});
	cout << "the http server listen..." << endl;
	svr.listen(HOST_NAME, PORT);
}

void httpClient() {
	httplib::Client httpCli(HOST_NAME, PORT);
	auto res = httpCli.Get(PATH);
	cout << "httpClient,host:" << HOST_NAME << ",port:" << PORT << ",action:" << "Get" << endl;
	if (res) {
		cout << "httpClient, resp:" << endl;
		cout << "status:" << res->status << endl;
		cout << "Content-Type:" << res->get_header_value("Content-Type") << endl;
		cout << "body:" << res->body << endl;
	} else {
		cout << "httpClient get error..." << endl;
	}
}

int main(void) {
	std::thread t = std::thread(std::bind(httpServer, std::placeholders::_1), CONTENT);
	t.detach();
	Sleep(1);
	cout << "----------------------------------------------------" << endl;
	httpClient();

	return 0;
}