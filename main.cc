#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <lexer.hh>
#include <sys/stat.h>
#include <unistd.h>

static inline void usage()
{
    std::cout << "usage: <program> <filepath>" << std::endl;
    std::exit(1);
}

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

int main(int argc, const char **argv)
{
    if (argc < 2)
        usage();

    Lexer lexer = Lexer();
    lexer.feed(load_source_code(argv[1]));

    Token token;
    do {
        token = lexer.run();
        std::cout << token.to_string() << std::endl;
    } while (token.kind != Token::Kind::Eof &&
             token.kind != Token::Kind::Unknown);

    return 0;
}
