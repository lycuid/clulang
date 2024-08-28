#include <clulang/lexer.hh>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>

std::string load_source_code(const char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    if (fd < 0)
        std::cerr << "Couldn't open file: '" << filepath << "'" << std::endl;

    struct stat st;
    if (fstat(fd, &st) != 0)
        std::cerr << "Couldn't query file: '" << filepath << "'" << std::endl;

    char *buffer = new char[st.st_size + 2];
    std::memset(buffer, 0, st.st_size + 2);
    read(fd, buffer, st.st_size);

    close(fd);

    return buffer;
}

int main(void)
{
    Lexer lexer;
    lexer.feed(load_source_code("code.scm"));

    Token token;
    do {
        token = lexer.next();
        std::cout << token.to_string() << std::endl;
    } while (token.kind != Token::Kind::Eof);

    return 0;
}
