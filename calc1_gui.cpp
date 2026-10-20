// Windows: g++ -std=c++17 -O2 -static -mwindows calc1_gui.cpp -o calc1_exam.exe -lws2_32 -lshell32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include <shellapi.h>
#include <fstream>
#define main terminal_main
#include "calc1_practice.cpp"
#undef main
#include "exam_bank.h"

std::string json(const std::string& value) {
    std::string out = "\"";
    for (unsigned char c : value) {
        if (c == '"' || c == '\\') { out += '\\'; out += c; }
        else if (c == '\n') out += "\\n";
        else if (c == '\r') out += "\\r";
        else if (c == '\t') out += "\\t";
        else if (c >= 32) out += c;
    }
    return out + "\"";
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    WSADATA data;
    if (WSAStartup(MAKEWORD(2,2), &data)) return 1;
    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = 0;
    if (server == INVALID_SOCKET || bind(server, reinterpret_cast<sockaddr*>(&address), sizeof(address)) || listen(server, 8)) {
        MessageBoxA(nullptr, "Unable to start the local practice app.", "Calculus practice", MB_ICONERROR);
        WSACleanup(); return 1;
    }
    int size = sizeof(address);
    getsockname(server, reinterpret_cast<sockaddr*>(&address), &size);
    char path[MAX_PATH]; GetModuleFileNameA(nullptr, path, MAX_PATH);
    std::string file(path);
    file = file.substr(0, file.find_last_of("\\/")) + "\\exam_gui.html";
    std::ifstream input(file, std::ios::binary);
    std::string html((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    if (html.empty()) {
        MessageBoxA(nullptr, "Keep exam_gui.html beside calc1_exam.exe.", "Missing interface", MB_ICONERROR);
        closesocket(server); WSACleanup(); return 1;
    }
    // An unpredictable path prevents unrelated pages from using this app's endpoints.
    std::string token = s(pick(100000000,999999999)) + s(pick(100000000,999999999));
    std::string root = "/" + token + "/";
    std::string url = "http://127.0.0.1:" + s(ntohs(address.sin_port)) + root;
    if (reinterpret_cast<INT_PTR>(ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL)) <= 32) {
        MessageBoxA(nullptr, "Unable to open your default browser.", "Calculus practice", MB_ICONERROR);
        closesocket(server); WSACleanup(); return 1;
    }
    bool running = true;
    int previousTopic=0, previousLevel=0;
    std::string previousProblem;
    while (running) {
        SOCKET client = accept(server, nullptr, nullptr);
        if (client == INVALID_SOCKET) break;
        DWORD timeout = 3000;
        setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&timeout), sizeof(timeout));
        char buffer[8192];
        int length = recv(client, buffer, sizeof(buffer), 0);
        std::string request = length > 0 ? std::string(buffer, length) : "";
        std::istringstream first(request);
        std::string method, target; first >> method >> target;
        std::string body, type = "text/plain; charset=utf-8", status = "200 OK";
        if (method == "GET" && target == root) { body = html; type = "text/html; charset=utf-8"; }
        else if (method == "GET" && target.rfind(root + "problem?topic=", 0) == 0) {
            int topic = -1, level=0;
            std::istringstream number(target.substr((root + "problem?topic=").size()));
            number >> topic;
            auto difficulty=target.find("&level=");
            if(difficulty!=std::string::npos) {
                std::istringstream value(target.substr(difficulty+7));value>>level;
            }
            if (topic < 0 || topic > 20 || level<0 || level>2) { status = "400 Bad Request"; body = "Invalid topic or difficulty"; }
            else {
                if (!topic) {
                    do { topic=pick(1,20); } while(topic==previousTopic);
                }
                if(!level) level=topic==previousTopic?3-previousLevel:pick(1,2);
                ExamProblem p;
                for(int attempt=0;attempt<30;++attempt) {
                    p=examProblem(topic,level);
                    if(p.math+p.prompt!=previousProblem)break;
                }
                previousTopic=topic;previousLevel=level;previousProblem=p.math+p.prompt;
                body = "{\"topic\":" + s(topic) + ",\"level\":"+s(level)+",\"id\":"+json(p.id)+",\"label\":" + json(examTopics[topic])
                    + ",\"prompt\":" + json(p.prompt) + ",\"math\":" + json(p.math) + ",\"answer\":" + json(p.answer)
                    + ",\"conclusion\":"+json(p.conclusion)+",\"check\":"+json(p.check)+",\"steps\":[";
                for (std::size_t i=0; i<p.steps.size(); ++i) {
                    if (i) body += ",";
                    const auto& step=p.steps[i];
                    body+="{\"title\":"+json(step.title)+",\"why\":"+json(step.why)+",\"math\":"+json(step.math)+",\"tip\":"+json(step.tip)+"}";
                }
                body += "]}";
                type = "application/json";
            }
        } else if (method == "POST" && target == root + "quit") { body = "Closed"; running = false; }
        else { status = "404 Not Found"; body = "Not found"; }
        std::string response = "HTTP/1.1 " + status + "\r\nContent-Type: " + type + "\r\nContent-Length: " + s(static_cast<int>(body.size())) + "\r\nCache-Control: no-store\r\nX-Content-Type-Options: nosniff\r\nConnection: close\r\n\r\n" + body;
        std::size_t sent = 0;
        while (sent < response.size()) {
            int result = send(client, response.data()+sent, static_cast<int>(response.size()-sent), 0);
            if (result <= 0) break;
            sent += result;
        }
        closesocket(client);
    }
    closesocket(server); WSACleanup(); return 0;
}
