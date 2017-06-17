#include <map>
#include <stack>
#include <string>
#include <iostream>

#include <stdio.h>

class bf_interpret
{
public:
    bf_interpret(const char *prog)
    {
        bf_program = std::string(prog);
        data_ptr = 0;
    }

    ~bf_interpret() {};

    void run()
    {
        for (unsigned int cnt = 0; cnt < bf_program.length(); cnt++)
        {
            switch (bf_program[cnt])
            {
            case '+':
                data_cell[data_ptr]++;
                break;
            case '-':
                data_cell[data_ptr]--;
                break;
            case '>':
                data_ptr++;
                break;
            case '<':
                data_ptr--;
                break;
            case '[':
                stack.push(cnt);
                break;
            case ']':
                if (data_cell[data_ptr] != 0)
                {
                    //check if brackets are matching
                    if (stack.empty())
                    {
                        std::cout << "error: brackets mismatch (pos: " << cnt << ")" << std::endl;
                        break;
                    }
                    cnt = stack.top();
                }
                else
                    stack.pop();
                break;
            case '.':
                putchar(data_cell[data_ptr]);
                break;
            case ',':
                data_cell[data_ptr] = getchar();
                break;
            default:
                std::cout << "warning: alien instruction (pos " << (cnt + 1) << ")" << std::endl;
            }
        }

        if (!stack.empty())
            std::cout << "error: brackets mismatch (end of the tape)" << std::endl;
    }

private:
    std::stack<int> stack;
    std::map<int, char> data_cell;
    std::string bf_program;
    int data_ptr;
};

/*

++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.

*/
int main(int argc, char **argv)
{
    bf_interpret bf(argv[1]);
    bf.run();

    return 0;
}
