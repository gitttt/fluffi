/*
Copyright 2017-2019 Siemens AG

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Author(s): Thomas Riedmaier
*/

#include <chrono>
#include <thread>
#include <string>
#include <stdio.h>

//g++ -std=c++11 DebuggerTester.cpp -o DebuggerTester

int main(int argc, char* argv[])
{
	printf("hello world from debugger tester\n");
	if (argc < 2) {
		return -1;
	}

	int whattoDo = std::stoi(argv[1]);

	switch (whattoDo)
	{
		case 0: //do nothing
			printf("option 0: do nothing\n");
			break;
		case 1: //access violation
			{
				printf("option 1: pre exception\n");
				int * test = (int *)0x12345678;
				*test = 0x11223344;
				printf("option 1: post exception\n");
			}
			break;
		case 2: //div by zero
			{
				printf("option 2: pre exception\n");
				int a = 0;
				int b = 1 / a;
				*(int*)b = 0x182;
				printf("option 2: post exception\n");
			}
			break;
		case 3: //hang
			printf("option 3: do pre sleep\n");
			fflush(stdout);
			for(int i=0; i<10; i++){
				printf("option 3: sleeping\n");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			printf("option 3: do post sleep\n");
			fflush(stdout);
			break;

		default:
			break;
	}

	return 0;
}
